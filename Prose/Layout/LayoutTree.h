#pragma once
#include "LayoutBox.h"
#include "LayoutPointer.h"

namespace Prose {
	namespace Layout {
		namespace WFC = Windows::Foundation::Collections;

		public ref class LayoutTree sealed
		{
		public:
			property WFC::IVector<ILayoutBox^>^ Boxes {
				WFC::IVector<ILayoutBox^>^ get() { return _boxes; }
			}

			Windows::Foundation::Size Measure(void);

			LayoutTree(void);

			void Accept(ILayoutVisitor^ visitor);

			LayoutPointer^ HitTest(Windows::Foundation::Point point);
		private:
			WFC::IVector<ILayoutBox^>^ _boxes;
		};
	}
}

