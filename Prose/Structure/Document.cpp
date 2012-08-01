#include "pch.h"
#include "Document.h"
#include "DocumentVisitor.h"
#include "ChildNodeCollection.h"

using namespace Platform::Collections;

using namespace Prose;
using namespace Prose::Structure;

Document::Document(void) : _paragraphs(ref new ChildNodeCollection<IParagraph^, IDocumentNode^>(this)) {}

void Document::Accept(IDocumentVisitor^ visitor) {
	visitor->Visit(static_cast<IDocument^>(this));
}
