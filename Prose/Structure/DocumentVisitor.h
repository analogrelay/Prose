#pragma once
#include "Document.h"
#include "Paragraph.h"
#include "Run.h"

namespace Prose {
	namespace Structure {
		public ref class DocumentVisitor abstract
		{
		public:
			virtual void Visit(Document^ document);
			virtual void Visit(Paragraph^ paragraph);
			virtual void Visit(Run^ run);
		};
	}
}