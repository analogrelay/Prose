#pragma once

#include "pch.h"
#include "DWriteFactory.h"

DWriteFactory DWriteFactory::_theFactory;
DWriteFactory::DWriteFactory(void) : _factory(NULL) { };
IDWriteFactory* DWriteFactory::GetFactoryCore() {
	if(_factory == NULL) {
		ThrowIfFailed(DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED, 
			__uuidof(IDWriteFactory), 
			reinterpret_cast<IUnknown**>(&_factory)));
	}
	return _factory;
};
