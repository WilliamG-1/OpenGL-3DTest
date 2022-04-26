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
	cameraFront(glm::vec3(0.0f, 0.0f, -1.0f))
{

}

void Camera::processInput(glm::vec3 axis, int direction, float deltaTime)
{
	if (axis.x > 0)
	{
		cameraPosition += cameraRight * deltaTime * cameraSpeed * (float)direction;
	}
	if (axis.y > 0)
	{
		cameraPosition += cameraUp * deltaTime * cameraSpeed * (float)direction;
	}
	if (axis.z > 0)
	{
		cameraPosition += cameraFront * deltaTime * cameraSpeed * (float)direction;
	}
}

void Camera::update(GLFWwindow* window)
{
	glfwGetCursorPos(window, &xPos, &yPos);
	//std::cout << "x Position: " << xPos << ". Y Position: " << yPos << std::endl;
	//glfwSetCursorPos(window, screenWidth / 2, screenHeight / 2);
	//view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
	
}

   // --------> Getters <--------- \\

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
}

