#include "pch.h"
#include "Box.h"

using namespace Prose::Layout;
using namespace Platform::Collections;

Box::Box(void) : _inlines(ref new Vector<Inline^>()) { }