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

		private:
			LayoutTree^ _layout;
			Windows::Foundation::Collections::IVectorView<Prose::Structure::Paragraph^>^ _overflow;
		};
	}
}