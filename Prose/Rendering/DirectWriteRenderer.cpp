#include "pch.h"
#include "DirectWriteRenderer.h"
#include "RenderingLayoutVisitor.h"

using namespace Prose::Rendering;
using namespace Prose::Layout;

DirectWriteRenderer::DirectWriteRenderer(void) {
}

RenderingPlan^ DirectWriteRenderer::PlanRendering(LayoutTree^ tree) {
	// Run the visitor
	RenderingLayoutVisitor^ visitor = ref new RenderingLayoutVisitor();
	tree->Accept(visitor);

	// Return the rendering plan
	return visitor->RenderingPlan;
}
