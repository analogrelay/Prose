#pragma once
#include "..\ObjectTracking.h"
#include "DocumentHostBase.h"
#include "Nodes\Document.h"

namespace Prose {
	namespace Controls {
		namespace WFM = Windows::Foundation::Metadata;
		namespace PS = Prose::Structure;

		[WFM::WebHostHidden]
		public ref class OverflowDocumentHost sealed :
			public DocumentHostBase
		{
		public:
			OverflowDocumentHost() { TrackCreation(L"OverflowDocumentHost"); }
			virtual ~OverflowDocumentHost() { TrackDestruction(L"OverflowDocumentHost"); }

		protected:
			virtual property DocumentHost^ RootHost {
				DocumentHost^ get() override;
			};

		internal:
			void Detach(void);
			void Attach(DocumentHost^ rootHost);
			void RecieveOverflow(Windows::Foundation::Collections::IVectorView<PS::Block^>^ overflow);

			virtual PS::StructureTree^ GetStructureTree() override { return _overflowTree; }

		private:
			TrackingId;

			Microsoft::WRL::WeakRef _hostRef;
			PS::StructureTree^ _overflowTree;
		};
	}
}