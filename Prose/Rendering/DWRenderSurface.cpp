#include "pch.h"
#include "DWRenderSurface.h"

#include <sstream>

#include <d2d1.h>
#include <d2d1_1.h>

#include <wrl.h>
#include <windows.ui.xaml.media.dxinterop.h>

using namespace Microsoft::WRL;

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media::Imaging;

using namespace Prose::Rendering;

DWRenderSurface::DWRenderSurface(void) : _ranges(ref new Platform::Collections::Vector<DWRenderRange^>()) { }

UIElement^ DWRenderSurface::RenderToUIElement() {
	// Create a border - It's easy to render to the background of a border ;)
	Border^ border = ref new Border();

	// Collect all the text in the ranges
	std::wstringstream strm;
	for(UINT32 i = 0; i < Ranges->Size; i++) {
		auto range = Ranges->GetAt(i);
		strm << range->Text->Data();
	}
	std::wstring str = strm.str();

	// Create a base text format

	return border;
}