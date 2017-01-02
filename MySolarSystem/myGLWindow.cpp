//
//
//
// THis is the Window implementaion for Solar System Rendering
//
//
#include "myGLWindow.h"


//Required Matrices
glm::mat4 projectionMatrix;
glm::mat4 viewMatrix;
//glm::mat4 modelMatrix;
glm::mat4 mvp;
glm::mat4 modelViewMatrix;


//Materials for planets
Material* planetMaterials[10];
Planet* planets[10];

Camera* camera;
//Arc ball to rotate planets around its axis using mouse motion as input
ArcBall* arcBall;

//Utility to compile and link shaders
ShaderHelper* planetShaderHelper;

//Variables to toggle functionalites from Menu
int planetOrbitCheck;
int lightCheck;
int nightLights;
int bloomCheck;
int blurCheck;
int cameraAutoZoom;
int cameraTypeSelected;
int arcBallOn;
int renderOnlyPlanet;

float orbitCamEyes=24.969;
float cameraZoom=500.0f;

TwBar *solarSystemConfigureBar;
float renderTime;
int isZooming=0;

typedef enum {SOLAR_SYTEM=0, SUN=1, MERCURY,VENUS,EARTH,MARS,JUPITER,SATRUN,URANUS,NEPTUNE } PlanetsEnum;
typedef enum {FRONT_VIEW=0,TOP_VIEW=1,ORIBIT_VIEW} CameraEnums;

static int Rotation;
float orbitCamXpos=75.5;

void setPlanetUniformsAndVAO(Planet* planet)
{
	//
	//This method binds Planet Shader and set uniforms for Rendering Planets  
	//and bind Planet Vertex Array, called once before rendering 
	//planets for Solar System
	//

	planetShaderHelper->useProgram();

	//call static method to bind vertex array.
	Planet::bindVertesArray();

	//Set differnet Light positions for different types for renders
	if(renderOnlyPlanet)
	{
		planetShaderHelper->setUniform("lightPosition",Planet::lightForPlanetRender->getLightPosition());

	}
	else{
		planetShaderHelper->setUniform("lightPosition",planet->getLightOnPlanet()->getLightPosition());
	}
	//set all uniforms
	planetShaderHelper->setUniform("diffuseMaterial",planet->getPlanetMaterial()->getDiffuseMaterial());
	planetShaderHelper->setUniform("ambientMaterial",planet->getPlanetMaterial()->getAmbientMaterial());
	planetShaderHelper->setUniform("specularMaterial",planet->getPlanetMaterial()->getSpecularMaterial());

	planetShaderHelper->setUniform("diffuseComponent",planet->getLightOnPlanet()->getDiffuseComponent());
	planetShaderHelper->setUniform("ambientComponent",planet->getLightOnPlanet()->getAmbientComponent());
	planetShaderHelper->setUniform("specularComponent",planet->getLightOnPlanet()->getSpecularComponent());

	planetShaderHelper->setUniform("shininess",planet->getPlanetMaterial()->getShininess());
	planetShaderHelper->setUniform("rimColor",planet->getPlanetMaterial()->getRimColor());
	planetShaderHelper->setUniform("rimPower",planet->getPlanetMaterial()->getRimPower());
	planetShaderHelper->setUniform("lightCheck",lightCheck);
	planetShaderHelper->setUniform("nightLights",nightLights);

	//planetShaderHelper->setUniform("viewMatrix",viewMatrix);




	glEnable(GL_TEXTURE_2D); 

	//Enable and bind the texture for planets
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, planet->getTextureID());

	//Get required matrices and set them
	mvp=projectionMatrix*viewMatrix*planet->getModelMatrix();
	modelViewMatrix=//viewMatrix*
		planet->getModelMatrix();
	planetShaderHelper->setUniform("mvp",mvp);
	planetShaderHelper->setUniform("modelViewMatrix",modelViewMatrix);
	planetShaderHelper->setUniform("normalMatrix",glm::transpose(glm::inverse(glm::mat3(modelViewMatrix))));

	//Bind Night Light texture for Planet Earth
	if(strcmp(planet->getName(),"Earth")==0)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, planet->getNightTextureID());

	}
	else
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}
void loadTextures()
{
	//This method loads all required textures for 
	//planet rendering
	//
	GLuint texIDs[9];
	glGenTextures(9, texIDs);

	//Load planet textures
	for(int i=0;i<numOfCelstialObjects;i++)
	{
		planets[i]->loadPlanetTexture(planets[i]->getTexFilePath(),texIDs[i],0);
	}


	//Load night light texture for planet Earth
	GLuint nightLightTexID;
	glGenTextures(1,&nightLightTexID);
	planets[3]->loadPlanetTexture(EARTH_NIGHT_TEXTURE,nightLightTexID,1);

}
void loadPlanetShaders()
{

	//This method compiles,links and attaches
	//shader requried for Planet rendering
	//
	planetShaderHelper=new ShaderHelper();

	//compile shaders for planet render
	planetShaderHelper->compileShader(GL_VERTEX_SHADER,"planetVertShader.glsl");
	planetShaderHelper->compileShader(GL_TESS_CONTROL_SHADER,"planetTCSShader.glsl");
	planetShaderHelper->compileShader(GL_TESS_EVALUATION_SHADER,"planetTESShader.glsl");
	planetShaderHelper->compileShader(GL_GEOMETRY_SHADER,"planetGeoShader.glsl");
	planetShaderHelper->compileShader(GL_FRAGMENT_SHADER,"planetFragShader.glsl");

	//link shaders and use program
	planetShaderHelper->linkAndUseProgram();

}



