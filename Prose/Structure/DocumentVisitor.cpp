#include "pch.h"
#include "DocumentVisitor.h"

using namespace Prose::Structure;

using namespace Windows::Foundation::Collections;

void DocumentVisitor::Visit(DocumentNode^ node) {
}

void DocumentVisitor::Visit(Document^ document) {
	Visit(static_cast<DocumentNode^>(document));
	for each(Paragraph^ node in document->Paragraphs) {
		node->Accept(this);
	}
}

void DocumentVisitor::Visit(Paragraph^ paragraph) {
	Visit(static_cast<DocumentNode^>(paragraph));
	for each(Inline^ node in paragraph->Inlines) {
		node->Accept(this);
	}
}

void DocumentVisitor::Visit(Span^ span) {
	Visit(static_cast<SpanBase^>(span));
}

void DocumentVisitor::Visit(SpanBase^ span) {
	Visit(static_cast<Inline^>(span));
	for each(Inline^ node in span->Inlines) {
		node->Accept(this);
	}
}

void DocumentVisitor::Visit(Run^ run) {
	Visit(static_cast<Inline^>(run));
}

void DocumentVisitor::Visit(Inline^ inl) {
	Visit(static_cast<DocumentNode^>(inl));
}