#include "List.h"


m3dfw::ListGen::ListGen() : _size(0)
{
}

m3dfw::ListGen::~ListGen()
{
	deallocEverything();
}

void m3dfw::ListGen::clear()
{
	if (empty())
		return;

	deallocEverything();

	_beg = alloc();
	_end = _beg;

	_beg->prev = nullptr;
	_beg->next = nullptr;

	_size = 0;
}

void m3dfw::ListGen::deallocEverything()
{
	if (empty())
		return;

	ListGenNode * node = _beg;
	while (node != _end)
	{
		ListGenNode * next = node->next;
		delete node;
		node = next;
	}
}

void m3dfw::ListGen::dealloc(m3dfw::ListGen::ListGenNode * ptr)
{
	delete ptr;
}

m3dfw::ListGen::GenIterator::GenIterator(m3dfw::ListGen::ListGenNode * node)
{
	_current_node = node;
}

m3dfw::ListGen::GenIterator::GenIterator(const m3dfw::ListGen::GenIterator && other) : _current_node(other._current_node)
{
}

typename m3dfw::ListGen::GenIterator & m3dfw::ListGen::GenIterator::operator=(const typename m3dfw::ListGen::GenIterator & other)
{
	_current_node = other._current_node;

	return *this;
}

void * m3dfw::ListGen::GenIterator::getPtr()
{
	return _current_node->getDataPtr();
}

bool m3dfw::ListGen::GenIterator::operator==(const typename m3dfw::ListGen::GenIterator && other) const
{
	return _current_node == other._current_node;
}

bool m3dfw::ListGen::GenIterator::operator!=(const typename m3dfw::ListGen::GenIterator && other) const
{
	return _current_node != other._current_node;
}

typename m3dfw::ListGen::GenIterator & m3dfw::ListGen::GenIterator::operator++()
{
	_current_node = _current_node->next;

	return *this;
}

m3dfw::ListGen::GenIterator & m3dfw::ListGen::GenIterator::operator--()
{
	_current_node = _current_node->prev;

	return *this;
}

m3dfw::ListGen::GenIterator m3dfw::ListGen::gBegin()
{
	return GenIterator(_beg);
}

m3dfw::ListGen::GenIterator m3dfw::ListGen::gEnd()
{
	return GenIterator(_end);
}

unsigned int m3dfw::ListGen::size() const
{
	return _size;
}

bool m3dfw::ListGen::empty() const
{
	return _size == 0;
}