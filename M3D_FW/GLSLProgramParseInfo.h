#pragma once

#include <vector>
#include <iostream>
#include <cstring>
#include <fstream>
//#include <set>

namespace m3dfw
{
	enum GLSLParseMode : uint8_t
	{
		ParseIn = 0x01,
		ParseUniform = 0x02,
	};
	
	enum glsl_type
	{
		BOOL,
		INT,
		UINT,
		FLOAT,
		DOUBLE,
		
		BVEC2,
		BVEC3,
		BVEC4,
		
		IVEC2,
		IVEC3,
		IVEC4,
		
		UVEC2,
		UVEC3,
		UVEC4,
		
		VEC2,
		VEC3,
		VEC4,
		
		DVEC2,
		DVEC3,
		DVEC4,
		
		MAT2,
		MAT3,
		MAT4,

		MAT2x2,
		MAT3x2,
		MAT4x2,

		MAT2x3,
		MAT3x3,
		MAT4x3,

		MAT2x4,
		MAT3x4,
		MAT4x4,
	};


	struct glsl_var
	{
		glsl_var();
		glsl_var(glsl_type t, const std::string & n);

		bool operator==(const glsl_var & other) const;

		//bieda syf do seta
		bool operator<(const glsl_var & other) const;

		glsl_type type;
		std::string name;
	};

	class GLSLProgramParseInfo
	{
	public:

		
		bool parse(const std::string & path, uint8_t flags);

		glsl_var getUniform(unsigned int index) const;
		glsl_var getIn (unsigned int index) const;
		unsigned int getUniformCount() const;
		unsigned int getInCount() const;

		void clear();

	private:

		void check(const std::string & co, std::fstream & file, std::vector<glsl_var> & uniforms, std::vector<glsl_var> & ins, uint8_t flags);

		std::vector<glsl_var> _uniforms;
		std::vector<glsl_var> _ins;
		void typek(m3dfw::glsl_type & type, const std::string & str);
	};
}
