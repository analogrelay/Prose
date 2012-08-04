#pragma once

#include "TextFormat.h"
#include "Structure\BlockNode.h"
#include "Structure\InlineNode.h"

namespace Prose {
	namespace Controls {
		namespace WFM = Windows::Foundation::Metadata;
		namespace WUX = Windows::UI::Xaml;
		namespace WUT = Windows::UI::Text;
		namespace PS = Prose::Structure;

		ref class TextStyle;

		[WFM::WebHostHidden]
		public ref class Stylable :
			public WUX::DependencyObject {
		
			DEPENDENCY_PROPERTY(WUX::Media::FontFamily^, FontFamily);
			DEPENDENCY_PROPERTY(WUX::Media::Brush^, Foreground);
			DEPENDENCY_PROPERTY(WUT::FontStretch, FontStretch);
			DEPENDENCY_PROPERTY(double, FontSize);
			DEPENDENCY_PROPERTY(WUT::FontStyle, FontStyle);
			DEPENDENCY_PROPERTY(WUT::FontWeight, FontWeight);
			DEPENDENCY_PROPERTY(bool, HasStrikethrough);
			DEPENDENCY_PROPERTY(bool, HasUnderline);
			DEPENDENCY_PROPERTY(TextStyle^, ParentStyle);

		internal:
			virtual Prose::TextFormat^ CreateFormat();
			static TextStyle^ Merge(Stylable^ general, Stylable^ specific);
		};

		public ref class TextStyle sealed :
			public Stylable {
		public:
			TextStyle(void) { }
		};

		[WFM::WebHostHidden]
		public ref class Block :
			public Stylable {
		internal:
			virtual PS::BlockNode^ ConstructStructureNode() { return nullptr; }
		};

		[WFM::WebHostHidden]
		public ref class Inline :
			public Stylable {
		internal:
			virtual PS::InlineNode^ ConstructStructureNode() { return nullptr; }
		};
	}
}