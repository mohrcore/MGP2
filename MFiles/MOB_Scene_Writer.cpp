#include "MOB_Scene_Writer.h"

#include "Util.h"


unsigned int calculateRequiredFileSpace(const mfile::MOB_Scene & scene)
{
	unsigned int req_sz = 0;

	req_sz += mfile::cStrSize(scene.name);
	req_sz += sizeof(scene.models_count);
	req_sz += sizeof(scene.lights_count);
	req_sz += sizeof(scene.cameras_count);

	req_sz += scene.lights_count * sizeof(float) * 3;
	req_sz += scene.cameras_count * sizeof(float) * 3;

	for (unsigned int i = 0; i < scene.models_count; i++)
	{
		req_sz += mfile::cStrSize(scene.models[i].name);
		req_sz += mfile::cStrSize(scene.models[i].path);
	}

	return req_sz;
}

bool mfile::writeScene(mfile::MFile & target, const mfile::MOB_Scene & source)
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

	target.write(source.models_count);
	target.write(source.lights_count);
	target.write(source.cameras_count);

	for (unsigned int i = 0; i < source.models_count; i++)
	{
		target.writeCStr(source.models[i].name);
		target.writeCStr(source.models[i].path);
	}

	target.writeRange(source.light_data, source.lights_count * sizeof(float) * 3);
	target.writeRange(source.camera_data, source.cameras_count * sizeof(float) * 3);
}