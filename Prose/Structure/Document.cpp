#include "pch.h"
#include "Document.h"
#include "DocumentVisitor.h"
#include "ChildNodeCollection.h"

using namespace Platform::Collections;

using namespace Prose;
using namespace Prose::Structure;

Document::Document(void) : _paragraphs(ref new ChildNodeCollection<Paragraph^, DocumentNode^>(this)) {}

void Document::Accept(DocumentVisitor^ visitor) {
	visitor->Visit(this);
}
