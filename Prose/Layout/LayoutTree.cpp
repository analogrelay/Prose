#include "pch.h"
#include "LayoutTree.h"
#include "LayoutVisitor.h"

using namespace Platform::Collections;
using namespace Prose::Layout;

LayoutTree::LayoutTree(void) : _boxes(ref new Vector<Box^>()) {}

void LayoutTree::Accept(LayoutVisitor^ visitor) { visitor->Visit(this); }