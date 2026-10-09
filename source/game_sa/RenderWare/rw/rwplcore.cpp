#ifndef NOTSA_STANDALONE_NATIVE
#include "StdInc.h"
#else
#include <cstdlib>
#include <cstring>
#include "Base.h"
#include "RenderWare/RenderWare.h"
#endif

#include "rwplcore.h"
#ifdef NOTSA_STANDALONE_NATIVE
#include "RenderWare/RwBridge.h"
#endif

RwMemoryFunctions* RwOsGetMemoryInterface() {
#ifdef NOTSA_STANDALONE_NATIVE
    return (RwMemoryFunctions*)&rw::Engine::memfuncs;
#else
    return ((RwMemoryFunctions*(__cdecl *)(void))0x802230)();
#endif
}

RwFreeList* _rwFreeListCreate(RwInt32 entrySize, RwInt32 entriesPerBlock, RwInt32 alignment, RwUInt32 hint, const RwChar* fileCreate, RwUInt32 lineCreate) {
#ifdef NOTSA_STANDALONE_NATIVE
    return reinterpret_cast<RwFreeList*>(std::malloc(entrySize > 0 ? entrySize : 64));
#else
    return ((RwFreeList*(__cdecl *)(RwInt32, RwInt32, RwInt32, RwUInt32, const RwChar*, RwUInt32))0x801980)(entrySize, entriesPerBlock, alignment, hint, fileCreate, lineCreate);
#endif
}

RwFreeList* RwFreeListCreateAndPreallocateSpace(RwInt32 entrySize, RwInt32 entriesPerBlock, RwInt32 alignment, RwInt32 numBlocksToPreallocate, RwFreeList* inPlaceSpaceForFreeListStruct, RwUInt32 hint) {
#ifdef NOTSA_STANDALONE_NATIVE
    return reinterpret_cast<RwFreeList*>(std::malloc(entrySize > 0 ? entrySize : 64));
#else
    return ((RwFreeList*(__cdecl *)(RwInt32, RwInt32, RwInt32, RwInt32, RwFreeList*, RwUInt32))0x801B70)(entrySize, entriesPerBlock, alignment, numBlocksToPreallocate, inPlaceSpaceForFreeListStruct, hint);
#endif
}

RwBool RwFreeListDestroy(RwFreeList* freelist) {
#ifdef NOTSA_STANDALONE_NATIVE
    std::free(freelist);
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwFreeList*))0x801B80)(freelist);
#endif
}

void RwFreeListSetFlags(RwFreeList* freeList, RwUInt32 flags) {
#ifdef NOTSA_STANDALONE_NATIVE
#else
    ((void(__cdecl *)(RwFreeList*, RwUInt32))0x801C10)(freeList, flags);
#endif
}

RwUInt32 RwFreeListGetFlags(RwFreeList* freeList) {
#ifdef NOTSA_STANDALONE_NATIVE
    return 0;
#else
    return ((RwUInt32(__cdecl *)(RwFreeList*))0x801C20)(freeList);
#endif
}

RwInt32 RwFreeListPurge(RwFreeList* freelist) {
#ifdef NOTSA_STANDALONE_NATIVE
    return 0;
#else
    return ((RwInt32(__cdecl *)(RwFreeList*))0x801E00)(freelist);
#endif
}

RwFreeList* RwFreeListForAllUsed(RwFreeList* freelist, RwFreeListCallBack fpCallBack, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    return freelist;
#else
    return ((RwFreeList*(__cdecl *)(RwFreeList*, RwFreeListCallBack, void*))0x801E90)(freelist, fpCallBack, data);
#endif
}

RwInt32 RwFreeListPurgeAllFreeLists() {
#ifdef NOTSA_STANDALONE_NATIVE
    return 0;
#else
    return ((RwInt32(__cdecl *)(void))0x801F90)();
#endif
}

void RwStreamSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
#ifdef NOTSA_STANDALONE_NATIVE
#else
    ((void(__cdecl *)(RwInt32, RwInt32))0x7EC760)(blockSize, numBlocksToPrealloc);
#endif
}

RwStream* _rwStreamInitialize(RwStream* stream, RwBool rwOwned, RwStreamType type, RwStreamAccessType accessType, const void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)stream;
    (void)rwOwned;
    return RwStreamOpen(type, accessType, data);
#else
    return ((RwStream*(__cdecl *)(RwStream*, RwBool, RwStreamType, RwStreamAccessType, const void*))0x7EC810)(stream, rwOwned, type, accessType, data);
#endif
}

RwStream* RwStreamOpen(RwStreamType type, RwStreamAccessType accessType, const void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (type == rwSTREAMMEMORY) {
        auto* memStream = new rw::StreamMemory();
        const auto* mem = static_cast<const RwMemory*>(data);
        if (mem && mem->start && mem->length > 0) {
            memStream->open(mem->start, (accessType == rwSTREAMWRITE) ? 0 : mem->length, mem->length);
        } else {
            memStream->open(const_cast<rw::uint8*>(reinterpret_cast<const rw::uint8*>(data)), 0, 65536);
        }
        return reinterpret_cast<RwStream*>(memStream);
    } else if (type == rwSTREAMFILENAME) {
        auto* fileStream = new rw::StreamFile();
        const char* mode = (accessType == rwSTREAMREAD) ? "rb" : "wb";
        fileStream->open(static_cast<const char*>(data), mode);
        return reinterpret_cast<RwStream*>(fileStream);
    }
    return nullptr;
#else
    return ((RwStream*(__cdecl *)(RwStreamType, RwStreamAccessType, const void*))0x7ECEF0)(type, accessType, data);
#endif
}

