#include"planet.h"


Planet::Planet(char* name,float distanceFromSun,float rotationSpeed,float revalutionSpeed,float scale,char* texFilePath,glm::vec3 planetCameraEye ,glm::vec3 planetCameraCenter)
	:name(name),
	distanceFromSun(distanceFromSun),
	rotationSpeed(rotationSpeed),
	revalutionSpeed(revalutionSpeed),
	scale(scale),
	modelMatrix(glm::mat4(scale)),
	shaderHelper(new ShaderHelper()),
	lightFromPlanet(new Light),
	textureID(-1),
	texFilePath(texFilePath),
	planetCameraEye(glm::vec3(0)), //planetCameraEye),
	planetCameraCenter(planetCameraCenter),
	planetCamera(glm::lookAt(planetCameraEye,planetCameraCenter,
	glm::vec3(0,1,0))),
	planetCenter(glm::vec3(0)),
	rotationFactor(.002),
	rotationTime(0),
	planetOrbitRedialSegmet(256)

{
}
Planet::~Planet()
{

	glDeleteVertexArrays(1,&planetVertexArray);
	glDeleteBuffers(1,&indexBufferObject);
	glDeleteBuffers(1,&planetOrbitBufferObject);
	glDeleteBuffers(1,&planetOrbitBufferArray);
	glDeleteTextures(1,&textureID);
	glDeleteTextures(1,&nigthTextureID);




}

char* Planet::getName()
{
	return name;
}


void Planet::setMaterial(Material* planetMaterial)
{

	this->planetMaterial=new Material(planetMaterial->getDiffuseMaterial(),
		planetMaterial->getAmbientMaterial(),
		planetMaterial->getSpecularMaterial(),
		planetMaterial->getShininess(),
		planetMaterial->getRimColor(),
		planetMaterial->getRimPower());
}



void Planet::setLightOnPlanet(Light* light)
{
	this->lightOnPlanet=new Light(
		light->getLightPosition(),
		light->getAmbientComponent(),
		light->getDiffuseComponent(),
		light->getSpecularComponent());
}

void Planet::setLightFromPlanet(Light* light)
{
	this->lightFromPlanet=new Light(
		light->getLightPosition(),
		light->getAmbientComponent(),
		light->getDiffuseComponent(),
		light->getSpecularComponent());
}


Light* Planet::getLightOnPlanet()
{
	return lightOnPlanet;

}

Light* Planet::getLightFromPlanet()
{
	return lightFromPlanet;
}
Material* Planet::getPlanetMaterial()
{
	return planetMaterial;
}


///////////////////////////////////


void Planet::setModelMatrix(glm::mat4 modelMatrix)
{
	this->modelMatrix=modelMatrix;

}
glm::mat4 Planet::getModelMatrix()
{
	return modelMatrix;
}




GLint Planet::getNumVertices()
{
	return numVertices;
}
GLint Planet::getNumIndices()
{
	return numIndices;
}


GLuint Planet::getIndexBufferObject()
{
	return indexBufferObject;
}
void Planet::setShaderHelper(ShaderHelper* shaderHelper)
{
	this->shaderHelper=new ShaderHelper(shaderHelper->getProgramID());

}
ShaderHelper* Planet::getShaderHelper()
{
	return shaderHelper;
}

void Planet::setTextureID(GLenum textureID)
{
	this->textureID=textureID;
}


GLenum Planet::getTextureID()
{
	if(textureID<0)
	{
		std::cout<<"textrure not set for "<<getName()<<std::endl;
		exit(0);
	}
	return textureID;
}

char* Planet::getTexFilePath()
{
	return texFilePath;
}
void Planet::setTexFilePath(char* texFilePath)
{
	this->texFilePath=texFilePath;
}

void Planet::loadPlanetTexture(const char* textureFile,GLuint textureID,int texType)
{
	planetTextureReader=new TextureReader();
	planetTextureReader->loadTexture2D(textureFile,textureID);
	if(texType==0)
		setTextureID(textureID);
	else if (texType==1)
		setNightTextureID(textureID);
}



void Planet::setNightTextureID(GLenum nigthTextureID)
{
	this->nigthTextureID=nigthTextureID;
}
GLenum Planet::getNightTextureID()
{
	return nigthTextureID;

}

Light* Planet::lightForPlanetRender=NULL;

GLint Planet::numIndices=-1;
GLuint Planet::planetVertexArray=-1;
void Planet::createIcosahedron()
{
	//indices for Icosahedron
	const int Faces[] = {
		2, 1, 0,
		3, 2, 0,
		4, 3, 0,
		5, 4, 0,
		1, 5, 0,
		11, 6,  7,
		11, 7,  8,
		11, 8,  9,
		11, 9,  10,
		11, 10, 6,
		1, 2, 6,
		2, 3, 7,
		3, 4, 8,
		4, 5, 9,
		5, 1, 10,
		2,  7, 6,
		3,  8, 7,
		4,  9, 8,
		5, 10, 9,
		1, 6, 10 };
		/*{0,1,2,
		1,3,2};*/

		//Vertices for Icosahedron
		float Verts[] = {
			0.000f,  0.000f,  1.000f,
			0.894f,  0.000f,  0.447f,
			0.276f,  0.851f,  0.447f,
			-0.724f,  0.526f,  0.447f,
			-0.724f, -0.526f,  0.447f,
			0.276f, -0.851f,  0.447f,
			0.724f,  0.526f, -0.447f,
			-0.276f,  0.851f, -0.447f,
			-0.894f,  0.000f, -0.447f,
			-0.276f, -0.851f, -0.447f,
			0.724f, -0.526f, -0.447f,
			0.000f,  0.000f, -1.000f };



			numIndices = sizeof(Faces) / sizeof(Faces[0]);

			int PositionSlot=0;
			// Create the VAO:
			glGenVertexArrays(1, &planetVertexArray);
			glBindVertexArray(planetVertexArray);

			// Create the VBO for positions:
			GLuint positions;
			GLsizei stride = 3 * sizeof(float);
			glGenBuffers(1, &positions);
			glBindBuffer(GL_ARRAY_BUFFER, positions);
			glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);
			glEnableVertexAttribArray(PositionSlot);
			glVertexAttribPointer(PositionSlot, 3, GL_FLOAT, GL_FALSE, stride, 0);

			// Create the VBO for indices:
			GLuint indices;
			glGenBuffers(1, &indices);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Faces), Faces, GL_STATIC_DRAW);

			//planet orbit
			//	setupPlanetOrbit();
}

