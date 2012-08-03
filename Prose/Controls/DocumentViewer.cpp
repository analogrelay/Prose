//
// DocumentViewer.cpp
// Implementation of the DocumentViewer class.
//

#include "pch.h"
#include "DocumentViewer.h"
#include "DocumentHost.h"
#include "Structure\StructureTree.h"

using namespace Prose::Controls;
using namespace Prose::Structure;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Documents;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;

DependencyProperty^ DocumentViewer::_DocumentProperty = DependencyProperty::Register(
	L"Document", Prose::Controls::Document::typeid, DocumentViewer::typeid, ref new PropertyMetadata(
	nullptr, ref new PropertyChangedCallback(DocumentViewer::DocumentChanged)));

DependencyProperty^ DocumentViewer::_OverflowTemplateProperty = DependencyProperty::Register(
	L"OverflowTemplate", DataTemplate::typeid, DocumentViewer::typeid, ref new PropertyMetadata(
	nullptr, ref new PropertyChangedCallback(DocumentViewer::DocumentChanged)));

DependencyProperty^ DocumentViewer::_HostTemplateProperty = DependencyProperty::Register(
	L"HostTemplate", DataTemplate::typeid, DocumentViewer::typeid, ref new PropertyMetadata(
	nullptr, ref new PropertyChangedCallback(DocumentViewer::DocumentChanged)));

DependencyProperty^ DocumentViewer::_ColumnWidthProperty = DependencyProperty::Register(
	L"ColumnWidth", double::typeid, DocumentViewer::typeid, ref new PropertyMetadata(
	nullptr, ref new PropertyChangedCallback(DocumentViewer::DocumentChanged)));

DocumentViewer::DocumentViewer() : _overflows()
{
}

void DocumentViewer::DocumentChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args) {
	auto viewer = (DocumentViewer^)sender;
	viewer->RelayoutDocument();
}

void DocumentViewer::RelayoutDocument() {
	if(_root) {
		_root->Width = ColumnWidth;
	}
	InvalidateMeasure();
}

void ConfigureDocumentHost(DocumentHostBase^ host, double columnWidth) {
	host->Width = columnWidth;
	host->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Left;
	host->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Top;
}

void DocumentViewer::InitializeHost() {
	if(HostTemplate) {
		_root = (DocumentHost^)HostTemplate->LoadContent();
	} else {
		_root = ref new DocumentHost();
		ConfigureDocumentHost(_root, ColumnWidth);
	}

	Children->Clear();
	Children->Append(_root);
}

OverflowDocumentHost^ DocumentViewer::CreateOverflow() {
	if(OverflowTemplate) {
		return (OverflowDocumentHost^)OverflowTemplate->LoadContent();
	} else {
		auto overflow = ref new OverflowDocumentHost();
		ConfigureDocumentHost(overflow, ColumnWidth);
		return overflow;
	}
}

Size DocumentViewer::MeasureOverride(Size availableSize) {
	// If there's no document...
	if(!this->Document) {
		// Just return
		return availableSize;
	}

	if(!_root) {
		// Add the main host
		InitializeHost();
	}
	_root->Document = Document;

	// Measure the main host
	_root->Measure(availableSize);
	auto usedWidth = _root->DesiredSize.Width;
	auto usedHeight = _root->DesiredSize.Height;
	auto hasOverflow = _root->HasOverflowContent;

	// Set up overflow chain
	UINT32 counter = 0;
	while(hasOverflow && usedWidth < availableSize.Width) {
		// Try to reuse overflows
		OverflowDocumentHost^ overflow = nullptr;
		if(counter < _overflows.size()) {
			overflow = _overflows.at(counter);
			if(overflow->Width != ColumnWidth) {
				overflow->Width = ColumnWidth;
			}
		}
		else {
			// Need to create one
			overflow = CreateOverflow();
			_overflows.push_back(overflow);
			Children->Append(overflow);
			if(counter > 0) {
				_overflows.at(counter - 1)->OverflowTarget = overflow;
			} else {
				_root->OverflowTarget = overflow;				
			}
		}

		// Measure the new overflow and determine if there is still extra content
		overflow->Measure(SizeHelper::FromDimensions(availableSize.Width - usedWidth, availableSize.Height));
		auto size = overflow->DesiredSize;
		usedWidth += size.Width;
		usedHeight = max(size.Height, usedHeight);
		hasOverflow = overflow->HasOverflowContent;
		counter++;
	}

	if(counter < _overflows.size()) {
		if(counter == 0) {
			_root->OverflowTarget = nullptr;
		} else {
			_overflows.at(counter - 1)->OverflowTarget = nullptr;
		}
		_overflows.resize(counter);

		UINT32 removePoint = (counter + 1); // Always remove the (counter+1)th item.
		for(UINT32 i = Children->Size; i > removePoint; i--) {
			Children->RemoveAt(removePoint);
		}
	}

	return SizeHelper::FromDimensions(usedWidth, usedHeight);
}

Size DocumentViewer::ArrangeOverride(Size finalSize) {
	float maxHeight = 0.0;
	float maxWidth = 0.0;
	for(UINT32 i = 0; i < Children->Size; i++) {
		auto child = Children->GetAt(i);
		auto size = child->DesiredSize;
		child->Arrange(
			RectHelper::FromCoordinatesAndDimensions(maxWidth, 0, size.Width, size.Height));
		maxWidth += size.Width;
		maxHeight = max(maxHeight, size.Height);
	}

	return SizeHelper::FromDimensions(maxWidth, maxHeight);
}