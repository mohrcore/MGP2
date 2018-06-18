#include <MFiles.h>
#include <M3DFW.h>

#include <vector>
#include <string>
#include <iostream>

#include "EXT_ModelImporter.h"

void writeFileMeta(mfile::MFile & file)
{
	std::cout << "File path: \"" << file.getFilePath() << "\"" << std::endl
		<< "Content type: \"" << file.getHeaderData().type << "\"" << std::endl
		<< "Internal format version: \"" << file.getHeaderData().version << "\"" << std::endl;
}

void exportMaterial(const mfile::MOB_Material & material, const std::string & name)
{
	mfile::MFile file;

	bool succ = file.createAndOpen(name.c_str(), 0x0001, "[fmt_ver]=\"0.00.001\"[type]=\"material\"[encrypted]=\"false\"");

	mfile::writeMaterial(file, material);

	file.save();
}

void exportMaterials(const std::vector<mfile::MOB_Material> & materials, const std::string & mdp_file_path)
{
	std::ofstream mdp_file(mdp_file_path, std::ofstream::trunc);

	for (unsigned int i = 0; i < materials.size(); i++)
	{
		std::string path = std::string(materials[i].name) + ".mmt";
		exportMaterial(materials[i], path);

		mdp_file << materials[i].name << " " << path << "\n";
	}

	mdp_file.close();
}

int main()
{
	mfile::MFile file;

	std::cout << "Mohr's File Utility v0.00.001pa\n" << std::endl;

	std::string mf_path;
	std::string s_path;
	std::string e_path;

	//do
	//{
	//	std::cout << "Please enter file's path: ";
	//	std::cin >> mf_path;
	//} while (!file.open(mf_path));

	file.createAndOpen("blank_mfile_model3d.mob", 0x0001, "[fmt_ver]=\"0.00.001\"[type]=\"model_3d\"[encrypted]=\"false\"[name]=\"blank\"");

	//writeFileMeta(file);

	std::cout << "Please specify import data source path: ";
	std::cin >> mf_path;

	std::cout << "Please name the exported files: ";
	std::cin >> e_path;

	m3dfw::ResourceManager rm;
	m3dfw::ResourceLoader rloader(rm);

	mfile::EditableModel3d model1;
	mfile::copyCStr(e_path.c_str(), model1.name);
	std::vector<mfile::MOB_Material> model1_materials;
	importExteranalModelToEditableModel3d(mf_path, model1, model1_materials);

	std::cout << "Data import succesful!" << std::endl;

	exportMaterials(model1_materials, e_path + ".mdp");

	mfile::writeModel3d(file, model1);
	file.save(e_path + ".mob");

	std::cout << "Done." << std::endl;

	system("pause");

	return 0;
}