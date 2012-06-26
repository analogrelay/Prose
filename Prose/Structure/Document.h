#pragma once
#include "Paragraph.h"

namespace Prose {
	namespace Structure {
		public ref class Document sealed :
			public DocumentNode
		{
		public:
			property Windows::Foundation::Collections::IVector<Paragraph^>^ Paragraphs {
				Windows::Foundation::Collections::IVector<Paragraph^>^ get() { return _paragraphs; }
			}

			Document(void);

			virtual void Accept(DocumentVisitor^ visitor) override;
		private:
			Windows::Foundation::Collections::IVector<Paragraph^>^ _paragraphs;
		};
	}
}