#pragma once
#include "..\Structure\Document.h"
#include "LayoutTree.h"

namespace Prose {
	namespace Layout {
		public interface class ILayoutEngine {
			LayoutTree^ CreateLayout(Prose::Structure::Document^ document, Windows::Foundation::Size layoutSize);
		};
	}
}