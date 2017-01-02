#ifndef WINDOW_H
#define WINDOW_H
#include<GL/glew.h>
#include<gtc\matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "material.h"
#include "light.h"
#include<math.h>
#include<glm.hpp>
#include<iostream>
#include "textureReader.h"
#include<iostream>
#include "planet.h"
#include "shaderReader.h"
#include "camera.h"
#include "arcBall.h"
#include "constants.h"
#include <string.h>
#include <AntTweakBar.h>
class MyGLWindow
{

public:


	void initializeGL(GLFWwindow *glfwWindow,int width,int height);


	void update( float t,GLFWwindow *glfwWindow);

	void render();

	void cleanUp();











};

#endif 
