#pragma once

#include "MemoryManagement.h"

#define M3DFW_createInitializedResourceArray(S, T, ...) m3dfw::createResourceArray<T>(S, [](m3dfw::Resource<T> * ptr){ new(ptr)m3dfw::Resource<T>(new T(##__VA_ARGS__)); });

namespace m3dfw
{
	class ResourceBase
		: public SmartPtrRC
	{
	public:

		ResourceBase();
		~ResourceBase();

		void * getResourcePtr();

		//Noncopyable
		//ResourceBase(const ResourceBase & other) = delete;
		//ResourceBase & operator=(const ResourceBase & other) = delete;

	protected:

		void * _res;
	};


	template <typename T>
	class Resource
		: public ResourceBase
	{
	public:

		Resource(T * res_ptr);
		//~Resource();

		T & operator*();
		T * operator->();

		const T & operator*() const;
		const T * operator->() const;

	protected:

		virtual void free();

		//T * _res;
	};

	template <typename T>
	using ResourcePlacementNew = void(*)(Resource<T> *);

	template <typename T>
	T & ResourceBaseDereference(ResourceBase * rb);
	template <typename T>
	Resource<T> * createResourceArray(unsigned int size, ResourcePlacementNew<T> placement_new);
	template <typename T>
	Resource<T> * copyResourceArray(unsigned int size, Resource<T> * arr);
}

// TEMPLATE IMPLEMENTATIONS ----------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
m3dfw::Resource<T>::Resource(T * res_ptr)/* : ResourceBase::_res(res_ptr)*/
{
	_res = res_ptr;
}

template <typename T>
void m3dfw::Resource<T>::free()
{
	delete (T *)_res;
}

template <typename T>
T & m3dfw::Resource<T>::operator*()
{
	return *(T *)_res;
}

template <typename T>
T * m3dfw::Resource<T>::operator->()
{
	return (T *)_res;
}

template <typename T>
const T & m3dfw::Resource<T>::operator*() const
{
	return *(T *)_res;
}

template <typename T>
const T * m3dfw::Resource<T>::operator->() const
{
	return (T *)_res;
}


template <typename T>
T & m3dfw::ResourceBaseDereference(m3dfw::ResourceBase * rb)
{
	return *(*(dynamic_cast<Resource<T> *>rb));
}

template <typename T>
m3dfw::Resource<T> * m3dfw::createResourceArray(unsigned int size, m3dfw::ResourcePlacementNew<T> placement_new)
{
	Resource<T> * t_ptr = allocAligned<Resource<T>>(size);
	for (unsigned int i = 0; i < size; i++)
		placement_new(t_ptr + i);

	return t_ptr;
}

template <typename T>
m3dfw::Resource<T> * m3dfw::copyResourceArray(unsigned int size, m3dfw::Resource<T> * arr)
{
	Resource<T> * t_ptr = allocAligned<Resource<T>>(size);
	for (unsigned int i = 0; i < size; i++)
		new(t_ptr + i)Resource<T>(arr[i]);

	return t_ptr;
}