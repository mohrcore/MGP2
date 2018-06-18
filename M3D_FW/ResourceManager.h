#pragma once

#include <string>
#include <map>
#include <unordered_map>

#include "Resource.h"
#include "GfxModel3d.h"

namespace m3dfw
{
	//typedef unsigned int RsID; // Resource ID

	enum ResourceKind
	{
		GMESH3D,
		TEXTURE2D,
		AUDIO
	};

	enum ResourceManagerExceptions : int
	{
		ResourceWrongType
	};

	class ResourceManager
	{
	public:

		ResourceManager();
		~ResourceManager();

		//void loadResourcePack(const std::string & path);
		//void importResource(const std::string & path, const std::string & name, ResourceKind kind);

		template <typename T>
		Resource<T> & addResource(T * rs, const std::string & name);

		template <typename T>
		Resource<T> & getResource(const std::string & name);

		bool isAnyKindOfResourceAvaible(const std::string & name) const;
		template <typename T>
		bool isResourceAvaible(const std::string & name) const;

		void clearAllResources();

	private:

		//void importResourceGfxModel3d(const std::string & path, ResourceBase * res_ptr);

		std::unordered_map<std::string, ResourceBase *> _name_to_resource;
	};
}


// TEMPLATE IMPLEMENTATIONS ----------------------------------------------------------------------------------------------------------------------------------------------


template <typename T>
m3dfw::Resource<T> & m3dfw::ResourceManager::getResource(const std::string & name)
{
	auto ptr = dynamic_cast<Resource<T> *>(_name_to_resource[name]);
	if (ptr == nullptr)
		throw ResourceManagerExceptions::ResourceWrongType;

	return *ptr;
}

template <typename T>
m3dfw::Resource<T> & m3dfw::ResourceManager::addResource(T * rs, const std::string & name)
{
	auto * res = new Resource<T>(rs);
	_name_to_resource[name] = res;

	return *res;
}

template <typename T>
bool m3dfw::ResourceManager::isResourceAvaible(const std::string & name) const
{
	if (_name_to_resource.count(name) == 0)
		return false;

	if(dynamic_cast<const Resource<T> *>(_name_to_resource.at(name)))
		return true;

	return false;
}