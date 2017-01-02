#ifndef PLANET_H
#define PLANET_H

#include<GL/glew.h>
#include "material.h"
#include "light.h"
#include<math.h>
#include<glm.hpp>
#include<iostream>
#include "textureReader.h"
#include <glm.hpp>
#include "shaderReader.h"
#include<gtc\matrix_transform.hpp>


static const int  MIN_STACKS=3;
static const int  MIN_SLICES=3;
static const float PI=3.141592653589;
static const int VERTEX_LOC=0;
static const int NORMAL_LOC=1;
static const int TEXTURE_LOC=2;
class Planet
{
public:
	static Light* lightForPlanetRender;
	
	
	Planet(char* name,float distanceFromSun,float rotationSpeed,float revalutionSpeed,float scale,char* texFilePath,glm::vec3 planetCameraEye ,glm::vec3 planetCameraCenter);
	
	~Planet();
	static GLint getNumIndices();
	static void   createIcosahedron();
	static void bindVertesArray();
	void rotatePlanet(float renderTime,glm::mat4 arcBallMatrix,int renderAtCenter);
	void setupPlanetOrbit();

	void loadPlanetTexture(const char* textureFile,GLuint textureID,int texType);
	
	char* getName();
	GLint getNumVertices();
	GLuint getVertexArrayBufferObject();
	GLuint getIndexBufferObject();
	GLuint getplanetOrbitBufferObject();
	GLuint getplanetOrbitBufferArray();

	void setMaterial(Material*);
	Material* getPlanetMaterial();

	void setLightOnPlanet(Light*);
	Light* getLightOnPlanet();

	void setLightFromPlanet(Light*);
	Light* getLightFromPlanet();

	void setModelMatrix(glm::mat4);
	glm::mat4 getModelMatrix();

	void setShaderHelper(ShaderHelper*);
	ShaderHelper* getShaderHelper();

	void setPlanetOrbitRedialSegmet(int planetOrbitRedialSegmet);
	int getPlanetOrbitRedialSegmet();

	
	void setTextureID(GLenum);
	GLenum getTextureID();

	

	void setNightTextureID(GLenum);
	GLenum getNightTextureID();


	void setDistanceFromSun(float distanceFromSun);
	float getDistanceFromSun();


	void setRotationSpeed(float rotationSpeed);
	float getRotationSpeed();

	void setRevalutionSpeed(float revalutionSpeed);
	float getRevalutionSpeed();

	void setScale(float scale);
	float getScale();

	
	 
	char* getTexFilePath();
	 void setTexFilePath(char* texFilePath);
	 
	 glm::mat4 getPlanetCamera();
	glm::vec3 planetCenter;

private:
	char* name;
	GLint numVertices;
	static GLint numIndices;
	GLuint indexBufferObject;
	GLuint planetOrbitBufferObject;
	GLuint planetOrbitBufferArray;
	Material* planetMaterial;
	Light* lightOnPlanet;
	Light* lightFromPlanet;
	TextureReader* planetTextureReader;
	char* texFilePath;
	glm::mat4 modelMatrix;
    ShaderHelper* shaderHelper;
	glm::vec3 planetCameraEye;
	glm::vec3 planetCameraCenter;
	glm::mat4 planetCamera;
	GLenum textureID;
	GLenum nigthTextureID;
	float distanceFromSun;
	float rotationSpeed;
	float revalutionSpeed;
	float scale;
    static GLuint planetVertexArray;
	float rotationFactor;
	float rotationTime;
	int planetOrbitRedialSegmet;
};

#endif