#pragma once

#include "..\Structure\TextPointer.h"
#include "LayoutBox.h"
#include "LayoutInline.h"

namespace Prose {
	namespace Layout {
		public ref class LayoutPointer sealed
		{
		public:
			property LayoutBox^ Owner { LayoutBox^ get() { return _owner; } }
			property LayoutInline^ Node { LayoutInline^ get() { return _node; } }
			property UINT32 NodeIndex { UINT32 get() { return _nodeIndex; } }
			property UINT32 LocalOffset { UINT32 get() { return _localOffset; } }
			property UINT32 GlobalOffset { UINT32 get() { return _globalOffset; } }

			LayoutPointer(LayoutBox^ owner, LayoutInline^ node, UINT32 nodeIndex, UINT32 localOffset, UINT32 globalOffset) :
				_owner(owner), _node(node), _nodeIndex(nodeIndex), _localOffset(localOffset), _globalOffset(globalOffset) {}

			Prose::Structure::TextPointer^ GetTextPointer(void) {
				return Owner->LayoutToText(this);
			}

		private:
			LayoutBox^ _owner;
			LayoutInline^ _node;
			UINT32 _localOffset;
			UINT32 _globalOffset;
			UINT32 _nodeIndex;
		};
	}
}