#include "StdInc.h"

#include "rtdict.h"

RtDictSchema* RtDictSchemaInit(RtDictSchema* schema) {
#ifdef NOTSA_STANDALONE_NATIVE
    return schema;
#else
    return ((RtDictSchema*(__cdecl *)(RtDictSchema*))0x7CED40)(schema);
#endif
}

RwBool RtDictSchemaDestruct(RtDictSchema* schema) {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RtDictSchema*))0x7CED70)(schema);
#endif
}

RtDict* RtDictSchemaStreamReadDict(RtDictSchema* schema, RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
    return ((RtDict*(__cdecl *)(RtDictSchema*, RwStream*))0x7CF240)(schema, stream);
#endif
}

RtDict* RtDictSchemaCreateDict(RtDictSchema* schema) {
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
    return ((RtDict*(__cdecl *)(RtDictSchema*))0x7CED90)(schema);
#endif
}

RtDictSchema* RtDictSchemaAddDict(RtDictSchema* schema, RtDict* dict) {
#ifdef NOTSA_STANDALONE_NATIVE
    return schema;
#else
    return ((RtDictSchema*(__cdecl *)(RtDictSchema*, RtDict*))0x7CEE50)(schema, dict);
#endif
}

RtDictSchema* RtDictSchemaRemoveDict(RtDictSchema* schema, RtDict* dict) {
#ifdef NOTSA_STANDALONE_NATIVE
    return schema;
#else
    return ((RtDictSchema*(__cdecl *)(RtDictSchema*, RtDict*))0x7CEE80)(schema, dict);
#endif
}

RwBool RtDictSchemaForAllDictionaries(RtDictSchema* schema, RtDictCallBack* callback, RtDictEntryType data) {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RtDictSchema*, RtDictCallBack*, RtDictEntryType))0x7CF5B0)(schema, callback, data);
#endif
}

RtDict* RtDictSchemaGetCurrentDict(RtDictSchema* schema) {
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
    return ((RtDict*(__cdecl *)(RtDictSchema*))0x7CEEE0)(schema);
#endif
}

RtDictSchema* RtDictSchemaSetCurrentDict(RtDictSchema* schema, RtDict* dict) {
#ifdef NOTSA_STANDALONE_NATIVE
    return schema;
#else
    return ((RtDictSchema*(__cdecl *)(RtDictSchema*, RtDict*))0x7CEEF0)(schema, dict);
#endif
}

RwBool RtDictDestroy(RtDict* dictionary) {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RtDict*))0x7CF130)(dictionary);
#endif
}

RtDictEntryType RtDictAddEntry(RtDict* dictionary, RtDictEntryType entry) {
#ifdef NOTSA_STANDALONE_NATIVE
    return entry;
#else
    return ((RtDictEntryType(__cdecl *)(RtDict*, RtDictEntryType))0x7CEFB0)(dictionary, entry);
#endif
}

RtDictEntryType RtDictFindNamedEntry(RtDict* dictionary, const RwChar* name) {
#ifdef NOTSA_STANDALONE_NATIVE
    return nullptr;
#else
    return ((RtDictEntryType(__cdecl *)(RtDict*, const RwChar*))0x7CEFE0)(dictionary, name);
#endif
}

const RtDict* RtDictForAllEntries(const RtDict* dictionary, RtDictEntryCallBack* callBack, RtDictEntryType data) {
#ifdef NOTSA_STANDALONE_NATIVE
    return dictionary;
#else
    return ((const RtDict*(__cdecl *)(const RtDict*, RtDictEntryCallBack*, RtDictEntryType))0x7CF060)(dictionary, callBack, data);
#endif
}

RtDict* RtDictRemoveEntry(RtDict* dictionary, RtDictEntryType entry) {
#ifdef NOTSA_STANDALONE_NATIVE
    return dictionary;
#else
    return ((RtDict*(__cdecl *)(RtDict*, RtDictEntryType))0x7CF0C0)(dictionary, entry);
#endif
}

const RtDict* RtDictStreamWrite(const RtDict* dictionary, RwStream* stream) {
#ifdef NOTSA_STANDALONE_NATIVE
    return dictionary;
#else
    return ((const RtDict*(__cdecl *)(const RtDict*, RwStream*))0x7CF490)(dictionary, stream);
#endif
}

RwUInt32 RtDictStreamGetSize(const RtDict* dictionary) {
#ifdef NOTSA_STANDALONE_NATIVE
    return 0;
#else
    return ((RwUInt32(__cdecl *)(const RtDict*))0x7CF1F0)(dictionary);
#endif
}

RtDict* _rtDictSchemaInitDict(RtDictSchema* schema, RtDict* dictionary) {
#ifdef NOTSA_STANDALONE_NATIVE
    return dictionary;
#else
    return ((RtDict*(__cdecl *)(RtDictSchema*, RtDict*))0x7CEF00)(schema, dictionary);
#endif
}

RwBool _rtDictDestruct(RtDict* dictionary) {
#ifdef NOTSA_STANDALONE_NATIVE
    return TRUE;
#else
    return ((RwBool(__cdecl *)(RtDict*))0x7CEF60)(dictionary);
#endif
}
