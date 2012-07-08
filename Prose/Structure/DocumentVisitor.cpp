#include "pch.h"
#include "DocumentVisitor.h"

using namespace Prose::Structure;

using namespace Windows::Foundation::Collections;

void DocumentVisitor::Visit(Document^ document) {
	for each(Paragraph^ node in document->Paragraphs) {
		node->Accept(this);
	}
}

void DocumentVisitor::Visit(Paragraph^ paragraph) {
	for each(Inline^ node in paragraph->Inlines) {
		node->Accept(this);
	}
}

void DocumentVisitor::Visit(Run^ run) {
}