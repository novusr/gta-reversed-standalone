#include <iostream>
#include <vector>
#include <cassert>
#include <cstring>
#include <cmath>
#include <cstdlib>

#define NOTSA_STANDALONE_NATIVE 1
#include "Base.h"
#include "RenderWare/RenderWare.h"
#include "RenderWare/RwBridge.h"
#include "rtanim.h"

void TestMathAndMatrices() {
    std::cout << "[Test 1] Testing RenderWare Matrix & Vector Math..." << std::endl;
    
    RwMatrix* matA = RwMatrixCreate();
    assert(matA != nullptr);
    RwMatrix* matB = RwMatrixCreate();
    assert(matB != nullptr);
    RwMatrix* matOut = RwMatrixCreate();
    assert(matOut != nullptr);

    // Translation check
    RwV3d pos{ 10.0f, 20.0f, 30.0f };
    RwMatrixTranslate(matA, &pos, rwCOMBINEREPLACE);
    assert(matA->pos.x == 10.0f && matA->pos.y == 20.0f && matA->pos.z == 30.0f);

    RwV3d scale{ 2.0f, 2.0f, 2.0f };
    RwMatrixScale(matB, &scale, rwCOMBINEREPLACE);

    RwMatrixMultiply(matOut, matB, matA);
    assert(matOut != nullptr);

    // Vector transform check
    RwV3d pointsIn[2] = { { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } };
    RwV3d pointsOut[2];
    RwV3dTransformPoints(pointsOut, pointsIn, 2, matA);
    assert(pointsOut[0].x == 11.0f && pointsOut[0].y == 20.0f && pointsOut[0].z == 30.0f);
    assert(pointsOut[1].x == 10.0f && pointsOut[1].y == 21.0f && pointsOut[1].z == 30.0f);

    // Matrix Invert
    RwMatrix* invMat = RwMatrixCreate();
    RwMatrixInvert(invMat, matA);
    RwV3d restoredPoint[1];
    RwV3dTransformPoints(restoredPoint, &pointsOut[0], 1, invMat);
    assert(std::abs(restoredPoint[0].x - pointsIn[0].x) < 0.001f);
    assert(std::abs(restoredPoint[0].y - pointsIn[0].y) < 0.001f);
    assert(std::abs(restoredPoint[0].z - pointsIn[0].z) < 0.001f);

    RwMatrixDestroy(matA);
    RwMatrixDestroy(matB);
    RwMatrixDestroy(matOut);
    RwMatrixDestroy(invMat);

    std::cout << "  -> Matrix & Vector Math PASSED!" << std::endl;
}

void TestRastersAndTextures() {
    std::cout << "[Test 2] Testing RenderWare Rasters & Textures..." << std::endl;

    RwRaster* raster = RwRasterCreate(64, 64, 32, static_cast<RwInt32>(rwRASTERTYPETEXTURE | rwRASTERFORMAT8888));
    assert(raster != nullptr);
    assert(RwRasterGetWidth(raster) == 64);
    assert(RwRasterGetHeight(raster) == 64);
    assert(RwRasterGetDepth(raster) == 32);

    RwUInt8* pixels = RwRasterLock(raster, 0, rwRASTERLOCKWRITE);
    assert(pixels != nullptr);
    pixels[0] = 0xAA;
    pixels[1] = 0xBB;
    pixels[2] = 0xCC;
    pixels[3] = 0xFF;
    RwRasterUnlock(raster);

    RwTexture* texture = RwTextureCreate(raster);
    assert(texture != nullptr);
    assert(RwTextureGetRaster(texture) == raster);

    RwTextureSetName(texture, "test_tex");
    RwTextureSetMaskName(texture, "test_mask");
    assert(std::strcmp(RwTextureGetName(texture), "test_tex") == 0);
    assert(std::strcmp(RwTextureGetMaskName(texture), "test_mask") == 0);

    RwTextureDestroy(texture);
    std::cout << "  -> Rasters & Textures PASSED!" << std::endl;
}

