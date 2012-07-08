#pragma once

namespace Prose {
	namespace Structure {
		ref class Paragraph;
		ref class Inline;

		public ref class TextPointer sealed
		{
		public:
			property Paragraph^ Owner { Paragraph^ get() { return _owner; } }
			property Inline^ Node { Inline^ get() { return _node; } }
			property UINT32 NodeIndex { UINT32 get() { return _nodeIndex; } }
			property UINT32 LocalOffset { UINT32 get() { return _localOffset; } }
			property UINT32 GlobalOffset { UINT32 get() { return _globalOffset; } }

			TextPointer(Paragraph^ owner, Inline^ node, UINT32 nodeIndex, UINT32 localOffset, UINT32 globalOffset) :
				_owner(owner), _node(node), _nodeIndex(nodeIndex), _localOffset(localOffset), _globalOffset(globalOffset) {}

		private:
			Paragraph^ _owner;
			Inline^ _node;
			UINT32 _localOffset;
			UINT32 _globalOffset;
			UINT32 _nodeIndex;
		};
	}
}