#pragma once

namespace mfile
{
	struct MOB_Res
	{
		MOB_Res();
		MOB_Res(const MOB_Res & other);
		MOB_Res(const char * n, const char * p);
		~MOB_Res();

		MOB_Res & operator=(const MOB_Res & other);

		bool operator==(const MOB_Res & other) const;
		bool operator!=(const MOB_Res & other) const;

		char * name;
		char * path;

		void clear();
	};

	struct MOB_ShadingProgram
	{
		MOB_ShadingProgram();
		MOB_ShadingProgram(const MOB_ShadingProgram & other);
		MOB_ShadingProgram(const char * n, const char * p_vert, const char * p_frag);
		~MOB_ShadingProgram();

		MOB_ShadingProgram & operator=(const MOB_ShadingProgram & other);

		bool operator==(const MOB_ShadingProgram & other) const;
		bool operator!=(const MOB_ShadingProgram & other) const;

		char * name;
		char * vertex_path;
		char * fragment_path;

		void clear();
	};
}