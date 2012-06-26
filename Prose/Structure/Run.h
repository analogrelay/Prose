#pragma once
#include "DocumentNode.h"

namespace Prose {
	namespace Structure {
		public ref class Run sealed :
			public DocumentNode
		{
		public:
			Run(void);
			Run(Platform::String^);

			property Platform::String^ Text;

			virtual void Accept(DocumentVisitor^ visitor) override;
		};
	}
}