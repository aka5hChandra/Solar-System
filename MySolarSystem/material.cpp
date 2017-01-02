#include "material.h"

Material::Material(glm::vec3 ambientMaterial,glm::vec3 diffuseMaterial,
							       glm::vec3 specularMaterial,GLfloat shininess,
								   glm::vec3 rimColor,GLfloat rimPower)
								   :ambientMaterial(ambientMaterial),
									diffuseMaterial(diffuseMaterial),
									specularMaterial(specularMaterial),
									shininess(shininess),rimColor(rimColor),rimPower(rimPower)
{

}

void Material::setDiffuseMaterial(glm::vec3 diffuseMaterial){this->diffuseMaterial=diffuseMaterial;    } 
void Material::setAmbientMaterial(glm::vec3 ambientMaterial){this->ambientMaterial=ambientMaterial;    } 
void Material::setSpecularMaterial(glm::vec3 specularMaterial){  this->specularMaterial=specularMaterial; }
void Material::setShininess(GLfloat shininess){        this->shininess=shininess;       }
void Material::setRimColor(glm::vec3 rimColor){this->rimColor=rimColor;}
void Material::setRimPower(float rimPower){this->rimPower=rimPower;}

glm::vec3 Material::getDiffuseMaterial(){return diffuseMaterial;} 
glm::vec3 Material::getAmbientMaterial(){return ambientMaterial;} 
glm::vec3 Material::getSpecularMaterial(){return specularMaterial;}
glm::vec3 Material::getRimColor(){return rimColor;}

GLfloat   Material::getShininess(){return shininess;}
GLfloat   Material::getRimPower(){return rimPower;}