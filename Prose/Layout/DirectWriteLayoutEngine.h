#pragma once
#include "ILayoutEngine.h"

namespace Prose {
	namespace Layout {
		private ref class DirectWriteLayoutEngine sealed :
			public ILayoutEngine
		{
		public:
			virtual LayoutResult^ CreateLayout(Prose::Structure::StructureTree^ tree, Windows::Foundation::Size layoutSize, Prose::TextFormat^ baseFormat);
		};
	}
}