#include "Camera.h"
#include <iostream>
const int screenWidth = 720;
const int screenHeight = 660;
const float aspectRatio = screenWidth / screenHeight;
Camera::Camera()
	: xPos(0), yPos(0),
	cameraPosition(glm::vec3(0.0f, 0.0f, 5.0f)), // Vector Denoting the position of the camera
	cameraTarget(glm::vec3(0.0f, 0.0f, 0.0f)), // Vector denoting positon of target (what camera is looking at)

	cameraDirection(glm::normalize(cameraPosition - cameraTarget)), // Vector pointing at the camera 
	cameraRight(glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), cameraDirection))),
	cameraUp(glm::normalize(glm::cross(cameraDirection, cameraRight))),
	cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),

	// Initalize MVP matrices to Identitity Matrices
	model(glm::mat4(1.0f)),		// Matrix that converts model
	view(glm::mat4(1.0f)),		// Matrix that views camera
	projection(glm::mat4(1.0f)) // Matrix that creates projection


{
	projection = glm::perspective((float)PI/4, aspectRatio, 0.1f, 100.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));	
	view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

}

void Camera::processInput(char input)
{

}

void Camera::rotateLeftRight(float degrees, float deltaTime)
{
	model = glm::rotate(model, glm::radians(degrees), glm::vec3(0.0, 0.0f, 0.2f));
}

void Camera::rotateUpDown(float degrees, float deltaTime)
{
	model = glm::rotate(model, glm::radians(degrees), glm::vec3(1.0f, 0.0f, 0.0f));
}

// Movement
void Camera::moveLeftRight(int direction, float deltaTime)
{
	cameraPosition += (float)direction * cameraSpeed * deltaTime * cameraRight;
}

void Camera::moveUpDown(int direction, float deltaTime)
{
	cameraPosition += (float)direction * cameraSpeed * deltaTime * cameraUp;
}

void Camera::moveForwardsBackwards(int direction, float deltaTime)
{	
	cameraPosition += (float)direction * cameraSpeed * deltaTime * cameraFront;
}




void Camera::update(GLFWwindow* window)
{
	glfwGetCursorPos(window, &xPos, &yPos);
	//std::cout << "x Position: " << xPos << ". Y Position: " << yPos << std::endl;
	//glfwSetCursorPos(window, screenWidth / 2, screenHeight / 2);
	view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
	
}

   // --------> Getters <--------- \\

glm::mat4 Camera::getModelMatrix() const
{
	return model;
}

glm::mat4 Camera::getViewMatrix() const
{
	return view;
}

glm::mat4 Camera::getProjectionMatrix() const
{
	return projection;
}


