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
	for(auto node : tree->Blocks) {
		node->Accept(this);
	}
}

void StructureVisitor::Visit(Block^ block) {
	Visit(static_cast<StructureNode^>(block));
	for(auto node : block->Inlines) {
		node->Accept(this);
	}
}

void StructureVisitor::Visit(Span^ span) {
	Visit(static_cast<Inline^>(span));
	for each(Inline^ node in span->Inlines) {
		node->Accept(this);
	}
}

void StructureVisitor::Visit(Paragraph^ paragraph) {
	Visit(static_cast<Block^>(paragraph));
}

void StructureVisitor::Visit(Run^ run) {
	Visit(static_cast<Inline^>(run));
}

void StructureVisitor::Visit(Inline^ inl) {
	Visit(static_cast<StructureNode^>(inl));
}