RwBool RwStreamClose(RwStream* stream, void* data) {
#ifdef NOTSA_STANDALONE_NATIVE
    (void)data;
    if (stream) {
        auto* s = reinterpret_cast<rw::Stream*>(stream);
        s->close();
        delete s;
        return TRUE;
    }
    return FALSE;
#else
    return ((RwBool(__cdecl *)(RwStream*, void*))0x7ECE20)(stream, data);
#endif
}

RwUInt32 RwStreamRead(RwStream* stream, void* buffer, RwUInt32 length) {
#ifdef NOTSA_STANDALONE_NATIVE
    return stream ? reinterpret_cast<rw::Stream*>(stream)->read8(buffer, length) : 0;
#else
    return ((RwUInt32(__cdecl *)(RwStream*, void*, RwUInt32))0x7EC9D0)(stream, buffer, length);
#endif
}

RwStream* RwStreamWrite(RwStream* stream, const void* buffer, RwUInt32 length) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (stream) reinterpret_cast<rw::Stream*>(stream)->write8(buffer, length);
    return stream;
#else
    return ((RwStream*(__cdecl *)(RwStream*, const void*, RwUInt32))0x7ECB30)(stream, buffer, length);
#endif
}

RwStream* RwStreamSkip(RwStream* stream, RwUInt32 offset) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (stream) reinterpret_cast<rw::Stream*>(stream)->seek(offset, 1);
    return stream;
#else
    return ((RwStream*(__cdecl *)(RwStream*, RwUInt32))0x7ECD00)(stream, offset);
#endif
}

RwBool _rwStringOpen() {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(void))0x80A240)();
#endif
}

void _rwStringClose() {
#ifdef NOTSA_STANDALONE_NATIVE
#else
    ((void(__cdecl *)(void))0x80A440)();
#endif
}

RwBool _rwStringDestroy(RwChar* string) {
#ifdef NOTSA_STANDALONE_NATIVE
    std::free(string);
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwChar*))0x80A450)(string);
#endif
}

RwUInt32 _rwStringStreamGetSize(const RwChar* string) {
#ifdef NOTSA_STANDALONE_NATIVE
    return string ? static_cast<RwUInt32>(std::strlen(string) + 1) : 0;
#else
    return ((RwUInt32(__cdecl *)(const RwChar*))0x80A470)(string);
#endif
}

const RwChar* _rwStringStreamWrite(const RwChar* string, RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (string && stream) {
        auto len = static_cast<RwUInt32>(std::strlen(string) + 1);
        reinterpret_cast<rw::Stream*>(stream)->write8(string, len);
    }
    return string;
#else
    return ((const RwChar*(__cdecl *)(const RwChar*, RwStream*))0x80A4A0)(string, stream);
#endif
}

RwChar* _rwStringStreamFindAndRead(RwChar* string, RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    return string;
#else
    return ((RwChar*(__cdecl *)(RwChar*, RwStream*))0x80A510)(string, stream);
#endif
}

void RwPluginRegistrySetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
#ifdef NOTSA_STANDALONE_NATIVE
#else
    ((void(__cdecl *)(RwInt32, RwInt32))0x8087B0)(blockSize, numBlocksToPrealloc);
#endif
}

RwBool _rwPluginRegistrySetStaticPluginsSize(RwPluginRegistry* reg, RwInt32 size) {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwPluginRegistry*, RwInt32))0x808430)(reg, size);
#endif
}

RwInt32 _rwPluginRegistryAddPlugin(RwPluginRegistry* reg, RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return reg ? reinterpret_cast<rw::PluginList*>(reg)->registerPlugin(size, pluginID, (rw::Constructor)constructCB, (rw::Destructor)destructCB, (rw::CopyConstructor)copyCB) : -1;
#else
    return ((RwInt32(__cdecl *)(RwPluginRegistry*, RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x8084A0)(reg, size, pluginID, constructCB, destructCB, copyCB);
#endif
}

RwInt32 _rwPluginRegistryGetPluginOffset(const RwPluginRegistry* reg, RwUInt32 pluginID) {
#ifdef NOTSA_STANDALONE_NATIVE
    return reg ? const_cast<rw::PluginList*>(reinterpret_cast<const rw::PluginList*>(reg))->getPluginOffset(pluginID) : -1;
#else
    return ((RwInt32(__cdecl *)(const RwPluginRegistry*, RwUInt32))0x808470)(reg, pluginID);
#endif
}

const RwPluginRegistry* _rwPluginRegistryInitObject(const RwPluginRegistry* reg, void* object) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (reg && object) const_cast<rw::PluginList*>(reinterpret_cast<const rw::PluginList*>(reg))->construct(object);
    return reg;
#else
    return ((const RwPluginRegistry*(__cdecl *)(const RwPluginRegistry*, void*))0x8086E0)(reg, object);
#endif
}

const RwPluginRegistry* _rwPluginRegistryDeInitObject(const RwPluginRegistry* reg, void* object) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (reg && object) const_cast<rw::PluginList*>(reinterpret_cast<const rw::PluginList*>(reg))->destruct(object);
    return reg;
#else
    return ((const RwPluginRegistry*(__cdecl *)(const RwPluginRegistry*, void*))0x808740)(reg, object);
#endif
}