void setUpMaterials()
{
	//This method sep ups Material for Sun and 
	//Planets
	//

	//Sun material
	planetMaterials[0]=new Material(glm::vec3(1,1,1),
		glm::vec3(.3),
		glm::vec3(0,0,0),
		1.0,
		glm::vec3(1,1,0),
		100.0);
	//Planets material
	planetMaterials[1]=new Material(glm::vec3(1,1,1),
		glm::vec3(0.0),
		glm::vec3(0),
		1.0,glm::vec3(0,0,0),
		1.0);



}
void loadPlantes()
{
	//This method sets up Sun and all the Planets
	//there lighting and Material properites
	//

	//Sun
	planets[0]=new Planet("Sun",SUN_DISTANCE_FROM_SUN,SUN_ROTATION_SPEED,SUN_REVALTUION_SPEED,SUN_SCALE,SUN_TEXTURE,glm::vec3(6.5,0,-5),glm::vec3(6.5,0,0));

	//Planets
	planets[1]=new Planet("Mercury",MERCURY_DISTANCE_FROM_SUN,MERCURY_ROTATION_SPEED,MERCURY_REVALTUION_SPEED,MERCURY_SCALE,MERCURY_TEXTURE,glm::vec3(6.5,0,-5),glm::vec3(6.5,0,0));

	planets[2]=new Planet("Venus",VENUS_DISTANCE_FROM_SUN,VENUS_ROTATION_SPEED,VENUS_REVALTUION_SPEED,VENUS_SCALE,VENUS_TEXTURE,glm::vec3(6.5,0,-5),glm::vec3(6.5,0,0));

	planets[3]=new Planet("Earth",EARTH_DISTANCE_FROM_SUN,EARTH_ROTATION_SPEED,JUPITER_REVALTUION_SPEED,EARTH_SCALE,EARTH_TEXTURE,glm::vec3(6.5,0,-5),glm::vec3(6.5,0,0));

	planets[4]=new Planet("Mars",MARS_DISTANCE_FROM_SUN,MARS_ROTATION_SPEED,JUPITER_REVALTUION_SPEED,MARS_SCALE,MARS_TEXTURE,glm::vec3(6.5,0,-5),glm::vec3(6.5,0,0));

	planets[5]=new Planet("Jupiter",JUPITER_DISTANCE_FROM_SUN,JUPITER_ROTATION_SPEED,JUPITER_REVALTUION_SPEED,JUPITER_SCALE,JUPITER_TEXTURE,glm::vec3(6.5,0,-5),glm::vec3(6.5,0,0));

	planets[6]=new Planet("Satrun",SATRUN_DISTANCE_FROM_SUN,SATRUN_ROTATION_SPEED,SATRUN_REVALTUION_SPEED,SATRUN_SCALE,SATRUN_TEXTURE,glm::vec3(6.5,0,-5),glm::vec3(6.5,0,0));

	planets[7]=new Planet("Uranus",URANUS_DISTANCE_FROM_SUN,URANUS_ROTATION_SPEED,URANUS_REVALTUION_SPEED,URANUS_SCALE,URANUS_TEXTURE,glm::vec3(6.5,0,-5),glm::vec3(6.5,0,0));

	planets[8]=new Planet("Neptune",NEPTUNE_DISTANCE_FROM_SUN,NEPTUNE_ROTATION_SPEED,NEPTUNE_REVALTUION_SPEED,NEPTUNE_SCALE,NEPTUNE_TEXTURE,glm::vec3(6.5,0,-5),glm::vec3(6.5,0,0));

	planets[9]=new Planet("Pluto",PLUTO_DISTANCE_FROM_SUN,PLUTO_ROTATION_SPEED,PLUTO_REVALTUION_SPEED,PLUTO_SCALE,PLUTO_TEXTURE,glm::vec3(6.5,0,-5),glm::vec3(6.5,0,0));


	//Static method call to create Icosahedron which 
	//will be tesselated in shader to sphere
	//
	Planet::createIcosahedron();

	//Set materials for all planets
	setUpMaterials();

	//Sun light on other plnaets
	Light* sunLight=new Light(glm::vec3(0.0, 00.0,0.0),glm::vec3(1,1,1),glm::vec3(1.0),
		glm::vec3(1));

	//Light on Sun
	Light* lightOnSun=new Light(glm::vec3(0.0, 0.0,0.0),
		glm::vec3(1,1,1),
		glm::vec3(.3),
		glm::vec3(0,0,0));

	//Light on planet ,when single planet is rendered
	Light* lightForPlanetOnly=new Light(glm::vec3(-100.0, 0.0, 0.0),
		glm::vec3(1,1,1),
		glm::vec3(1.0),
		glm::vec3(1)
		);



	//set Light and material properties for all planets
	Planet::lightForPlanetRender=lightForPlanetOnly;

	for(int i=0;i<numOfCelstialObjects;i++)
	{

		if(i==0)
		{
			//Material property of Sun
			planets[i]->setMaterial(planetMaterials[0]);

			//Light on Sun
			planets[i]->setLightOnPlanet(lightOnSun);

		}
		else{
			//Material property of Planets
			planets[i]->setMaterial(planetMaterials[1]);

			//Light on ther planets
			planets[i]->setLightOnPlanet(sunLight);
		}

		//set up oribits for planets
		planets[i]->setupPlanetOrbit();

	}
}



