#pragma once

namespace Prose {
	namespace Structure {
		ref class Run;
		ref class Span;
		ref class Inline;
		ref class Block;
		ref class StructureTree;
		ref class Paragraph;
		ref class StructureNode;
		
		private ref class StructureVisitor abstract
		{
		public:
			virtual void Visit(StructureTree^ tree);
			virtual void Visit(StructureNode^ node);
			virtual void Visit(Block^ block);
			virtual void Visit(Paragraph^ paragraph);
			virtual void Visit(Inline^ inl);
			virtual void Visit(Run^ run);
			virtual void Visit(Span^ span);
		};
	}
}
