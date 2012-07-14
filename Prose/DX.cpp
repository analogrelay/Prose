#pragma once

#include "pch.h"
#include "DX.h"

using namespace Prose;

using namespace Windows::UI;
using namespace Windows::UI::Xaml::Media;
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

D2D1_COLOR_F DX::ToDXColor(Color winColor) {
	return D2D1::ColorF(
		((float)winColor.R / 255), 
		((float)winColor.G / 255), 
		((float)winColor.B / 255), 
		((float)winColor.A / 255));
}

D2D1_POINT_2F DX::ToDXPoint(Point winPoint) {
	return D2D1::Point2F(winPoint.X, winPoint.Y);
}

D2D1_BRUSH_PROPERTIES DX::ToDXBrushProperties(Brush^ winBrush) {
	// TODO: Handle Transform...
	return D2D1::BrushProperties((float)winBrush->Opacity);
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
