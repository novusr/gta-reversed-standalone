#include "StdInc.h"

#include <cerrno>
#include <cstring>
#include <cctype>
#include <unordered_map>
#include <mutex>
#include <vector>
#include <filesystem>

#ifdef _WIN32
#include <direct.h>
#include "winincl.h"
#include <ShlObj.h>
#else
#include <unistd.h>
#define _chdir chdir
#define _getcwd getcwd
#endif

#include "FileMgr.h"

#include "extensions/Configs/Miscellaneous.hpp"

auto& user_tracks_dir_path = StaticRef<char[256]>(0xc92168);
auto& user_gallery_dir_path = StaticRef<char[256]>(0xc92268);
auto& gta_user_dir_path = StaticRef<char[256]>(0xc92368);

constexpr size_t PATH_SIZE = 256;

static std::mutex s_VfsMutex;
static std::unordered_map<std::string, std::string> s_PathCache;
static std::unordered_map<std::string, std::vector<std::string>> s_DirCache;

std::string CFileMgr::NormalizePath(std::string_view path) {
    if (path.empty()) {
        return {};
    }

    // Trim leading/trailing whitespace and quotes
    size_t start = 0;
    while (start < path.size() && (path[start] == ' ' || path[start] == '\t' || path[start] == '\r' || path[start] == '\n' || path[start] == '"')) {
        start++;
    }
    size_t end = path.size();
    while (end > start && (path[end - 1] == ' ' || path[end - 1] == '\t' || path[end - 1] == '\r' || path[end - 1] == '\n' || path[end - 1] == '"')) {
        end--;
    }
    if (start >= end) {
        return {};
    }

    std::string out;
    out.reserve(end - start);

    for (size_t i = start; i < end; ++i) {
        char c = path[i];
        if (c == '\\') {
            c = '/';
        }
        // Collapse consecutive slashes
        if (c == '/' && !out.empty() && out.back() == '/') {
            continue;
        }
        out.push_back(c);
    }

    // Strip leading "./" if it has characters after (e.g., "./data/gta.dat" -> "data/gta.dat")
    if (out.size() >= 2 && out[0] == '.' && out[1] == '/') {
        if (out.size() > 2) {
            out.erase(0, 2);
        }
    }

    // Remove redundant "/./" in path
    size_t dotSlashPos = 0;
    while ((dotSlashPos = out.find("/./", dotSlashPos)) != std::string::npos) {
        out.erase(dotSlashPos, 2);
    }

    return out;
}

void CFileMgr::ClearPathCache() {
    std::scoped_lock lock(s_VfsMutex);
    s_PathCache.clear();
    s_DirCache.clear();
}