const RwPluginRegistry* _rwPluginRegistryCopyObject(const RwPluginRegistry* reg, void* dstObject, const void* srcObject) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (reg && dstObject && srcObject) const_cast<rw::PluginList*>(reinterpret_cast<const rw::PluginList*>(reg))->copy(dstObject, const_cast<void*>(srcObject));
    return reg;
#else
    return ((const RwPluginRegistry*(__cdecl *)(const RwPluginRegistry*, void*, const void*))0x808770)(reg, dstObject, srcObject);
#endif
}

RwInt32 _rwPluginRegistryAddPluginStream(RwPluginRegistry* reg, RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return reg ? reinterpret_cast<rw::PluginList*>(reg)->registerStream(pluginID, (rw::StreamRead)readCB, (rw::StreamWrite)writeCB, (rw::StreamGetSize)getSizeCB) : -1;
#else
    return ((RwInt32(__cdecl *)(RwPluginRegistry*, RwUInt32, RwPluginDataChunkReadCallBack, RwPluginDataChunkWriteCallBack, RwPluginDataChunkGetSizeCallBack))0x8088E0)(reg, pluginID, readCB, writeCB, getSizeCB);
#endif
}

RwInt32 _rwPluginRegistryAddPlgnStrmlwysCB(RwPluginRegistry* reg, RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return 0;
#else
    return ((RwInt32(__cdecl *)(RwPluginRegistry*, RwUInt32, RwPluginDataChunkAlwaysCallBack))0x808920)(reg, pluginID, alwaysCB);
#endif
}

RwInt32 _rwPluginRegistryAddPlgnStrmRightsCB(RwPluginRegistry* reg, RwUInt32 pluginID, RwPluginDataChunkRightsCallBack rightsCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return 0;
#else
    return ((RwInt32(__cdecl *)(RwPluginRegistry*, RwUInt32, RwPluginDataChunkRightsCallBack))0x808950)(reg, pluginID, rightsCB);
#endif
}

const RwPluginRegistry* _rwPluginRegistryReadDataChunks(const RwPluginRegistry* reg, RwStream* stream, void* object) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (reg && stream && object) const_cast<rw::PluginList*>(reinterpret_cast<const rw::PluginList*>(reg))->streamRead(reinterpret_cast<rw::Stream*>(stream), object);
    return reg;
#else
    return ((const RwPluginRegistry*(__cdecl *)(const RwPluginRegistry*, RwStream*, void*))0x808980)(reg, stream, object);
#endif
}

const RwPluginRegistry* _rwPluginRegistryWriteDataChunks(const RwPluginRegistry* reg, RwStream* stream, const void* object) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (reg && stream && object) const_cast<rw::PluginList*>(reinterpret_cast<const rw::PluginList*>(reg))->streamWrite(reinterpret_cast<rw::Stream*>(stream), const_cast<void*>(object));
    return reg;
#else
    return ((const RwPluginRegistry*(__cdecl *)(const RwPluginRegistry*, RwStream*, const void*))0x808B40)(reg, stream, object);
#endif
}

const RwPluginRegistry* _rwPluginRegistrySkipDataChunks(const RwPluginRegistry* reg, RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (reg && stream) const_cast<rw::PluginList*>(reinterpret_cast<const rw::PluginList*>(reg))->streamSkip(reinterpret_cast<rw::Stream*>(stream));
    return reg;
#else
    return ((const RwPluginRegistry*(__cdecl *)(const RwPluginRegistry*, RwStream*))0x808C10)(reg, stream);
#endif
}

RwInt32 _rwPluginRegistryGetSize(const RwPluginRegistry* reg, const void* object) {
#ifdef NOTSA_STANDALONE_NATIVE
    return reg && object ? const_cast<rw::PluginList*>(reinterpret_cast<const rw::PluginList*>(reg))->streamGetSize(const_cast<void*>(object)) : 0;
#else
    return ((RwInt32(__cdecl *)(const RwPluginRegistry*, const void*))0x808B00)(reg, object);
#endif
}

const RwPluginRegistry* _rwPluginRegistryInvokeRights(const RwPluginRegistry* reg, RwUInt32 id, void* obj, RwUInt32 extraData) {
#ifdef NOTSA_STANDALONE_NATIVE
    return reg;
#else
    return ((const RwPluginRegistry*(__cdecl *)(const RwPluginRegistry*, RwUInt32, void*, RwUInt32))0x808AB0)(reg, id, obj, extraData);
#endif
}

RwBool RwEngineGetMatrixTolerances(RwMatrixTolerance * const tolerance) {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwMatrixTolerance * const))0x7F1780)(tolerance);
#endif
}

RwBool RwEngineSetMatrixTolerances(const RwMatrixTolerance * const tolerance) {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(const RwMatrixTolerance*))0x7F17B0)(tolerance);
#endif
}

void RwMatrixSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
#ifdef NOTSA_STANDALONE_NATIVE
#else
    ((void(__cdecl *)(RwInt32, RwInt32))0x7F16A0)(blockSize, numBlocksToPrealloc);
#endif
}

RwBool RwMatrixDestroy(RwMatrix* mpMat) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (mpMat) reinterpret_cast<rw::Matrix*>(mpMat)->destroy();
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwMatrix*))0x7F2A20)(mpMat);
#endif
}

