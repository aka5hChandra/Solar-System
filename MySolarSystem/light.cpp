#include "light.h"

Light::Light(glm::vec3 lightPosition,
		glm::vec3 ambientComponent,
	 glm::vec3	diffuseComponent,
	 glm::vec3 specularComponent):lightPosition(lightPosition),
									 ambientComponent(ambientComponent),
									diffuseComponent(diffuseComponent),
									specularComponent(specularComponent)
								  
									{}

Light::Light(){}

void Light::setLightPosition(glm::vec3 lightPosition){  this->lightPosition=lightPosition;   }

void Light::setDiffuseComponent(glm::vec3 diffuseComponent){   this->diffuseComponent=diffuseComponent;}
void Light::setAmbientComponent(glm::vec3 ambientComponent){   this->ambientComponent=ambientComponent;}
void Light::setSpecularComponent(glm::vec3 specularComponent){ this->specularComponent=specularComponent;}


glm::vec3 Light::getLightPosition(){return lightPosition; }


glm::vec3 Light::getDiffuseComponent( ){return diffuseComponent; }
glm::vec3 Light::getAmbientComponent( ){return ambientComponent; }
glm::vec3 Light::getSpecularComponent(){return specularComponent;}