#pragma once

#include <GL\glew.h>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

#include "CommonTypes.h"
#include "MemoryManagement.h"
#include "Util.h"
#include "GLSLProgramParseInfo.h"


// --------------------------------------------------------------------------------------------------------------------------------------------------------
// ShaderManager - a collection of utilities for managing shaders.
// 
// ShID stands for Shader ID - a number used to identify a GLSL program.
// ShCK stands for Shader Compatibility Key - a hashcode used to distinguish potentially compatible (in terms of swapping them with each other) shaders.
// --------------------------------------------------------------------------------------------------------------------------------------------------------


namespace m3dfw
{
	//Shader Compatibility Key typedef
	typedef unsigned long long ShCK;
	//Shader ID typedef
	typedef unsigned int ShID;

	typedef GLint GLSL_UniHandle;

	enum GLSLProgramCompatibility : int
	{
		EVERYTHING, // Programs have exactly same input
		INPUT, // Programs share only common "in" variable declarations
		UNIFORM_EXTENSION, // Programs share common "in" variable declarations, and feature all uniform declarations that are present in the key
		NONE // Programs are incompatible
	};

	enum class GLSLProgramErrorEnum
	{
		None,
		ErrorOpeningFile_Vertex,
		ErrorOpeningFile_Fragment,
		ShaderCompilationError_Vertex,
		ShaderCompilationError_Fragment,
		ProgramLinkingError
	};

	struct GLSLProgramError
	{
		GLSLProgramError();
		GLSLProgramError(GLSLProgramErrorEnum t, const std::string & d);

		GLSLProgramErrorEnum type;
		std::string details;
	};

	class GLSLProgram
	{
	public:

		GLSLProgram();
		~GLSLProgram();

		bool compileFromSrc(const std::string & v_src, const std::string & f_src);
		void clear();

		void bind() const;

		GLSL_UniHandle getUniformHandle(const std::string & name) const;

		void setUniformFloat(GLSL_UniHandle loc, float val) const;
		void setUniformVec2(GLSL_UniHandle loc, Vec2f val) const;
		void setUniformVec3(GLSL_UniHandle loc, Vec3f val) const;
		void setUniformVec4(GLSL_UniHandle loc, Vec4f val) const;
		void setUniformInt(GLSL_UniHandle loc, int val) const;
		void setUniformMat2(GLSL_UniHandle loc, const float * data) const;
		void setUniformMat3(GLSL_UniHandle loc, const float * data) const;
		void setUniformMat4(GLSL_UniHandle loc, const float * data) const;
		void setUniformSampler2D(GLSL_UniHandle loc, unsigned int value) const;
		void setUniformArrFloat(GLSL_UniHandle loc, const std::vector<float> & data);
		void setUniformArrVec2(GLSL_UniHandle loc, const std::vector<Vec2f> & data);
		void setUniformArrVec3(GLSL_UniHandle loc, const std::vector<Vec3f> & data);
		void setUniformArrVec4(GLSL_UniHandle loc, const std::vector<Vec4f> & data);
		void setUniformArrVec2(GLSL_UniHandle loc, const float * data, unsigned int count);
		void setUniformArrVec3(GLSL_UniHandle loc, const float * data, unsigned int count);
		void setUniformArrVec4(GLSL_UniHandle loc, const float * data, unsigned int count);

		// 64bit hash key with 11 fields for 5bit values
		ShCK getShaderCompatibilityKey() const;

		GLSLProgramCompatibility compare(const GLSLProgram & other) const; //Do not use!

		const GLSLProgramError & getError();

		const GLSLProgramParseInfo & getInfo();

		bool good() const;
		bool compiled() const;

	private:

		GLSLProgram(const GLSLProgram & other) = delete;
		GLSLProgram & operator=(const GLSLProgram & other) = delete;

		bool compile(const char * v_src, const char * f_src, unsigned int vsz, unsigned int fsz);
		void bindAttrib(GLuint id, const char * name);
		bool link();

		bool extractSrc(const std::string & path, char * & target, unsigned int & len) const;

		void generateShCK();

		GLuint _id;
		GLuint _vshID, _fshID;

		//std::vector<GLuint> _attrib_array;
		std::unordered_map<std::string, GLuint> _uniforms;

		GLSLProgramParseInfo _programInfo;

		GLSLProgramError _error;

		ShCK _shck;

		DynamicStackAllocator _stack_alloc1;

		bool _compiled;
		bool _good;
	};

	enum ShaderManagerExceptions
	{
		ShaderCompilationFailedException
	};

	class ShaderManager
	{
	public:

		ShaderManager();
		~ShaderManager();

		void clear();

		void unbindProgram();

		ShID loadProgram(const std::string & v_src, const std::string & f_src, const std::string & name);
		void deleteProgram(ShID id);

		GLSLProgram & getProgram(ShID id);
		ShID getID(const std::string & name);

		bool isShaderAvaible(const std::string & name) const;

	private:

		//GLSLProgramCompatibility deepCompatibilityCompare(GLSLProgram & key, GLSLProgram & candidate);

		ShID generateNewShaderID();

		//Quicker data access by making uint-uint comparisons instead of string-string. Makes using name strings a little bit slower, so shader references should be stored as uint's.
		std::unordered_map<ShID, GLSLProgram> _programs;
		std::unordered_map<std::string, ShID> _name_to_id;

		ShID _max_id;

		ShID _bound_prog;
	};
}


