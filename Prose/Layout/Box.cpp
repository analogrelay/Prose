#include "pch.h"
#include "Box.h"
#include "LayoutVisitor.h"

using namespace Prose;
using namespace Prose::Layout;
using namespace Prose::Structure;
using namespace Platform::Collections;

Box::Box(void) : _spans(ref new Vector<Span^>()), _metrics(nullptr) { }

void Box::Accept(LayoutVisitor^ visitor) { visitor->Visit(this); }