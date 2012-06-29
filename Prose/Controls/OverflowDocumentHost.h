#pragma once
#include "DocumentHostBase.h"

namespace Prose {
	namespace Controls {
		public ref class OverflowDocumentHost sealed :
			public DocumentHostBase
		{
		public protected:
			virtual property DocumentHost^ RootHost {
				DocumentHost^ get() override { return _rootHost; }
			};

			virtual Prose::Structure::Document^ GetDocument() override { return _overflowDocument; }

		internal:
			void RecieveOverflow(DocumentHost^ rootHost, Windows::Foundation::Collections::IVectorView<Prose::Structure::Paragraph^>^ overflow);

		private:
			DocumentHost^ _rootHost;
			Prose::Structure::Document^ _overflowDocument;
		};
	}
}