void TestClumpStreamReadWrite() {
    std::cout << "[Test 3] Testing Clump Binary Stream Read/Write..." << std::endl;

    // 1. Create clump, frame, geometry, material, atomic
    RpClump* clump = RpClumpCreate();
    assert(clump != nullptr);

    RwFrame* frame = RwFrameCreate();
    assert(frame != nullptr);
    RpClumpSetFrame(clump, frame);

    RpGeometry* geom = RpGeometryCreate(0, 0, 0);
    assert(geom != nullptr);

    RpMaterial* mat = RpMaterialCreate();
    assert(mat != nullptr);
    RwRGBA col = { 255, 128, 64, 255 };
    RpMaterialSetColor(mat, &col);

    RpAtomic* atomic = RpAtomicCreate();
    assert(atomic != nullptr);
    RpAtomicSetGeometry(atomic, geom, 0);

    RwFrame* atomicFrame = RwFrameCreate();
    RwFrameAddChild(frame, atomicFrame);
    RpAtomicSetFrame(atomic, atomicFrame);

    RpClumpAddAtomic(clump, atomic);
    assert(RpClumpGetNumAtomics(clump) == 1);

    // 2. Stream write to memory buffer
    std::vector<RwUInt8> buffer(65536, 0);
    RwMemory writeMem{ buffer.data(), static_cast<RwUInt32>(buffer.size()) };
    RwStream* writeStream = RwStreamOpen(rwSTREAMMEMORY, rwSTREAMWRITE, &writeMem);
    assert(writeStream != nullptr);

    RpClump* writtenClump = RpClumpStreamWrite(clump, writeStream);
    assert(writtenClump != nullptr);
    RwStreamClose(writeStream, nullptr);

    RpClumpDestroy(clump);

    // 3. Stream read from memory buffer
    RwMemory readMem{ buffer.data(), static_cast<RwUInt32>(buffer.size()) };
    RwStream* readStream = RwStreamOpen(rwSTREAMMEMORY, rwSTREAMREAD, &readMem);
    assert(readStream != nullptr);

    RpClump* loadedClump = RpClumpStreamRead(readStream);
    assert(loadedClump != nullptr);
    RwStreamClose(readStream, nullptr);

    assert(RpClumpGetNumAtomics(loadedClump) == 1);

    int atomicCount = 0;
    RpClumpForAllAtomics(loadedClump, [](RpAtomic* a, void* data) -> RpAtomic* {
        int* count = static_cast<int*>(data);
        (*count)++;
        assert(RpAtomicGetGeometry(a) != nullptr);
        return a;
    }, &atomicCount);
    assert(atomicCount == 1);

    RpClumpDestroy(loadedClump);
    std::cout << "  -> Clump Stream Read/Write PASSED!" << std::endl;
}

void TestTexDictionaryStreamReadWrite() {
    std::cout << "[Test 4] Testing TexDictionary Binary Stream Read/Write..." << std::endl;

    RwTexDictionary* txd = RwTexDictionaryCreate();
    assert(txd != nullptr);

    RwTexDictionarySetCurrent(txd);
    assert(RwTexDictionaryGetCurrent() == txd);

    RwRaster* ras = RwRasterCreate(16, 16, 32, static_cast<RwInt32>(rwRASTERTYPETEXTURE | rwRASTERFORMAT8888));
    assert(ras != nullptr);
    RwTexture* tex = RwTextureCreate(ras);
    assert(tex != nullptr);
    RwTextureSetName(tex, "my_txd_tex");
    RwTexDictionaryAddTexture(txd, tex);

    RwTexture* found = RwTexDictionaryFindNamedTexture(txd, "my_txd_tex");
    assert(found == tex);

    // Write to memory stream
    std::vector<RwUInt8> buffer(65536, 0);
    RwMemory writeMem{ buffer.data(), static_cast<RwUInt32>(buffer.size()) };
    RwStream* writeStream = RwStreamOpen(rwSTREAMMEMORY, rwSTREAMWRITE, &writeMem);
    assert(writeStream != nullptr);
    RwTexDictionaryStreamWrite(txd, writeStream);
    RwStreamClose(writeStream, nullptr);

    RwTexDictionaryDestroy(txd);

    // Read back
    RwMemory readMem{ buffer.data(), static_cast<RwUInt32>(buffer.size()) };
    RwStream* readStream = RwStreamOpen(rwSTREAMMEMORY, rwSTREAMREAD, &readMem);
    assert(readStream != nullptr);
    RwTexDictionary* loadedTxd = RwTexDictionaryStreamRead(readStream);
    assert(loadedTxd != nullptr);
    RwStreamClose(readStream, nullptr);

    RwTexture* loadedTex = RwTexDictionaryFindNamedTexture(loadedTxd, "my_txd_tex");
    assert(loadedTex != nullptr);
    assert(std::strcmp(RwTextureGetName(loadedTex), "my_txd_tex") == 0);

    RwTexDictionaryDestroy(loadedTxd);
    std::cout << "  -> TexDictionary Stream Read/Write PASSED!" << std::endl;
}