std::string CFileMgr::ResolvePath(std::string_view path) {
    if (path.empty()) {
        return {};
    }

    std::string normalized = NormalizePath(path);
    if (normalized.empty()) {
        return {};
    }

    {
        std::scoped_lock lock(s_VfsMutex);
        auto it = s_PathCache.find(normalized);
        if (it != s_PathCache.end()) {
            return it->second;
        }
    }

    std::error_code ec;
    // Fast path: if the path already exists directly as written on disk
    if (fs::exists(normalized, ec)) {
        std::scoped_lock lock(s_VfsMutex);
        s_PathCache[normalized] = normalized;
        return normalized;
    }

    // If path does not exist directly, perform case-insensitive directory resolution
    // Split into path segments
    std::string current;
    size_t idx = 0;

    // Check for root prefix:
    // 1. Unix absolute root: "/"
    // 2. Windows drive root: "C:/"
    if (normalized[0] == '/') {
        current = "/";
        idx = 1;
    } else if (normalized.size() >= 3 && std::isalpha(static_cast<unsigned char>(normalized[0])) && normalized[1] == ':' && normalized[2] == '/') {
        current = normalized.substr(0, 3);
        idx = 3;
    } else {
        current = ".";
    }

    auto stringEqualsCaseInsensitive = [](std::string_view a, std::string_view b) {
        if (a.size() != b.size()) return false;
        for (size_t i = 0; i < a.size(); ++i) {
            if (std::tolower(static_cast<unsigned char>(a[i])) !=
                std::tolower(static_cast<unsigned char>(b[i]))) {
                return false;
            }
        }
        return true;
    };

    bool resolutionFailed = false;

    while (idx < normalized.size()) {
        size_t nextSlash = normalized.find('/', idx);
        std::string segment;
        if (nextSlash == std::string::npos) {
            segment = normalized.substr(idx);
            idx = normalized.size();
        } else {
            segment = normalized.substr(idx, nextSlash - idx);
            idx = nextSlash + 1;
        }

        if (segment.empty() || segment == ".") {
            continue;
        }
        if (segment == "..") {
            if (current != "." && current != "/") {
                current = (fs::path(current) / "..").lexically_normal().string();
            } else {
                current = (current == ".") ? ".." : "/";
            }
            continue;
        }

        if (resolutionFailed) {
            // Already failed on a parent directory; just append remaining segments
            if (current == "." || current.empty()) {
                current = segment;
            } else if (current == "/" || current.back() == '/') {
                current += segment;
            } else {
                current += "/" + segment;
            }
            continue;
        }

        // Query directory cache or read directory entries
        const std::vector<std::string>* dirEntries = nullptr;
        {
            std::scoped_lock lock(s_VfsMutex);
            auto dirIt = s_DirCache.find(current);
            if (dirIt != s_DirCache.end()) {
                dirEntries = &dirIt->second;
            } else {
                std::vector<std::string> entries;
                std::error_code dirEc;
                for (const auto& entry : fs::directory_iterator(current, fs::directory_options::skip_permission_denied, dirEc)) {
                    entries.push_back(entry.path().filename().string());
                }
                auto [newIt, _] = s_DirCache.emplace(current, std::move(entries));
                dirEntries = &newIt->second;
            }
        }

        // Search in directory entries: prioritize exact match first, then case-insensitive
        const std::string* matched = nullptr;
        for (const auto& entry : *dirEntries) {
            if (entry == segment) {
                matched = &entry;
                break;
            }
            if (!matched && stringEqualsCaseInsensitive(entry, segment)) {
                matched = &entry;
            }
        }

        if (matched) {
            if (current == "." || current.empty()) {
                current = *matched;
            } else if (current == "/" || current.back() == '/') {
                current += *matched;
            } else {
                current += "/" + *matched;
            }
        } else {
            // No match found in this directory
            resolutionFailed = true;
            if (current == "." || current.empty()) {
                current = segment;
            } else if (current == "/" || current.back() == '/') {
                current += segment;
            } else {
                current += "/" + segment;
            }
        }
    }

    // Normalize output format (remove leading "./" if relative)
    if (current.size() >= 2 && current[0] == '.' && current[1] == '/') {
        if (current.size() > 2) {
            current.erase(0, 2);
        }
    }

    {
        std::scoped_lock lock(s_VfsMutex);
        s_PathCache[normalized] = current;
    }

    return current;
}

inline void createDirectory(const wchar_t* path)
{
#ifdef _WIN32
    HANDLE folderHandle = CreateFileW(
        path,
        GENERIC_READ,
        FILE_SHARE_READ,
        nullptr,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS | FILE_ATTRIBUTE_NORMAL,
        nullptr
    );
    if (folderHandle == INVALID_HANDLE_VALUE)
        CreateDirectoryW(path, nullptr);
    else
        CloseHandle(folderHandle);
#else
    std::string pathUtf8 = UnicodeToUTF8(path);
    std::error_code ec;
    fs::create_directories(pathUtf8, ec);
#endif
}

