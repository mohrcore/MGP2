#include "TextureBank.h"



TextureBank::TextureBank()
{
}


TextureBank::~TextureBank()
{
	clearBank();
}


Texture * TextureBank::getTextureByPath(const std::string & path)
{
	Texture * ptr;

	//if (_path_index_map.count(path) == 0)
	//{
	//	_textures.push_back(nullptr);
	//	_textures.back() = new Texture();
	//	_textures.back()->loadFromFile(path, DIFFUSE_MAP);
	//	_path_index_map[path] = _textures.size() - 1;
	//	ptr = _textures.back();
	//}
	//else
	//{
	//	ptr = _textures[_path_index_map[path]];
	//}

	////ptr->addUser(user);

	if (_path_index_map.count(path) == 0)
	{
		_path_index_map[path].loadFromFile(path, DIFFUSE_MAP);
	}

	ptr = &_path_index_map[path];

	return ptr;
}

//Texture * TextureBank::getTextureByIndex(unsigned int id)
//{
//	//_textures[id]->addUser(user);
//
//	return _textures[id];
//}
//
//unsigned int TextureBank::getTextureID(const std::string & path)
//{
//	return _path_index_map[path];
//}
//
//void TextureBank::freeTexture(unsigned int id)
//{
//	delete _textures[id];
//}

//void TextureBank::removeUser(void * user)
//{
//
//}

////--------------------------------------------------------------------------------------------------
//
//Shared_Texture::Shared_Texture() : Texture(), _auto_clean(true)
//{
//}
//
//
//void Shared_Texture::addUser(void * user)
//{
//	_users.push_back(user);
//}
//
//void Shared_Texture::removeUser(void * user)
//{
//	std::vector<void *>::iterator it = _users.begin();
//	for (int i = 0; i < _users.size(); i++)
//	{
//		if (_users[i] = user)
//			_users.erase(it);
//		else
//			it++;
//	}
//}
//
//bool Shared_Texture::hasNoUsers()
//{
//	if (_users.empty())
//		return true;
//	else
//		return false;
//}
//

void TextureBank::clearBank()
{
	//for (int i = 0; i < _textures.size(); i++)
	//{
	//	delete _textures[i];
	//}

	//_textures.clear();

	_path_index_map.clear();
}