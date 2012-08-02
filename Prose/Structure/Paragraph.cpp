#include "pch.h"
#include "Paragraph.h"
#include "StructureVisitor.h"
#include "Run.h"
#include "..\ChildNodeCollection.h"

using namespace Prose;
using namespace Prose::Structure;
using namespace Platform::Collections;

Paragraph::Paragraph(void) : _inlines(ref new Vector<Inline^>()) { }

void Paragraph::Accept(StructureVisitor^ visitor) {
	visitor->Visit(this);
}

Paragraph^ Paragraph::Clone() {
	return ref new Paragraph();
}

TextPointer^ Paragraph::OffsetToPointer(UINT32 offset) {
	UINT32 counter = 0;
	for(UINT32 i = 0; i < Inlines->Size; i++) {
		auto inlin = Inlines->GetAt(i);
		if((counter + inlin->Length) > offset) {
			// This is the node!
			return ref new TextPointer(
				this,
				inlin,
				i,
				offset - counter,
				offset);
		} else {
			// This isn't the node, advance the counter
			counter += inlin->Length;
		}
	}

	// Didn't find it :(
	return nullptr;
}