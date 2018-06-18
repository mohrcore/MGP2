#pragma once


namespace mfile
{
	struct MOB_GMesh3d
	{
	public:

		MOB_GMesh3d();
		~MOB_GMesh3d();

		void clear();

		unsigned long vertices_cnt;
		unsigned long indices_cnt;

		unsigned char vec3_per_vertex;
		unsigned char vec2_per_vertex;
		unsigned char f_per_vertex;

		//unsigned char texture_cnt;
		//unsigned char * textures;
		unsigned char material;

		float * v_data;

		unsigned long * i_data;

		const float * getVec3Data(unsigned int vertex, unsigned int id) const;
		const float * getVec2Data(unsigned int vertex, unsigned int id) const;
		float getFloatData(unsigned int vertex, unsigned int id) const;

		float * vec3Data(unsigned int vertex, unsigned int id);
		float * vec2Data(unsigned int vertex, unsigned int id);
		float & floatData(unsigned int vertex, unsigned int id);

		unsigned int getVertexSize() const;
	};

	class MOB_Model3d
	{
	public:

		MOB_Model3d();
		~MOB_Model3d();

		void clear();

		MOB_GMesh3d * meshes;

		unsigned long mesh_cnt;

		//char * * texture_names;
		char * * material_names;

		//unsigned long texture_cnt;
		unsigned long material_cnt;

		char * name;
	};
}


