#include "pch.h"
#include "StructureVisitor.h"
#include "StructureTree.h"
#include "Paragraph.h"
#include "Run.h"
#include "Span.h"

using namespace Prose::Structure;

using namespace Windows::Foundation::Collections;

void StructureVisitor::Visit(StructureNode^ node) {
}

void StructureVisitor::Visit(StructureTree^ tree) {
	Visit(static_cast<StructureNode^>(tree));
	for each(Paragraph^ node in tree->Paragraphs) {
		node->Accept(this);
	}
}

void StructureVisitor::Visit(Paragraph^ paragraph) {
	Visit(static_cast<StructureNode^>(paragraph));
	for each(Inline^ node in paragraph->Inlines) {
		node->Accept(this);
	}
}

void StructureVisitor::Visit(SpanBase^ span) {
	Visit(static_cast<Inline^>(span));
	for each(Inline^ node in span->Inlines) {
		node->Accept(this);
	}
}

void StructureVisitor::Visit(Run^ run) {
	Visit(static_cast<Inline^>(run));
}

void StructureVisitor::Visit(Inline^ inl) {
	Visit(static_cast<StructureNode^>(inl));
}