void TestWorldAndLights() {
    std::cout << "[Test 5] Testing World & Light Hierarchy..." << std::endl;

    RwBBox bbox = { { -100.0f, -100.0f, -100.0f }, { 100.0f, 100.0f, 100.0f } };
    RpWorld* world = RpWorldCreate(&bbox);
    assert(world != nullptr);

    RpLight* light = RpLightCreate(rpLIGHTDIRECTIONAL);
    assert(light != nullptr);
    RwRGBAReal col = { 1.0f, 0.9f, 0.8f, 1.0f };
    RpLightSetColor(light, &col);

    RpWorldAddLight(world, light);
    assert(RpLightGetWorld(light) == world);

    int lightCount = 0;
    RpWorldForAllLights(world, [](RpLight* l, void* data) -> RpLight* {
        int* count = static_cast<int*>(data);
        (*count)++;
        return l;
    }, &lightCount);
    assert(lightCount == 1);

    RpClump* clump = RpClumpCreate();
    RpWorldAddClump(world, clump);
    assert(RpClumpGetWorld(clump) == world);

    int clumpCount = 0;
    RpWorldForAllClumps(world, [](RpClump* c, void* data) -> RpClump* {
        int* count = static_cast<int*>(data);
        (*count)++;
        return c;
    }, &clumpCount);
    assert(clumpCount == 1);

    RpWorldRemoveClump(world, clump);
    assert(RpClumpGetWorld(clump) == nullptr);
    RpClumpDestroy(clump);

    RpWorldRemoveLight(world, light);
    assert(RpLightGetWorld(light) == nullptr);
    RpLightDestroy(light);

    RpWorldDestroy(world);
    std::cout << "  -> World & Light Hierarchy PASSED!" << std::endl;
}

void TestPipelineBridge() {
    std::cout << "[Test 6] Testing RenderWare Pipelines & Stubs..." << std::endl;

    RxPipeline* pipe = RxPipelineCreate();
    assert(pipe != nullptr);

    RxPipeline* locked = RxPipelineLock(pipe);
    assert(locked != nullptr);

    RxPipeline* unlocked = RxLockedPipeUnlock(locked);
    assert(unlocked == pipe);

    RxPipelineDestroy(pipe);
    std::cout << "  -> Pipeline Bridge PASSED!" << std::endl;
}

void TestAnimations() {
    std::cout << "[Test 7] Testing RtAnim Animation & Interpolation..." << std::endl;

    RtAnimAnimation* anim = RtAnimAnimationCreate(1, 10, 0, 5.0f);
    assert(anim != nullptr);

    RtAnimInterpolator* interp = RtAnimInterpolatorCreate(5, 64);
    assert(interp != nullptr);

    RtAnimInterpolatorDestroy(interp);
    RtAnimAnimationDestroy(anim);
    std::cout << "  -> RtAnim Animation & Interpolation PASSED!" << std::endl;
}

int main() {
    std::cout << "========================================================" << std::endl;
    std::cout << "  GTA REVERSED: LIBRW STANDALONE VALIDATION TEST HARNESS" << std::endl;
    std::cout << "========================================================" << std::endl;

    std::cout << "[Test 0] Testing Engine Lifecycle..." << std::endl;
    RwBool initOk = RwEngineInit(nullptr, 0, 0);
    assert(initOk == TRUE);
    std::cout << "  -> RwEngineInit succeeded." << std::endl;

    RwEngineOpenParams openParams{};
    RwBool openOk = RwEngineOpen(&openParams);
    assert(openOk == TRUE);
    std::cout << "  -> RwEngineOpen succeeded." << std::endl;

    RwBool startOk = RwEngineStart();
    assert(startOk == TRUE);
    std::cout << "  -> RwEngineStart succeeded." << std::endl;

    TestMathAndMatrices();
    TestRastersAndTextures();
    TestClumpStreamReadWrite();
    TestTexDictionaryStreamReadWrite();
    TestWorldAndLights();
    TestPipelineBridge();
    TestAnimations();

    RwEngineStop();
    RwEngineClose();
    RwEngineTerm();
    std::cout << "  -> Engine shutdown (Stop/Close/Term) succeeded." << std::endl;

    std::cout << "\n========================================================" << std::endl;
    std::cout << "  ALL LIBRW VALIDATION TESTS PASSED (100% SUCCESS)!" << std::endl;
    std::cout << "========================================================" << std::endl;
    return 0;
}
