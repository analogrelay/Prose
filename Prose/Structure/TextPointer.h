#pragma once

namespace Prose {
	namespace Structure {
		ref class BlockNode;
		ref class InlineNode;

		private ref class TextPointer sealed
		{
		public:
			property BlockNode^ Owner { BlockNode^ get() { return _owner; } }
			property InlineNode^ Node { InlineNode^ get() { return _node; } }
			property UINT32 NodeIndex { UINT32 get() { return _nodeIndex; } }
			property UINT32 LocalOffset { UINT32 get() { return _localOffset; } }
			property UINT32 GlobalOffset { UINT32 get() { return _globalOffset; } }

			TextPointer(BlockNode^ owner, InlineNode^ node, UINT32 nodeIndex, UINT32 localOffset, UINT32 globalOffset) :
				_owner(owner), _node(node), _nodeIndex(nodeIndex), _localOffset(localOffset), _globalOffset(globalOffset) {}

		private:
			BlockNode^ _owner;
			InlineNode^ _node;
			UINT32 _localOffset;
			UINT32 _globalOffset;
			UINT32 _nodeIndex;
		};
	}
}