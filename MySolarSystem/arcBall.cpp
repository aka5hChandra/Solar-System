#include "arcBall.h"

//Arc ball impementation on mouse movement input

void ArcBall::onMouseButton( GLFWwindow* window,int button, int action ) 	
{
	//when mouse button is pressed update the last and and current position of
	//mouse cursor 
	if (button == GLFW_MOUSE_BUTTON_LEFT && action==GLFW_PRESS)
	{
		arcballOn = true;
		arcballBeenActive=1;
		double xpos;
		double ypos;
		glfwGetCursorPos(window,&xpos,&ypos);

		lastMx = curMx = xpos;
		lastMy = curMy = xpos;
	} else {
		arcballOn = false;
	}

}
void ArcBall::onMouseMotion(double x, double y)
{
	//on mouse motion keep tracking mouse current cursor postion
	if (arcballOn) {  
		// if left button is pressed
		curMx = x;
		curMy = y;
	}
}
glm::vec3 ArcBall::computeArcbalVector(int x, int y)
{

	//compute the vector on screen for mouse last and current cursor points
	//using pythagorean theoram
	glm::vec3 P = glm::vec3(1.0*x/screenWidth*2 - 1.0,
		1.0*y/screenHeight*2 - 1.0,
		0);
	P.y = -P.y;
	float OP_squared = P.x * P.x + P.y * P.y;
	if (OP_squared <= 1*1)
		P.z = sqrt(1*1 - OP_squared);  // Pythagore
	else
		P = glm::normalize(P);  // nearest point


	return P;

}
void ArcBall::updateModelMatrix(Planet* planet,glm::mat4 viewMatrix)
{
	//get model matrix for arc ball rotaion

	if (curMx != lastMx || curMy != lastMy) {
	//when arc ball is activated by pressing mouse button and mouse cursor postion is changed
		
		//compute vectors for last and current mouse postions on screen
		glm::vec3 va = computeArcbalVector(lastMx, lastMy);
		glm::vec3 vb = computeArcbalVector( curMx,  curMy);
		//get angle between vectors
		angle = acos(std::min(1.0f, glm::dot(va, vb)));
		//get camera axis by using cross prodcut
		axisInCameraCoord = glm::cross(va, vb);
		
		//get object cordinates from camera cordinates using inverse function
		glm::mat3 camera2object = glm::inverse(glm::mat3(viewMatrix) * glm::mat3(planet->getModelMatrix()));
		glm::vec3 axis_in_object_coord = camera2object * axisInCameraCoord;


		planet->setModelMatrix(glm::scale(curMatrix,glm::vec3(planet->getScale())));

		//curMatrix);
		lastMx = curMx;
		lastMy = curMy;

		//////

		//for further refrence
		glm::mat3 camera2object2 = glm::inverse(glm::mat3(viewMatrix) * glm::mat3(curMatrix));
		glm::vec3 axis_in_object_coord2 = camera2object2 * axisInCameraCoord;
		cameraEye=curMatrix*cameraEye;
		curMatrix= glm::rotate(
			curMatrix,
			glm::degrees(angle), axis_in_object_coord2);

	}

}

int ArcBall::getAcrballOn()
{
	return arcballOn;
}

glm::mat4 ArcBall::getCurMatrix()
{
	return curMatrix;

}


