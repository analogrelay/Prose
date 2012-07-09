#pragma once

#include "..\Layout\LayoutBox.h"

namespace Prose {
	namespace Rendering {
		private ref class DirectWriteSurface {
		internal:
			property Windows::Foundation::Rect RenderArea {
				Windows::Foundation::Rect get() { return _renderArea; }
			};

			property Windows::Foundation::Rect LayoutBounds {
				Windows::Foundation::Rect get() { return _layoutBounds; }
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

			property Windows::UI::Xaml::Media::Brush^ Foreground {
				Windows::UI::Xaml::Media::Brush^ get() { return _foreground; }
			}

			property Windows::Foundation::Collections::IVector<FormattedRange^>^ FormattedRanges {
				Windows::Foundation::Collections::IVector<FormattedRange^>^ get() { return _formattedRanges; }
			}

			property UINT32 TextLength {
				UINT32 get() { return _textLength; }
			}

			DirectWriteSurface(Windows::Foundation::Rect renderArea, 
							   Windows::Foundation::Rect layoutBounds, 
							   Microsoft::WRL::ComPtr<IDWriteTextLayout> layout, 
							   DWRITE_TEXT_METRICS metrics, 
							   Prose::Layout::LayoutBox^ box, 
							   Windows::Foundation::Collections::IVector<FormattedRange^>^ formattedRanges,
							   UINT32 textLength) : 
				_renderArea(renderArea), 
				_layoutBounds(layoutBounds), 
				_layout(layout), 
				_metrics(metrics), 
				_box(box), 
				_formattedRanges(formattedRanges),
				_textLength(textLength) { };

		private:
			Windows::Foundation::Collections::IVector<FormattedRange^>^ _formattedRanges;
			Windows::UI::Xaml::Media::Brush^ _foreground;
			Prose::Layout::LayoutBox^ _box;
			DWRITE_TEXT_METRICS _metrics;
			Microsoft::WRL::ComPtr<IDWriteTextLayout> _layout;
			Windows::Foundation::Rect _renderArea;
			Windows::Foundation::Rect _layoutBounds;
			UINT32 _textLength;
		};
	}
}

