#include "RenderGroups.h"



m3dfw::RenderGroups::RenderGroups(unsigned int rendergroups_count) : _group_count(rendergroups_count)
{
	_groups = new RenderGroup[_group_count];
}


m3dfw::RenderGroups::~RenderGroups()
{
	delete[] _groups;
}

m3dfw::RenderConfiguration & m3dfw::RenderGroups::getGroupConfig(RGID id)
{
	return _groups[id].config;
}

//void m3dfw::RenderGroup::getGroupMembers(std::vector<m3dfw::RenderConfigInfo &> & target)
//{
//
//}