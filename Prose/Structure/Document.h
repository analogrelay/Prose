#pragma once

#include "DocumentNode.h"
#include "Paragraph.h"

namespace Prose {
	namespace Structure {
		namespace WUX = Windows::UI::Xaml;
		namespace WFC = Windows::Foundation::Collections;

		public interface class IDocument {
			property Windows::Foundation::Collections::IVector<IParagraph^>^ Paragraphs {
				Windows::Foundation::Collections::IVector<IParagraph^>^ get();
			}
		};

		[WUX::Markup::ContentProperty(Name = "Paragraphs")]
		private ref class Document :
			public DocumentNode,
			public IDocument
		{
		public:
			virtual property WFC::IVector<IParagraph^>^ Paragraphs {
				WFC::IVector<IParagraph^>^ get() { return _paragraphs; }
			}

			virtual void Accept(IDocumentVisitor^ visitor) override;

		internal:
			Document(void);

		private:
			WFC::IVector<IParagraph^>^ _paragraphs;
		};
	}
}