RwMatrix* RwMatrixCreate() {
#ifdef NOTSA_STANDALONE_NATIVE
    return (RwMatrix*)rw::Matrix::create();
#else
    return ((RwMatrix*(__cdecl *)(void))0x7F2A50)();
#endif
}

RwMatrix* RwMatrixMultiply(RwMatrix* matrixOut, const RwMatrix* MatrixIn1, const RwMatrix* matrixIn2) {
#ifdef NOTSA_STANDALONE_NATIVE
    return (RwMatrix*)rw::Matrix::mult(reinterpret_cast<rw::Matrix*>(matrixOut), reinterpret_cast<const rw::Matrix*>(MatrixIn1), reinterpret_cast<const rw::Matrix*>(matrixIn2));
#else
    return ((RwMatrix*(__cdecl *)(RwMatrix*, const RwMatrix*, const RwMatrix*))0x7F18B0)(matrixOut, MatrixIn1, matrixIn2);
#endif
}

RwMatrix* RwMatrixTransform(RwMatrix* matrix, const RwMatrix* transform, RwOpCombineType combineOp) {
#ifdef NOTSA_STANDALONE_NATIVE
    return (RwMatrix*)reinterpret_cast<rw::Matrix*>(matrix)->transform(reinterpret_cast<const rw::Matrix*>(transform), (rw::CombineOp)combineOp);
#else
    return ((RwMatrix*(__cdecl *)(RwMatrix*, const RwMatrix*, RwOpCombineType))0x7F25A0)(matrix, transform, combineOp);
#endif
}

RwMatrix* RwMatrixOrthoNormalize(RwMatrix* matrixOut, const RwMatrix* matrixIn) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (matrixOut != matrixIn) *matrixOut = *matrixIn;
    reinterpret_cast<rw::Matrix*>(matrixOut)->optimize();
    return matrixOut;
#else
    return ((RwMatrix*(__cdecl *)(RwMatrix*, const RwMatrix*))0x7F1920)(matrixOut, matrixIn);
#endif
}

RwMatrix* RwMatrixInvert(RwMatrix* matrixOut, const RwMatrix* matrixIn) {
#ifdef NOTSA_STANDALONE_NATIVE
    return (RwMatrix*)rw::Matrix::invert(reinterpret_cast<rw::Matrix*>(matrixOut), reinterpret_cast<const rw::Matrix*>(matrixIn));
#else
    return ((RwMatrix*(__cdecl *)(RwMatrix*, const RwMatrix*))0x7F2070)(matrixOut, matrixIn);
#endif
}

RwMatrix* RwMatrixScale(RwMatrix* matrix, const RwV3d* scale, RwOpCombineType combineOp) {
#ifdef NOTSA_STANDALONE_NATIVE
    return (RwMatrix*)reinterpret_cast<rw::Matrix*>(matrix)->scale(reinterpret_cast<const rw::V3d*>(scale), (rw::CombineOp)combineOp);
#else
    return ((RwMatrix*(__cdecl *)(RwMatrix*, const RwV3d*, RwOpCombineType))0x7F22C0)(matrix, scale, combineOp);
#endif
}

RwMatrix* RwMatrixTranslate(RwMatrix* matrix, const RwV3d* translation, RwOpCombineType combineOp) {
#ifdef NOTSA_STANDALONE_NATIVE
    return (RwMatrix*)reinterpret_cast<rw::Matrix*>(matrix)->translate(reinterpret_cast<const rw::V3d*>(translation), (rw::CombineOp)combineOp);
#else
    return ((RwMatrix*(__cdecl *)(RwMatrix*, const RwV3d*, RwOpCombineType))0x7F2450)(matrix, translation, combineOp);
#endif
}

RwMatrix* RwMatrixRotate(RwMatrix* matrix, const RwV3d* axis, RwReal angle, RwOpCombineType combineOp) {
#ifdef NOTSA_STANDALONE_NATIVE
    return (RwMatrix*)reinterpret_cast<rw::Matrix*>(matrix)->rotate(reinterpret_cast<const rw::V3d*>(axis), angle, (rw::CombineOp)combineOp);
#else
    return ((RwMatrix*(__cdecl *)(RwMatrix*, const RwV3d*, RwReal, RwOpCombineType))0x7F1FD0)(matrix, axis, angle, combineOp);
#endif
}

RwMatrix* RwMatrixRotateOneMinusCosineSine(RwMatrix* matrix, const RwV3d* unitAxis, RwReal oneMinusCosine, RwReal sine, RwOpCombineType combineOp) {
#ifdef NOTSA_STANDALONE_NATIVE
    return matrix;
#else
    return ((RwMatrix*(__cdecl *)(RwMatrix*, const RwV3d*, RwReal, RwReal, RwOpCombineType))0x7F1D00)(matrix, unitAxis, oneMinusCosine, sine, combineOp);
#endif
}

const RwMatrix* RwMatrixQueryRotate(const RwMatrix* matrix, RwV3d* unitAxis, RwReal* angle, RwV3d* center) {
#ifdef NOTSA_STANDALONE_NATIVE
    return matrix;
#else
    return ((const RwMatrix*(__cdecl *)(const RwMatrix*, RwV3d*, RwReal*, RwV3d*))0x7F2720)(matrix, unitAxis, angle, center);
#endif
}

RwMatrix* RwMatrixUpdate(RwMatrix* matrix) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (matrix) reinterpret_cast<rw::Matrix*>(matrix)->update();
    return matrix;
