#pragma once
#include "Inline.h"

namespace Prose {
	namespace Layout {
		using namespace Windows::Foundation::Collections;
		public ref class Box sealed
		{
		public:
			Box(void);

			property IVector<Inline^>^ Inlines {
				IVector<Inline^>^ get() { return _inlines; }
			};

		private:
			IVector<Inline^>^ _inlines;
		};
	}
}