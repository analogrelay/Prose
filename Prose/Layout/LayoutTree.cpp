#include "pch.h"
#include "LayoutTree.h"
#include "LayoutVisitor.h"

using namespace Platform::Collections;
using namespace Prose::Layout;

using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;

LayoutTree::LayoutTree(void) : _boxes(ref new Vector<LayoutBox^>()) {}

void LayoutTree::Accept(LayoutVisitor^ visitor) { visitor->Visit(this); }

Windows::Foundation::Size LayoutTree::Measure() {
	float height = 0;
	float width = 0;
	for each(auto box in Boxes) {
		height += box->Metrics->LayoutBounds.Height;
		width = max(box->Metrics->LayoutBounds.Width, width);
	}
	return SizeHelper::FromDimensions(width, height);
}

LayoutPointer^ LayoutTree::HitTest(Point point) {
	// Find a box that contains the point
	for each(auto box in Boxes) {
		if(box->Metrics->LayoutBounds.Contains(point)) {
			return box->HitTest(point);
		}
	}

	// No match
	return nullptr;
}