#else
    return ((RwMatrix*(__cdecl *)(RwMatrix*))0x7F18A0)(matrix);
#endif
}

RwMatrix* RwMatrixOptimize(RwMatrix* matrix, const RwMatrixTolerance* tolerance) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (matrix) reinterpret_cast<rw::Matrix*>(matrix)->optimize(reinterpret_cast<rw::Matrix::Tolerance*>(const_cast<RwMatrixTolerance*>(tolerance)));
    return matrix;
#else
    return ((RwMatrix*(__cdecl *)(RwMatrix*, const RwMatrixTolerance*))0x7F17E0)(matrix, tolerance);
#endif
}

RwReal _rwMatrixDeterminant(const RwMatrix* matrix) {
#ifdef NOTSA_STANDALONE_NATIVE
    return 1.0f;
#else
    return ((RwReal(__cdecl *)(const RwMatrix*))0x7F1450)(matrix);
#endif
}

RwReal _rwMatrixNormalError(const RwMatrix* matrix) {
#ifdef NOTSA_STANDALONE_NATIVE
    return 0.0f;
#else
    return ((RwReal(__cdecl *)(const RwMatrix*))0x7F1500)(matrix);
#endif
}

RwReal _rwMatrixOrthogonalError(const RwMatrix* matrix) {
#ifdef NOTSA_STANDALONE_NATIVE
    return 0.0f;
#else
    return ((RwReal(__cdecl *)(const RwMatrix*))0x7F14A0)(matrix);
#endif
}

RwReal _rwMatrixIdentityError(const RwMatrix* matrix) {
#ifdef NOTSA_STANDALONE_NATIVE
    return 0.0f;
#else
    return ((RwReal(__cdecl *)(const RwMatrix*))0x7F1590)(matrix);
#endif
}

RwReal RwV3dNormalize(RwV3d* out, const RwV3d* in) {
#ifdef NOTSA_STANDALONE_NATIVE
    float len = in ? rw::length(*reinterpret_cast<const rw::V3d*>(in)) : 0.0f;
    if (out && in) {
        if (len > 0.0f) *reinterpret_cast<rw::V3d*>(out) = rw::scale(*reinterpret_cast<const rw::V3d*>(in), 1.0f / len);
        else *out = *in;
    }
    return len;
#else
    return ((RwReal(__cdecl *)(RwV3d*, const RwV3d*))0x7ED9B0)(out, in);
#endif
}

RwReal RwV3dLength(const RwV3d* in) {
#ifdef NOTSA_STANDALONE_NATIVE
    return in ? rw::length(*reinterpret_cast<const rw::V3d*>(in)) : 0.0f;
#else
    return ((RwReal(__cdecl *)(const RwV3d*))0x7EDAC0)(in);
#endif
}

RwReal RwV2dLength(const RwV2d* in) {
#ifdef NOTSA_STANDALONE_NATIVE
    return in ? rw::length(*reinterpret_cast<const rw::V2d*>(in)) : 0.0f;
#else
    return ((RwReal(__cdecl *)(const RwV2d*))0x7EDBF0)(in);
#endif
}

RwReal RwV2dNormalize(RwV2d* out, const RwV2d* in) {
#ifdef NOTSA_STANDALONE_NATIVE
    float len = in ? rw::length(*reinterpret_cast<const rw::V2d*>(in)) : 0.0f;
    if (out && in) {
        if (len > 0.0f) *reinterpret_cast<rw::V2d*>(out) = rw::scale(*reinterpret_cast<const rw::V2d*>(in), 1.0f / len);
        else *out = *in;
    }
    return len;
#else
    return ((RwReal(__cdecl *)(RwV2d*, const RwV2d*))0x7EDC60)(out, in);
#endif
}

RwV3d* RwV3dTransformPoint(RwV3d* pointOut, const RwV3d* pointIn, const RwMatrix* matrix) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (pointOut && pointIn && matrix)
        rw::V3d::transformPoints(reinterpret_cast<rw::V3d*>(pointOut), reinterpret_cast<const rw::V3d*>(pointIn), 1, reinterpret_cast<const rw::Matrix*>(matrix));
    return pointOut;
#else
    return ((RwV3d*(__cdecl *)(RwV3d*, const RwV3d*, const RwMatrix*))0x7EDD60)(pointOut, pointIn, matrix);
#endif
}

RwV3d* RwV3dTransformPoints(RwV3d* pointsOut, const RwV3d* pointsIn, RwInt32 numPoints, const RwMatrix* matrix) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (pointsOut && pointsIn && matrix && numPoints > 0)
        rw::V3d::transformPoints(reinterpret_cast<rw::V3d*>(pointsOut), reinterpret_cast<const rw::V3d*>(pointsIn), numPoints, reinterpret_cast<const rw::Matrix*>(matrix));
    return pointsOut;
#else
    return ((RwV3d*(__cdecl *)(RwV3d*, const RwV3d*, RwInt32, const RwMatrix*))0x7EDD90)(pointsOut, pointsIn, numPoints, matrix);
#endif
}

RwV3d* RwV3dTransformVector(RwV3d* vectorOut, const RwV3d* vectorIn, const RwMatrix* matrix) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (vectorOut && vectorIn && matrix)
        rw::V3d::transformVectors(reinterpret_cast<rw::V3d*>(vectorOut), reinterpret_cast<const rw::V3d*>(vectorIn), 1, reinterpret_cast<const rw::Matrix*>(matrix));
    return vectorOut;