static int lastMx ;
static int lastMy;
static int curMx ;
static int curMy ;
static int arcballOn ;
static int width;
static int height;
void onMouseButton(GLFWwindow* window, int button, int action,int mods ) 
{

	//This method is call event call back method 
	//for Mouse button
	//

	if( !TwEventMouseButtonGLFW(button, action) )  // Send event to AntTweakBar 
	{
		//call for arcball
		arcBall->onMouseButton( window,button,action);
	}

}


void onMouseMotion(GLFWwindow* window,double x, double y)
{

	//This method is call event call back method 
	//for Mouse motion
	//

	if( !TwEventMousePosGLFW(x,y)) // Send event to AntTweakBar
	{	
		//call for arcball
		arcBall->onMouseMotion(x,y);
	}



}



ShaderHelper* planetOrbitShaderHelper;

void loadOrbitProgram()
{
	//This method compiles and link
	//shader for Orbit rendering
	//
	planetOrbitShaderHelper=new ShaderHelper();
	planetOrbitShaderHelper->compileShader(GL_VERTEX_SHADER,"passThroughVertShader.glsl");
	planetOrbitShaderHelper->compileShader(GL_FRAGMENT_SHADER,"orbitFragShader.glsl");
	planetOrbitShaderHelper->link();

}



void cameraZoomAdjustment(int mark)
{
	//This is helper method for adujusting Camera'auto zoom
	//
	if(cameraZoom !=mark)
	{
		//if current camera zoom is not as required zoom, the caliberate zoom accordingly.
		isZooming=1;
		if(cameraZoom <mark )
		{
			//if current camera zoom is less then zoom , increament the zoom in multipels of 5.
			if(cameraZoom>mark-5)
			{
				//for final adustment.
				cameraZoom=cameraZoom+((int)cameraZoom%5);
			}
			else
			{
				cameraZoom+=5;
			}

		}
		else
		{
			//if current camera zoom is less then zoom , decrement the zoom in multipels of 5.

			if(cameraZoom<mark+5)
			{
				//for final adustment.
				cameraZoom=cameraZoom-((int)cameraZoom%5);
			}
			else
			{
				cameraZoom-=5;
			}
		}
	}else{

		// current camera zoom is as required zoom.

		isZooming=0;

	}

}



