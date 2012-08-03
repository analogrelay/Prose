#include "pch.h"
#include "RenderingLayoutVisitor.h"
#include "DirectWriteSurface.h"
#include "Layout\DWLayoutMetrics.h"

using namespace Prose::Layout;
using namespace Prose::Rendering;

using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;

RenderingLayoutVisitor::RenderingLayoutVisitor(DirectWriteRenderer^ renderer) : _plan(ref new DirectWriteRenderingPlan(renderer)) { }

void RenderingLayoutVisitor::Visit(LayoutBox^ box) {
	// Create a surface to hold this box
	auto metrics = (safe_cast<DWLayoutMetrics^>(box->Metrics));
	DirectWriteSurface^ surface = ref new DirectWriteSurface(
		metrics->RenderArea,
		metrics->LayoutBounds,
		metrics->Layout,
		metrics->DWMetrics,
		box,
		metrics->FormattedRanges,
		metrics->TextLength);

	// Add it to the plan and we're done (for now... maybe more later ;))
	_plan->Surfaces->Append(surface);
}