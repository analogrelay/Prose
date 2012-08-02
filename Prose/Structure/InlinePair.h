#pragma once
#include "pch.h"

namespace Prose {
	namespace Structure {
		ref class Inline;

		private ref class InlinePair sealed
		{
		public:
			property Inline^ Left { Inline^ get() { return _left; } }
			property Inline^ Right { Inline^ get() { return _right; } }

			InlinePair(Inline^ left, Inline^ right) : _left(left), _right(right) {}
		private:
			Inline^ _left;
			Inline^ _right;
		};
	}
}