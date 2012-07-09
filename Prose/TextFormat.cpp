#include "pch.h"
#include "TextFormat.h"

using namespace Prose;

using namespace Microsoft::WRL;

using namespace Windows::UI;
using namespace Windows::UI::Xaml::Media;

void TextFormat::ApplyDeviceIndependent(ComPtr<IDWriteTextLayout> layout, UINT32 offset, UINT32 length) {
	DWRITE_TEXT_RANGE range;
	range.startPosition = offset;
	range.length = length;

	if(!_isnan(FontSize)) {
		layout->SetFontSize((float)FontSize, range);
	}
	if(FontFamily) {
		layout->SetFontFamilyName(FontFamily->Source->Data(), range);
	}
}

void TextFormat::ApplyDeviceDependent(ComPtr<ID2D1RenderTarget> target, ComPtr<IDWriteTextLayout> layout, UINT32 offset, UINT32 length) {
	DWRITE_TEXT_RANGE range;
	range.startPosition = offset;
	range.length = length;

	if(Foreground) {
		ComPtr<ID2D1Brush> brush = ConvertBrush(target, Foreground);
		layout->SetDrawingEffect(brush.Get(), range);
	}
}

ComPtr<ID2D1Brush> TextFormat::ConvertBrush(ComPtr<ID2D1RenderTarget> target, Brush^ xamlBrush) {
	ComPtr<ID2D1Brush> brush;
	if(xamlBrush->GetType() == SolidColorBrush::typeid) {
		SolidColorBrush^ solidBrush = reinterpret_cast<SolidColorBrush^>(xamlBrush);
		Color color = solidBrush->Color;
		ThrowIfFailed(target->CreateSolidColorBrush(
			DX::ToDXColor(color),
			DX::ToDXBrushProperties(xamlBrush),
			(reinterpret_cast<ID2D1SolidColorBrush**>(brush.GetAddressOf()))));
	}
	else if(xamlBrush->GetType() == LinearGradientBrush::typeid) {
		// TODO: Handle MappingMode

		LinearGradientBrush^ lgBrush = reinterpret_cast<LinearGradientBrush^>(xamlBrush);
		
		D2D1_GRADIENT_STOP* stops = new D2D1_GRADIENT_STOP[lgBrush->GradientStops->Size];
		for(UINT32 i = 0; i < lgBrush->GradientStops->Size; i++) {
			auto stop = lgBrush->GradientStops->GetAt(i);
			stops[i].color = DX::ToDXColor(stop->Color);
			stops[i].position = (float)stop->Offset;
		}

		ComPtr<ID2D1GradientStopCollection> stopCollection;
		ThrowIfFailed(target->CreateGradientStopCollection(
			stops,
			lgBrush->GradientStops->Size,
			lgBrush->ColorInterpolationMode == ColorInterpolationMode::SRgbLinearInterpolation ? D2D1_GAMMA_2_2 : D2D1_GAMMA_1_0,
			lgBrush->SpreadMethod == GradientSpreadMethod::Pad ? D2D1_EXTEND_MODE_CLAMP :
				(lgBrush->SpreadMethod == GradientSpreadMethod::Repeat ? D2D1_EXTEND_MODE_WRAP : D2D1_EXTEND_MODE_MIRROR),
			&stopCollection));
		ThrowIfFailed(target->CreateLinearGradientBrush(
			D2D1::LinearGradientBrushProperties(
				DX::ToDXPoint(lgBrush->StartPoint),
				DX::ToDXPoint(lgBrush->EndPoint)),				
			DX::ToDXBrushProperties(xamlBrush),
			stopCollection.Get(),
			(reinterpret_cast<ID2D1LinearGradientBrush**>(brush.GetAddressOf()))));
	}
	else {
		throw ref new Platform::InvalidArgumentException("The specified brush type is not supported. Only SolidColorBrush and LinearGradientBrush are supported at this time.");
	}
	return brush;
}