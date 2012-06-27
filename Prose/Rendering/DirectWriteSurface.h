#pragma once

namespace Prose {
	namespace Rendering {
		private ref class DirectWriteSurface {
		internal:
			property Windows::Foundation::Rect Region {
				Windows::Foundation::Rect get() { return _region; }
			};

			property Microsoft::WRL::ComPtr<IDWriteTextLayout> Layout {
				Microsoft::WRL::ComPtr<IDWriteTextLayout> get() { return _layout; }
			};

			DirectWriteSurface(Windows::Foundation::Rect region, Microsoft::WRL::ComPtr<IDWriteTextLayout> layout) : _region(region), _layout(layout) { };

		private:
			Microsoft::WRL::ComPtr<IDWriteTextLayout> _layout;
			Windows::Foundation::Rect _region;
		};
	}
}

