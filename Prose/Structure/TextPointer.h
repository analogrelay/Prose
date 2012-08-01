#pragma once

namespace Prose {
	namespace Structure {
		interface class IParagraph;
		interface class IInline;

		public ref class TextPointer sealed
		{
		public:
			property IParagraph^ Owner { IParagraph^ get() { return _owner; } }
			property IInline^ Node { IInline^ get() { return _node; } }
			property UINT32 NodeIndex { UINT32 get() { return _nodeIndex; } }
			property UINT32 LocalOffset { UINT32 get() { return _localOffset; } }
			property UINT32 GlobalOffset { UINT32 get() { return _globalOffset; } }

			TextPointer(IParagraph^ owner, IInline^ node, UINT32 nodeIndex, UINT32 localOffset, UINT32 globalOffset) :
				_owner(owner), _node(node), _nodeIndex(nodeIndex), _localOffset(localOffset), _globalOffset(globalOffset) {}

		private:
			IParagraph^ _owner;
			IInline^ _node;
			UINT32 _localOffset;
			UINT32 _globalOffset;
			UINT32 _nodeIndex;
		};
	}
}