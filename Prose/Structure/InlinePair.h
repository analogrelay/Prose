#pragma once
#include "pch.h"

namespace Prose {
	namespace Structure {
		ref class InlineNode;

		private ref class InlinePair sealed
		{
		public:
			property InlineNode^ Left { InlineNode^ get() { return _left; } }
			property InlineNode^ Right { InlineNode^ get() { return _right; } }

			InlinePair(InlineNode^ left, InlineNode^ right) : _left(left), _right(right) {}
		private:
			InlineNode^ _left;
			InlineNode^ _right;
		};
	}
}