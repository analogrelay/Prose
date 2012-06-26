#pragma once
#include "ILayoutMetrics.h"

namespace Prose {
	namespace Layout {
		private ref class DWLayoutMetrics sealed :
			public ILayoutMetrics
		{
		public:
			virtual property Windows::Foundation::Size Size {
				Windows::Foundation::Size get() { return _size; }
			};

		internal:
			DWLayoutMetrics(Microsoft::WRL::ComPtr<IDWriteTextLayout> layout);

			property DWRITE_TEXT_METRICS TextMetrics;
			property Microsoft::WRL::ComPtr<IDWriteTextLayout> Layout {
				Microsoft::WRL::ComPtr<IDWriteTextLayout> get() { return _layout; }
			};
		private:
			Microsoft::WRL::ComPtr<IDWriteTextLayout> _layout;
			Windows::Foundation::Size _size;
		};
	}
}