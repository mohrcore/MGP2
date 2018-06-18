#pragma once

#include "MOB_Res.h"

namespace mfile
{
	class MOB_Material
	{
	public:

		MOB_Material();
		MOB_Material(const MOB_Material & other);
		~MOB_Material();

		MOB_Material & operator=(const MOB_Material & other);

		bool operator==(const MOB_Material & other) const;
		bool operator!=(const MOB_Material & other) const;
		
		char * name;

		MOB_Res * textures;
		unsigned long texture_cnt;

		MOB_ShadingProgram program;

		void clear();
	}; 
}

