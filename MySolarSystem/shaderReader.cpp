#include "shaderReader.h"


//Utility class for compling and linking shaders and binding uniforms

//Each object of this class, represents its own shader program,
//that makes compiling and linking of shader to program and binding uniforms easy.
//this also enables to handle different shader programs using different objects of 
//this class

//constructors
ShaderHelper::ShaderHelper() : progamID(-1) { }
ShaderHelper::ShaderHelper(GLint programID) : progamID(programID) { }

//destructors
ShaderHelper::~ShaderHelper() {
	if(progamID == 0) return;


	GLint numShaders = 0;
	glGetProgramiv(progamID, GL_ATTACHED_SHADERS, &numShaders);


	GLuint * shaderNames = new GLuint[numShaders];
	glGetAttachedShaders(progamID, numShaders, NULL, shaderNames);


	for (int i = 0; i < numShaders; i++)
		glDeleteShader(shaderNames[i]);


	glDeleteProgram (progamID);

	delete[] shaderNames;
}
void ShaderHelper::compileShader(GLint ID,char* fileName)
{

	//helper funciton to compile shaders
	std::ifstream myStream(fileName);
	if(!myStream.good())
	{
		fprintf(stderr,"Cant read file... %s \n",fileName);

		exit(0);
	}

	std::string temp=  std::string(std::istreambuf_iterator<char>(myStream),
		std::istreambuf_iterator<char>());

	const char* adaptor[1];
	adaptor[0]=temp.c_str();

	GLint shaderID =glCreateShader(ID);
	glShaderSource(shaderID,1,adaptor,0);


	GLint compileStatus;
	glCompileShader(shaderID);
	glGetShaderiv(shaderID,GL_COMPILE_STATUS,&compileStatus);
	if(compileStatus!=GL_TRUE)
	{

		std::cout<<"compile failed ..."<<fileName<<std::endl;
		GLint infoLogLenght;
		glGetShaderiv(shaderID,GL_INFO_LOG_LENGTH,&infoLogLenght);
		GLchar* buffer=new GLchar[infoLogLenght];
		GLsizei bufferSize;
		glGetShaderInfoLog(shaderID,infoLogLenght,&bufferSize,buffer);
		std::cout<<"infoLength .."<<infoLogLenght<<"bufferSIze.."<<bufferSize<<fileName<<std::endl;

		std::cout<<buffer<<std::endl;
		delete [] buffer;
		//exit(0);
	}
	else
		std::cout<<"compile successfull ------ "<<fileName<<std::endl;


	GLint programID=getProgramID();

	glAttachShader(progamID,shaderID);


}



void ShaderHelper::linkAndUseProgram()
{
	//helper function to link and use the program
	GLint programID=getProgramID();
	glLinkProgram(progamID);
	GLint linkStatus;
	glGetProgramiv(programID,GL_LINK_STATUS,&linkStatus);
	if(linkStatus!=GL_TRUE)
	{
		std::cout<<"link failed "<<std::endl;
		GLint infoLoglenght;
		glGetProgramiv(programID,GL_INFO_LOG_LENGTH,&infoLoglenght);
		GLchar* buffer =new GLchar[infoLoglenght];
		GLsizei bufferSize;
		glGetProgramInfoLog(programID,infoLoglenght,&bufferSize,buffer);
		std::cout<<buffer<<std::endl;


		delete [] buffer;
		//exit(0);
	}
	else
		std::cout<<"link successfull"<<std::endl;
	glUseProgram(progamID);
}

void ShaderHelper::link()
{
	//helper function to link the shaders
	GLint programID=getProgramID();
	glLinkProgram(progamID);
	GLint linkStatus;
	glGetProgramiv(programID,GL_LINK_STATUS,&linkStatus);
	if(linkStatus!=GL_TRUE)
	{
		std::cout<<"link failed "<<std::endl;
		GLint infoLoglenght;
		glGetProgramiv(programID,GL_INFO_LOG_LENGTH,&infoLoglenght);
		GLchar* buffer =new GLchar[infoLoglenght];
		GLsizei bufferSize;
		glGetProgramInfoLog(programID,infoLoglenght,&bufferSize,buffer);
		std::cout<<buffer<<std::endl;


		delete [] buffer;
		exit(0);
	}
	else
		std::cout<<"link successfull"<<std::endl;

}


void ShaderHelper::useProgram()
{
	//helper function to use program
	glUseProgram(progamID);

}
GLint ShaderHelper::getProgramID()
{
	//singleton to get program ID
	if(progamID<0)
	{
		progamID=glCreateProgram();
	}
	return progamID;
}

GLint  ShaderHelper::getUniformLocation(const char * name )
{
	//helper function to get unifrom location
	GLint uniformLocation=glGetUniformLocation(getProgramID(),name);
	if(uniformLocation<0)
	{
		std::cout<<" uniform "<<name<<"is not found "<<std::endl;
		exit(0);
	}


	return uniformLocation;
}

//overrided functions to set uniforms.
void ShaderHelper::setUniform( const char *name, float x, float y, float z)
{
	GLint uniformLocation = getUniformLocation(name);
	glUniform3f(uniformLocation,x,y,z);
}

void ShaderHelper::setUniform( const char *name, const glm::vec3 & v)
{
	this->setUniform(name,v.x,v.y,v.z);
}

void ShaderHelper::setUniform( const char *name, const glm::vec4 & v)
{
	GLint uniformLocation = getUniformLocation(name);
	glUniform4f(uniformLocation,v.x,v.y,v.z,v.w);
}

void ShaderHelper::setUniform( const char *name, const glm::vec2 & v)
{
	GLint uniformLocation = getUniformLocation(name);
	glUniform2f(uniformLocation,v.x,v.y);
}

void ShaderHelper::setUniform( const char *name, const glm::mat4 & m)
{
	GLint uniformLocation = getUniformLocation(name);
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &m[0][0]);
}

void ShaderHelper::setUniform( const char *name, const glm::mat3 & m)
{
	GLint uniformLocation = getUniformLocation(name);
	glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, &m[0][0]);
}

void ShaderHelper::setUniform( const char *name, float val )
{
	GLint uniformLocation = getUniformLocation(name);
	glUniform1f(uniformLocation, val);
}

void ShaderHelper::setUniform( const char *name, int val )
{
	GLint uniformLocation = getUniformLocation(name);
	glUniform1i(uniformLocation, val);
}

void ShaderHelper::setUniform( const char *name, GLuint val )
{
	GLint uniformLocation = getUniformLocation(name);
	glUniform1ui(uniformLocation, val);
}

void ShaderHelper::setUniform( const char *name, bool val )
{
	int uniformLocation = getUniformLocation(name);
	glUniform1i(uniformLocation, val);
}
