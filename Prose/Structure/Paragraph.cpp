#include "pch.h"
#include "Paragraph.h"
#include "DocumentVisitor.h"

using namespace Prose::Structure;
using namespace Platform::Collections;

Paragraph::Paragraph(void) : _runs(ref new Vector<Run^>()) { }

void Paragraph::Accept(DocumentVisitor^ visitor) {
	visitor->Visit(this);
}

Paragraph^ Paragraph::Clone() {
	return ref new Paragraph();
}