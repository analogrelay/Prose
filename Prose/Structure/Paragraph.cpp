#include "pch.h"
#include "Paragraph.h"
#include "StructureVisitor.h"
#include "Run.h"
#include "..\ChildNodeCollection.h"

using namespace Prose;
using namespace Prose::Structure;
using namespace Platform::Collections;

Paragraph::Paragraph(void) { }

Block^ Paragraph::Clone() {
	return ref new Paragraph();
}

void Paragraph::Accept(StructureVisitor^ visitor) {
	visitor->Visit(this);
}