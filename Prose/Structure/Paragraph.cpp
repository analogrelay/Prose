#include "pch.h"
#include "Paragraph.h"

using namespace Prose::Structure;
using namespace Platform::Collections;

Paragraph::Paragraph(void) : _runs(ref new Vector<Run^>()) { }