#include "pch.h"
#include "LayoutBox.h"
#include "LayoutVisitor.h"

using namespace Prose;
using namespace Prose::Layout;
using namespace Prose::Structure;
using namespace Platform::Collections;

LayoutBox::LayoutBox(void) : _metrics(nullptr) { }

void LayoutBox::Accept(LayoutVisitor^ visitor) { visitor->Visit(this); }