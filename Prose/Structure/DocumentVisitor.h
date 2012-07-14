#pragma once

namespace Prose {
	namespace Structure {
		interface class IRun;
		interface class ISpan;
		interface class IInline;
		interface class IDocument;
		interface class IParagraph;
		interface class IDocumentNode;
		
		public interface class IDocumentVisitor {
			void Visit(IRun^ run);
			void Visit(ISpan^ span);
			void Visit(IInline^ inl);
			void Visit(IDocument^ document);
			void Visit(IDocumentNode^ node);
			void Visit(IParagraph^ paragraph);
		};

		private ref class DocumentVisitor abstract :
			public IDocumentVisitor
		{
		public:
			virtual void Visit(IRun^ run);
			virtual void Visit(ISpan^ span);
			virtual void Visit(IInline^ inl);
			virtual void Visit(IDocument^ document);
			virtual void Visit(IDocumentNode^ node);
			virtual void Visit(IParagraph^ paragraph);
		};
	}
}
