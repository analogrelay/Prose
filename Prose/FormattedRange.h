#pragma once

#include "TextRange.h"
#include "TextFormat.h"

namespace Prose {
	private ref class FormattedRange sealed
	{
	public:
		property TextRange^ Range {
			TextRange^ get() { return _range; }
		}

		property TextFormat^ Format {
			TextFormat^ get() { return _format; }
		}

		FormattedRange(TextRange^ range, TextFormat^ format) :
			_range(range), _format(format) { }

	private:
		TextRange^ _range;
		TextFormat^ _format;
	};
}