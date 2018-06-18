#pragma once

#include <atomic>
#include <list>
#include <map>

#include "HardwareInfo.h"

#define M3DFW_PLACEMENT_NEW(T, ...) [](T * ptr){ new(ptr)T(##__VA_ARGS__); } //Creates lanbda for creating initialized objects at given address. Useful for m3dfw::createResourceArray function.

namespace m3dfw
{
	class SmartPtrRC
	{
	public:

		SmartPtrRC();
		SmartPtrRC(const SmartPtrRC & other);
		~SmartPtrRC();

		SmartPtrRC & operator=(const SmartPtrRC & other);

	protected:

		virtual void free() =0;

	private:

		void destroyInstance();

		std::atomic_uint * _ref_cnt;
	};

	struct SafeVPtr
		: SmartPtrRC
	{
	public:

		SafeVPtr(void * obj);

		void kill();

		bool isAlive() const;

		operator bool() const;

	protected:

		virtual void free();

		void *_ptr;

		std::atomic_bool * _is_avaible;
	};

	template <typename C>
	struct SafePtr
		: SafeVPtr
	{
	public:

		SafePtr(C & obj);

		C & operator*();
		C * operator->();
	};

	enum class AllocError
	{
		None,
		OutOfBoundAlloc,
		OutOfBoundDealloc,
		BadArgument,
		NothingToDealloc,
		UnknownError
	};

	////////////////////////////////////////// REWRITE! STRICT ALIASING RULE VIOLATION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	template <typename T>
	T * allocAligned(unsigned int count);

	void * allocAligned(unsigned int sz, unsigned int align_req);

	void * alignPtr(const void * ptr, unsigned int align_req);

	class Allocator
	{
	public:

		Allocator();

		virtual void * allocBytes(unsigned int sz, unsigned int align_req) =0;
		virtual bool dealloc(void * ptr) =0;
		virtual bool deallocEverything() = 0;

		template <typename T>
		T * alloc(unsigned int count);

		AllocError getErrorEnum();

	protected:

		AllocError _err;

		HardwareInfo & _hwi;

	private:

		// Non-copyable
		Allocator(const Allocator & other) = delete;
		Allocator & operator=(const Allocator & other) = delete;
	};

	template <typename C>
	class FixedAllocator
	{
		virtual C * alloc() =0;
		virtual bool dealloc(C * ptr) =0;
		virtual bool deallocEverything() =0;

		AllocError getErrorEnum();

	protected:

		AllocError _err;

		HardwareInfo & _hwi;

	private:

		// Non-copyable
		FixedAllocator(const FixedAllocator & other) = delete;
		FixedAllocator & operator=(const FixedAllocator & other) = delete;
	};

	class DynamicAllocator
		: public Allocator
	{
	public:

		virtual void freeUnusedMemory() = 0;

	protected:

		virtual void resize(unsigned int sz) =0;
	};

	class StaticStackAllocator
		: public Allocator
	{
	public:



		StaticStackAllocator(unsigned int sz);
		~StaticStackAllocator();

		virtual void * allocBytes(unsigned int sz, unsigned int align_req);
		virtual bool dealloc(void * ptr);
		virtual bool deallocEverything();

	private:

		char * _mem_block;
		char * _curpos;

		char * _end;

		char * _allocmem;
	};

	//BROKEN
	class DynamicStackAllocator
		: public DynamicAllocator
	{
	public:

		DynamicStackAllocator();
		DynamicStackAllocator(unsigned int sz);
		~DynamicStackAllocator();

		virtual void * allocBytes(unsigned int sz, unsigned int align_req);
		virtual bool dealloc(void * ptr);
		virtual bool deallocEverything();

		virtual void freeUnusedMemory();

	protected:

		virtual void resize(unsigned int sz);

	private:

		char * _mem_block;
		char * _curpos;

		char * _end;

		char * _allocmem;
	};

	/*class StaticLinearAllocator
		: public Allocator
	{
	public:

		StaticLinearAllocator(unsigned int sz);
		~StaticLinearAllocator();

		virtual void * allocBytes(unsigned int sz, unsigned int align_req);
		virtual bool dealloc(void * ptr);
		virtual bool deallocEverything();

	private:


	};*/

	//Allocation: O(1)
	//Deallocation: O(m), where m is a number of free cells that are present in range from deallocated cell that was allocated at the earliest and the target cell
	//Full Deallocation: O(n), where n is the totalnumber of cells
	class GenericStaticPoolAllocator
	{
		GenericStaticPoolAllocator(unsigned int type_size, unsigned int align_req, unsigned int pool_size);

		void * alloc();
		bool dealloc(void * ptr);
		bool deallocEverything();

		AllocError getErrorEnum();

	private:

		AllocError _err;

		HardwareInfo & _hwi;

		void * _free_cell;

		void * * _pool;

		unsigned int _cell_sz;
		unsigned int _cnt;
	};

	template <typename C>
	class StaticPoolAllocator
		: FixedAllocator<C>
	{
	public:

		StaticPoolAllocator(unsigned int pool_size);

		virtual C * alloc();
		virtual bool dealloc(C * ptr);
		virtual bool deallocEverything();

	private:

		GenericStaticPoolAllocator _palloc;
	};
}


template <typename C>
m3dfw::SafePtr<C>::SafePtr(C & obj) : SafeVPtr(&obj)
{
}

template <typename C>
C & m3dfw::SafePtr<C>::operator*()
{
	return *(C *)_ptr;
}

template <typename C>
C * m3dfw::SafePtr<C>::operator->()
{
	return (C *)_ptr;
}

template <typename T>
T * m3dfw::allocAligned(unsigned int count)
{
	return (T *)allocAligned(count * sizeof(T), alignof(T));
}

template <typename T>
T * m3dfw::Allocator::alloc(unsigned int count)
{
	return (T *)allocBytes(count * sizeof(T), alignof(T));
}

template <typename C>
m3dfw::AllocError m3dfw::FixedAllocator<C>::getErrorEnum()
{
	return _err;
}

template <typename C>
m3dfw::StaticPoolAllocator<C>::StaticPoolAllocator(unsigned int pool_size) : _palloc(sizeof(C), alignof(C), pool_size)
{
}

template <typename C>
C * m3dfw::StaticPoolAllocator<C>::alloc()
{
	return (C *)_palloc.alloc();
}

template <typename C>
bool m3dfw::StaticPoolAllocator<C>::dealloc(C * ptr)
{
	return _palloc.dealloc(ptr);
}

template <typename C>
bool m3dfw::StaticPoolAllocator<C>::deallocEverything()
{
	return _palloc.deallocEverything();
}