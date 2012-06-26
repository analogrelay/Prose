#pragma once

namespace Prose {
	namespace Rendering {
		private ref class DWRenderRange sealed
		{
		public:
			DWRenderRange(Platform::String^ text);

			property Platform::String^ Text;
		};
	}
}