#pragma once

#include <vector>
#include <string>
#include <map>

#include "Texture.h"

class TextureBank //Main container for managing textures, which might or might not be shared between assets
{
public:

	TextureBank();
	~TextureBank();

	Texture * getTextureByPath(const std::string & path);
	//Texture * getTextureByIndex(unsigned int id);
	//unsigned int getTextureID(const std::string & path);

	//void freeTexture(unsigned int id); //Should not be used!!!

	//void removeUser(void * user);

	void clearBank(); //Call this only when clearing an entire scene (eg. quitting to main menu)

private:

	//std::vector<Texture * > _textures;

	std::map<std::string, /*unsigned int*/Texture> _path_index_map;
};


//class Shared_Texture
//	: public Texture
//{
//public:
//
//	Shared_Texture();
//
//	void addUser(void * user);
//	void removeUser(void * user);
//
//	bool hasNoUsers();
//
//	bool _auto_clean; //If true, TextureBank will automatically delete this texture if it has no users.
//
//private:
//
//	std::vector<void *> _users;
//};