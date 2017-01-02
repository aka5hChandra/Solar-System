#ifndef ARC_BALL
#define ARC_BALL
#include "planet.h"

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <GLFW\glfw3.h>
#include <algorithm>
#include <iostream>
class ArcBall
{
public:
	ArcBall(int screenWidth,int screenHeight):lastMx(0),lastMy(0),curMx(0),curMy(0),arcballOn(false),
		 screenWidth(screenWidth), screenHeight(screenHeight),curMatrix(glm::mat4(1)),arcballBeenActive(0)
	,cameraEye(glm::vec4(50))
	{
	
	}
	//typedef void(* GLFWmousebuttonfun)(GLFWwindow *, int, int, int);
	//
		void onMouseButton( GLFWwindow* window,int button, int action ) ;	
		void onMouseMotion(double x, double y);
	glm::vec3 computeArcbalVector(int x, int y);
	void updateModelMatrix(Planet* planet,glm::mat4 viewMatrix);
	int getAcrballOn();
	glm::mat4 getCurMatrix();

	glm::mat4 camMatrix;

private:
	int lastMx ;
	int lastMy;
	int curMx ;
	int curMy ;
	int arcballOn ;
	int screenWidth;
	int screenHeight;
	glm::mat4 curMatrix;
	int arcballBeenActive;
	 float angle;
	 glm::vec3 axisInCameraCoord;

	 glm::vec4 cameraEye;

	 
};
#endif