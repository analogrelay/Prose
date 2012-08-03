#pragma once

#include "TextFormat.h"
#include "Structure\Block.h"
#include "Structure\Inline.h"

namespace Prose {
	namespace Controls {
		namespace WFM = Windows::Foundation::Metadata;
		namespace WUX = Windows::UI::Xaml;
		namespace WUT = Windows::UI::Text;
		namespace PS = Prose::Structure;

		[WFM::WebHostHidden]
		public ref class StylableNode :
			public WUX::DependencyObject {
		public:
			DEPENDENCY_PROPERTY(WUX::Media::FontFamily^, FontFamily);
			DEPENDENCY_PROPERTY(WUX::Media::Brush^, Foreground);
			DEPENDENCY_PROPERTY(WUT::FontStretch, FontStretch);
			DEPENDENCY_PROPERTY(double, FontSize);
			DEPENDENCY_PROPERTY(WUT::FontStyle, FontStyle);
			DEPENDENCY_PROPERTY(WUT::FontWeight, FontWeight);
			DEPENDENCY_PROPERTY(bool, HasStrikethrough);
			DEPENDENCY_PROPERTY(bool, HasUnderline);

		internal:
			Prose::TextFormat^ CreateFormat();
		};

		[WFM::WebHostHidden]
		public ref class BlockNode :
			public StylableNode {
		internal:
			virtual PS::Block^ ConstructStructureNode() { return nullptr; }
		};

		[WFM::WebHostHidden]
		public ref class InlineNode :
			public StylableNode {
		internal:
			virtual PS::Inline^ ConstructStructureNode() { return nullptr; }
		};
	}
}