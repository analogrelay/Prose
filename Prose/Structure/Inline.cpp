#include "pch.h"
#include "Inline.h"

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media;

using namespace Prose::Structure;

void Inline::CopyStyleTo(Inline^ other) {
	other->FontFamily = this->FontFamily;
	other->FontSize = this->FontSize;
}