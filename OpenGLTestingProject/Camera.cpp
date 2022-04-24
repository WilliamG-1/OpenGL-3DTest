#include "Camera.h"
#include <iostream>
const int screenWidth = 720;
const int screenHeight = 660;
const float aspectRatio = screenWidth / screenHeight;
Camera::Camera()	
{
	model = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);
	// Projects (creates an orthographic frustrum) Take the aspect ratio
	projection = glm::perspective((float)PI/4, aspectRatio, 0.1f, 100.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));

}

void Camera::processInput(char input)
{

}

void Camera::rotateLeftRight(float degrees)
{
	model = glm::rotate(model, glm::radians(degrees), glm::vec3(0.0, 0.0f, 1.0f));
}

void Camera::rotateUpDown(float degrees)
{
	model = glm::rotate(model, glm::radians(degrees), glm::vec3(1.0f, 0.0f, 0.0f));
}

void Camera::moveLeftRight(float deltaX)
{
	view = glm::translate(view, glm::vec3(deltaX, 0.0f, 0.0f));
}

void Camera::moveUpDown(float deltaY)
{
	view = glm::translate(view, glm::vec3(0.0f, deltaY, 0.0f));
}

void Camera::moveForwardsBackwards(float deltaZ)
{
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, deltaZ));
}




void Camera::update()
{
	std::cout << angle << std::endl;
	//projection = glm::perspective((float)PI / 4, aspectRatio, 0.1f, 100.0f);
	
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
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


