#pragma once

#ifdef OBJECT_TRACKING
class ObjectTracking
{
public:
	static UINT64 CreateObject(const wchar_t* descriptor);
	static void DestroyObject(UINT64 id, const wchar_t* descriptor);
private:
	static volatile LONGLONG _nextId;
};

#define TrackingId UINT64 TrackingIdName
#define TrackingIdName __tracking__id__
#define TrackCreation(descriptor) TrackingIdName = ObjectTracking::CreateObject((descriptor))
#define TrackDestruction(descriptor) ObjectTracking::DestroyObject(TrackingIdName, (descriptor))

#else
#define TrackingId
#define TrackingIdName
#define TrackCreation(descriptor)
#define TrackDestruction(descriptor)
#endif