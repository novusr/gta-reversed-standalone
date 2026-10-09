#include "StdInc.h"

#include "rtquat.h"
#ifdef NOTSA_STANDALONE_NATIVE
#include "RenderWare/RwBridge.h"
#endif

RwBool RtQuatConvertFromMatrix(RtQuat* qpQuat, const RwMatrix* const mpMatrix) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (qpQuat && mpMatrix) {
        rw::Quat q = rw::Quat::fromMatrix((const rw::Matrix*)mpMatrix);
        qpQuat->imag.x = q.v.x;
        qpQuat->imag.y = q.v.y;
        qpQuat->imag.z = q.v.z;
        qpQuat->real   = q.w;
        return TRUE;
    }
    return FALSE;
#else
    return ((RwBool(__cdecl*)(RtQuat*, const RwMatrix* const))0x7EB5C0)(qpQuat, mpMatrix);
#endif
}

RtQuat* RtQuatRotate(RtQuat* quat, const RwV3d* axis, RwReal angle, RwOpCombineType combineOp) {
#ifdef NOTSA_STANDALONE_NATIVE
    return quat;
#else
    return ((RtQuat*(__cdecl *)(RtQuat*, const RwV3d*, RwReal, RwOpCombineType))0x7EB7C0)(quat, axis, angle, combineOp);
#endif
}

const RtQuat* RtQuatQueryRotate(const RtQuat* quat, RwV3d* unitAxis, RwReal* angle) {
#ifdef NOTSA_STANDALONE_NATIVE
    return quat;
#else
    return ((const RtQuat*(__cdecl *)(const RtQuat*, RwV3d*, RwReal*))0x7EBA80)(quat, unitAxis, angle);
#endif
}

RwV3d* RtQuatTransformVectors(RwV3d* vectorsOut, const RwV3d* vectorsIn, const RwInt32 numPoints, const RtQuat* quat) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (vectorsOut && vectorsIn && numPoints > 0) {
        std::memcpy(vectorsOut, vectorsIn, numPoints * sizeof(RwV3d));
    }
    return vectorsOut;
#else
    return ((RwV3d*(__cdecl *)(RwV3d*, const RwV3d*, const RwInt32, const RtQuat*))0x7EBBB0)(vectorsOut, vectorsIn, numPoints, quat);
#endif
}

RwReal RtQuatModulus(RtQuat* q) {
#ifdef NOTSA_STANDALONE_NATIVE
    if (!q) return 0.0f;
    return std::sqrt(q->imag.x * q->imag.x + q->imag.y * q->imag.y + q->imag.z * q->imag.z + q->real * q->real);
#else
    return ((RwReal(__cdecl *)(RtQuat*))0x7EBD10)(q);
#endif
}
