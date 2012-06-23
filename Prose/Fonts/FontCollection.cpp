#include "pch.h"
#include "FontCollection.h"
#include "FontFamily.h"

using namespace Prose::Fonts;

FontCollection::FontCollection(IDWriteFontCollection* collection) : _collection(collection) {}

FontFamily^ FontCollection::GetFontFamily(Platform::String^ name) {
	UINT32 index = 0;
	BOOL exists = FALSE;
	ThrowIfFailed(_collection->FindFamilyName(name->Data(), &index, &exists));

	if(!exists) {
		throw ref new Platform::InvalidArgumentException(
			// (boost::wformat(L"Cannot find font family with name: '%1'") % name->Data()).str().c_str())
			"Cannot find that font family");
	}
	IDWriteFontFamily* family = NULL;
	ThrowIfFailed(_collection->GetFontFamily(index, &family));
	return ref new FontFamily(family);
}

FontFamily^ FontCollection::GetFontFamily(UINT32 index) {
	if(index >= Count) {
		throw ref new Platform::InvalidArgumentException("'index' is out of the bounds of the collection");
	}
	
	IDWriteFontFamily* family = NULL;
	ThrowIfFailed(_collection->GetFontFamily(index, &family));
	return ref new FontFamily(family);
}

UINT32 FontCollection::GetFontFamilyCount() {
	return _collection->GetFontFamilyCount();
}

FontCollection^ FontCollection::GetSystemFonts() {
	IDWriteFontCollection* fontCollection;
	ThrowIfFailed(DWriteFactory::GetFactory()->GetSystemFontCollection(&fontCollection, TRUE));
	return ref new FontCollection(fontCollection);
}

IIterator<FontFamily^>^ FontCollection::First() {
	UINT32 count = _collection->GetFontFamilyCount();
	return ref new FontFamilyIterator(this);
}

FontCollection::FontFamilyIterator::FontFamilyIterator(FontCollection^ collection) : 
	_collection(collection), 
	_count(collection->Count), 
	_position(0) 
{
	MoveNext();
}

UINT32 FontCollection::FontFamilyIterator::GetMany(WriteOnlyArray<FontFamily^>^ a) {
	for(UINT32 i = 0; i < _count; i++) {
		a[i] = _collection->GetFontFamily(i);
	}
	return _count;
}

bool FontCollection::FontFamilyIterator::MoveNext() {
	// Check for an item
	_hasCurrent = _position < _count;

	if(_hasCurrent) {
		// Grab the item
		_current = _collection->GetFontFamily(_position++);
	}
	return _hasCurrent;
}