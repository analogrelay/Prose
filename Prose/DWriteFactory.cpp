#pragma once

#include "pch.h"
#include "DWriteFactory.h"

using namespace Microsoft::WRL;

DWriteFactory DWriteFactory::_theFactory;
DWriteFactory::DWriteFactory(void) : _factory(nullptr), _systemFonts(nullptr) { };

ComPtr<IDWriteFactory> DWriteFactory::GetFactoryCore() {
	if(!_factory) {
		ThrowIfFailed(DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED, 
			__uuidof(IDWriteFactory), 
			&_factory));
	}
	return _factory;
};

ComPtr<IDWriteFontCollection> DWriteFactory::GetSystemFontsCore() {
	if(!_systemFonts) {
		ThrowIfFailed(GetFactory()->GetSystemFontCollection(
			&_systemFonts,
			FALSE));
	}
	return _systemFonts;
}
