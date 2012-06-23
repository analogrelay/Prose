#pragma once
#include "Run.h"

namespace Prose {
	namespace Structure {
		using namespace Windows::Foundation::Collections;
		public ref class Paragraph sealed
		{
		public:
			Paragraph(void);

			property IVector<Run^>^ Runs {
				IVector<Run^>^ get() { return _runs; }
			};

		private:
			IVector<Run^>^ _runs;
		};
	}
}