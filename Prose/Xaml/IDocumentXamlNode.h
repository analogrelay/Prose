#pragma once

#include "..\Structure\DocumentNode.h"

namespace Prose {
	namespace Xaml {
		public interface class IDocumentXamlNode {
			Prose::Structure::IDocumentNode^ CreateDocumentNode();
		};
	}
}