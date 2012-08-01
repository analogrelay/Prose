#pragma once
#include "ILayoutEngine.h"

namespace Prose {
	namespace Layout {
		public ref class DirectWriteLayoutEngine sealed :
			public ILayoutEngine
		{
		public:
			virtual LayoutResult^ CreateLayout(Prose::Structure::IDocument^ document, Windows::Foundation::Size layoutSize);
		};
	}
}