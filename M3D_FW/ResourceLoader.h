#pragma once

#include <string>

#include <MFiles.h>


#include "ResourceManager.h"
#include "GfxModel3dLoader.h"
#include "GTexture2dLoader.h"
#include "GMaterialLoader.h"
#include "GMaterial.h"
#include "Resource.h"
#include "ShaderManager.h"
#include "Util.h"


namespace m3dfw
{
	enum ResourceLoaderExceptions : int
	{
		FileNotFoundException,
		UnknownFileExtensionException,
		ErrorLoadingFileException,
		ErrorReadingDataException,
		ErrorImportingFileException
	};

	class ResourceLoader
	{
	public:

		ResourceLoader(ResourceManager & res_mngr);
		~ResourceLoader();

		Resource<GfxModel3d> & importGfxModel3d(const std::string & path, const std::string & name);
		Resource<GTexture2d> & importGTexture2d(const std::string & path, const std::string & name);
		Resource<GMaterial> & importGMaterial(const std::string & path, const std::string & name, ShaderManager & sm);

	private:

		GfxModel3dLoader _gfxmodel3dloader;
		GTexture2dLoader _gtexture2dloader;
		GMaterialLoader _gmaterialloader;

		ResourceManager & _rm;
	};

	bool loadMaterialResourcesFromMDPFile(const std::string & path, m3dfw::ResourceLoader & rloader, m3dfw::ShaderManager & sm);
}