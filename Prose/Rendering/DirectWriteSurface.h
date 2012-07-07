#pragma once

#include "..\Layout\LayoutBox.h"

namespace Prose {
	namespace Rendering {
		private ref class DirectWriteSurface {
		internal:
			property Windows::Foundation::Rect Region {
				Windows::Foundation::Rect get() { return _region; }
			};

			property DWRITE_TEXT_METRICS Metrics {
				DWRITE_TEXT_METRICS get() { return _metrics; }
			}

			property Microsoft::WRL::ComPtr<IDWriteTextLayout> Layout {
				Microsoft::WRL::ComPtr<IDWriteTextLayout> get() { return _layout; }
			};

			property Prose::Layout::LayoutBox^ Box {
				Prose::Layout::LayoutBox^ get() { return _box; }
			}

			DirectWriteSurface(Windows::Foundation::Rect region, Microsoft::WRL::ComPtr<IDWriteTextLayout> layout, DWRITE_TEXT_METRICS metrics, Prose::Layout::LayoutBox^ box) : _region(region), _layout(layout), _metrics(metrics), _box(box) { };

		private:
			Prose::Layout::LayoutBox^ _box;
			DWRITE_TEXT_METRICS _metrics;
			Microsoft::WRL::ComPtr<IDWriteTextLayout> _layout;
			Windows::Foundation::Rect _region;
		};
	}
}

