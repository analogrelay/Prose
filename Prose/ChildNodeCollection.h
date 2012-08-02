//#pragma once
//namespace Prose {
//	template<typename _NodeType, typename _ParentType = _NodeType>
//	struct set_parent {
//		// Overload for clearing the parent (nullptr)
//		void operator()(_NodeType node) {
//			node->DetachParent();
//		}
//
//		// Overload for setting the parent
//		void operator()(_NodeType node, _ParentType parent) {
//			operator()(node);
//			if(parent) {
//				node->AttachParent(parent);
//			}
//		}
//	};
//
//	template<typename _NodeType, typename _ParentType = _NodeType, typename _SetParentFunctor = set_parent<_NodeType, _ParentType>>
//	private ref class ChildNodeCollection sealed :
//		public Windows::Foundation::Collections::IVector<_NodeType>
//	{
//	public:
//		virtual property UINT32 Size { 
//			UINT32 get() {
//				return _inner->Size;
//			} 
//		}
//
//		virtual Windows::Foundation::Collections::IIterator<_NodeType>^ First() {
//			return _inner->First();
//		}
//
//		virtual void Append(_NodeType value) {
//			_setParent(value, _parent);
//			_inner->Append(value);
//		}
//
//		virtual void Clear() {
//			for each(auto node in _inner) {
//				_setParent(node);
//			}
//			_inner->Clear();
//		}
//
//		virtual _NodeType GetAt(UINT32 index) {
//			return _inner->GetAt(index);
//		}
//
//		virtual UINT32 GetMany(UINT32 startIndex, Platform::WriteOnlyArray<_NodeType>^ items) {
//			return _inner->GetMany(startIndex, items);
//		}
//
//		virtual Windows::Foundation::Collections::IVectorView<_NodeType>^ GetView() {
//			return _inner->GetView();
//		}
//
//		virtual bool IndexOf(_NodeType value, UINT32* index) {
//			return _inner->IndexOf(value, index);
//		}
//
//		virtual void InsertAt(UINT32 index, _NodeType value) {
//			_setParent(value, _parent);
//			_inner->InsertAt(index, value);
//		}
//
//		virtual void RemoveAt(UINT32 index) {
//			_setParent(_inner->GetAt(index));
//			_inner->RemoveAt(index);
//		}
//
//		virtual void RemoveAtEnd() {
//			if(Size > 0) {
//				_setParent(_inner->GetAt(Size - 1));
//			}
//			_inner->RemoveAtEnd();
//		}
//
//		virtual void ReplaceAll(const Platform::Array<_NodeType>^ items) {
//			for each(auto node in _inner) {
//				_setParent(node);
//			}
//			for each(auto node in items) {
//				_setParent(node, _parent);
//			}
//			_inner->ReplaceAll(items);
//		}
//
//		virtual void SetAt(UINT32 index, _NodeType value) {
//			_setParent(_inner->GetAt(index));
//			_setParent(value, _parent);
//			_inner->SetAt(index, value);
//		}
//
//		ChildNodeCollection(_ParentType parent) : _inner(ref new Platform::Collections::Vector<_NodeType>()), _parent(parent) {
//		}
//	private:
//		_ParentType _parent;
//		Windows::Foundation::Collections::IVector<_NodeType>^ _inner;
//		_SetParentFunctor _setParent;
//	};
//}