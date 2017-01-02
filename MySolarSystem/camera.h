#ifndef CAMERA_H
#define CAMERA_H
#include<gtc\matrix_transform.hpp>

class Camera
{
public:
	Camera();
	glm::mat4 getViewMatrix();
	void mouseUpdate(glm::vec2 newMousePosition);
	void resetCamera();

private:
	glm::vec3 position;
	glm::vec3 viewDirection;
	glm::vec3 up;
	glm::vec2 oldMousePosition;

};
#endif