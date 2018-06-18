#include <M3DFW.h>

#include <vector>

#include "EXPORT.h"


// -------------------------------------------------------------------------------------
// Please, don't use this shit.
// -------------------------------------------------------------------------------------


typedef std::vector<m3dfw::GfxBasicLight> LightsVec;
typedef std::vector<m3dfw::GfxBasicLight>::iterator LightsVec_Iterator;

LightsVec PTR_EXPORT(*) m3dfwUW__new__LightsVec()
{
	return new LightsVec();
}

void EXPORT m3dfwUW__delete__LightsVec(LightsVec * o_ptr)
{
	delete o_ptr;
}

unsigned int EXPORT m3dfwUW__LightsVec_size(LightsVec * o_ptr)
{
	return o_ptr->size();
}

void EXPORT m3dfwUW__LightsVec_resize(LightsVec * o_ptr, unsigned int sz)
{
	o_ptr->resize(sz);
}

m3dfw::GfxBasicLight PTR_EXPORT(*) m3dfwUW__LghtsVec_getItem(LightsVec * o_ptr, unsigned int id)
{
	return &(*o_ptr)[id];
}

void EXPORT m3dfUW__LightsVec_push_back(LightsVec * o_ptr, m3dfw::GfxBasicLight * item)
{
	o_ptr->push_back(*item);
}

void EXPORT m3dfwUW__LightsVec_clear(LightsVec * o_ptr)
{
	o_ptr->clear();
}

LightsVec_Iterator PTR_EXPORT(*) m3dfwUW__LightsVec_insert(LightsVec * o_ptr, LightsVec_Iterator * iterator, m3dfw::GfxBasicLight * item)
{
	return &o_ptr->insert(*iterator, *item);
}

LightsVec_Iterator PTR_EXPORT(*) m3dfwUW__LightsVec_erase(LightsVec * o_ptr, LightsVec_Iterator * iterator)
{
	return &o_ptr->erase(*iterator);
}

LightsVec_Iterator PTR_EXPORT(*) m3dfwUW__LightsVec_begin(LightsVec * o_ptr)
{
	return &o_ptr->begin();
}

LightsVec_Iterator PTR_EXPORT(*) m3dfwUW__LightsVec_end(LightsVec * o_ptr)
{
	return &o_ptr->end();
}

bool EXPORT m3dfwUW__LightsVec_compare(LightsVec_Iterator * it1, LightsVec_Iterator * it2)
{
	return *it1 == *it2;
}