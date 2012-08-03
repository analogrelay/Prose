#pragma once

#include "Structure\ParagraphNode.h"
#include "LayoutTree.h"
#include "LayoutBox.h"

namespace Prose {
	namespace Layout {
		namespace PS = Prose::Structure;
		namespace WFC = Windows::Foundation::Collections;

		private ref class LayoutResult sealed
		{
		public:
			property LayoutTree^ Layout {
				LayoutTree^ get() { return _layout; }
			};

			property WFC::IVectorView<PS::BlockNode^>^ Overflow {
				WFC::IVectorView<PS::BlockNode^>^ get() { return _overflow; }
			}

			LayoutResult(LayoutTree^ layout, WFC::IVectorView<PS::BlockNode^>^ overflow) :
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
			WFC::IVectorView<PS::BlockNode^>^ _overflow;
			Windows::Foundation::Size _layoutSize;
			bool _layoutSizeCalulated;
		};
	}
}