#include "pch.h"
#include "RenderingLayoutVisitor.h"
#include "DirectWriteSurface.h"
#include "..\Layout\DWLayoutMetrics.h"

using namespace Prose::Layout;
using namespace Prose::Rendering;

using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;

RenderingLayoutVisitor::RenderingLayoutVisitor(void) : _plan(ref new DirectWriteRenderingPlan()) { }

void RenderingLayoutVisitor::Visit(Box^ box) {
	// Create a surface to hold this box
	/*DirectWriteSurface^ surface = ref new DirectWriteSurface(
		RectHelper::FromLocationAndSize(
			box->Metrics->Origin, 
			box->Metrics->Size),
		((DWLayoutMetrics^)box->Metrics)->Layout));*/

	// Add it to the plan and we're done (for now... maybe more later ;))
	/*_plan->Surfaces->Append(surface);*/
}

void RenderingLayoutVisitor::Visit(Span^ span) {
	
}