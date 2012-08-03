#include "pch.h"
#include "Paragraph.h"
#include "Structure\ParagraphNode.h"

using namespace Prose::Controls;
using namespace Prose::Structure;

using namespace Platform::Collections;

Paragraph::Paragraph() : _children(ref new Vector<Inline^>()) { }

BlockNode^ Paragraph::ConstructStructureNode() {
	// Construct a paragraph
	auto para = ref new ParagraphNode();
	para->Format = CreateFormat();

	// Convert children
	for(auto child : Children) {
		auto node = child->ConstructStructureNode();
		if(node) {
			para->Inlines->Append(node);
		}
	}
	return para;
}