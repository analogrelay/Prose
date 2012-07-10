#include "pch.h"
#include "Inline.h"
#include "..\TextFormat.h"

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media;

using namespace Prose;
using namespace Prose::Structure;

void Inline::CopyStyleTo(Inline^ other) {
	other->FontFamily = this->FontFamily;
	other->FontSize = this->FontSize;
	other->Foreground = this->Foreground;
	other->FontStretch = this->FontStretch;
	if(this->IsFontStyleSet) {
		other->FontStyle = this->FontStyle;
	}
}

TextFormat^ Inline::CreateFormat(void) {
	TextFormat^ format = ref new TextFormat();
	format->FontSize = FontSize;
	format->FontFamily = FontFamily;
	format->Foreground = Foreground;
	format->FontStretch = FontStretch;
	if(this->IsFontStyleSet) {
		format->FontStyle = FontStyle;
	}
	return format;
}