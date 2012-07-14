#pragma once

#include "DocumentNode.h"
#include "Paragraph.h"

namespace Prose {
	namespace Structure {
		public interface class IDocument :
			public IDocumentNode {
			property Windows::Foundation::Collections::IVector<IParagraph^>^ Paragraphs {
				Windows::Foundation::Collections::IVector<IParagraph^>^ get();
			}
		};

		[Windows::UI::Xaml::Markup::ContentProperty(Name = "Paragraphs")]
		public ref class Document sealed :
			public DocumentNode,
			public IDocument
		{
		public:
			virtual property Windows::Foundation::Collections::IVector<IParagraph^>^ Paragraphs {
				Windows::Foundation::Collections::IVector<IParagraph^>^ get() { return _paragraphs; }
			}

			Document(void);

			virtual void Accept(IDocumentVisitor^ visitor) override;
		private:
			Windows::Foundation::Collections::IVector<IParagraph^>^ _paragraphs;
		};
	}
}