void updateCamera()
{
	//This methods updates Camera before every render

	//set view matrix based camera selection from menu
	if(cameraTypeSelected==TOP_VIEW)
	{
		viewMatrix =glm::lookAt(glm::vec3(0.0f, cameraZoom, 0.0f),glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.0f, 0.0f, -1.0f));
	}
	else if(cameraTypeSelected==FRONT_VIEW)
	{
		viewMatrix =glm::lookAt(glm::vec3(0.0f, 0.0f, -(cameraZoom)),glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.0f, 1.0f, 0.0f));
	}
	else if(cameraTypeSelected==ORIBIT_VIEW)
	{
		glm::vec3 tempEye =glm::vec3(cosf(orbitCamEyes)*orbitCamXpos,0,sinf(orbitCamEyes)*orbitCamXpos);
		glm::vec3 tempCenter =glm::vec3(cosf(25.969)*orbitCamXpos,0,sinf(25.969)*orbitCamXpos);
		viewMatrix=glm::lookAt(tempEye,tempCenter,glm::vec3(0,1,0));

		//Set Solar system render Mode 
		//Orbit View only Supports Solar System Render
		renderOnlyPlanet=0;
	}

	//Auto Zoom Funtionality
	if(cameraAutoZoom)
	{
		if(renderOnlyPlanet)

		{
			//Auto zoom set for 150 for sun and 45 for other planets
			(renderOnlyPlanet==1)?cameraZoomAdjustment(150):cameraZoomAdjustment(45);


		}
		else
		{
			//Auto zoom set for 500 for solars system

			cameraZoomAdjustment(500);

		}
		//set view matirx for top/front view based on selection made in menu
		if(cameraTypeSelected==FRONT_VIEW)
		{
			viewMatrix =glm::lookAt(glm::vec3(0.0f, 0.0f, -(cameraZoom)),glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.0f, 1.0f, 0.0f));
		}
		else if(cameraTypeSelected==TOP_VIEW)
		{
			viewMatrix =glm::lookAt(glm::vec3(0.0f, cameraZoom, 0.0f),glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.0f, 0.0f, -1.0f));

		}

	}
}

void updateMenuBar()
{
	//This methods updates Menu before every render.
	//i.e Make Menu option visible/invisible base on 
	//mode of rendering

	//flags for on and off
	int on=1;
	int off=0;
	if(renderOnlyPlanet)
	{
		//Disable Planet orbit and enable Arc ball 'Planet only render' mode
		TwSetParam(solarSystemConfigureBar, "Arc Ball On", "visible", TW_PARAM_INT32, 1, &on);
		TwSetParam(solarSystemConfigureBar, "Planet Orbits", "visible", TW_PARAM_INT32, 1, &off);
		planetOrbitCheck=0;
	}
	else
	{
		//Disable Arcball enable Planet orbit for 'Solar System render' mode
		arcBallOn=0;


		TwSetParam(solarSystemConfigureBar, "Arc Ball On", "visible", TW_PARAM_INT32, 1, &off);
		TwSetParam(solarSystemConfigureBar, "Planet Orbits", "visible", TW_PARAM_INT32, 1, &on);




	}

	if(cameraTypeSelected==ORIBIT_VIEW)
	{
		//Enable orbit camera and oribit camera eye position for orbit view
		//Disalbe Auto zoom for Orbit view
		//Disable 'Render Planet Only mode' for Orbit view
		renderOnlyPlanet=0;
		TwSetParam(solarSystemConfigureBar, "Orbit Camera X axis pos", "visible", TW_PARAM_INT32, 1, &on);
		TwSetParam(solarSystemConfigureBar, "Orbit Camera Eye pos", "visible", TW_PARAM_INT32, 1, &on);
		TwSetParam(solarSystemConfigureBar, "Auto Zoom", "visible", TW_PARAM_INT32, 1, &off);


		//Set zoom to 500 and disable manual zoom
		TwSetParam(solarSystemConfigureBar, "Camera Zoom", "visible", TW_PARAM_INT32, 1, &off);
		cameraZoom=500;

	}
	else
	{
		//Enable auto Zoom and Manual Zoom
		//Disable orbit camera and oribit camera eye position for from and top view

		TwSetParam(solarSystemConfigureBar, "Auto Zoom", "visible", TW_PARAM_INT32, 1, &on);
		TwSetParam(solarSystemConfigureBar, "Camera Zoom", "visible", TW_PARAM_INT32, 1, &on);
		TwSetParam(solarSystemConfigureBar, "Orbit Camera X axis pos", "visible", TW_PARAM_INT32, 1, &off);
		TwSetParam(solarSystemConfigureBar, "Orbit Camera Eye pos", "visible", TW_PARAM_INT32, 1, &off);

	}
	if(blurCheck)
	{	//Enable 'Bloom effect' toggle button when blur is checked
		TwSetParam(solarSystemConfigureBar, "Bloom effect", "visible", TW_PARAM_INT32, 1, &on);

	}else
	{
		//Disable 'Bloom effect' toggel button when blur is not checked
		bloomCheck=0;
		TwSetParam(solarSystemConfigureBar, "Bloom effect", "visible", TW_PARAM_INT32, 1, &off);

	}

	if(lightCheck)
	{
		//Enable 'Night light for Earth' Toggle button when Light is checked
		TwSetParam(solarSystemConfigureBar, "Night Lights for Earth", "visible", TW_PARAM_INT32, 1, &on);

	}else{
		//Disable 'Night light for Earth' Toggle button when Light is not checked

		nightLights=0;
		TwSetParam(solarSystemConfigureBar, "Night Lights for Earth", "visible", TW_PARAM_INT32, 1, &off);

	}
}


