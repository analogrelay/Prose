#pragma once

#include "..\Structure\Paragraph.h"
#include "LayoutTree.h"
#include "LayoutBox.h"

namespace Prose {
	namespace Layout {
		public ref class LayoutResult sealed
		{
		public:
			property LayoutTree^ Layout {
				LayoutTree^ get() { return _layout; }
			};

			property Windows::Foundation::Collections::IVectorView<Prose::Structure::Paragraph^>^ Overflow {
				Windows::Foundation::Collections::IVectorView<Prose::Structure::Paragraph^>^ get() { return _overflow; }
			}

			LayoutResult(LayoutTree^ layout, Windows::Foundation::Collections::IVectorView<Prose::Structure::Paragraph^>^ overflow) :
				_layout(layout),
				_overflow(overflow) {}

			property Windows::Foundation::Size LayoutSize {
				Windows::Foundation::Size get() {
					if(!_layoutSizeCalulated) {
						float width = 0.0;
						float height = 0.0;
						for each(auto box in _layout->Boxes) {
							width = max(width, box->Metrics->LayoutBounds.Width);
							height += box->Metrics->LayoutBounds.Height;
						}
						_layoutSize = Windows::UI::Xaml::SizeHelper::FromDimensions(width, height);
						_layoutSizeCalulated = true;
					}
					return _layoutSize;
				}
			}

		private:
			LayoutTree^ _layout;
			Windows::Foundation::Collections::IVectorView<Prose::Structure::Paragraph^>^ _overflow;
			Windows::Foundation::Size _layoutSize;
			bool _layoutSizeCalulated;
		};
	}
}