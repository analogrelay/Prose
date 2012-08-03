#include "pch.h"
#include "Paragraph.h"

using namespace Prose::Controls;

using namespace Platform::Collections;

Paragraph::Paragraph() : _children(ref new Vector<InlineNode^>()) { }