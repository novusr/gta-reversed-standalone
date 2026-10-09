#pragma once

#ifdef NOTSA_STANDALONE_NATIVE

#pragma push_macro("RWALIGN")
#undef RWALIGN
#include <rw.h>
#pragma pop_macro("RWALIGN")

#include <cassert>
#include <cstring>
#include <type_traits>

#ifndef ZoneScoped
#define ZoneScoped
#endif

// Forward declarations of RenderWare types
struct RwCamera;
struct RwRaster;
struct RwTexture;
struct RwTexDictionary;
struct RwStream;
struct RwFrame;
struct RpClump;
struct RpAtomic;
struct RpGeometry;
struct RpMaterial;
struct RpWorld;
struct RpLight;
struct RwMatrixTag;
using RwMatrix = RwMatrixTag;
struct RwV3d;
struct RwV2d;
struct RwRGBA;
struct RpHAnimHierarchy;
struct RtAnimAnimation;
struct RpSkin;
struct RwBBox;
struct RwSphere;
struct RwRect;
struct RwRGBAReal;
struct RwImage;

namespace notsa::rwbridge {

// Type conversion helpers
inline rw::Camera* ToRw(RwCamera* c) { return reinterpret_cast<rw::Camera*>(c); }
inline const rw::Camera* ToRw(const RwCamera* c) { return reinterpret_cast<const rw::Camera*>(c); }
inline RwCamera* FromRw(rw::Camera* c) { return reinterpret_cast<RwCamera*>(c); }

inline rw::Raster* ToRw(RwRaster* r) { return reinterpret_cast<rw::Raster*>(r); }
inline const rw::Raster* ToRw(const RwRaster* r) { return reinterpret_cast<const rw::Raster*>(r); }
inline RwRaster* FromRw(rw::Raster* r) { return reinterpret_cast<RwRaster*>(r); }

inline rw::Texture* ToRw(RwTexture* t) { return reinterpret_cast<rw::Texture*>(t); }
inline const rw::Texture* ToRw(const RwTexture* t) { return reinterpret_cast<const rw::Texture*>(t); }
inline RwTexture* FromRw(rw::Texture* t) { return reinterpret_cast<RwTexture*>(t); }

inline rw::TexDictionary* ToRw(RwTexDictionary* d) { return reinterpret_cast<rw::TexDictionary*>(d); }
inline const rw::TexDictionary* ToRw(const RwTexDictionary* d) { return reinterpret_cast<const rw::TexDictionary*>(d); }
inline RwTexDictionary* FromRw(rw::TexDictionary* d) { return reinterpret_cast<RwTexDictionary*>(d); }

inline rw::Stream* ToRw(RwStream* s) { return reinterpret_cast<rw::Stream*>(s); }
inline const rw::Stream* ToRw(const RwStream* s) { return reinterpret_cast<const rw::Stream*>(s); }
inline RwStream* FromRw(rw::Stream* s) { return reinterpret_cast<RwStream*>(s); }

inline rw::Frame* ToRw(RwFrame* f) { return reinterpret_cast<rw::Frame*>(f); }
inline const rw::Frame* ToRw(const RwFrame* f) { return reinterpret_cast<const rw::Frame*>(f); }
inline RwFrame* FromRw(rw::Frame* f) { return reinterpret_cast<RwFrame*>(f); }

inline rw::Clump* ToRw(RpClump* c) { return reinterpret_cast<rw::Clump*>(c); }
inline const rw::Clump* ToRw(const RpClump* c) { return reinterpret_cast<const rw::Clump*>(c); }
inline RpClump* FromRw(rw::Clump* c) { return reinterpret_cast<RpClump*>(c); }

inline rw::Atomic* ToRw(RpAtomic* a) { return reinterpret_cast<rw::Atomic*>(a); }
inline const rw::Atomic* ToRw(const RpAtomic* a) { return reinterpret_cast<const rw::Atomic*>(a); }
inline RpAtomic* FromRw(rw::Atomic* a) { return reinterpret_cast<RpAtomic*>(a); }

inline rw::Geometry* ToRw(RpGeometry* g) { return reinterpret_cast<rw::Geometry*>(g); }
inline const rw::Geometry* ToRw(const RpGeometry* g) { return reinterpret_cast<const rw::Geometry*>(g); }
inline RpGeometry* FromRw(rw::Geometry* g) { return reinterpret_cast<RpGeometry*>(g); }

inline rw::Material* ToRw(RpMaterial* m) { return reinterpret_cast<rw::Material*>(m); }
inline const rw::Material* ToRw(const RpMaterial* m) { return reinterpret_cast<const rw::Material*>(m); }
inline RpMaterial* FromRw(rw::Material* m) { return reinterpret_cast<RpMaterial*>(m); }

inline rw::World* ToRw(RpWorld* w) { return reinterpret_cast<rw::World*>(w); }
inline const rw::World* ToRw(const RpWorld* w) { return reinterpret_cast<const rw::World*>(w); }
inline RpWorld* FromRw(rw::World* w) { return reinterpret_cast<RpWorld*>(w); }

inline rw::Light* ToRw(RpLight* l) { return reinterpret_cast<rw::Light*>(l); }
inline const rw::Light* ToRw(const RpLight* l) { return reinterpret_cast<const rw::Light*>(l); }
inline RpLight* FromRw(rw::Light* l) { return reinterpret_cast<RpLight*>(l); }

inline rw::Matrix* ToRw(RwMatrix* m) { return reinterpret_cast<rw::Matrix*>(m); }
inline const rw::Matrix* ToRw(const RwMatrix* m) { return reinterpret_cast<const rw::Matrix*>(m); }
inline RwMatrix* FromRw(rw::Matrix* m) { return reinterpret_cast<RwMatrix*>(m); }

inline rw::V3d* ToRw(RwV3d* v) { return reinterpret_cast<rw::V3d*>(v); }
inline const rw::V3d* ToRw(const RwV3d* v) { return reinterpret_cast<const rw::V3d*>(v); }
inline RwV3d* FromRw(rw::V3d* v) { return reinterpret_cast<RwV3d*>(v); }

inline rw::V2d* ToRw(RwV2d* v) { return reinterpret_cast<rw::V2d*>(v); }
inline const rw::V2d* ToRw(const RwV2d* v) { return reinterpret_cast<const rw::V2d*>(v); }
inline RwV2d* FromRw(rw::V2d* v) { return reinterpret_cast<RwV2d*>(v); }

inline rw::RGBA* ToRw(RwRGBA* c) { return reinterpret_cast<rw::RGBA*>(c); }
inline const rw::RGBA* ToRw(const RwRGBA* c) { return reinterpret_cast<const rw::RGBA*>(c); }
inline RwRGBA* FromRw(rw::RGBA* c) { return reinterpret_cast<RwRGBA*>(c); }

inline rw::HAnimHierarchy* ToRw(RpHAnimHierarchy* h) { return reinterpret_cast<rw::HAnimHierarchy*>(h); }
inline RpHAnimHierarchy* FromRw(rw::HAnimHierarchy* h) { return reinterpret_cast<RpHAnimHierarchy*>(h); }

inline rw::Animation* ToRw(RtAnimAnimation* a) { return reinterpret_cast<rw::Animation*>(a); }
inline RtAnimAnimation* FromRw(rw::Animation* a) { return reinterpret_cast<RtAnimAnimation*>(a); }

inline rw::Skin* ToRw(RpSkin* s) { return reinterpret_cast<rw::Skin*>(s); }
inline RpSkin* FromRw(rw::Skin* s) { return reinterpret_cast<RpSkin*>(s); }

inline rw::BBox* ToRw(RwBBox* b) { return reinterpret_cast<rw::BBox*>(b); }
inline const rw::BBox* ToRw(const RwBBox* b) { return reinterpret_cast<const rw::BBox*>(b); }
inline RwBBox* FromRw(rw::BBox* b) { return reinterpret_cast<RwBBox*>(b); }

inline rw::Sphere* ToRw(RwSphere* s) { return reinterpret_cast<rw::Sphere*>(s); }
inline const rw::Sphere* ToRw(const RwSphere* s) { return reinterpret_cast<const rw::Sphere*>(s); }
inline RwSphere* FromRw(rw::Sphere* s) { return reinterpret_cast<RwSphere*>(s); }

inline rw::Rect* ToRw(RwRect* r) { return reinterpret_cast<rw::Rect*>(r); }
inline const rw::Rect* ToRw(const RwRect* r) { return reinterpret_cast<const rw::Rect*>(r); }
inline RwRect* FromRw(rw::Rect* r) { return reinterpret_cast<RwRect*>(r); }

inline rw::RGBAf* ToRw(RwRGBAReal* c) { return reinterpret_cast<rw::RGBAf*>(c); }
inline const rw::RGBAf* ToRw(const RwRGBAReal* c) { return reinterpret_cast<const rw::RGBAf*>(c); }
inline RwRGBAReal* FromRw(rw::RGBAf* c) { return reinterpret_cast<RwRGBAReal*>(c); }

inline rw::Image* ToRw(RwImage* i) { return reinterpret_cast<rw::Image*>(i); }
inline const rw::Image* ToRw(const RwImage* i) { return reinterpret_cast<const rw::Image*>(i); }
inline RwImage* FromRw(rw::Image* i) { return reinterpret_cast<RwImage*>(i); }

} // namespace notsa::rwbridge

#endif // NOTSA_STANDALONE_NATIVE
