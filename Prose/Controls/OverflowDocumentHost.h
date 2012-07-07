#pragma once
#include "..\ObjectTracking.h"
#include "DocumentHostBase.h"

namespace Prose {
	namespace Controls {
		public ref class OverflowDocumentHost sealed :
			public DocumentHostBase
		{
		public:
			OverflowDocumentHost() { TrackCreation(L"OverflowDocumentHost"); }
			~OverflowDocumentHost() { TrackDestruction(L"OverflowDocumentHost"); }

		public protected:
			virtual property DocumentHost^ RootHost {
				DocumentHost^ get() override;
			};

			virtual Prose::Structure::Document^ GetDocument() override { return _overflowDocument; }

		internal:
			void Detach(void);
			void Attach(DocumentHost^ rootHost);
			void RecieveOverflow(Windows::Foundation::Collections::IVectorView<Prose::Structure::Paragraph^>^ overflow);

		private:
			TrackingId;

			Microsoft::WRL::WeakRef _hostRef;
			Prose::Structure::Document^ _overflowDocument;
		};
	}
}