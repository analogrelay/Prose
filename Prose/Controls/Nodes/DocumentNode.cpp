#include "pch.h"
#include "DocumentNode.h"

using namespace Prose;
using namespace Prose::Controls;

using namespace Platform;

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Text;

DependencyProperty^ StylableNode::_FontFamilyProperty = RegisterDP(L"FontFamily", FontFamily::typeid, StylableNode::typeid);
DependencyProperty^ StylableNode::_ForegroundProperty = RegisterDP(L"Foreground", Brush::typeid, StylableNode::typeid);
DependencyProperty^ StylableNode::_FontStretchProperty = RegisterDP(L"FontStretch", Box<::FontStretch>::typeid, StylableNode::typeid);
DependencyProperty^ StylableNode::_FontSizeProperty = RegisterDP(L"FontSize", double::typeid, StylableNode::typeid);
DependencyProperty^ StylableNode::_FontStyleProperty = RegisterDP(L"FontStyle", Box<::FontStyle>::typeid, StylableNode::typeid);
DependencyProperty^ StylableNode::_FontWeightProperty = RegisterDP(L"FontWeight", FontWeight::typeid, StylableNode::typeid);
DependencyProperty^ StylableNode::_HasStrikethroughProperty = RegisterDP(L"HasStrikethrough", bool::typeid, StylableNode::typeid);
DependencyProperty^ StylableNode::_HasUnderlineProperty = RegisterDP(L"HasUnderline", bool::typeid, StylableNode::typeid);

TextFormat^ StylableNode::CreateFormat() {
	auto format = ref new TextFormat();
	format->FontFamily = FontFamily;
	format->Foreground = Foreground;
	format->FontStretch = FontStretch;
	if(DPHasLocalValue(this, FontSizeProperty)) {
		format->FontSize = FontSize;
	}
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