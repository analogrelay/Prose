#pragma once
#include "pch.h"

namespace Prose {
	namespace Structure {
		interface class IInline;

		public interface class IInlinePair {
			property IInline^ Left { IInline^ get(); }
			property IInline^ Right { IInline^ get(); }
		};

		private ref class InlinePair sealed :
			public IInlinePair
		{
		public:
			property virtual IInline^ Left { IInline^ get() { return _left; } }
			property virtual IInline^ Right { IInline^ get() { return _right; } }

			InlinePair(IInline^ left, IInline^ right) : _left(left), _right(right) {}
		private:
			IInline^ _left;
			IInline^ _right;
		};
	}
}