// 0x744FB0
char* InitUserDirectories()
{
    if (gta_user_dir_path[0] != '\0')
        return gta_user_dir_path;

    // NOTSA(MikuAuahDark): Let's improve the function to use wide char
    static std::array<wchar_t, MAX_PATH> gtaUserDirWide;
    static std::array<wchar_t, MAX_PATH> userGalleryDirWide;
    static std::array<wchar_t, MAX_PATH> userTracksDirWide;
    constexpr const wchar_t*             GALLERY    = L".\\Gallery";
    constexpr const wchar_t*             USERTRACKS = L".\\User Tracks";

    if (g_MiscConfig.SaveDirectoryPath.has_value()) {
        const auto absolutePath = fs::absolute(fs::path(*g_MiscConfig.SaveDirectoryPath));
        wcscpy_s(gtaUserDirWide.data(), gtaUserDirWide.size(), UTF8ToUnicode(absolutePath.string()).c_str());
    } else {
#ifdef _WIN32
        if (SHGetFolderPathW(nullptr, CSIDL_PERSONAL, nullptr, SHGFP_TYPE_CURRENT, gtaUserDirWide.data()) != S_OK) {
            strcpy_s(gta_user_dir_path, std::size("data"), "data"); // 2nd param is required or game won't be able to find files!
            return gta_user_dir_path;
        }

        constexpr const wchar_t* USERFILES = L"\\GTA San Andreas User Files";
        // Base GTASA User Files
        if ((wcslen(gtaUserDirWide.data()) + wcslen(USERFILES)) >= MAX_PATH) {
            wcscpy_s(gtaUserDirWide.data(), gtaUserDirWide.size(), L".");
        } else {
            wcscat_s(gtaUserDirWide.data(), gtaUserDirWide.size(), USERFILES);
        }
#else
        const char* home = getenv("HOME");
        std::string userFiles = (home && *home) ? (std::string(home) + "/.config/gta-sa") : "./user_files";
        std::wstring userFilesWide = UTF8ToUnicode(userFiles);
        wcscpy_s(gtaUserDirWide.data(), gtaUserDirWide.size(), userFilesWide.c_str());
#endif
    }
    createDirectory(gtaUserDirWide.data());

    size_t userDirLen = wcslen(gtaUserDirWide.data());
    wcscpy_s(userGalleryDirWide.data(), userGalleryDirWide.size(), gtaUserDirWide.data());
    wcscpy_s(userTracksDirWide.data(), userTracksDirWide.size(), gtaUserDirWide.data());

    // Gallery
    if ((userDirLen + wcslen(GALLERY + 1)) >= PATH_SIZE)
        wcscpy_s(userGalleryDirWide.data(), userGalleryDirWide.size(), GALLERY);
    else
        wcscat_s(userGalleryDirWide.data(), userGalleryDirWide.size(), GALLERY + 1);
    createDirectory(userGalleryDirWide.data());

    // User Tracks
    if ((userDirLen + wcslen(USERTRACKS + 1)) >= PATH_SIZE)
        wcscpy_s(userTracksDirWide.data(), userTracksDirWide.size(), USERTRACKS);
    else
        wcscat_s(userTracksDirWide.data(), userTracksDirWide.size(), USERTRACKS + 1);
    createDirectory(userTracksDirWide.data());

    std::string temp = UnicodeToUTF8(gtaUserDirWide.data());
    if (temp.length() >= PATH_SIZE)
        strcpy_s(gta_user_dir_path, ".");
    else
        strcpy_s(gta_user_dir_path, temp.c_str());

    temp = UnicodeToUTF8(userGalleryDirWide.data());
    if (temp.length() >= PATH_SIZE)
        strcpy_s(user_gallery_dir_path, ".\\Gallery");
    else
        strcpy_s(user_gallery_dir_path, temp.c_str());

    temp = UnicodeToUTF8(userTracksDirWide.data());
    if (temp.length() >= PATH_SIZE)
        strcpy_s(user_tracks_dir_path, ".\\User Tracks");
    else
        strcpy_s(user_tracks_dir_path, temp.c_str());

    return gta_user_dir_path;
}

// 0x5386f0
void CFileMgr::Initialise()
{
    memset(ms_rootDirName, 0, DIRNAMELENGTH);

#ifdef _WIN32
    if (WindowsCharset != CP_UTF8)
    {
        // MikuAuahDark: Improve the function to use wide char
        wchar_t rootDirTemp[DIRNAMELENGTH];
        VERIFY(_wgetcwd(rootDirTemp, DIRNAMELENGTH));

        // Just in case
        if (errno == ERANGE)
            VERIFY(_getcwd(ms_rootDirName, DIRNAMELENGTH));
        else
        {
            std::string rootDirUTF8 = UnicodeToUTF8(rootDirTemp);
            if (rootDirUTF8.length() >= (DIRNAMELENGTH - 2))
                VERIFY(_getcwd(ms_rootDirName, DIRNAMELENGTH));
            else
                strcpy_s(ms_rootDirName, rootDirUTF8.size() + 1, rootDirUTF8.c_str());
        }
    }
    else
        VERIFY(_getcwd(ms_rootDirName, DIRNAMELENGTH));
#else
    VERIFY(getcwd(ms_rootDirName, DIRNAMELENGTH));
#endif

    const size_t len = strlen(ms_rootDirName);
    if (len > 0 && ms_rootDirName[len - 1] != '/' && ms_rootDirName[len - 1] != '\\') {
        ms_rootDirName[len] = '/';
        ms_rootDirName[len + 1] = '\0';
    }
}

