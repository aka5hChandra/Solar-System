#include "myGLWindow.h"

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>


#define WIN_WIDTH 1200//800
#define WIN_HEIGHT 800//600

GLFWwindow *glfw_window;
MyGLWindow *myGLWidnow;

void mainLoop()
{
	while( ! glfwWindowShouldClose(glfw_window) && !glfwGetKey(glfw_window, GLFW_KEY_ESCAPE) ) {
		myGLWidnow->update(glfwGetTime(),glfw_window);
		myGLWidnow->render();
		glfwSwapBuffers(glfw_window);
		glfwPollEvents();
	}

}

int main(int argc,char* argv[])
{
	if( !glfwInit() ) 
		{
			printf("glfw initialize failed",stderr);
			exit( EXIT_FAILURE );
		}
	
	glfwWindowHint( GLFW_SAMPLES ,4 );
	
	glfw_window = glfwCreateWindow( WIN_WIDTH, WIN_HEIGHT, "My Solar System", NULL, NULL);
	if( ! glfw_window ) {
		glfwTerminate();
		exit( EXIT_FAILURE );
	}
	glfwMakeContextCurrent(glfw_window);
	
	myGLWidnow->initializeGL(glfw_window,WIN_WIDTH,WIN_HEIGHT);

	//myGLWidnow->resize(WIN_WIDTH,WIN_HEIGHT,glfw_window);

	
	mainLoop();

	
	myGLWidnow->cleanUp();

}