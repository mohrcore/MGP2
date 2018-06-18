#include <M3DFW.h>

#include "EXPORT.h"

//GraphicsSystem class unwrap

m3dfw::GraphicsSystem PTR_EXPORT(*) m3dfw__new__GraphicsSystem()
{
	return new m3dfw::GraphicsSystem();
}

void EXPORT m3dfw__delete__GraphicsSystem(m3dfw::GraphicsSystem * o_ptr)
{
	delete o_ptr;
}

void EXPORT m3dfw__GraphicsSystem_execute(m3dfw::GraphicsSystem * o_ptr)
{
	o_ptr->execute();
}

void EXPORT m3dfw__GraphicSystem_setActiveScene(m3dfw::GraphicsSystem * o_ptr, m3dfw::ScID * id)
{
	o_ptr->setActiveScene(*id);
}
