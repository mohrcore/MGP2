#pragma once

#include <MFiles.h>
#include <M3DFW.h>

#include <string>
#include <vector>

void importExteranalModelToEditableModel3d(const std::string & path, mfile::EditableModel3d & target, std::vector<mfile::MOB_Material> & materials);
//void generateTextureResources(mfile::EditableModel3d & target, std::vector<std::string> & texture_paths, m3dfw::ResourceLoader & resloader);