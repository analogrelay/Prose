#include "pch.h"
#include "Inline.h"
#include "..\TextFormat.h"

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media;

using namespace Prose;
using namespace Prose::Structure;

IMPLEMENT_DP(Inline, Windows::UI::Xaml::Media::FontFamily, FontFamily, nullptr);
IMPLEMENT_DP(Inline, double, FontSize, std::numeric_limits<double>::quiet_NaN());
IMPLEMENT_DP(Inline, Windows::UI::Xaml::Media::Brush, Foreground, nullptr);
IMPLEMENT_DP(Inline, Platform::Box<Windows::UI::Text::FontStretch>, FontStretch, Windows::UI::Text::FontStretch::Undefined);
IMPLEMENT_DP(Inline, Platform::Box<Windows::UI::Text::FontStyle>, FontStyle, Windows::UI::Text::FontStyle::Normal);
IMPLEMENT_DP(Inline, Windows::UI::Text::FontWeight, FontWeight, Windows::UI::Text::FontWeights::Normal);
IMPLEMENT_DP(Inline, bool, Strikethrough, false);
IMPLEMENT_DP(Inline, bool, Underline, false);

void Inline::CopyStyleTo(Inline^ other) {
	other->FontFamily = this->FontFamily;
	other->FontSize = this->FontSize;
	other->Foreground = this->Foreground;
	other->FontStretch = this->FontStretch;
	if(DPHasLocalValue(this, FontStyleProperty)) {
		other->FontStyle = this->FontStyle;
	}
	if(DPHasLocalValue(this, FontWeightProperty)) {
		other->FontWeight = FontWeight;
	}
	if(DPHasLocalValue(this, StrikethroughProperty)) {
		other->Strikethrough = Strikethrough;
	}
	if(DPHasLocalValue(this, UnderlineProperty)) {
		other->Underline = Underline;
	}
}

TextFormat^ Inline::CreateFormat(void) {
	TextFormat^ format = ref new TextFormat();
	format->FontSize = FontSize;
	format->FontFamily = FontFamily;
	format->Foreground = Foreground;
	format->FontStretch = FontStretch;
	if(DPHasLocalValue(this, FontStyleProperty)) {
		format->FontStyle = FontStyle;
	}
	if(DPHasLocalValue(this, FontWeightProperty)) {
		format->FontWeight = FontWeight;
	}
	if(DPHasLocalValue(this, StrikethroughProperty)) {
		format->Strikethrough = Strikethrough;
	}
	if(DPHasLocalValue(this, UnderlineProperty)) {
		format->Underline = Underline;
	}
	return format;
}