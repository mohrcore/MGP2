#include "MemoryManagement.h"

#include <xutility>

#include "Util.h"


#define M3DFW_REGISTER_FIXEDALLOC_CLASS_ID 


m3dfw::SmartPtrRC::SmartPtrRC()
{
	_ref_cnt = new std::atomic_uint();
	*_ref_cnt = 1;
}

m3dfw::SmartPtrRC::SmartPtrRC(const SmartPtrRC & other)
{
	_ref_cnt = other._ref_cnt;

	(*_ref_cnt)++;
}

m3dfw::SmartPtrRC::~SmartPtrRC()
{
	destroyInstance();
}

m3dfw::SmartPtrRC & m3dfw::SmartPtrRC::operator=(const m3dfw::SmartPtrRC & other)
{
	destroyInstance();

	_ref_cnt = other._ref_cnt;
	(*_ref_cnt)++;

	return *this;
}

void m3dfw::SmartPtrRC::destroyInstance()
{
	(*_ref_cnt)--;

	if (*_ref_cnt == 0)
	{
		free();

		delete _ref_cnt;
	}
}


m3dfw::SafeVPtr::SafeVPtr(void * obj) : _ptr(obj)
{
	_is_avaible = new std::atomic_bool(true);
}

void m3dfw::SafeVPtr::free()
{
	delete _is_avaible;
}

void m3dfw::SafeVPtr::kill()
{
	_is_avaible = false;
}

bool m3dfw::SafeVPtr::isAlive() const
{
	return _is_avaible;
}

m3dfw::SafeVPtr::operator bool() const
{
	return _is_avaible;
}

void * m3dfw::allocAligned(unsigned int sz, unsigned int align_req)
{
	char * ptr = new char[sz + max(HardwareInfo::getInstance().getCPUCacheLineSize(), align_req) - 1];

	if((size_t)ptr % align_req != 0)
		ptr += align_req - ((size_t)ptr % align_req);

	return ptr;
}


m3dfw::Allocator::Allocator() : _hwi(HardwareInfo::getInstance())
{
}

void * m3dfw::alignPtr(const void * ptr, unsigned int align_req)
{
	if((size_t)ptr % align_req != 0)
		return (char*)ptr + align_req - ((size_t)ptr % align_req);
	else return (void *)ptr;
}

m3dfw::AllocError m3dfw::Allocator::getErrorEnum()
{
	return _err;
}


m3dfw::StaticStackAllocator::StaticStackAllocator(unsigned int sz)
{
	_allocmem = new char[sz + _hwi.getCPUCacheLineSize() - 1];

	_mem_block = (char *)alignPtr(_allocmem, _hwi.getCPUCacheLineSize());

	_end = _mem_block + sz;
	_curpos = _mem_block;
}

m3dfw::StaticStackAllocator::~StaticStackAllocator()
{
	delete[] _allocmem;
}

void * m3dfw::StaticStackAllocator::allocBytes(unsigned int sz, unsigned int align_req)
{
	_curpos = (char *)alignPtr(_curpos, max(align_req, _hwi.getCPUCacheLineSize()));

	if (_curpos + sz >= _end)
	{
		_err = AllocError::OutOfBoundAlloc;
		return nullptr;
	}

	_curpos += sz;

	return _curpos - sz;
}

bool m3dfw::StaticStackAllocator::dealloc(void * ptr)
{
	if (ptr < _mem_block || ptr >= _end)
	{
		_err = AllocError::OutOfBoundDealloc;
		return false;
	}
	if (ptr >= _curpos)
	{
		_err = AllocError::NothingToDealloc;
		return false;
	}

	_curpos = (char *)ptr;

	return true;
}

bool m3dfw::StaticStackAllocator::deallocEverything()
{
	_curpos = _mem_block;

	return true;
}


m3dfw::DynamicStackAllocator::DynamicStackAllocator()
{
	_allocmem = new char[1 + _hwi.getCPUCacheLineSize()];

	_mem_block = (char *)alignPtr(_curpos, _hwi.getCPUCacheLineSize());

	_curpos = _mem_block;
	_end = _curpos + 1;
}

m3dfw::DynamicStackAllocator::DynamicStackAllocator(unsigned int sz)
{
	_mem_block = new char[sz + _hwi.getCPUCacheLineSize() - 1];

	_curpos = (char *)alignPtr(_mem_block, _hwi.getCPUCacheLineSize());
	_end = _curpos + sz;
}

m3dfw::DynamicStackAllocator::~DynamicStackAllocator()
{
	delete[] _mem_block;
}

