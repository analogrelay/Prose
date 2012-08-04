#include "pch.h"
#include "BaseNodes.h"

using namespace Prose;
using namespace Prose::Controls;

using namespace Platform;

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Text;

DependencyProperty^ Stylable::_FontFamilyProperty = RegisterDP(L"FontFamily", FontFamily::typeid, Stylable::typeid);
DependencyProperty^ Stylable::_ForegroundProperty = RegisterDP(L"Foreground", Brush::typeid, Stylable::typeid);
DependencyProperty^ Stylable::_FontStretchProperty = RegisterDP(L"FontStretch", Box<::FontStretch>::typeid, Stylable::typeid, ::FontStretch::Undefined);
DependencyProperty^ Stylable::_FontSizeProperty = RegisterDP(L"FontSize", double::typeid, Stylable::typeid, std::numeric_limits<double>::quiet_NaN());
DependencyProperty^ Stylable::_FontStyleProperty = RegisterDP(L"FontStyle", Box<::FontStyle>::typeid, Stylable::typeid, ::FontStyle::Normal);
DependencyProperty^ Stylable::_FontWeightProperty = RegisterDP(L"FontWeight", FontWeight::typeid, Stylable::typeid, ::FontWeights::Normal);
DependencyProperty^ Stylable::_HasStrikethroughProperty = RegisterDP(L"HasStrikethrough", bool::typeid, Stylable::typeid, false);
DependencyProperty^ Stylable::_HasUnderlineProperty = RegisterDP(L"HasUnderline", bool::typeid, Stylable::typeid, false);
DependencyProperty^ Stylable::_ParentStyleProperty = RegisterDP(L"ParentStyle", TextStyle::typeid, Stylable::typeid);

TextFormat^ Stylable::CreateFormat() {
	auto source = this;
	if(ParentStyle) {
		source = Stylable::Merge(ParentStyle, this);
	}
	auto format = ref new TextFormat();
	format->FontFamily = source->FontFamily;
	format->Foreground = source->Foreground;
	format->FontStretch = source->FontStretch;
	if(DPHasLocalValue(this, FontSizeProperty)) {
		format->FontSize = source->FontSize;
	}
	if(DPHasLocalValue(this, FontStyleProperty)) {
		format->FontStyle = source->FontStyle;
	}
	if(DPHasLocalValue(this, FontWeightProperty)) {
		format->FontWeight = source->FontWeight;
	}
	if(DPHasLocalValue(this, HasStrikethroughProperty)) {
		format->HasStrikethrough = source->HasStrikethrough;
	}
	if(DPHasLocalValue(this, HasUnderlineProperty)) {
		format->HasUnderline = source->HasUnderline;
	}
	return format;
}

TextStyle^ Stylable::Merge(Stylable^ general, Stylable^ specific) {
	auto newStyle = ref new TextStyle();
#define MERGENL(PropertyName) if(!::isnull(specific-> ## PropertyName)) { newStyle-> ## PropertyName = specific-> ## PropertyName; } else { newStyle-> ## PropertyName = general-> ## PropertyName; }
#define MERGEDP(PropertyName) if(DPHasLocalValue(specific, PropertyName ## Property)) { newStyle-> ## PropertyName = specific-> ## PropertyName; } else { newStyle-> ## PropertyName = general-> ## PropertyName; }
	MERGENL(FontFamily);
	MERGENL(Foreground);
	MERGENL(FontStretch);
	MERGEDP(FontSize);
	MERGEDP(FontStyle);
	MERGEDP(FontWeight);
	MERGEDP(HasStrikethrough);
	MERGEDP(HasUnderline);
	return newStyle;
}