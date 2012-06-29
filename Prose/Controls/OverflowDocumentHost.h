#pragma once
#include "DocumentHostBase.h"

namespace Prose {
	namespace Controls {
		public ref class OverflowDocumentHost sealed :
			public DocumentHostBase
		{
		internal:
			void RecieveOverflow(Windows::Foundation::Collections::IVectorView<Prose::Structure::Paragraph^>^ overflow);
		};
	}
}