// 0x538730
int32 CFileMgr::ChangeDir(const char *path)
{
    memset(ms_dirName, 0, DIRNAMELENGTH);

    if (*path == '\\' || *path == '/')
    {
        memcpy(ms_dirName, ms_rootDirName, strlen(ms_rootDirName));
        path++;
    }

    if (*path)
    {
        if ((strlen(ms_dirName) + strlen(path) + 1) > DIRNAMELENGTH)
        {
            errno = EINVAL;
            return -1;
        }
        strcat_s(ms_dirName, path);

        char *lastPos = strchr(ms_dirName, 0) - 1;
        if (*lastPos != '\\' && *lastPos != '/')
            lastPos[1] = '/';
    }

    std::string resolved = ResolvePath(ms_dirName);
    strncpy_s(ms_dirName, resolved.c_str(), DIRNAMELENGTH - 1);

    int32 r;
#ifdef _WIN32
    if (WindowsCharset != CP_UTF8)
    {
        std::wstring pathWide = UTF8ToUnicode(ms_dirName);
        r = _wchdir(pathWide.c_str());
    }
    else
        r = _chdir(ms_dirName);
#else
    r = chdir(ms_dirName);
#endif

    return r;
}

// 0x5387D0
int32 CFileMgr::SetDir(const char *path)
{
    memset(ms_dirName, 0, DIRNAMELENGTH);
    memcpy(ms_dirName, ms_rootDirName, strlen(ms_rootDirName));

    if (*path)
    {
        const auto destSizeAfterConcat = strlen(ms_dirName) + strlen(path) + 2;
        if (destSizeAfterConcat > DIRNAMELENGTH)
        {
            errno = EINVAL;
            return -1;
        }
        strcat_s(ms_dirName, destSizeAfterConcat, path);

        char *lastPos = strchr(ms_dirName, 0) - 1;
        if (*lastPos != '\\' && *lastPos != '/')
            lastPos[1] = '/';
    }

    std::string resolved = ResolvePath(ms_dirName);
    strncpy_s(ms_dirName, resolved.c_str(), DIRNAMELENGTH - 1);

    int32 r;
#ifdef _WIN32
    if (WindowsCharset != CP_UTF8)
    {
        std::wstring pathWide = UTF8ToUnicode(ms_dirName);
        r = _wchdir(pathWide.c_str());
    }
    else
        r = _chdir(ms_dirName);
#else
    r = chdir(ms_dirName);
#endif

    return r;
}

// 0x538860
int32 CFileMgr::SetDirMyDocuments()
{
    char *userDir = InitUserDirectories();
    if (strlen(userDir) >= DIRNAMELENGTH)
    {
        errno = ENOMEM;
        return -1;
    }

    strcpy_s(ms_dirName, userDir);

    int32 r;
#ifdef _WIN32
    if (WindowsCharset != CP_UTF8)
    {
        std::wstring pathWide = UTF8ToUnicode(ms_dirName);
        r = _wchdir(pathWide.c_str());
    }
    else
        r = _chdir(ms_dirName);
#else
    r = chdir(ms_dirName);
#endif

    return r;
}

// 0x538890
size_t CFileMgr::LoadFile(const char *path, uint8 *buf, size_t size, const char *mode)
{
    FILESTREAM f = CFileMgr::OpenFile(path, mode);
    if (f == nullptr)
        return -1;

    // MikuAuahDark: The original implementation actually ignore
    // "size" parameter and adds NUL terminator at the end of the
    // buffer, but that behavior causes buffer overflow
    size_t readed = fread(buf, 1, size, f);
    fclose(f);

    return readed;
}

