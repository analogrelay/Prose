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

			virtual property Windows::Foundation::Collections::IVector<FormattedRange^>^ FormattedRanges {
				Windows::Foundation::Collections::IVector<FormattedRange^>^ get() { return _formattedRanges; };
			}

			virtual property UINT32 TextLength {
				UINT32 get() { return _textLength; }
			}

			virtual INT32 HitTest(Windows::Foundation::Point point);

		internal:
			DWLayoutMetrics(Microsoft::WRL::ComPtr<IDWriteTextLayout> layout, 
							DWRITE_TEXT_METRICS metrics, 
							Windows::Foundation::Rect renderArea, 
							Windows::Foundation::Rect layoutBounds,
							Windows::Foundation::Collections::IVector<FormattedRange^>^ formattedRanges,
							UINT32 textLength) :
				_layout(layout),
				_metrics(metrics),
				_renderArea(renderArea),
				_layoutBounds(layoutBounds),
				_foreground(nullptr), 
				_formattedRanges(formattedRanges),
				_textLength(textLength) {};

			property Microsoft::WRL::ComPtr<IDWriteTextLayout> Layout {
				Microsoft::WRL::ComPtr<IDWriteTextLayout> get() { return _layout; }
			};

			property DWRITE_TEXT_METRICS DWMetrics {
				DWRITE_TEXT_METRICS get() { return _metrics; }
			}
		private:
			Windows::Foundation::Collections::IVector<FormattedRange^>^ _formattedRanges;
			Windows::UI::Xaml::Media::Brush^ _foreground;
			Microsoft::WRL::ComPtr<IDWriteTextLayout> _layout;
			Windows::Foundation::Rect _renderArea;
			Windows::Foundation::Rect _layoutBounds;
			DWRITE_TEXT_METRICS _metrics;
			UINT32 _textLength;
		};
	}
}