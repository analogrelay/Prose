#include "pch.h"
#include "DocumentNode.h"

using namespace Prose;
using namespace Prose::Controls;

namespace WUX = Windows::UI::Xaml;
namespace WUT = Windows::UI::Text;

TextFormat^ DocumentNode::CreateFormat() {
	auto format = ref new TextFormat();
	format->FontFamily = _fontFamily;
	format->Foreground = _foreground;
	format->FontStretch = _fontStretch;
	format->FontSize = _fontSize;
	format->FontStyle = _fontStyle;
	format->FontWeight = _fontWeight;
	format->HasStrikethrough = _hasStrikethrough;
	format->HasUnderline = _hasUnderline;
	return format;
}

WUX::Media::FontFamily^ DocumentNode::FontFamily::get() {
	return _fontFamily;
}

void DocumentNode::FontFamily::set(WUX::Media::FontFamily^ value) {
	_fontFamily = value;
}

WUX::Media::Brush^ DocumentNode::Foreground::get() {
	return _foreground;
}

void DocumentNode::Foreground::set(WUX::Media::Brush^ value) {
	_foreground = value;
}

WUT::FontStretch DocumentNode::FontStretch::get() {
	return _fontStretch;
}

void DocumentNode::FontStretch::set(WUT::FontStretch value) {
	_fontStretch = value;
}

double DocumentNode::FontSize::get() {
	return _fontSize == nullptr ?
		std::numeric_limits<double>::quiet_NaN() :
		_fontSize;
}
void DocumentNode::FontSize::set(double value) {
	_fontSize = value;
}

WUT::FontStyle DocumentNode::FontStyle::get() {
	return _fontStyle == nullptr ?
		WUT::FontStyle::Normal :
		_fontStyle;
}

void DocumentNode::FontStyle::set(WUT::FontStyle value) {
	_fontStyle = value;
}

WUT::FontWeight DocumentNode::FontWeight::get() {
	return _fontWeight == nullptr ?
		WUT::FontWeights::Normal :
		_fontWeight;
}

void DocumentNode::FontWeight::set(WUT::FontWeight value) {
	_fontWeight = value;
}

bool DocumentNode::HasStrikethrough::get() {
	return _hasStrikethrough == nullptr ? false : _hasStrikethrough;
}

void DocumentNode::HasStrikethrough::set(bool value) {
	_hasStrikethrough = value;
}

bool DocumentNode::HasUnderline::get() {
	return _hasUnderline == nullptr ? false : _hasUnderline;
}

void DocumentNode::HasUnderline::set(bool value) {
	_hasUnderline = value;
}