void updatePlanetUniforms()
{
	//This Method updates uniforms for planet rendeing 
	//in every rending
	//
	planetShaderHelper->setUniform("lightCheck",lightCheck);
	planetShaderHelper->setUniform("nightLights",nightLights);

}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//This is a call back funtion for 
	//winodws change in size.
	//

	//View port and projection matirx are updated accordingly
	glViewport(0, 0, width, height);
	projectionMatrix=glm::perspective(35.0f,  (float)width/height, 1.0f, 1000.0f);

}

void MyGLWindow::update( float t,GLFWwindow *glfw_window )
{

	//This is the Windows Update method
	//

	renderTime=t;


	//Rotate planets when Arcball is disabled
	if(!arcBallOn)
	{
		//Arcball is disabled, rotate and revolve planets according to the render time.
		for(int i=0;i<numOfCelstialObjects;i++)
		{
			planets[i]->rotatePlanet(t,arcBall->getCurMatrix(),renderOnlyPlanet);

		}
	}
	else
	{
		//use Arcball 
		arcBall->updateModelMatrix(planets[renderOnlyPlanet-1],viewMatrix);

	}

	updateCamera();
	updateMenuBar();
	updatePlanetUniforms();


}
//bloom effect
GLuint fbo[2];

unsigned int renderTexture,renderTexture2,depthTexture,tempRenderTexture,tempDepthTexture;
GLuint bloomVAO;
ShaderHelper* bloomShaderHelper;




unsigned int createTextureForBloom(int w,int h,bool isDepth,bool isLinear)
{
	//This method creates the texture required
	//for bloom effect

	unsigned int textureId;
	glGenTextures(1,&textureId);
	glBindTexture(GL_TEXTURE_2D,textureId);
	glTexImage2D(GL_TEXTURE_2D,0,(!isDepth ? GL_RGBA8 : GL_DEPTH_COMPONENT),w,h,0,isDepth ? GL_DEPTH_COMPONENT : GL_RGBA,GL_FLOAT,NULL);
	if(isLinear)
	{
		//Liner filter to make copy of render for Bloom effect
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	}
	else
	{
		//Near filter for render to texture
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	}


	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

	int i;
	i=glGetError();
	if(i!=0)
	{
		std::cout << "Error happened while loading the texture: " << i << std::endl;
		exit(0);
	}
	glBindTexture(GL_TEXTURE_2D,0);
	return textureId;
}
void setUpBloomProgram()
{
	//This program compiles and 
	//links the bloom shaders
	//

	bloomShaderHelper=new ShaderHelper();
	bloomShaderHelper->compileShader(GL_VERTEX_SHADER,"passThroughVertShader.glsl");
	bloomShaderHelper->compileShader(GL_FRAGMENT_SHADER,"bloomFragmentShader.glsl");
	bloomShaderHelper->linkAndUseProgram();




}

