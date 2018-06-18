#include "GLSLProgramParseInfo.h"

#include "Util.h"

#include <string>

m3dfw::glsl_var::glsl_var()
{

}

m3dfw::glsl_var::glsl_var(glsl_type t, const std::string & n)
{
	type = t;
	name = n;
}

bool m3dfw::glsl_var::operator<(const m3dfw::glsl_var & other) const
{
	return name < other.name;
}


void m3dfw::GLSLProgramParseInfo::check(const std::string & co, std::fstream & file, std::vector<glsl_var> & uniforms, std::vector<glsl_var> & ins, uint8_t flags)
{
	if (co == "uniform")
	{
		if(flags & ParseUniform)
		{
			std::string typ;
			std::string nazwa;
			file >> typ >> nazwa;

			if (nazwa[nazwa.length() - 1] == ';')
				nazwa.resize(nazwa.length() - 1);
		
			m3dfw::glsl_var Uniform;
			Uniform.name = nazwa;
		
			m3dfw::glsl_type typo;
			typek(typo, typ);
			Uniform.type = typo;
		
			uniforms.push_back(Uniform);
		}

	}
	else if (co == "in")
	{
		if (flags & ParseIn)
		{
			std::string typ;
			std::string nazwa;
			file >> typ >> nazwa;

			if (nazwa[nazwa.length() - 1] == ';')
				nazwa.resize(nazwa.length() - 1);
		
			m3dfw::glsl_var In;
			In.name = nazwa;
		
			m3dfw::glsl_type typo;
			typek(typo, typ);
			In.type = typo;
		
			ins.push_back(In);
		}

	}
}

bool m3dfw::GLSLProgramParseInfo::parse(const std::string & path, uint8_t flags)
{
	std::fstream plik;
	plik.open(path.c_str());

	if (!plik.good())
		return false;

	while (true)
	{
		//char * UnIn = nullptr;

		std::string UnIn;
		plik >> UnIn;
		if (!plik.eof())
			check(UnIn, plik, _uniforms, _ins, flags);
		else
			break;

	}

	removeDuplicatesInVector(_uniforms);

	return true;
}

void m3dfw::GLSLProgramParseInfo::typek(m3dfw::glsl_type & type, const std::string & str)
{
	if (str == "int")
		type = m3dfw::glsl_type::INT;
	else if (str == "bool")
		type = m3dfw::glsl_type::BOOL;
	else if (str == "uint")
		type = m3dfw::glsl_type::UINT;
	else if (str == "float")
		type = m3dfw::glsl_type::FLOAT;
	else if (str == "double")
		type = m3dfw::glsl_type::DOUBLE;
	
	else if (str == "bvec2")
		type = m3dfw::glsl_type::BVEC2;
	else if (str == "bvec3")
		type = m3dfw::glsl_type::BVEC3;
	else if (str == "bvec4")
		type = m3dfw::glsl_type::BVEC4;
	
	else if (str == "ivec2")
		type = m3dfw::glsl_type::IVEC2;
	else if (str == "ivec3")
		type = m3dfw::glsl_type::IVEC3;
	else if (str == "ivec4")
		type = m3dfw::glsl_type::IVEC4;
	
	else if (str == "uvec2")
		type = m3dfw::glsl_type::UVEC2;
	else if (str == "uvec3")
		type = m3dfw::glsl_type::UVEC3;
	else if (str == "uvec4")
		type = m3dfw::glsl_type::UVEC4;
	
	else if (str == "vec2")
		type = m3dfw::glsl_type::VEC2;
	else if (str == "vec3")
		type = m3dfw::glsl_type::VEC3;
	else if (str == "vec4")
		type = m3dfw::glsl_type::VEC4;
	
	else if (str == "dvec2")
		type = m3dfw::glsl_type::DVEC2;
	else if (str == "dvec3")
		type = m3dfw::glsl_type::DVEC3;
	else if (str == "dvec4")
		type = m3dfw::glsl_type::DVEC4;
	
	else if (str == "mat2")
		type = m3dfw::glsl_type::MAT2;
	else if (str == "mat3")
		type = m3dfw::glsl_type::MAT3;
	else if (str == "mat4")
		type = m3dfw::glsl_type::MAT4;
	
	else if (str == "mat2x2")
		type = m3dfw::glsl_type::MAT2x2;
	else if (str == "mat3x2")
		type = m3dfw::glsl_type::MAT2x3;
	else if (str == "mat4x2")
		type = m3dfw::glsl_type::MAT2x4;
	
	else if (str == "mat2x3")
		type = m3dfw::glsl_type::MAT3x2;
	else if (str == "mat3x3")
		type = m3dfw::glsl_type::MAT3x3;
	else if (str == "mat4x3")
		type = m3dfw::glsl_type::MAT3x4;
	
	else if (str == "mat2x4")
		type = m3dfw::glsl_type::MAT4x2;
	else if (str == "mat3x4")
		type = m3dfw::glsl_type::MAT4x3;
	else if (str == "mat4x4")
		type = m3dfw::glsl_type::MAT4x4;
}

void m3dfw::GLSLProgramParseInfo::clear()
{
	_uniforms.clear();
	_ins.clear();
}

unsigned int m3dfw::GLSLProgramParseInfo::getUniformCount() const
{
	return _uniforms.size();
};

unsigned int m3dfw::GLSLProgramParseInfo::getInCount() const
{
	return _ins.size();
};

bool m3dfw::glsl_var::operator==(const m3dfw::glsl_var & other) const
{
	if ((type == other.type) && (name == other.name))
		return true;

	return false;
}

m3dfw::glsl_var m3dfw::GLSLProgramParseInfo::getUniform(unsigned int index) const
{
	return _uniforms[index];
};

m3dfw::glsl_var m3dfw::GLSLProgramParseInfo::getIn(unsigned int index) const
{
	return _ins[index];
};