#include "pch.h"
#include "ObjectTracking.h"

#ifdef OBJECT_TRACKING
volatile LONGLONG ObjectTracking::_nextId = -1;

UINT64 ObjectTracking::CreateObject(const wchar_t* descriptor) {
	UINT64 id = (UINT64)InterlockedIncrement64(&_nextId);
	dbgf(L"[TRACK] [%llu] Created %ws", id, descriptor);
	return id;
}

void ObjectTracking::DestroyObject(UINT64 id, const wchar_t* descriptor) {
	dbgf(L"[TRACK] [%llu] Destroyed %ws", id, descriptor);
}
#endif