void setUpFBO()
{
	//This program sets up required Frame buffers 
	//objects for bloom efect
	glGenFramebuffers(2, fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo[0]);

	//Ping pong textrues for blur effect
	renderTexture=createTextureForBloom(width,height,false,false);
	renderTexture2=createTextureForBloom(width,height,false,false);
	depthTexture=createTextureForBloom(width,height,true,false);

	//Temp texture to store original render for further reference in bloom effect
	tempRenderTexture=createTextureForBloom(width,height,false,true);
	tempDepthTexture=createTextureForBloom(width,height,true,true);
	// Now, attach the color and depth textures to the FBO
	glFramebufferTexture(GL_FRAMEBUFFER,
		GL_COLOR_ATTACHMENT0,
		renderTexture, 0);
	glFramebufferTexture(GL_FRAMEBUFFER,
		GL_DEPTH_ATTACHMENT,
		depthTexture, 0);
	// Tell OpenGL that we want to draw into the framebuffer’s color
	// attachment
	static const GLenum draw_buffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, draw_buffers);


	////////////////////////////////
	glBindFramebuffer(GL_FRAMEBUFFER, fbo[1]);
	glFramebufferTexture(GL_FRAMEBUFFER,
		GL_COLOR_ATTACHMENT0,
		tempRenderTexture, 0);
	glFramebufferTexture(GL_FRAMEBUFFER,
		GL_DEPTH_ATTACHMENT,
		tempDepthTexture, 0);
	//static const GLenum draw_buffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, draw_buffers);
	///////////////////

}



void loadBloom()
{

	//This method sets up quad and Vertex array object 
	//for bloom effect
	//
	setUpBloomProgram();
	setUpFBO();

	// Array for full-screen quad
	GLfloat verts[] = {
		-1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f
	};

	// Array for texture for full-screen quad

	GLfloat tc[] = {
		0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
	};


	// Set up the buffers

	glGenVertexArrays( 1, &bloomVAO );
	glBindVertexArray(bloomVAO);

	GLuint handle[2];
	glGenBuffers(2, handle);

	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0); 
	glVertexAttribPointer( (GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0 );


	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glBufferData(GL_ARRAY_BUFFER,  sizeof(tc), tc, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1); 
	glVertexAttribPointer( (GLuint)1, 2, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindVertexArray(0);
	glBindFramebuffer(GL_FRAMEBUFFER,0);

}
void updateBloomUniforms()
{
	//This method update uniforms for bloom
	//every render
	//
	bloomShaderHelper->setUniform("width",width);
	bloomShaderHelper->setUniform("height",height);
	bloomShaderHelper->setUniform("mvp",glm::mat4(1));

}
void renderBloomObjects()
{
	//This is the helper method for rending bloom effect
	//

	bloomShaderHelper->useProgram();
	updateBloomUniforms();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,renderTexture);
	glBindFramebuffer(GL_FRAMEBUFFER,0);

	glBindVertexArray(bloomVAO);



}



void renderSolarSystem()
{
	//This the helper method for rending solar system
	//

	if(!renderOnlyPlanet)
	{
		//Render only selected planet from menu
		for(int i=0;i<numOfCelstialObjects;i++)
		{	

			//Bind VAO for plant and render it
			setPlanetUniformsAndVAO(planets[i]);
			glDrawElements(GL_PATCHES, Planet::getNumIndices(), GL_UNSIGNED_INT, 0);
		}
	}
	else
	{
		//Render all the planets for Solar system
		setPlanetUniformsAndVAO(planets[renderOnlyPlanet-1]);
		glDrawElements(GL_PATCHES, Planet::getNumIndices(), GL_UNSIGNED_INT, 0);

	}
	if(planetOrbitCheck)
	{
		//Use program for orbit render 
		glUseProgram(planetOrbitShaderHelper->getProgramID());
		planetOrbitShaderHelper->setUniform("mvp",projectionMatrix*viewMatrix);//*sun->getModelMatrix());
		glLineWidth(3);
		//Render orbit for every planets
		for(int i=0;i<numOfCelstialObjects;i++)
		{	
			glBindVertexArray(planets[i]->getplanetOrbitBufferArray());
			glBindBuffer(GL_DRAW_BUFFER, planets[i]->getplanetOrbitBufferObject());
			glDrawElements(GL_LINE_LOOP,86,GL_UNSIGNED_INT,0);
		}
	}


}

