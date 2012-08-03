#include "pch.h"
#include "ParagraphNode.h"
#include "StructureVisitor.h"
#include "RunNode.h"
#include "ChildNodeCollection.h"

using namespace Prose;
using namespace Prose::Structure;
using namespace Platform::Collections;

ParagraphNode::ParagraphNode(void) { }

BlockNode^ ParagraphNode::Clone() {
	return ref new ParagraphNode();
}

void ParagraphNode::Accept(StructureVisitor^ visitor) {
	visitor->Visit(this);
}