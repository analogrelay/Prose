#pragma once

#include "TextFormat.h"

namespace Prose {
	namespace Structure {
		namespace WUX = Windows::UI::Xaml;

		ref class StructureVisitor;

		private ref class StructureNode abstract
		{
		public:
			virtual property StructureNode^ Parent { StructureNode^ get() { return _parent; } }
			virtual property TextFormat^ Format {
				TextFormat^ get() { return _format; }
				void set(TextFormat^ value) { _format = value; }
			}

			virtual void Accept(StructureVisitor^ visitor) abstract;
			
			virtual void DetachParent(void) { _parent = nullptr; }
			virtual void AttachParent(StructureNode^ parent) { _parent = parent; }

		private protected:
			StructureNode(void);

		private:
			TextFormat^ _format;
			StructureNode^ _parent;
		};
	}
}
