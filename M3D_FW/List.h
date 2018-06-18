#pragma once


#include "MemoryManagement.h"


namespace m3dfw
{
	class ListGen
	{
	protected:

		struct ListGenNode;

	public:

		class GenIterator
		{

			friend ListGen;

		public:
			
			GenIterator(const GenIterator && other);

			GenIterator & operator=(const GenIterator & other);

			void * getPtr();

			bool operator==(const GenIterator && other) const;
			bool operator!=(const GenIterator && other) const;

			GenIterator & operator++();
			GenIterator & operator--();

		protected:

			GenIterator(ListGenNode * node);

			ListGenNode * _current_node;
		};

		ListGen();
		~ListGen();

		void clear();

		GenIterator gBegin();
		GenIterator gEnd();

		unsigned int size() const;

		bool empty() const;

	protected:

		struct ListGenNode
		{
			virtual void * getDataPtr() =0;
			ListGenNode * prev, * next;
		};

		ListGenNode * _beg;
		ListGenNode * _end;

		virtual ListGenNode * alloc() =0;
		virtual void dealloc(ListGenNode * ptr);
		virtual void deallocEverything();

		unsigned int _size;

	private:

		//temporary
		ListGen(ListGen && other) = delete;
		ListGen & operator=(ListGen && other) = delete;
	};

	template <typename C>
	class List
		: public ListGen
	{
	private:

		struct ListNode;

	public:

		class ConstIterator;

		class Iterator
		{

			friend List<C>;

		public:

			Iterator(const Iterator && other);

			C & operator*() const;
			C * operator->() const;

			Iterator & operator++();
			Iterator & operator--();

			bool operator==(const Iterator & other) const;
			bool operator!=(const Iterator & other) const;

			operator ConstIterator() const;

		private:

			Iterator(ListNode * node);

			ListNode * _node;
		};

		class ConstIterator
		{

			friend List<C>;

		public:

			ConstIterator(const ConstIterator && other);

			const C & operator*() const;
			const C * operator->() const;

			ConstIterator & operator++();
			ConstIterator & operator--();

			bool operator==(const ConstIterator & other) const;
			bool operator!=(const ConstIterator & other) const;

		private:

			ConstIterator(ListNode * node);

			ListNode * _node;
		};

		List();

		Iterator begin();
		Iterator end();
		ConstIterator begin() const;
		ConstIterator end() const;

		Iterator push(const C & item);
		Iterator insert(Iterator where, const C & item);
		Iterator remove(Iterator where);


	protected:

		virtual ListGenNode * alloc();

		struct ListNode
			: public ListGenNode
		{

			friend List<C>;

		public:

			virtual void * getDataPtr();

		private:

			C _data;
		};
	};

	/*
	Template parameters:
	first: contained type
	second: allocator class
	*/
	template <typename C, template <class> class A>
	class CustomAllocList
		: public List<C>
	{
	public:

		CustomAllocList();

	protected:

		virtual ListGenNode * alloc();
		virtual void dealloc(ListGenNode * ptr);
		virtual void deallocEverything();

	private:

		FixedAllocator<ListNode> & _alloc;
	};
}




template <typename C>
m3dfw::List<C>::Iterator::Iterator(typename m3dfw::List<C>::ListNode * node)
{
	_node = node;
}

template <typename C>
m3dfw::List<C>::Iterator::Iterator(const typename m3dfw::List<C>::Iterator && other)
{
	_node = other._node;
}

template <typename C>
typename m3dfw::List<C>::Iterator & m3dfw::List<C>::Iterator::operator++()
{
	_node = (m3dfw::List<C>::ListNode *)_node->next;

	return *this;
}

template <typename C>
typename m3dfw::List<C>::Iterator & m3dfw::List<C>::Iterator::operator--()
{
	_node = (m3dfw::List<C>::ListNode *)_node->prev;

	return *this;
}

template <typename C>
bool m3dfw::List<C>::Iterator::operator==(const typename m3dfw::List<C>::Iterator & other) const
{
	return _node == _node;
}

template <typename C>
bool m3dfw::List<C>::Iterator::operator!=(const typename m3dfw::List<C>::Iterator & other) const
{
	return _node != _node;
}

template <typename C>
C & m3dfw::List<C>::Iterator::operator*() const
{
	return **_node;
}

template <typename C>
C * m3dfw::List<C>::Iterator::operator->() const
{
	return &**_node;
}

