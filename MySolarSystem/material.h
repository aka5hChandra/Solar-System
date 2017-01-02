#ifndef MATERIAL_H
#define MATERIAL_H
#include <GL/glew.h>
#include <glm.hpp>

class Material
{
public:
Material(
	 glm::vec3 ambientMaterial,
	 glm::vec3 diffuseMaterial,
	 glm::vec3 specularMaterial,
	 GLfloat shininess,glm::vec3 rimColor,GLfloat rimPower);



void setDiffuseMaterial(glm::vec3); 
void setAmbientMaterial(glm::vec3); 
void setSpecularMaterial(glm::vec3);
void setRimColor(glm::vec3);
void setShininess(GLfloat);
void setRimPower(GLfloat);

glm::vec3 getDiffuseMaterial(); 
glm::vec3 getAmbientMaterial(); 
glm::vec3 getSpecularMaterial();
glm::vec3 getRimColor();
GLfloat getShininess();
GLfloat getRimPower();


private:
glm::vec3 diffuseMaterial; 
glm::vec3 ambientMaterial; 
glm::vec3 specularMaterial;

glm::vec3 rimColor;

    GLfloat shininess;
	GLfloat rimPower;

};

#endif