#include "pch.h"
#include "Helpers.h"

using namespace Prose;

using namespace Platform;

using namespace Windows::UI::Text;
using namespace Windows::UI::Xaml;

bool operator==(FontWeight left, FontWeight right) {
	return left.Weight == right.Weight;
};

bool operator!=(FontWeight left, FontWeight right) {
	return left.Weight != right.Weight;
};

Windows::UI::Xaml::DependencyProperty^ RegisterDPCore(
	String^ name,
	Type^ type,
	Type^ owner,
	PropertyMetadata^ meta) {
	return DependencyProperty::Register(name, type, owner, meta);
}

Windows::UI::Xaml::DependencyProperty^ Prose::RegisterDP(
	String^ name,
	Type^ type,
	Type^ owner) {
	return RegisterDPCore(name, type, owner, ref new PropertyMetadata(nullptr));
}

Windows::UI::Xaml::DependencyProperty^ Prose::RegisterDP(
	String^ name,
	Type^ type,
	Type^ owner,
	Object^ defaultValue) {
	return RegisterDPCore(name, type, owner, ref new PropertyMetadata(defaultValue));
}

Windows::UI::Xaml::DependencyProperty^ Prose::RegisterDP(
	String^ name,
	Type^ type,
	Type^ owner,
	PropertyChangedCallback^ changedCallback) {
	return RegisterDPCore(name, type, owner, ref new PropertyMetadata(nullptr, changedCallback));
}

Windows::UI::Xaml::DependencyProperty^ Prose::RegisterDP(
	String^ name,
	Type^ type,
	Type^ owner,
	Object^ defaultValue,
	PropertyChangedCallback^ changedCallback) {
	return RegisterDPCore(name, type, owner, ref new PropertyMetadata(defaultValue, changedCallback));
}

template<>
bool Prose::isnull<Windows::UI::Text::FontStretch>(Windows::UI::Text::FontStretch const& item) {
	return item == Windows::UI::Text::FontStretch::Undefined;
}