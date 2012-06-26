#include "pch.h"
#include "DWLayoutMetrics.h"

using namespace Prose::Layout;

using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;

DWLayoutMetrics::DWLayoutMetrics(ComPtr<IDWriteTextLayout> layout) : _layout(layout) {
	DWRITE_TEXT_METRICS metrics;
	layout->GetMetrics(&metrics);

	TextMetrics = metrics;
	_size = SizeHelper::FromDimensions(metrics.width, metrics.height);
}