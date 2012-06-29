#include "pch.h"
#include "OverflowDocumentHost.h"

using namespace Windows::Foundation::Collections;

using namespace Prose::Controls;
using namespace Prose::Structure;

void OverflowDocumentHost::RecieveOverflow(DocumentHost^ rootHost, IVectorView<Paragraph^>^ overflow) {
	_rootHost = rootHost;
	_overflowDocument = ref new Document();
	
	for(UINT32 i = 0; i < overflow->Size; i++) {
		_overflowDocument->Paragraphs->Append(overflow->GetAt(i));
	}

	InvalidateMeasure();
}