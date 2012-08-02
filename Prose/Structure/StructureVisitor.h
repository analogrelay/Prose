#pragma once

namespace Prose {
	namespace Structure {
		ref class Run;
		ref class SpanBase;
		ref class Inline;
		ref class StructureTree;
		ref class Paragraph;
		ref class StructureNode;
		
		private ref class StructureVisitor abstract
		{
		public:
			virtual void Visit(Run^ run);
			virtual void Visit(SpanBase^ span);
			virtual void Visit(Inline^ inl);
			virtual void Visit(StructureTree^ tree);
			virtual void Visit(StructureNode^ node);
			virtual void Visit(Paragraph^ paragraph);
		};
	}
}