#else
    return ((RwV3d*(__cdecl *)(RwV3d*, const RwV3d*, const RwMatrix*))0x7EDDC0)(vectorOut, vectorIn, matrix);
#endif
}

RwV3d* RwV3dTransformVectors(RwV3d* vectorsOut, const RwV3d* vectorsIn, RwInt32 numPoints, const RwMatrix* matrix) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (vectorsOut && vectorsIn && matrix && numPoints > 0)
        rw::V3d::transformVectors(reinterpret_cast<rw::V3d*>(vectorsOut), reinterpret_cast<const rw::V3d*>(vectorsIn), numPoints, reinterpret_cast<const rw::Matrix*>(matrix));
    return vectorsOut;
#else
    return ((RwV3d*(__cdecl *)(RwV3d*, const RwV3d*, RwInt32, const RwMatrix*))0x7EDDF0)(vectorsOut, vectorsIn, numPoints, matrix);
#endif
}

RwReal _rwSqrt(const RwReal num) {
#ifdef NOTSA_STANDALONE_NATIVE
    return std::sqrt(num);
#else
    return ((RwReal(__cdecl *)(const RwReal))0x7EDB30)(num);
#endif
}

RwReal _rwInvSqrt(const RwReal num) {
#ifdef NOTSA_STANDALONE_NATIVE
    return 1.0f / std::sqrt(num);
#else
    return ((RwReal(__cdecl *)(const RwReal))0x7EDB90)(num);
#endif
}

RwReal _rwV3dNormalize(RwV3d* out, const RwV3d* in) {
    return RwV3dNormalize(out, in);
}

RwSList* _rwSListCreate(RwInt32 size, RwUInt32 hint) {
#ifdef NOTSA_STANDALONE_NATIVE
    return reinterpret_cast<RwSList*>(std::malloc(size > 0 ? size : 64));
#else
    return ((RwSList*(__cdecl *)(RwInt32, RwUInt32))0x809160)(size, hint);
#endif
}

RwBool _rwSListDestroy(RwSList* sList) {
#ifdef NOTSA_STANDALONE_NATIVE
    std::free(sList);
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwSList*))0x809440)(sList);
#endif
}

void _rwSListDestroyEndEntries(RwSList* sList, RwInt32 amount) {
#ifdef NOTSA_STANDALONE_NATIVE
#else
    ((void(__cdecl *)(RwSList*, RwInt32))0x809400)(sList, amount);
#endif
}

void* _rwSListGetEntry(RwSList* sList, RwInt32 entry) {
#ifdef NOTSA_STANDALONE_NATIVE
    return sList;
#else
    return ((void*(__cdecl *)(RwSList*, RwInt32))0x809510)(sList, entry);
#endif
}

void* _rwSListGetNewEntry(RwSList* sList, RwUInt32 hint) {
#ifdef NOTSA_STANDALONE_NATIVE
    return sList;
#else
    return ((void*(__cdecl *)(RwSList*, RwUInt32))0x809240)(sList, hint);
#endif
}

RwInt32 _rwSListGetNumEntries(const RwSList* sList) {
#ifdef NOTSA_STANDALONE_NATIVE
    return 0;
#else
    return ((RwInt32(__cdecl *)(const RwSList*))0x8094B0)(sList);
#endif
}

void* _rwSListGetEnd(RwSList* sList) {
#ifdef NOTSA_STANDALONE_NATIVE
    return sList;
#else
    return ((void*(__cdecl *)(RwSList*))0x809540)(sList);
#endif
}

RwUInt32 RwEngineGetVersion() {
#ifdef NOTSA_STANDALONE_NATIVE
    return 0x36003;
#else
    return ((RwUInt32(__cdecl *)(void))0x7F2BA0)();
#endif
}

RwBool RwEngineInit(const RwMemoryFunctions* memFuncs, RwUInt32 initFlags, RwUInt32 resArenaSize) {
#ifdef NOTSA_STANDALONE_NATIVE
    bool res = rw::Engine::init(memFuncs ? (rw::MemoryFunctions*)memFuncs : nullptr);
    if (res) {
        rw::Charset::open();
        static RwGlobals s_RwGlobals{};
        RwEngineInstance = &s_RwGlobals;
        RwInitialized = true;
    }
    return res ? TRUE : FALSE;
#else
    return ((RwBool(__cdecl *)(const RwMemoryFunctions*, RwUInt32, RwUInt32))0x7F3170)(memFuncs, initFlags, resArenaSize);
#endif
}

RwInt32 RwEngineRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor initCB, RwPluginObjectDestructor termCB) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Engine::registerPlugin(size, pluginID, (rw::Constructor)initCB, (rw::Destructor)termCB);
#else
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor))0x7F2BB0)(size, pluginID, initCB, termCB);
#endif
}

RwInt32 RwEngineGetPluginOffset(RwUInt32 pluginID) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Engine::s_plglist.getPluginOffset(pluginID);
#else
    return ((RwInt32(__cdecl *)(RwUInt32))0x7F2BE0)(pluginID);
#endif
}

