#pragma once
#include "LayoutBox.h"

namespace Prose {
	namespace Layout {
		namespace WFC = Windows::Foundation::Collections;

		private ref class LayoutTree sealed
		{
		public:
			property WFC::IVector<LayoutBox^>^ Boxes {
				WFC::IVector<LayoutBox^>^ get() { return _boxes; }
			}

			Windows::Foundation::Size Measure(void);

			LayoutTree(void);

			void Accept(LayoutVisitor^ visitor);
		private:
			WFC::IVector<LayoutBox^>^ _boxes;
		};
	}
}

