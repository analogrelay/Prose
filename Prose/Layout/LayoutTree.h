#pragma once
#include "LayoutBox.h"

namespace Prose {
	namespace Layout {
		public ref class LayoutTree sealed
		{
		public:
			property Windows::Foundation::Collections::IVector<LayoutBox^>^ Boxes {
				Windows::Foundation::Collections::IVector<LayoutBox^>^ get() { return _boxes; }
			}

			Windows::Foundation::Size Measure(void);

			LayoutTree(void);

			virtual void Accept(LayoutVisitor^ visitor);
		private:
			Windows::Foundation::Collections::IVector<LayoutBox^>^ _boxes;
		};
	}
}

