#include "pch.h"
#include "OverflowDocumentHost.h"

using namespace Prose::Controls;

void OverflowDocumentHost::RecieveOverflow(Windows::Foundation::Collections::IVectorView<Prose::Structure::Paragraph^>^ overflow) {
	throw ref new Platform::Exception(E_FAIL);
}