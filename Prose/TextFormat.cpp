#include "pch.h"
#include "TextFormat.h"

using namespace Prose;

using namespace Microsoft::WRL;

using namespace Windows::UI;
using namespace Windows::UI::Text;
using namespace Windows::UI::Xaml::Media;

IMPLEMENT_DP(TextFormat, Windows::UI::Xaml::Media::FontFamily, FontFamily, nullptr);
IMPLEMENT_DP(TextFormat, double, FontSize, std::numeric_limits<double>::quiet_NaN());
IMPLEMENT_DP(TextFormat, Windows::UI::Xaml::Media::Brush, Foreground, nullptr);
IMPLEMENT_DP(TextFormat, Platform::Box<Windows::UI::Text::FontStretch>, FontStretch, Windows::UI::Text::FontStretch::Undefined);
IMPLEMENT_DP(TextFormat, Platform::Box<Windows::UI::Text::FontStyle>, FontStyle, Windows::UI::Text::FontStyle::Normal);
IMPLEMENT_DP(TextFormat, Windows::UI::Text::FontWeight, FontWeight, Windows::UI::Text::FontWeights::Normal);
IMPLEMENT_DP(TextFormat, bool, Strikethrough, false);
IMPLEMENT_DP(TextFormat, bool, Underline, false);

DWRITE_FONT_STRETCH stretchTable[] = {
	DWRITE_FONT_STRETCH_UNDEFINED,
	DWRITE_FONT_STRETCH_ULTRA_CONDENSED,
	DWRITE_FONT_STRETCH_EXTRA_CONDENSED,
	DWRITE_FONT_STRETCH_CONDENSED,
	DWRITE_FONT_STRETCH_SEMI_CONDENSED,
	DWRITE_FONT_STRETCH_NORMAL, // DWRITE_FONT_STRETCH_MEDIUM == DWRITE_FONT_STRETCH_NORMAL
	DWRITE_FONT_STRETCH_SEMI_EXPANDED,
	DWRITE_FONT_STRETCH_EXPANDED,
	DWRITE_FONT_STRETCH_EXTRA_EXPANDED,
	DWRITE_FONT_STRETCH_ULTRA_EXPANDED  
};

DWRITE_FONT_STYLE styleTable[] = {
	DWRITE_FONT_STYLE_NORMAL,
	DWRITE_FONT_STYLE_OBLIQUE,
	DWRITE_FONT_STYLE_ITALIC
};

void TextFormat::ApplyDeviceIndependent(ComPtr<IDWriteTextLayout> layout, UINT32 offset, UINT32 length) {
	DWRITE_TEXT_RANGE range;
	range.startPosition = offset;
	range.length = length;

	if(!_isnan(FontSize)) {
		ThrowIfFailed(layout->SetFontSize((float)FontSize, range));
	}
	if(FontFamily) {
		ThrowIfFailed(layout->SetFontFamilyName(FontFamily->Source->Data(), range));
	}
	if(FontStretch != Text::FontStretch::Undefined) {
		INT32 stretchIndex = (INT32)FontStretch;
		if(stretchIndex >= 0 && stretchIndex < ARRAYSIZE(stretchTable)) {
			ThrowIfFailed(layout->SetFontStretch(stretchTable[stretchIndex], range));
		}
	}

	INT32 styleIndex = (INT32)FontStyle;
	if(styleIndex >= 0 && styleIndex < ARRAYSIZE(styleTable)) {
		ThrowIfFailed(layout->SetFontStyle(styleTable[styleIndex], range));
	}

	UINT16 weight = (UINT16)FontWeight.Weight;
	if(weight >= 1 && weight <= 999) {
		ThrowIfFailed(layout->SetFontWeight((DWRITE_FONT_WEIGHT)weight, range));
	}

	ThrowIfFailed(layout->SetStrikethrough(Strikethrough, range));
	ThrowIfFailed(layout->SetUnderline(Underline, range));
}

void TextFormat::ApplyDeviceDependent(ComPtr<ID2D1RenderTarget> target, ComPtr<IDWriteTextLayout> layout, UINT32 offset, UINT32 length) {
	DWRITE_TEXT_RANGE range;
	range.startPosition = offset;
	range.length = length;

	if(Foreground) {
		ComPtr<ID2D1Brush> brush = ConvertBrush(target, Foreground);
		ThrowIfFailed(layout->SetDrawingEffect(brush.Get(), range));
	}
}

ComPtr<ID2D1Brush> TextFormat::ConvertBrush(ComPtr<ID2D1RenderTarget> target, Brush^ xamlBrush) {
	ComPtr<ID2D1Brush> brush;
	auto type = xamlBrush->GetType();
	if(type->FullName->Equals(SolidColorBrush::typeid->FullName)) {
		SolidColorBrush^ solidBrush = safe_cast<SolidColorBrush^>(xamlBrush);
		Color color = solidBrush->Color;
		ThrowIfFailed(target->CreateSolidColorBrush(
			DX::ToDXColor(color),
			DX::ToDXBrushProperties(xamlBrush),
			(reinterpret_cast<ID2D1SolidColorBrush**>(brush.GetAddressOf()))));
	}
	else if(type->FullName->Equals(LinearGradientBrush::typeid->FullName)) {
		// TODO: Handle MappingMode

		LinearGradientBrush^ lgBrush = safe_cast<LinearGradientBrush^>(xamlBrush);

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