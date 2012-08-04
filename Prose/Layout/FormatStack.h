#pragma once

#include "TextFormat.h"
#include <list>
#include <deque>

namespace Prose {
	namespace Layout {
		private ref class FormatStack sealed
		{
		public:
			FormatStack(void);
			FormatStack(TextFormat^ baseFormat);

			void PushFormat(TextFormat^ format);
			TextFormat^ CalculateCurrentFormat(TextFormat^ inputFormat);
			void PopFormat(void);

		private:
			std::deque<TextFormat^> _stack;
			TextFormat^ _baseFormat;
		};
	}
}