template <typename C>
m3dfw::List<C>::ConstIterator::ConstIterator(typename m3dfw::List<C>::ListNode * node)
{
	_node = node;
}

template <typename C>
m3dfw::List<C>::ConstIterator::ConstIterator(const typename m3dfw::List<C>::ConstIterator && other)
{
	_node = other._node;
}

template <typename C>
typename m3dfw::List<C>::ConstIterator & m3dfw::List<C>::ConstIterator::operator++()
{
	_node = (m3dfw::List<C>::ListNode *)_node->next;

	return *this;
}

template <typename C>
typename m3dfw::List<C>::ConstIterator & m3dfw::List<C>::ConstIterator::operator--()
{
	_node = (m3dfw::List<C>::ListNode *)_node->prev;

	return *this;
}

template <typename C>
bool m3dfw::List<C>::ConstIterator::operator==(const typename m3dfw::List<C>::ConstIterator & other) const
{
	return _node == other._node;
}

template <typename C>
bool m3dfw::List<C>::ConstIterator::operator!=(const typename m3dfw::List<C>::ConstIterator & other) const
{
	return _node != other._node;
}

template <typename C>
const C & m3dfw::List<C>::ConstIterator::operator*() const
{
	return *(C *)_node->getDataPtr();
}

template <typename C>
const C * m3dfw::List<C>::ConstIterator::operator->() const
{
	return (C *)_node->getDataPtr();
}

template <typename C>
void * m3dfw::List<C>::ListNode::getDataPtr()
{
	return &_data;
}

template <typename C>
m3dfw::List<C>::List()
{
	_beg = alloc();
	_end = alloc();

	_beg->prev = nullptr;
	_beg->next = _end;
	_end->prev = _beg;
	_end->next = nullptr;
}

template <typename C>
typename m3dfw::ListGen::ListGenNode * m3dfw::List<C>::alloc()
{
	return new ListNode();
}

template <typename C>
typename m3dfw::List<C>::Iterator m3dfw::List<C>::begin()
{
	return Iterator((ListNode *)_beg);
}

template <typename C>
typename m3dfw::List<C>::Iterator m3dfw::List<C>::end()
{
	return Iterator((ListNode *)_end);
}

template <typename C>
m3dfw::List<C>::Iterator::operator typename m3dfw::List<C>::ConstIterator() const
{
	return ConstIterator(_node);
}

template <typename C>
typename m3dfw::List<C>::ConstIterator m3dfw::List<C>::begin() const
{
	return ConstIterator((ListNode *)_beg->next);
}

template <typename C>
typename m3dfw::List<C>::ConstIterator m3dfw::List<C>::end() const
{
	return ConstIterator((ListNode *)_end);
}

template <typename C>
typename m3dfw::List<C>::Iterator m3dfw::List<C>::push(const C & item)
{
	return insert(end(), item);
}

template <typename C>
typename m3dfw::List<C>::Iterator m3dfw::List<C>::insert(typename m3dfw::List<C>::Iterator where, const C & item)
{
	ListGenNode * next = where._node;
	ListGenNode * prev = where._node->prev;
	ListNode * new_node = (ListNode *)alloc();
	if(prev)
		prev->next = new_node;
	next->prev = new_node;
	new_node->prev = prev;
	new_node->next = next;

	new_node->_data = item;

	_size++;

	return Iterator(new_node);
}

template <typename C>
typename m3dfw::List<C>::Iterator m3dfw::List<C>::remove(typename m3dfw::List<C>::Iterator where)
{
	ListGenNode * prev = where._node->prev;
	ListGenNode * next = where._node->next;
	dealloc(where._node);
	prev->next = next;
	next->prev = prev;

	_size--;

	return Iterator((ListNode *)next);
}

template <typename C, template <class> class A>
m3dfw::CustomAllocList<C, A>::CustomAllocList() : _alloc(A<m3dfw::List<C>::ListNode>(128)) //T I N K E R   I T
{
}

template <typename C, template <class> class A>
typename m3dfw::ListGen::ListGenNode * m3dfw::CustomAllocList<C, A>::alloc()
{
	return _alloc.alloc();
}

template <typename C, template <class> class A>
void m3dfw::CustomAllocList<C, A>::dealloc(m3dfw::ListGen::ListGenNode * ptr)
{
	_alloc.dealloc(ptr);
}

template <typename C, template <class> class A>
void m3dfw::CustomAllocList<C, A>::deallocEverything()
{
	_alloc.deallocEverything();
}