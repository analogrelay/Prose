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
			// Clamp the point into the range owned by this box
			auto x = point.X - box->Metrics->RenderArea.Left;
			auto y = point.Y - box->Metrics->RenderArea.Top;
			if(x >= 0 && y >= 0) {
				auto clamped = PointHelper::FromCoordinates(x, y);
				return box->HitTest(clamped);
			}
		}
	}

	// No match
	return nullptr;
}