// 0x538900
FILESTREAM CFileMgr::OpenFile(const char *path, const char *mode) {
    ZoneScoped;

    if (!path || !mode) {
        return nullptr;
    }

    std::string resolved = ResolvePath(path);
    FILESTREAM fs{nullptr};
#ifdef _WIN32
    if (WindowsCharset != CP_UTF8) {
        // MikuAuahDark: Let's improve it to allow opening non-ANSI names
        // Convert to wide char
        std::wstring pathWide = UTF8ToUnicode(resolved.c_str());
        std::wstring modeWide = UTF8ToUnicode(mode);
        _wfopen_s(&fs, pathWide.c_str(), modeWide.c_str());
        return fs;
    }
#endif
    fs = fopen(resolved.c_str(), mode);
    return fs;
}

// 0x538910
FILESTREAM CFileMgr::OpenFileForWriting(const char *path)
{
    return CFileMgr::OpenFile(path, "wb");
}

// 0x538930
FILESTREAM CFileMgr::OpenFileForAppending(const char *path)
{
    return CFileMgr::OpenFile(path, "a");
}

// 0x538950
size_t CFileMgr::Read(FILESTREAM file, void *buf, size_t size)
{
    return fread(buf, 1, size, file);
}

// 0x538970
size_t CFileMgr::Write(FILESTREAM file, const void *buf, size_t size)
{
    return fwrite(buf, 1, size, file);
}

// 0x538990
bool CFileMgr::Seek(FILESTREAM file, long offset, int32 origin)
{
    // MikuAuahDark: Pretty sure it shouldn't be ret != 0
    return fseek(file, offset, origin) != 0;
}

// 0x5389b0
bool CFileMgr::ReadLine(FILESTREAM file, char *str, int32 num)
{
    return fgets(str, num, file) != nullptr;
}

// 0x5389d0
int32 CFileMgr::CloseFile(FILESTREAM file)
{
    return fclose(file);
}

// 0x5389e0
int32 CFileMgr::GetTotalSize(FILESTREAM file)
{
    int32 currentPos, size;
    // MikuAuahDark: The actual implementation uses RwOsGetFileInterface
    // but for sake of portability, default stdio functions is used.
    /*
    RwFileFunctions *functions = RwOsGetFileInterface();

    currentPos = functions->rwftell(file);
    functions->rwfseek(file, 0, SEEK_END);
    size = functions->rwftell(file);
    functions->rwfseek(file, currentPos, SEEK_SET);

    return size;
    */
    currentPos = ftell(file);
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, currentPos, SEEK_SET);

    return size;
}

// 0x538a20
int32 CFileMgr::Tell(FILESTREAM file)
{
    /*
    RwFileFunctions *functions = RwOsGetFileInterface();
    return functions->rwftell(file);
    */
    return ftell(file);
}

// 0x538a50
bool CFileMgr::GetErrorReadWrite(FILESTREAM file)
{
    return (bool) ferror(file);
}

// notsa
void CFileMgr::SeekNextLine(FILESTREAM file) {
    while (!feof(file) && fgetc(file) != '\n');
}

void CFileMgr::InjectHooks()
{
    RH_ScopedClass(CFileMgr);
    RH_ScopedCategoryGlobal();

    // File related functions locked to prevent crashes

    RH_ScopedInstall(Initialise, 0x5386f0);
    RH_ScopedInstall(ChangeDir, 0x538730);
    RH_ScopedInstall(SetDir, 0x5387D0);
    RH_ScopedInstall(SetDirMyDocuments, 0x538860, { .Locked = true });
    RH_ScopedInstall(LoadFile, 0x538890, { .Locked = true });
    RH_ScopedInstall(OpenFile, 0x538900, { .Locked = true });
    RH_ScopedInstall(OpenFileForWriting, 0x538910, { .Locked = true });
    RH_ScopedInstall(OpenFileForAppending, 0x538930, { .Locked = true });
    RH_ScopedInstall(Read, 0x538950, { .Locked = true });
    RH_ScopedInstall(Write, 0x538970, { .Locked = true });
    RH_ScopedInstall(Seek, 0x538990, { .Locked = true });
    RH_ScopedInstall(ReadLine, 0x5389b0, { .Locked = true });
    RH_ScopedInstall(CloseFile, 0x5389d0, { .Locked = true });
    RH_ScopedInstall(GetTotalSize, 0x5389e0, { .Locked = true });
    RH_ScopedInstall(Tell, 0x538a20, { .Locked = true });
    RH_ScopedInstall(GetErrorReadWrite, 0x538a50, { .Locked = true });
    RH_ScopedGlobalInstall(InitUserDirectories, 0x744fb0);
}
