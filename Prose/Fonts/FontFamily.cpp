#include "pch.h"
#include "FontFamily.h"

using namespace Platform;
using namespace Prose::Fonts;

FontFamily::FontFamily(IDWriteFontFamily* family) : _family(family) {}

Array<String^>^ FontFamily::GetFamilyNames() {
	if(_familyNames == nullptr) {
		IDWriteLocalizedStrings* names;
		ThrowIfFailed(_family->GetFamilyNames(&names));
		auto nameCount = names->GetCount();
		auto familyNames = ref new Array<String^>(nameCount);
		for(UINT32 i = 0; i < nameCount; i++) {
			UINT32 length;
			ThrowIfFailed(names->GetStringLength(i, &length));
			WCHAR* buf = new WCHAR[length + 1];
			ThrowIfFailed(names->GetString(i, buf, length + 1));
			familyNames[i] = ref new Platform::String(buf, length);
		}
		_familyNames = familyNames;
	}
	return _familyNames;
}