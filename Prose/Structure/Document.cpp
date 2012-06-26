#include "pch.h"
#include "Document.h"
#include "DocumentVisitor.h"

using namespace Platform::Collections;
using namespace Prose::Structure;

Document::Document(void) : _paragraphs(ref new Vector<Paragraph^>()) {}

void Document::Accept(DocumentVisitor^ visitor) {
	visitor->Visit(this);
}
