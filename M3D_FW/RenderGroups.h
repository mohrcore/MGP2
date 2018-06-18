#pragma once

#include <vector>

#include "RenderConfigInfo.h"

#define __M3DFWINT_DEFAULT_RENDERGROUPS_COUNT 16

namespace m3dfw
{
	typedef unsigned int RGID; // Render Group ID

	class RenderGroup
	{
	public:

		RenderConfiguration config;

		//void getGroupMembers(std::vector<RenderConfigInfo &> & target);

	private:

	};

	class RenderGroups
	{
	public:

		RenderGroups(unsigned int rendergroups_count = __M3DFWINT_DEFAULT_RENDERGROUPS_COUNT);
		~RenderGroups();

		RenderConfiguration & getGroupConfig(RGID id);

	private:

		RenderGroup * _groups;
		unsigned int _group_count;
	};
}


