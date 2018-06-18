#pragma once

#include <M3DFW.h>

#include "ResourceManager.h"
#include "ShaderManager.h"


namespace m3dfw_cli
{
	public enum class ResourceLoader_ExceptionEnum
	{
		FileNotFoundException,
		UnknownFileExtensionException,
		ErrorLoadingFileException,
		ErrorReadingDataException,
		ErrorImportingFileException,
		UnknownException
	};

	public ref class ResourceLoader_Exception
	{
	public:

		ResourceLoader_Exception(ResourceLoader_ExceptionEnum t, System::String ^ d);

		ResourceLoader_ExceptionEnum type;
		System::String ^ details;
	};

	public ref class ResourceLoader
	{
	public:

		void importGfxModel3d(System::String ^ path, System::String ^ name);
		void importGTexture2d(System::String ^ path, System::String ^ name);
		void importGMaterial(System::String ^ path, System::String ^ name, ShaderManager ^ sm);

	protected:

		m3dfw::ResourceLoader * _instance;
	};
}