RwBool RwEngineOpen(RwEngineOpenParams* initParams) {
#ifdef NOTSA_STANDALONE_NATIVE
    rw::EngineOpenParams params{};
#ifdef RW_GL3
    static void* s_dummyWindow = nullptr;
    params.window = reinterpret_cast<decltype(params.window)>(&s_dummyWindow);
    params.width = 640;
    params.height = 480;
    params.windowtitle = "GTA: San Andreas";
    if (initParams && initParams->displayID) {
        s_dummyWindow = initParams->displayID;
    }
#elif defined(RW_D3D9)
    if (initParams && initParams->displayID) {
        params.window = (HWND)initParams->displayID;
    }
#endif
    return rw::Engine::open(&params) ? TRUE : FALSE;
#else
    return ((RwBool(__cdecl *)(RwEngineOpenParams*))0x7F2F70)(initParams);
#endif
}

RwBool RwEngineStart() {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Engine::start() ? TRUE : FALSE;
#else
    return ((RwBool(__cdecl *)(void))0x7F2E70)();
#endif
}

RwBool RwEngineStop() {
#ifdef NOTSA_STANDALONE_NATIVE
    rw::Engine::stop();
    return TRUE;
#else
    return ((RwBool(__cdecl *)(void))0x7F2E20)();
#endif
}

RwBool RwEngineClose() {
#ifdef NOTSA_STANDALONE_NATIVE
    rw::Engine::close();
    return TRUE;
#else
    return ((RwBool(__cdecl *)(void))0x7F2F00)();
#endif
}

RwBool RwEngineTerm() {
#ifdef NOTSA_STANDALONE_NATIVE
    rw::Charset::close();
    rw::Engine::term();
    return TRUE;
#else
    return ((RwBool(__cdecl *)(void))0x7F3130)();
#endif
}

RwInt32 RwEngineGetNumSubSystems() {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Engine::getNumSubSystems();
#else
    return ((RwInt32(__cdecl *)(void))0x7F2C00)();
#endif
}

RwSubSystemInfo* RwEngineGetSubSystemInfo(RwSubSystemInfo* subSystemInfo, RwInt32 subSystemIndex) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Engine::getSubSystemInfo(reinterpret_cast<rw::SubSystemInfo*>(subSystemInfo), subSystemIndex) ? subSystemInfo : nullptr;
#else
    return ((RwSubSystemInfo*(__cdecl *)(RwSubSystemInfo*, RwInt32))0x7F2C30)(subSystemInfo, subSystemIndex);
#endif
}

RwInt32 RwEngineGetCurrentSubSystem() {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Engine::getCurrentSubSystem();
#else
    return ((RwInt32(__cdecl *)(void))0x7F2C60)();
#endif
}

RwBool RwEngineSetSubSystem(RwInt32 subSystemIndex) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Engine::setSubSystem(subSystemIndex) ? TRUE : FALSE;
#else
    return ((RwBool(__cdecl *)(RwInt32))0x7F2C90)(subSystemIndex);
#endif
}

RwInt32 RwEngineGetNumVideoModes() {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Engine::getNumVideoModes();
#else
    return ((RwInt32(__cdecl *)(void))0x7F2CC0)();
#endif
}

RwVideoMode* RwEngineGetVideoModeInfo(RwVideoMode* vmi, RwInt32 modeIndex) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Engine::getVideoModeInfo(reinterpret_cast<rw::VideoMode*>(vmi), modeIndex) ? vmi : nullptr;
#else
    return plugin::CallAndReturn<RwVideoMode*, 0x7F2CF0>(vmi, modeIndex);
#endif
}

RwInt32 RwEngineGetCurrentVideoMode() {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Engine::getCurrentVideoMode();
#else
    return ((RwInt32(__cdecl *)(void))0x7F2D20)();
#endif
}

RwBool RwEngineSetVideoMode(RwInt32 modeIndex) {
#ifdef NOTSA_STANDALONE_NATIVE
    return rw::Engine::setVideoMode(modeIndex) ? TRUE : FALSE;
#else
    return ((RwBool(__cdecl *)(RwInt32))0x7F2D50)(modeIndex);
#endif
}

RwInt32 RwEngineGetTextureMemorySize() {
#ifdef NOTSA_STANDALONE_NATIVE
    return 64 * 1024 * 1024;
#else
    return ((RwInt32(__cdecl *)(void))0x7F2D80)();
#endif
}

RwInt32 RwEngineGetMaxTextureSize() {
#ifdef NOTSA_STANDALONE_NATIVE
    return 4096;
#else
    return ((RwInt32(__cdecl *)(void))0x7F2DB0)();
#endif
}

RwBool RwEngineSetFocus(RwBool enable) {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwBool))0x7F2DE0)(enable);
#endif
}

RwMetrics* RwEngineGetMetrics() {
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
    return ((RwMetrics*(__cdecl *)(void))0x7F2E10)();
#endif
}

RwError* RwErrorGet(RwError* code) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (code) {
        code->pluginID = 0;
        code->errorCode = 0;
    }
    return code;
#else
    return ((RwError*(__cdecl *)(RwError*))0x808880)(code);
#endif
}

RwError* RwErrorSet(RwError* code) {
#ifdef NOTSA_STANDALONE_NATIVE
    return code;
#else
    return ((RwError*(__cdecl *)(RwError*))0x808820)(code);
#endif
}

RwInt32 _rwerror(RwInt32 code, ...) {
    return code;
}

RwBool RwResourcesSetArenaSize(RwUInt32 size) {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwUInt32))0x8080C0)(size);
#endif
}

RwInt32 RwResourcesGetArenaSize() {
#ifdef NOTSA_STANDALONE_NATIVE
    return 32 * 1024 * 1024;
#else
    return ((RwInt32(__cdecl *)(void))0x8081B0)();
#endif
}

