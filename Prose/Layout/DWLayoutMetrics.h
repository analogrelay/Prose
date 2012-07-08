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

			virtual property Windows::Foundation::Rect RenderArea {
				Windows::Foundation::Rect get() { return _renderArea; }
			}

			virtual property Windows::Foundation::Rect LayoutBounds {
				Windows::Foundation::Rect get() { return _layoutBounds; }
			}

			property Windows::UI::Xaml::Media::Brush^ Foreground {
				Windows::UI::Xaml::Media::Brush^ get() { return _foreground; }
				void set(Windows::UI::Xaml::Media::Brush^ value) { _foreground = value; }
			}

		internal:
			DWLayoutMetrics(Microsoft::WRL::ComPtr<IDWriteTextLayout> layout, DWRITE_TEXT_METRICS metrics, Windows::Foundation::Rect renderArea, Windows::Foundation::Rect layoutBounds) :
				_layout(layout), _metrics(metrics), _renderArea(renderArea), _layoutBounds(layoutBounds), _foreground(nullptr) {};

			property Microsoft::WRL::ComPtr<IDWriteTextLayout> Layout {
				Microsoft::WRL::ComPtr<IDWriteTextLayout> get() { return _layout; }
			};

			property DWRITE_TEXT_METRICS DWMetrics {
				DWRITE_TEXT_METRICS get() { return _metrics; }
			}
		private:
			Windows::UI::Xaml::Media::Brush^ _foreground;
			Microsoft::WRL::ComPtr<IDWriteTextLayout> _layout;
			Windows::Foundation::Rect _renderArea;
			Windows::Foundation::Rect _layoutBounds;
			DWRITE_TEXT_METRICS _metrics;
		};
	}
}