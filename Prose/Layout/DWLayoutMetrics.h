#pragma once
#include "ILayoutMetrics.h"

namespace Prose {
	namespace Layout {
		private ref class DWLayoutMetrics sealed :
			public ILayoutMetrics
		{
		public:
			virtual property UINT32 LineCount {
				UINT32 get() { return _metrics.lineCount; }
			}

			virtual property Windows::Foundation::Size Size {
				Windows::Foundation::Size get() { return _size; }
			};

			virtual property Windows::Foundation::Point Origin {
				Windows::Foundation::Point get() { return _origin; }
			}

		internal:
			DWLayoutMetrics(Microsoft::WRL::ComPtr<IDWriteTextLayout> layout, DWRITE_TEXT_METRICS metrics, Windows::Foundation::Point origin, Windows::Foundation::Size size);

			property Microsoft::WRL::ComPtr<IDWriteTextLayout> Layout {
				Microsoft::WRL::ComPtr<IDWriteTextLayout> get() { return _layout; }
			};
		private:
			Microsoft::WRL::ComPtr<IDWriteTextLayout> _layout;
			Windows::Foundation::Point _origin;
			Windows::Foundation::Size _size;
			DWRITE_TEXT_METRICS _metrics;
		};
	}
}