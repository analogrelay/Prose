#pragma once

namespace Prose {
	namespace Structure {
		ref class RunNode;
		ref class SpanNode;
		ref class InlineNode;
		ref class BlockNode;
		ref class StructureTree;
		ref class ParagraphNode;
		ref class StructureNode;
		
		private ref class StructureVisitor abstract
		{
		public:
			virtual void Visit(StructureTree^ tree);
			virtual void Visit(StructureNode^ node);
			virtual void Visit(BlockNode^ BlockNode);
			virtual void Visit(ParagraphNode^ paragraph);
			virtual void Visit(InlineNode^ inl);
			virtual void Visit(RunNode^ run);
			virtual void Visit(SpanNode^ span);
		};
	}
}
