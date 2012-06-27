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

			virtual property Windows::Foundation::Point Origin {
				Windows::Foundation::Point get() { return _origin; }
			}

		internal:
			DWLayoutMetrics(Microsoft::WRL::ComPtr<IDWriteTextLayout> layout, Windows::Foundation::Point origin, Windows::Foundation::Size size);

			property Microsoft::WRL::ComPtr<IDWriteTextLayout> Layout {
				Microsoft::WRL::ComPtr<IDWriteTextLayout> get() { return _layout; }
			};
		private:
			Microsoft::WRL::ComPtr<IDWriteTextLayout> _layout;
			Windows::Foundation::Point _origin;
			Windows::Foundation::Size _size;
		};
	}
}