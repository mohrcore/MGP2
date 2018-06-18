#include "MOB_Material_Writer.h"

#include "Util.h"

unsigned int calculateRequiredFileSpace(const mfile::MOB_Material & material)
{
	unsigned int req_sz = 0;

	req_sz += mfile::cStrSize(material.name);
	req_sz += sizeof(material.texture_cnt);

	req_sz += mfile::cStrSize(material.program.name);
	req_sz += mfile::cStrSize(material.program.vertex_path);
	req_sz += mfile::cStrSize(material.program.fragment_path);

	for (unsigned long i = 0; i < material.texture_cnt; i++)
	{
		req_sz += mfile::cStrSize(material.textures[i].name);
		req_sz += mfile::cStrSize(material.textures[i].path);
	}

	return req_sz;
}


bool mfile::writeMaterial(mfile::MFile & target, const mfile::MOB_Material & source)
{
	if (!target.good())
		return false;

	unsigned int req_sz = calculateRequiredFileSpace(source);

	target.resize(req_sz);

	target.goBeginning();

	if (source.name == nullptr)
		target.writeCStr("<NAME_UNKNOWN>");
	else
		target.writeCStr(source.name);

	target.writeCStr(source.program.name);
	target.writeCStr(source.program.vertex_path);
	target.writeCStr(source.program.fragment_path);
	target.write(source.texture_cnt);

	for (unsigned long i = 0; i < source.texture_cnt; i++)
	{
		target.writeCStr(source.textures[i].name);
		target.writeCStr(source.textures[i].path);
	}

	return true;
}