void MyGLWindow::render()
{
	//This method renders the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//Disable blur while zooming as it take much time
	if(blurCheck && !isZooming)
	{

		//Render Solar System to texture for further refernce for blooming effect
		//i.e to add the original render to blured effect of same
		//
		glBindFramebuffer(GL_FRAMEBUFFER,fbo[1]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		//Render to store in temp texture for furter reference to acheive Bloom effect
		renderSolarSystem();



		//Bind FBO for Blur effect 
		glBindFramebuffer(GL_FRAMEBUFFER,fbo[0]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		//Render to texture for blur effect
		renderSolarSystem();



		bool b=true;

		renderBloomObjects();

		glDisable(GL_DEPTH_TEST);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		//ping pong for blur effect
		for(int i=0;i<40;i++)
		{

			glBindFramebuffer(GL_FRAMEBUFFER,fbo[0]);
			glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,b ? renderTexture2 : renderTexture,0);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D,b ? renderTexture : renderTexture2);

			//flag to toggle between verical and horiziontal blur
			bloomShaderHelper->setUniform("isVertical",(int)b);

			glDrawArrays(GL_TRIANGLES, 0, 6);

			//Toggle the flag
			b=!b;
		}
		//Render the blured effect to screen
		glBindFramebuffer(GL_FRAMEBUFFER,0);
		glClear(GL_COLOR_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,b ? renderTexture : renderTexture2);


		//combine blured effect to original redner to get the bloom effect
		if(bloomCheck)
		{
			GLuint bloomIndex = glGetSubroutineIndex(  bloomShaderHelper->getProgramID(), GL_FRAGMENT_SHADER, "bloomEffect");
			glUniformSubroutinesuiv( GL_FRAGMENT_SHADER, 1, &bloomIndex);


			//Textuer contianing origiranl render to be combined with blur effect
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D,tempRenderTexture);


		}


		glDrawArrays(GL_TRIANGLES, 0, 6);

		glEnable(GL_DEPTH_TEST);

	}
	else
	{
		//Render  with blur or bloom
		renderSolarSystem();
	}
	//Render menu
	TwDraw();


}








