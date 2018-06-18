#include "ResourceLoader.h"

#include <msclr\marshal_cppstd.h>


using namespace m3dfw_cli;
using namespace msclr::interop;


void ResourceLoader::importGfxModel3d(System::String ^ path, System::String ^ name)
{
	try
	{
		_instance->importGfxModel3d(marshal_as<std::string>(path), marshal_as<std::string>(name));
	}
	catch (m3dfw::ResourceLoaderExceptions e)
	{
		switch (e)
		{
		case m3dfw::ResourceLoaderExceptions::ErrorImportingFileException:
			throw gcnew ResourceLoader_Exception(ResourceLoader_ExceptionEnum::ErrorImportingFileException, "An error has occured when trying to read file \"" + path + "\"");
			break;

		case m3dfw::ResourceLoaderExceptions::ErrorLoadingFileException:
			throw gcnew ResourceLoader_Exception(ResourceLoader_ExceptionEnum::ErrorLoadingFileException, "An error has occured when trying to load file \"" + path + "\"");
			break;

		case m3dfw::ResourceLoaderExceptions::ErrorReadingDataException:
			throw gcnew ResourceLoader_Exception(ResourceLoader_ExceptionEnum::ErrorReadingDataException, "An error has occured when trying to read data from file \"" + path + "\"");
			break;

		default:
			throw gcnew ResourceLoader_Exception(ResourceLoader_ExceptionEnum::UnknownException, "An unknown exception has occured");
			break;
		}
	}
}

void ResourceLoader::importGTexture2d(System::String ^ path, System::String ^ name)
{
	try
	{
		_instance->importGTexture2d(marshal_as<std::string>(path), marshal_as<std::string>(name));
	}
	catch (m3dfw::ResourceLoaderExceptions e)
	{
		switch (e)
		{
		case m3dfw::ResourceLoaderExceptions::ErrorImportingFileException:
			throw gcnew ResourceLoader_Exception(ResourceLoader_ExceptionEnum::ErrorImportingFileException, "An error has occured when trying to read file \"" + path + "\"");
			break;

		case m3dfw::ResourceLoaderExceptions::ErrorLoadingFileException:
			throw gcnew ResourceLoader_Exception(ResourceLoader_ExceptionEnum::ErrorLoadingFileException, "An error has occured when trying to load file \"" + path + "\"");
			break;

		case m3dfw::ResourceLoaderExceptions::ErrorReadingDataException:
			throw gcnew ResourceLoader_Exception(ResourceLoader_ExceptionEnum::ErrorReadingDataException, "An error has occured when trying to read data from file \"" + path + "\"");
			break;

		default:
			throw gcnew ResourceLoader_Exception(ResourceLoader_ExceptionEnum::UnknownException, "An unknown exception has occured");
			break;
		}
	}
}

void ResourceLoader::importGMaterial(System::String ^ path, System::String ^ name, ShaderManager ^ sm)
{
	try
	{
		_instance->importGMaterial(marshal_as<std::string>(path), marshal_as<std::string>(name), (m3dfw::ShaderManager *)sm->getInstance());
	}
	catch (m3dfw::ResourceLoaderExceptions e)
	{
		switch (e)
		{
		case m3dfw::ResourceLoaderExceptions::ErrorImportingFileException:
			throw gcnew ResourceLoader_Exception(ResourceLoader_ExceptionEnum::ErrorImportingFileException, "An error has occured when trying to read file \"" + path + "\"");
			break;

		case m3dfw::ResourceLoaderExceptions::ErrorLoadingFileException:
			throw gcnew ResourceLoader_Exception(ResourceLoader_ExceptionEnum::ErrorLoadingFileException, "An error has occured when trying to load file \"" + path + "\"");
			break;

		case m3dfw::ResourceLoaderExceptions::ErrorReadingDataException:
			throw gcnew ResourceLoader_Exception(ResourceLoader_ExceptionEnum::ErrorReadingDataException, "An error has occured when trying to read data from file \"" + path + "\"");
			break;

		default:
			throw gcnew ResourceLoader_Exception(ResourceLoader_ExceptionEnum::UnknownException, "An unknown exception has occured");
			break;
		}
	}
}


ResourceLoader_Exception::ResourceLoader_Exception(ResourceLoader_ExceptionEnum t, System::String ^ d) : type(t), details(d)
{
}