RwInt32 RwResourcesGetArenaUsage() {
#ifdef NOTSA_STANDALONE_NATIVE
    return 0;
#else
    return ((RwInt32(__cdecl *)(void))0x8081C0)();
#endif
}

RwBool RwResourcesEmptyArena() {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(void))0x8081F0)();
#endif
}

RwResEntry* RwResourcesAllocateResEntry(void* owner, RwResEntry* ownerRef, RwInt32 size, RwResEntryDestroyNotify destroyNotify) {
#ifdef NOTSA_STANDALONE_NATIVE
    return reinterpret_cast<RwResEntry*>(std::calloc(1, size > 0 ? size : sizeof(RwResEntry)));
#else
    return ((RwResEntry*(__cdecl *)(void*, RwResEntry*, RwInt32, RwResEntryDestroyNotify))0x807ED0)(owner, ownerRef, size, destroyNotify);
#endif
}

RwBool RwResourcesFreeResEntry(RwResEntry* entry) {
#ifdef NOTSA_STANDALONE_NATIVE
    std::free(entry);
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RwResEntry*))0x807DE0)(entry);
#endif
}

void _rwResourcesPurge() {
#ifdef NOTSA_STANDALONE_NATIVE
#else
    ((void(__cdecl *)(void))0x807E50)();
#endif
}

RwBool RwStreamFindChunk(RwStream* stream, RwUInt32 type, RwUInt32* lengthOut, RwUInt32* versionOut) {
#ifdef NOTSA_STANDALONE_NATIVE
    return stream ? (rw::findChunk(reinterpret_cast<rw::Stream*>(stream), type, lengthOut, versionOut) ? TRUE : FALSE) : FALSE;
#else
    return ((RwBool(__cdecl *)(RwStream*, RwUInt32, RwUInt32*, RwUInt32*))0x7ED2D0)(stream, type, lengthOut, versionOut);
#endif
}

RwStream* _rwStreamWriteVersionedChunkHeader(RwStream* stream, RwInt32 type, RwInt32 size, RwUInt32 version, RwUInt32 buildNum) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (stream) rw::writeChunkHeader(reinterpret_cast<rw::Stream*>(stream), type, size);
    return stream;
#else
    return ((RwStream*(__cdecl *)(RwStream*, RwInt32, RwInt32, RwUInt32, RwUInt32))0x7ED270)(stream, type, size, version, buildNum);
#endif
}

RwStream* RwStreamWriteReal(RwStream* stream, const RwReal* reals, RwUInt32 numBytes) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (stream && reals) reinterpret_cast<rw::Stream*>(stream)->write8(reals, numBytes);
    return stream;
#else
    return ((RwStream*(__cdecl *)(RwStream*, const RwReal*, RwUInt32))0x7ED3D0)(stream, reals, numBytes);
#endif
}

RwStream* RwStreamWriteInt32(RwStream* stream, const RwInt32* ints, RwUInt32 numBytes) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (stream && ints) reinterpret_cast<rw::Stream*>(stream)->write8(ints, numBytes);
    return stream;
#else
    return ((RwStream*(__cdecl *)(RwStream*, const RwInt32*, RwUInt32))0x7ED460)(stream, ints, numBytes);
#endif
}

RwStream* RwStreamWriteInt16(RwStream* stream, const RwInt16* ints, RwUInt32 numBytes) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (stream && ints) reinterpret_cast<rw::Stream*>(stream)->write8(ints, numBytes);
    return stream;
#else
    return ((RwStream*(__cdecl *)(RwStream*, const RwInt16*, RwUInt32))0x7ED480)(stream, ints, numBytes);
#endif
}

RwStream* RwStreamReadReal(RwStream* stream, RwReal* reals, RwUInt32 numBytes) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (stream && reals) reinterpret_cast<rw::Stream*>(stream)->read8(reals, numBytes);
    return stream;
#else
    return ((RwStream*(__cdecl *)(RwStream*, RwReal*, RwUInt32))0x7ED4F0)(stream, reals, numBytes);
#endif
}

RwStream* RwStreamReadInt32(RwStream* stream, RwInt32* ints, RwUInt32 numBytes) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (stream && ints) reinterpret_cast<rw::Stream*>(stream)->read8(ints, numBytes);
    return stream;
#else
    return ((RwStream*(__cdecl *)(RwStream*, RwInt32*, RwUInt32))0x7ED540)(stream, ints, numBytes);
#endif
}

RwStream* RwStreamReadInt16(RwStream* stream, RwInt16* ints, RwUInt32 numBytes) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (stream && ints) reinterpret_cast<rw::Stream*>(stream)->read8(ints, numBytes);
    return stream;
#else
    return ((RwStream*(__cdecl *)(RwStream*, RwInt16*, RwUInt32))0x7ED4A0)(stream, ints, numBytes);
#endif
}

RwStream* RwStreamReadChunkHeaderInfo(RwStream* stream, RwChunkHeaderInfo* chunkHeaderInfo) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (stream && chunkHeaderInfo) {
        rw::readChunkHeaderInfo(reinterpret_cast<rw::Stream*>(stream), reinterpret_cast<rw::ChunkHeaderInfo*>(chunkHeaderInfo));
    }
    return stream;
#else
    return ((RwStream*(__cdecl *)(RwStream*, RwChunkHeaderInfo*))0x7ED590)(stream, chunkHeaderInfo);
#endif
}
