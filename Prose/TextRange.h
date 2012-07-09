#pragma once

namespace Prose {
	public ref class TextRange sealed
	{
	public:
		property UINT32 Offset {
			UINT32 get() { return _offset; }
		}

		property UINT32 Length {
			UINT32 get() { return _length; }
		}

		TextRange(UINT32 offset, UINT32 length) : _offset(offset), _length(length) { }
	private:
		UINT32 _offset;
		UINT32 _length;
	};
}