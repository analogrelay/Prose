#pragma once

namespace Prose {
	namespace Structure {
		public ref class Run sealed
		{
		public:
			Run(void);
			Run(Platform::String^);

			property Platform::String^ Text;
		};
	}
}