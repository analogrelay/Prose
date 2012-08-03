#include "pch.h"
#include "DocumentNode.h"

using namespace Prose;
using namespace Prose::Controls;

using namespace Platform;

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Text;

DependencyProperty^ DocumentNode::_FontFamilyProperty = RegisterDP(L"FontFamily", FontFamily::typeid, DocumentNode::typeid);
DependencyProperty^ DocumentNode::_ForegroundProperty = RegisterDP(L"Foreground", Brush::typeid, DocumentNode::typeid);
DependencyProperty^ DocumentNode::_FontStretchProperty = RegisterDP(L"FontStretch", Box<::FontStretch>::typeid, DocumentNode::typeid);
DependencyProperty^ DocumentNode::_FontSizeProperty = RegisterDP(L"FontSize", double::typeid, DocumentNode::typeid);
DependencyProperty^ DocumentNode::_FontStyleProperty = RegisterDP(L"FontStyle", Box<::FontStyle>::typeid, DocumentNode::typeid);
DependencyProperty^ DocumentNode::_FontWeightProperty = RegisterDP(L"FontWeight", FontWeight::typeid, DocumentNode::typeid);
DependencyProperty^ DocumentNode::_HasStrikethroughProperty = RegisterDP(L"HasStrikethrough", bool::typeid, DocumentNode::typeid);
DependencyProperty^ DocumentNode::_HasUnderlineProperty = RegisterDP(L"HasUnderline", bool::typeid, DocumentNode::typeid);

TextFormat^ DocumentNode::CreateFormat() {
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