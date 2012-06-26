#pragma once
#include "Box.h"

namespace Prose {
	namespace Layout {
		public ref class LayoutTree sealed
		{
		public:
			property Windows::Foundation::Collections::IVector<Box^>^ Boxes {
				Windows::Foundation::Collections::IVector<Box^>^ get() { return _boxes; }
			}

			LayoutTree(void);

			virtual void Accept(LayoutVisitor^ visitor);
		private:
			Windows::Foundation::Collections::IVector<Box^>^ _boxes;
		};
	}
}

