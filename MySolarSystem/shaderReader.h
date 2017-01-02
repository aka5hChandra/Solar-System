#ifndef SHADER_HELPER_H
#define SHADER_HELPER_H
#include <GL/glew.h>
#include<glm.hpp>
#include <iostream>
#include <fstream>

class ShaderHelper
{
private:
	int  progamID;

	GLint  getUniformLocation(const char * name );
public:
	ShaderHelper();
	ShaderHelper(GLint programID);

	~ShaderHelper();
	void compileShader(GLint ID,char* fileName);
	void linkAndUseProgram();
	void link();
	void useProgram();
	int    getProgramID();
	//bool   isLinked();

	void   setUniform( const char *name, float x, float y, float z);
	void   setUniform( const char *name, const glm::vec2 & v);
	void   setUniform( const char *name, const glm::vec3 & v);
	void   setUniform( const char *name, const glm::vec4 & v);
	void   setUniform( const char *name, const glm::mat4 & m);
	void   setUniform( const char *name, const glm::mat3 & m);
	void   setUniform( const char *name, float val );
	void   setUniform( const char *name, int val );
	void   setUniform( const char *name, bool val );
	void   setUniform( const char *name, GLuint val );

};


#endif