void loadMenus(int width,int height)
{
	//This method setups ANTTweekBar for renderng Menu bar
	//

	TwInit(TW_OPENGL_CORE, NULL);
	TwWindowSize(width, height);

	//Intialize menu bar
	solarSystemConfigureBar = TwNewBar("Configure Solar System");
	TwDefine(" 'Configure Solar System' color='255 255 255' position='10 60' size='250 250' alpha=0");

	//Display group

	//Add drop down for render mode 
	//i.e to render entire solar systme or planets alone
	//
	TwEnumVal planetEV[10] = { {SOLAR_SYTEM,"Solar System"},{SUN, "Sun"}, {MERCURY, "Mercury"}, {VENUS, "Venus"} ,{EARTH, "Earth"},
	{MARS, "Mars"},{JUPITER, "Jupiter"},{SATRUN, "Satrun"},{URANUS, "Uranus"},{NEPTUNE, "Neptune"}};

	TwType planetType = TwDefineEnum("planetType", planetEV, 10);
	TwAddVarRW(solarSystemConfigureBar, "Planets", planetType, &renderOnlyPlanet, 
		" group='Display' ");

	//Add check box for Planets orbit toggle
	TwAddVarRW(solarSystemConfigureBar, "Planet Orbits", TW_TYPE_BOOLCPP, &planetOrbitCheck, 
		" group='Display' help='Planet Orbits.' visible=true");

	//Add check box for Light toggle
	TwAddVarRW(solarSystemConfigureBar, "Light", TW_TYPE_BOOLCPP, &lightCheck, 
		" group='Display' help='Planet Light toggle.' ");


	//Add check box for Earths night light toggle
	TwAddVarRW(solarSystemConfigureBar, "Night Lights for Earth", TW_TYPE_BOOLCPP, &nightLights, 
		" group='Display' help='Planet Night Lights toggle.' visible=false");

	//Add check box for Arc Ball toggle
	//enabled only for Planet Render
	TwAddVarRW(solarSystemConfigureBar, "Arc Ball On", TW_TYPE_BOOLCPP, &arcBallOn, 
		" group='Display' help='Planet Arc Ball.' visible=false ");

	//Add check box for Blur effect toggle
	TwAddVarRW(solarSystemConfigureBar, "Blur effect", TW_TYPE_BOOLCPP, &blurCheck, 
		" group='Display'");

	//Add check box for bloom effect toggle
	TwAddVarRW(solarSystemConfigureBar, "Bloom effect", TW_TYPE_BOOLCPP, &bloomCheck, 
		" group='Display' visible=false ");

	//Camera group

	//Add Drop down for camera type selection
	TwEnumVal cameraEV[3] = { {FRONT_VIEW,"Front View"},{TOP_VIEW, "Top View"},{ORIBIT_VIEW,"Orbit View"}};

	TwType cameraType = TwDefineEnum("cameraType", cameraEV, 3);
	TwAddVarRW(solarSystemConfigureBar, "Cameras", cameraType, &cameraTypeSelected, 
		" group='Camera' ");



	//Add slider for Orbit Camere postion adjustment
	TwAddVarRW(solarSystemConfigureBar, "Orbit Camera X axis pos", TW_TYPE_FLOAT, &orbitCamXpos, " label='Orbit Camera X axis pos' min=-260 max=260  group='Camera' visible=false");

	//Add slider for Orbit Camere eye postion adjustment
	TwAddVarRW(solarSystemConfigureBar, "Orbit Camera Eye pos", TW_TYPE_FLOAT, &orbitCamEyes, " label='Orbit Camera Eye pos' min=0 max=360  group='Camera' visible=false");

	//Add slider for  Camere zoom postion adjustment
	//Only enabled for Front and Top view 
	//disabled for Orbit view
	TwAddVarRW(solarSystemConfigureBar, "Camera Zoom", TW_TYPE_FLOAT, &cameraZoom, " label='Camera Zoom' min=1 max=1000  group='Camera' visible=true");

	//Add check box for Auto zoom toggle
	//Only enabled for Front and Top view 
	//disabled for Orbit view
	TwAddVarRW(solarSystemConfigureBar, "Auto Zoom", TW_TYPE_BOOLCPP, &cameraAutoZoom, 
		" group='Camera'  ");


}
void MyGLWindow::initializeGL(GLFWwindow *glfw_window,int w, int h)
{
	//This method Intialzie OPENGL context
	//and all required setups
	//
	width=w;
	height=h;
	glewInit();
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glLineWidth(5);
	glViewport(0,0,width,height);
	//Create new Arcball and Camera
	arcBall=new ArcBall(width,height);
	camera=new Camera();

	projectionMatrix=glm::perspective(35.0f,  (float)width/height, 1.0f, 1000.0f);
	viewMatrix =glm::lookAt(glm::vec3(0.0f, 500.0f, 0.0f),glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.0f, 0.0f, -1.0f));


	glEnable(GL_TEXTURE_2D);
	//Call all helper intialize methods
	loadPlantes();
	loadPlanetShaders();
	loadTextures();
	loadMenus(width,height);
	loadBloom();
	loadOrbitProgram();


	glEnable(GL_DEPTH_TEST);
	glPointSize(10);

	//Decalre Function pointer for call back methods to trigger mouse events
	void(ArcBall::*GLFWmousebuttonfun)(GLFWwindow *, int, int, int);
	void(*GLFWmousebuttonfun2)(GLFWwindow *, int, int, int);

	void(* GLFWcursorposfun)(GLFWwindow *, double, double);
	void(* GLFWkeyfun)(GLFWwindow*,int,int,int,int);

	GLFWmousebuttonfun2=&onMouseButton;
	GLFWcursorposfun=&onMouseMotion;
	//set mouse button call back funtion
	glfwSetMouseButtonCallback(glfw_window,GLFWmousebuttonfun2);
	//set mouse motion call back funtion
	glfwSetCursorPosCallback(glfw_window,GLFWcursorposfun);
	//set resize call back funtion
	glfwSetFramebufferSizeCallback(glfw_window, framebuffer_size_callback);





}




void MyGLWindow::cleanUp()
{
	//This method is for clean up
	//Delete all Frame bufferes
	glDeleteFramebuffers(2,fbo);

	//Delete all textures
	glDeleteTextures(1,&renderTexture);
	glDeleteTextures(1,&renderTexture2);
	glDeleteTextures(1,&depthTexture);

	glDeleteTextures(1,&tempRenderTexture);
	glDeleteTextures(1,&tempDepthTexture);

	//Terminate window
	glfwTerminate();

}

