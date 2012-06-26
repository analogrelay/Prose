#include "pch.h"
#include "Span.h"
#include "LayoutVisitor.h"

using namespace Prose;
using namespace Prose::Layout;

Span::Span(void) {}
Span::Span(Platform::String^ text) {
	Text = text;
}

void Span::Accept(LayoutVisitor^ visitor) { visitor->Visit(this); }