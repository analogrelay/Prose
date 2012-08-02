#include "pch.h"
#include "StructureTree.h"
#include "StructureVisitor.h"
#include "ChildNodeCollection.h"

using namespace Platform::Collections;

using namespace Prose;
using namespace Prose::Structure;

StructureTree::StructureTree(void) : _paragraphs(ref new Vector<Paragraph^>()) {}

void StructureTree::Accept(StructureVisitor^ visitor) {
	visitor->Visit(static_cast<StructureTree^>(this));
}
