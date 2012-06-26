#pragma once
#include "..\Structure\Document.h"
#include "OverflowDocumentHost.h"

namespace Prose {
	namespace Controls {
		public interface class IDocumentSource {
		public:
			virtual property Prose::Structure::Document^ Document { 
				Prose::Structure::Document^ get();
			};

			virtual property Prose::Controls::OverflowDocumentHost^ OverflowTarget { 
				Prose::Controls::OverflowDocumentHost^ get();
			};
		};
	}
}