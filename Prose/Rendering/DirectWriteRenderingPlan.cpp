#include "pch.h"
#include "DirectWriteRenderingPlan.h"

using namespace Prose::Rendering;

using namespace Windows::Foundation;

using namespace Windows::UI::Xaml;

Size DirectWriteRenderingPlan::RenderSize::get() {
	if(!_renderSizeCalculated) {
		float width = 0.0;
		float height = 0.0;
		for(UINT32 i = 0; i < Surfaces->Size; i++) {
			auto surface = Surfaces->GetAt(i);
			width = max(width, surface->Region.Width);
			height += surface->Region.Height;
		}
		_renderSize = SizeHelper::FromDimensions(width, height);
	}
	return _renderSize;
}