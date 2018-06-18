#include <M3DFW.h>

#include <SDL.h>

#include "EXPORT.h"

bool EXPORT m3dfw__init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	return m3dfw::init();
}
