#pragma once

#include "MOB_Model3d.h"

namespace mfile
{
	typedef unsigned int GMesh3dID;

	class EditableModel3d
		: public MOB_Model3d
	{
	public:

		EditableModel3d();
		~EditableModel3d();

		unsigned int getMeshCount() const;

		void setMeshCount(unsigned int count);

		unsigned int getVec3AttribCount(GMesh3dID m_id) const;
		unsigned int getVec2AttribCount(GMesh3dID m_id) const;
		unsigned int getFloatAttribCount(GMesh3dID m_id) const;

		void setAttribCount(GMesh3dID m_id, unsigned char vec3_count, unsigned char vec2_count, unsigned char float_count);
		//void setTextureCount(GMesh3dID m_id, unsigned char count);

	private:


	};
}