#ifndef LIGHT_H
#define LIGHT_H
#include <GL/glew.h>
#include <glm.hpp>

class Light
{
public:
	Light(
		glm::vec3 lightPosition,
		glm::vec3 ambientMaterial,
	 glm::vec3 diffuseMaterial,
	 glm::vec3 specularMaterial
		);
	Light();


void setLightPosition(glm::vec3);


void setDiffuseComponent(glm::vec3);
void setAmbientComponent(glm::vec3);
void setSpecularComponent(glm::vec3);


glm::vec3 getLightPosition();


glm::vec3 getDiffuseComponent();
glm::vec3 getAmbientComponent();
glm::vec3 getSpecularComponent();
private:


glm::vec3 lightPosition;


glm::vec3 diffuseComponent; 
glm::vec3 ambientComponent; 
glm::vec3 specularComponent;
};

#endif