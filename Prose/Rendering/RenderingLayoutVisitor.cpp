#include "pch.h"
#include "RenderingLayoutVisitor.h"
#include "DWRenderSurface.h"

using namespace Prose::Layout;
using namespace Prose::Rendering;

RenderingLayoutVisitor::RenderingLayoutVisitor(void) : _currentSurface(nullptr), _plan(ref new RenderingPlan()) { }

void RenderingLayoutVisitor::Visit(Box^ box) {
	// Create a surface to render to.
	_currentSurface = ref new DWRenderSurface();

	// Visit the children
	LayoutVisitor::Visit(box);

	// Add the surface to the plan
	_plan->Surfaces->Append(_currentSurface);
}

void RenderingLayoutVisitor::Visit(Span^ span) {
	auto range = ref new DWRenderRange(span->Text);

	_currentSurface->Ranges->Append(range);
}