#include <M3DFW.h>

#include "EXPORT.h"

//System class unwrap

void EXPORT m3dfw__delete__System(m3dfw::System * o_ptr)
{
	delete o_ptr;
}

void EXPORT m3dfw__System_execute(m3dfw::System * o_ptr)
{
	o_ptr->execute();
}

m3dfw::SystemFct EXPORT m3dfw__System_pollTask(m3dfw::System * o_ptr)
{
	return o_ptr->pollTask();
}

//SysArg classs unwrap

m3dfw::SysArg PTR_EXPORT(*) m3dfw__new__SysArg(std::atomic_int * t_prog_ref)
{
	return new m3dfw::SysArg(* t_prog_ref);
}