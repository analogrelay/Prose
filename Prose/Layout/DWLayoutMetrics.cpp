#include "pch.h"
#include "DWLayoutMetrics.h"

using namespace Prose;
using namespace Prose::Layout;

using namespace Windows::Foundation;


INT32 DWLayoutMetrics::HitTest(Point point) {
	BOOL isTrailing;
	BOOL isInside;
	DWRITE_HIT_TEST_METRICS metrics;
	ThrowIfFailed(Layout->HitTestPoint(
		point.X, 
		point.Y,
		&isTrailing,
		&isInside,
		&metrics));

	// Did we even hit the text?
	if(!isInside) {
		return -1;
	}

	// We did, where?
	return metrics.textPosition;
}