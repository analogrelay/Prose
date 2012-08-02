#pragma once

#include "..\Structure\StructureTree.h"

namespace Prose {
	namespace Controls {
		public ref class Document sealed
		{
		internal:
			Prose::Structure::StructureTree^ CreateStructure();
		};
	}
}