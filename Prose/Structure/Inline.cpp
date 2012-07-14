#include "pch.h"
#include "Inline.h"
#include "DocumentVisitor.h"
#include "..\TextFormat.h"

using namespace Windows::UI::Text;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media;

using namespace Prose;
using namespace Prose::Events;
using namespace Prose::Structure;

using namespace Platform;

DependencyProperty^ Inline::_FontFamilyProperty = RegisterDP("FontFamily", FontFamily::typeid, Inline::typeid, ref new PropertyChangedCallback(&Inline::FormatPropertyChanged));
DependencyProperty^ Inline::_FontSizeProperty = RegisterDP("FontSize", double::typeid, Inline::typeid, std::numeric_limits<double>::quiet_NaN(), ref new PropertyChangedCallback(&Inline::FormatPropertyChanged));
DependencyProperty^ Inline::_ForegroundProperty = RegisterDP("Foreground", Brush::typeid, Inline::typeid, ref new PropertyChangedCallback(&Inline::FormatPropertyChanged));
DependencyProperty^ Inline::_FontStretchProperty = RegisterDP("FontStretch", Box<Windows::UI::Text::FontStretch>::typeid, Inline::typeid, Windows::UI::Text::FontStretch::Undefined, ref new PropertyChangedCallback(&Inline::FormatPropertyChanged));
DependencyProperty^ Inline::_FontStyleProperty = RegisterDP("FontStyle", Box<Windows::UI::Text::FontStyle>::typeid, Inline::typeid, Windows::UI::Text::FontStyle::Normal, ref new PropertyChangedCallback(&Inline::FormatPropertyChanged));
DependencyProperty^ Inline::_FontWeightProperty = RegisterDP("FontWeight", FontWeight::typeid, Inline::typeid, FontWeights::Normal, ref new PropertyChangedCallback(&Inline::FormatPropertyChanged));
DependencyProperty^ Inline::_HasStrikethroughProperty = RegisterDP("HasStrikethrough", bool::typeid, Inline::typeid, false, ref new PropertyChangedCallback(&Inline::FormatPropertyChanged));
DependencyProperty^ Inline::_HasUnderlineProperty = RegisterDP("HasUnderlineProperty", bool::typeid, Inline::typeid, false, ref new PropertyChangedCallback(&Inline::FormatPropertyChanged));

void Inline::CopyStyleTo(IInline^ other) {
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
	if(DPHasLocalValue(this, HasStrikethroughProperty)) {
		other->HasStrikethrough = HasStrikethrough;
	}
	if(DPHasLocalValue(this, HasUnderlineProperty)) {
		other->HasUnderline = HasUnderline;
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
	if(DPHasLocalValue(this, HasStrikethroughProperty)) {
		format->HasStrikethrough = HasStrikethrough;
	}
	if(DPHasLocalValue(this, HasUnderlineProperty)) {
		format->HasUnderline = HasUnderline;
	}
	return format;
}

void Inline::Accept(IDocumentVisitor^ visitor) {
	visitor->Visit(this);
}

void Inline::FormatPropertyChanged(
	DependencyObject^ sender, 
	DependencyPropertyChangedEventArgs^ args) {
	
	Inline^ inl = safe_cast<Inline^>(sender);
	inl->InvalidateFormat();
}

void Inline::InvalidateFormat() {
	Invalidated(this, ref new CustomRoutedEventArgs(this));
}