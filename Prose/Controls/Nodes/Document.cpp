#include "pch.h"
#include "Document.h"

using namespace Prose::Structure;
using namespace Prose::Controls;

using namespace Platform::Collections;

Document::Document() : _children(ref new Vector<BlockNode^>()) { }

StructureTree^ Document::CreateStructureTree() {
	// Create a tree
	auto tree = ref new StructureTree();

	// Set it's format
	tree->Format = CreateFormat();

	// Add nodes for the children
	for(auto child : Children) {
		auto node = child->ConstructStructureNode();
		if(node) {
			tree->Blocks->Append(node);
		}
	}

	// Return the tree
	return tree;
}