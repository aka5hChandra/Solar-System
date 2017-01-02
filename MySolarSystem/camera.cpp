#include "camera.h"

Camera::Camera():position(glm::vec3(0.0,0.0,50.0)),
	viewDirection(glm::vec3(0.0,0.0,-1.0)),up(glm::vec3(0.0,1.0,0.0)){
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(position,position+viewDirection,up);
                                            
}

void Camera::mouseUpdate(glm::vec2 newMousePosition)
{
	
	glm::vec2 mouseDelta=newMousePosition-oldMousePosition;
	if(glm::length(mouseDelta)>100.0f)
	{
	oldMousePosition=newMousePosition;
	return;	
	}


	const float ROTATIONAL_SPEED=0.5f;

	glm::vec3 toRotateAround=glm::cross(viewDirection,up);

	glm::mat4 rotator=glm::rotate(glm::mat4(1),mouseDelta.x*ROTATIONAL_SPEED,up)*
						glm::rotate(glm::mat4(1),mouseDelta.y*ROTATIONAL_SPEED,toRotateAround);
	

	viewDirection=glm::mat3(rotator)*viewDirection;

	oldMousePosition=newMousePosition;

}
void Camera::resetCamera()
{
viewDirection=glm::vec3(0.0,0.0,-1.0);
up=glm::vec3(0.0,1.0,0.0);

}