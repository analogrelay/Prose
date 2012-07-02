#pragma once

#include "pch.h"
#include "DX.h"

using namespace Windows::Foundation;
using namespace Microsoft::WRL;

DX DX::_theFactory;
DX::DX(void) : _dwFactory(nullptr), _d2dFactory(nullptr), _systemFonts(nullptr) { };

void DX::ToNativeRect(Rect rect, RECT* pRect) {
	pRect->bottom = (LONG)std::ceil(rect.Bottom);
	pRect->left = (LONG)std::ceil(rect.Left);
	pRect->right = (LONG)std::ceil(rect.Right);
	pRect->top = (LONG)std::ceil(rect.Top);
}

ComPtr<ID2D1Factory1> DX::GetD2DFactoryCore() {
	if(!_d2dFactory) {
		D2D1_FACTORY_OPTIONS options;
		ZeroMemory(&options, sizeof(D2D1_FACTORY_OPTIONS));
		ThrowIfFailed(D2D1CreateFactory(
			D2D1_FACTORY_TYPE_MULTI_THREADED,
			__uuidof(ID2D1Factory1), 
			&options,
			&_d2dFactory));
	}
	return _d2dFactory;
}

ComPtr<IDWriteFactory> DX::GetDWFactoryCore() {
	if(!_dwFactory) {
		ThrowIfFailed(DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED, 
			__uuidof(IDWriteFactory), 
			&_dwFactory));
	}
	return _dwFactory;
};

ComPtr<IDWriteFontCollection> DX::GetSystemFontsCore() {
	if(!_systemFonts) {
		ThrowIfFailed(GetDWFactory()->GetSystemFontCollection(
			&_systemFonts,
			FALSE));
	}
	return _systemFonts;
}
