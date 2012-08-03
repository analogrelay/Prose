#include "pch.h"
#include "TextFormat.h"

using namespace Prose;

using namespace Platform;
using namespace Microsoft::WRL;

using namespace Windows::UI;
using namespace Windows::UI::Text;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media;

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

TextFormat^ TextFormat::MergeWith(TextFormat^ overridingCopy) {
	TextFormat^ newFormat = ref new TextFormat();

#define MERGE(Property) if(!isnull(overridingCopy-> ## Property)) { newFormat-> ## Property = overridingCopy-> ## Property; } else { newFormat-> ## Property = this-> ## Property; }
	MERGE(FontSize);
	MERGE(FontFamily);
	MERGE(FontStretch);
	MERGE(Foreground);
	MERGE(FontStyle);
	MERGE(FontWeight);
	MERGE(HasStrikethrough);
	MERGE(HasUnderline);

	return newFormat;
}

TextFormat^ TextFormat::Clone(void) {
	auto clone = ref new TextFormat();
	clone->FontFamily = FontFamily;
	clone->FontSize = FontSize;
	clone->Foreground = Foreground;
	clone->FontStretch = FontStretch;
	clone->FontStyle = FontStyle;
	clone->FontWeight = FontWeight;
	clone->HasStrikethrough = HasStrikethrough;
	clone->HasUnderline = HasUnderline;	
	return clone;
}

TextFormat^ TextFormat::MergeSequence(std::deque<TextFormat^> const& list) {
	TextFormat^ current = nullptr;
	for(auto format : list) {
		if(!current) {
			current = format;
		} else {
			current = current->MergeWith(format);
		}
	}
	return current;
}

bool TextFormat::AnythingSet::get() {
	return 
		!isnull(FontFamily) ||
		!isnull(FontSize) ||
		!isnull(Foreground) ||
		!isnull(FontStretch) ||
		!isnull(FontStyle) ||
		!isnull(FontWeight) ||
		!isnull(HasStrikethrough) ||
		!isnull(HasUnderline);
}

void TextFormat::ApplyDeviceIndependent(ComPtr<IDWriteTextLayout> layout, UINT32 offset, UINT32 length) {
	DWRITE_TEXT_RANGE range;
	range.startPosition = offset;
	range.length = length;

	if(FontSize != nullptr) {
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

	if(FontStyle != nullptr) {
		INT32 styleIndex = (INT32)FontStyle.GetValue();
		if(styleIndex >= 0 && styleIndex < ARRAYSIZE(styleTable)) {
			ThrowIfFailed(layout->SetFontStyle(styleTable[styleIndex], range));
		}
	}

	if(FontWeight != nullptr) {
		UINT16 weight = (UINT16)FontWeight.GetValue().Weight;
		if(weight >= 1 && weight <= 999) {
			ThrowIfFailed(layout->SetFontWeight((DWRITE_FONT_WEIGHT)weight, range));
		}
	}

	if(HasStrikethrough != nullptr) {
		ThrowIfFailed(layout->SetStrikethrough(HasStrikethrough, range));
	}
	if(HasUnderline != nullptr) {
		ThrowIfFailed(layout->SetUnderline(HasUnderline, range));
	}
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