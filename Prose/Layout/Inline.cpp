#include "pch.h"
#include "Inline.h"

using namespace Prose::Layout;

Inline::Inline(void) {}
Inline::Inline(Platform::String^ text) {
	Text = text;
}