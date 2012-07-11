#pragma once
#include "Document.h"
#include "Paragraph.h"
#include "Run.h"
#include "Inline.h"
#include "Span.h"

namespace Prose {
	namespace Structure {
		public ref class DocumentVisitor abstract
		{
		public:
			virtual void Visit(DocumentNode^ node);
			virtual void Visit(Document^ document);
			virtual void Visit(Paragraph^ paragraph);
			virtual void Visit(Inline^ inl);
			virtual void Visit(Run^ run);
			virtual void Visit(SpanBase^ span);
			virtual void Visit(Span^ span);
		};
	}
}