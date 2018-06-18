#include "GMaterialLoader.h"

#include <string>

#include "Util.h"



m3dfw::GMaterialLoader::GMaterialLoader(m3dfw::ResourceManager & rm) : _rm(rm)
{
}

m3dfw::GMaterialLoader::~GMaterialLoader()
{
}

bool m3dfw::GMaterialLoader::loadGMaterialFromMOB_Material(m3dfw::GMaterial & target, const mfile::MOB_Material & source, std::string rootdir, m3dfw::ShaderManager & sm)
{
	ShID prog_id;

	m3dfw::addSlashToDirIfMissing(rootdir);

	if (!sm.isShaderAvaible(source.program.name))
	{
		try
		{
			prog_id = sm.loadProgram(rootdir + source.program.vertex_path, rootdir + source.program.fragment_path, source.program.name);
		}
		catch(ShaderManagerExceptions e)
		{
			return false;
		}
	}
	else
		prog_id = sm.getID(source.program.name);

	target.setProgram(prog_id);

	target.setTextureCount(source.texture_cnt);

	for (unsigned int i = 0; i < target.getTextureCount(); i++)
	{
		if (!_rm.isResourceAvaible<GTexture2d>(source.textures[i].name))
			return false;

		target.setTexture(i, _rm.getResource<GTexture2d>(source.textures[i].name));
	}

	return true;
}