#pragma once

namespace Prose {
	namespace Layout {
		public ref class Inline sealed
		{
		public:
			Inline(void);
			Inline(Platform::String^);

			property Platform::String^ Text;
		};
	}
}