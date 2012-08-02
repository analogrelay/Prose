#pragma once
#include "..\Structure\StructureTree.h"
#include "LayoutResult.h"

namespace Prose {
	namespace Layout {
		private interface class ILayoutEngine {
			LayoutResult^ CreateLayout(Prose::Structure::StructureTree^ tree, Windows::Foundation::Size layoutSize);
		};
	}
}