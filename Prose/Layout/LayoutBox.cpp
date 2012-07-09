#include "pch.h"
#include "LayoutBox.h"
#include "LayoutVisitor.h"

using namespace Prose;
using namespace Prose::Layout;
using namespace Prose::Structure;
using namespace Platform::Collections;

LayoutBox::LayoutBox(void) : _metrics(nullptr), _margin(0) { }
LayoutBox::LayoutBox(Windows::UI::Xaml::Thickness margin) : _metrics(nullptr), _margin(margin) { }

void LayoutBox::Accept(LayoutVisitor^ visitor) { visitor->Visit(this); }