void * m3dfw::DynamicStackAllocator::allocBytes(unsigned int sz, unsigned int align_req)
{
	_curpos = (char *)alignPtr(_curpos, max(align_req, _hwi.getCPUCacheLineSize() - 1));

	if (_curpos + sz >= _end)
	{
		unsigned int req_sz = (_curpos + sz) - _mem_block;
		unsigned int e_sz = _end - _mem_block;
		while (e_sz < req_sz)
			e_sz *= 2;

		resize(e_sz);
	}
		
	_curpos += sz;

	return _curpos - sz;
}

bool m3dfw::DynamicStackAllocator::dealloc(void * ptr)
{
	if (ptr < _mem_block || ptr >= _end)
	{
		_err = AllocError::OutOfBoundDealloc;
		return false;
	}
	if (ptr >= _curpos)
	{
		_err = AllocError::NothingToDealloc;
		return false;
	}

	_curpos = (char *)ptr;

	return true;
}

bool m3dfw::DynamicStackAllocator::deallocEverything()
{
	_curpos = _mem_block;

	return true;
}

void m3dfw::DynamicStackAllocator::resize(unsigned int sz)
{
	char * old_data = _mem_block;

	_mem_block = new char[sz];

	if (sz >= _curpos - _mem_block)
	{
		std::copy(old_data, _curpos, _mem_block);
		_curpos = _mem_block + (_curpos - old_data);
	}
	else
	{
		std::copy(old_data, old_data + sz, _mem_block);
		_curpos = _mem_block + sz;
	}

	_end = _mem_block + sz;
}

void m3dfw::DynamicStackAllocator::freeUnusedMemory()
{
	unsigned int req_sz = _curpos - _mem_block;
	unsigned int e_sz = _end - _mem_block;

	while (e_sz / 2 >= req_sz)
		e_sz /= 2;

	resize(e_sz);
}

m3dfw::GenericStaticPoolAllocator::GenericStaticPoolAllocator(unsigned int type_size, unsigned int align_req, unsigned int pool_size) : _cell_sz(max(type_size, sizeof(void *))), _cnt(pool_size), _hwi(HardwareInfo::getInstance()), _err(AllocError::None)
{
	unsigned int align = max(align_req, _hwi.getCPUCacheLineSize()); //Calculate memory alignment

	_pool = (void * *)new char[_cell_sz * (pool_size) + align]; //Allocate required memory
	_pool = (void * *)alignPtr(_pool, align); //Align pool pointer

	char * cpool = (char *)_pool; //Just a quick cast for the sake of code clarity (Ahem)

	for (int i = 0; i < pool_size - 1; i++)
		*(void * *)(cpool + _cell_sz * i) = (void *)(cpool + _cell_sz * (i + 1)); //Set cell's value to pointer to the next cell
	*(void * *)(cpool + _cell_sz * (pool_size - 1)) = nullptr; //Set last cell to point nullptr

	_free_cell = _pool; //Set the free cell pointer to beggining of the pool
}

void * m3dfw::GenericStaticPoolAllocator::alloc()
{
	void * ptr = _free_cell;
	_free_cell = (void *)*(char *)_free_cell; //Set free_cell

	return ptr;
}

bool m3dfw::GenericStaticPoolAllocator::dealloc(void * ptr)
{
	if (ptr < _free_cell)
	{
		if (ptr < _pool)
		{
			_err = AllocError::OutOfBoundDealloc;
			return false;
		}
		*(void * *)ptr = _free_cell;
		_free_cell = ptr;

		return true;
	}

	if (ptr == _free_cell)
	{
		_err = AllocError::NothingToDealloc;
		return false;
	}

	void * c_free = _free_cell;

	while ((ptr > *(void * *)c_free) && (*(void * *)c_free != nullptr)) //Search trough free-list for a free cell that is before ptr and points to nullptr, or a free cell that is after ptr.
		c_free = *(void * *)c_free;

	void * next_free = *(void * *)c_free;;

	*(void * *)c_free = ptr;
	*(void * *)ptr = next_free;

	return true;
}

bool m3dfw::GenericStaticPoolAllocator::deallocEverything()
{
	char * cpool = (char *)_pool; //Just a quick cast for the sake of code clarity (Ahem)

	for (int i = 0; i < _cnt - 1; i++)
		*(void * *)(cpool + _cell_sz * i) = (void *)(cpool + _cell_sz * (i + 1)); //Set cell's value to pointer to the next cell
	*(void * *)(cpool + _cell_sz * (_cnt - 1)) = nullptr; //Set last cell to point nullptr

	_free_cell = _pool; //Set the free cell pointer to beggining of the pool

	return true;
}

m3dfw::AllocError m3dfw::GenericStaticPoolAllocator::getErrorEnum()
{
	return _err;
}