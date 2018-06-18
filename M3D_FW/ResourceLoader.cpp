#include "ResourceLoader.h"

#include "Util.h"


#include <SDL.h>
#include <SDL_image.h>


m3dfw::ResourceLoader::ResourceLoader(m3dfw::ResourceManager & res_mngr) : _rm(res_mngr), _gfxmodel3dloader(res_mngr), _gmaterialloader(res_mngr)
{
}


m3dfw::ResourceLoader::~ResourceLoader()
{
}


m3dfw::Resource<m3dfw::GfxModel3d> & m3dfw::ResourceLoader::importGfxModel3d(const std::string & path, const std::string & name)
{
	mfile::MFile file(path);

	if (!file.good())
		throw ResourceLoaderExceptions::ErrorLoadingFileException;

	mfile::MOB_Model3d mob_model;

	auto & resource = _rm.addResource(new GfxModel3d, name);

	if (!mfile::loadModel3d(file, mob_model))
		throw ResourceLoaderExceptions::ErrorImportingFileException;

	if (!_gfxmodel3dloader.loadGfxModel3dFromMOB_Model(*resource, mob_model))
		throw ResourceLoaderExceptions::ErrorReadingDataException;

	return resource;
}

m3dfw::Resource<m3dfw::GTexture2d> & m3dfw::ResourceLoader::importGTexture2d(const std::string & path, const std::string & name)
{
	std::string ext = getFilenameExtension(path);

	SDL_Surface * surf;

	//Try loading file
	if (ext == "png" || ext == "bmp" || ext == "jpg")
	{
		if (!(surf = IMG_Load(path.c_str())))
			throw ResourceLoaderExceptions::ErrorLoadingFileException;
	}
	else
		throw ResourceLoaderExceptions::UnknownFileExtensionException;

	auto & resource = _rm.addResource(new GTexture2d, name);

	if (!_gtexture2dloader.loadTextureFromSDLSurface(*resource, surf, RGB))
		throw ResourceLoaderExceptions::ErrorReadingDataException;

	if (resource->src_path != nullptr)
		delete[] resource->src_path;
	resource->src_path = new char[path.length()];
	std::copy(path.c_str(), path.c_str() + path.length() + 1, resource->src_path);

	SDL_FreeSurface(surf);

	return resource;
}

m3dfw::Resource<m3dfw::GMaterial> & m3dfw::ResourceLoader::importGMaterial(const std::string & path, const std::string & name, m3dfw::ShaderManager & sm)
{
	mfile::MFile file(path);

	std::string dir = getFileDir(path);
	if(!dir.empty())
		dir += "/";

	if(!file.good())
		throw ResourceLoaderExceptions::ErrorLoadingFileException;

	mfile::MOB_Material material;

	auto & resource = _rm.addResource(new GMaterial(sm), name);

	if (!mfile::loadMaterial(file, material))
		throw ResourceLoaderExceptions::ErrorImportingFileException;

	//Import textures if not already imported
	for (int i = 0; i < material.texture_cnt; i++)
		if (!_rm.isResourceAvaible<GTexture2d>(material.textures[i].name))
			importGTexture2d(dir + material.textures[i].path, material.textures[i].name);

	if (!_gmaterialloader.loadGMaterialFromMOB_Material(*resource, material, dir, sm))
		throw ResourceLoaderExceptions::ErrorReadingDataException;

	return resource;
}

bool m3dfw::loadMaterialResourcesFromMDPFile(const std::string & path, m3dfw::ResourceLoader & rloader, m3dfw::ShaderManager & sm)
{
	std::ifstream stream(path);

	if (!stream.good())
		return false;

	std::string dir = getFileDir(path);

	if (!dir.empty())
		dir += "/";

	std::string n, p;

	GLenum error = glGetError();

	while (stream >> n >> p)
	{
		try
		{
			rloader.importGMaterial(dir + p, n, sm);
		}
		catch (ResourceLoaderExceptions ex)
		{
			return false;
		}
	}
		

	error = glGetError();

	return true;
}