void  Planet::bindVertesArray()
{
	glBindVertexArray(planetVertexArray);


}


void  Planet::setDistanceFromSun(float distanceFromSun)
{
	this->distanceFromSun=distanceFromSun;
}
void  Planet::setRotationSpeed(float rotationSpeed)
{
	this->rotationSpeed=rotationSpeed;
}
void  Planet::setRevalutionSpeed(float revalutionSpeed)
{
	this->revalutionSpeed=revalutionSpeed;
}

float  Planet::getDistanceFromSun()
{
	return distanceFromSun;
}
float  Planet::getRotationSpeed()
{
	return rotationSpeed;
}
float  Planet::getRevalutionSpeed()
{
	return revalutionSpeed;
}

void Planet::setScale(float scale)
{
	this->scale=scale;
}
float Planet::getScale()
{
	return scale;
}

void Planet::rotatePlanet(float renderTime,glm::mat4 arcBallMatrix,int renderAtCenter)
{
	float planetRotaion=(renderTime*rotationSpeed);
	rotationTime+=rotationFactor;


	modelMatrix=glm::scale(glm::mat4(),glm::vec3(scale));
	if(distanceFromSun>0){
		//rotation for all planets
		float planetRevalution=renderTime*revalutionSpeed;

		glm::mat4 rot=glm::mat4 (glm::vec4(2*cos(planetRotaion),0,sin(planetRotaion),0),
			glm::vec4(0,1,0,0),
			glm::vec4(-sin(planetRotaion),0,cos(planetRotaion),0),
			glm::vec4(0,0,0,1));


		if(!renderAtCenter)
		{
			//Rotaion for render only one planet at center of the screen
			modelMatrix=glm::rotate(modelMatrix,planetRotaion * -1.0f,glm::vec3(0.0,1.0,0.0));
			modelMatrix=glm::translate(modelMatrix,glm::vec3(distanceFromSun,0.0,0.0));
		}
		//rotation and revalution of planets in solar system
		modelMatrix=glm::rotate(modelMatrix,23.5f,glm::vec3(0.0,0.0,1.0)); 
		modelMatrix=glm::rotate(modelMatrix,planetRevalution * 1.0f,glm::vec3(0.0,1.0,0.0));


	}
	else
	{
		//rotation for sun
		modelMatrix=glm::rotate(modelMatrix,planetRotaion * -1.0f,glm::vec3(0.0,1.0,0.0));


	}




}




void Planet::setupPlanetOrbit()
{
	//function to set vertices for planets orbits

	//orbits radius is based on planets distance from sun and its size scale
	int r =distanceFromSun*scale;
	GLfloat* verts=new GLfloat [planetOrbitRedialSegmet*3];


	for(int i=0;i<planetOrbitRedialSegmet*3;i+=3)
	{

		//set vertices in circuilar path for each planet based on planets distance from sum
		float phi=PI/6;
		GLfloat x=r*
			cos(i*((2*PI)/planetOrbitRedialSegmet));//*sin(phi));
		GLfloat y=1;
		GLfloat z=r*sin(i*((2*PI)/planetOrbitRedialSegmet));//r*cos(phi);



		verts[i]=x;
		verts[i+1]=y;
		verts[i+2]=z;

	}
	int *orbitIndex=new int[planetOrbitRedialSegmet];

	for(int i=0;i<planetOrbitRedialSegmet;i++)
	{
		orbitIndex[i]=i;
	}
	
	//bind vertex array and enable it 
	glGenVertexArrays(1,&planetOrbitBufferArray);
	glBindVertexArray(planetOrbitBufferArray);
	glGenBuffers(1, &planetOrbitBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, planetOrbitBufferObject);
	glBufferData(GL_ARRAY_BUFFER, planetOrbitRedialSegmet* 3 * sizeof(verts), verts, GL_STATIC_DRAW);


	glVertexAttribPointer( (GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
	glEnableVertexAttribArray(0); 



	GLuint indices;
	glGenBuffers(1, &indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, planetOrbitRedialSegmet*sizeof(orbitIndex), orbitIndex, GL_STATIC_DRAW);


}



void Planet::setPlanetOrbitRedialSegmet(int planetOrbitRedialSegmet)
{
	this->planetOrbitRedialSegmet=planetOrbitRedialSegmet;
}
int Planet::getPlanetOrbitRedialSegmet()
{
	return planetOrbitRedialSegmet;
}

GLuint Planet::getplanetOrbitBufferObject()
{
	return planetOrbitBufferObject;
}

GLuint Planet::getplanetOrbitBufferArray()
{
	return planetOrbitBufferArray;
}

glm::mat4 Planet::getPlanetCamera()
{
	return planetCamera;

}
