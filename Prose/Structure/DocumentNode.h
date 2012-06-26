#pragma once

namespace Prose {
	namespace Structure {
		ref class DocumentVisitor;

		public ref class DocumentNode abstract
		{
		public:
			virtual void Accept(DocumentVisitor^ visitor) = 0;
		};
	}
}