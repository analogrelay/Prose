#include "pch.h"
#include "DocumentHostBase.h"

using namespace Windows::UI::Xaml;

using namespace Prose::Controls;

DependencyProperty^ DocumentHostBase::_OverflowTargetProperty = DependencyProperty::Register(
	L"OverflowTarget", 
	OverflowDocumentHost::typeid, 
	DocumentHostBase::typeid,
	ref new PropertyMetadata(nullptr, ref new PropertyChangedCallback(DocumentHostBase::TargetChanged)));

void DocumentHostBase::SendOverflow() {
}

void DocumentHostBase::TargetChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args) {
	DocumentHostBase^ host = (DocumentHostBase^)sender;
	host->SendOverflow();
}