#include "Camera.h"
#include <iostream>
#include <iomanip>
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
	std::cout << std::fixed << std::setprecision(2);

	std::cout << "Initial Front Vector is: ";
	printVector(cameraFront);
	std::cout << " Initial Up Vector is: ";
	printVector(cameraUp);
	std::cout << std::endl;
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


void Camera::changeView(float dx, float dy, float dz)
{
	float cameraSpeed = 0.025f;
	if (firstCalculate)
	{
		//direction.x = cameraFront.x + dx;
		//direction.y = cameraFront.y + dy;
		//direction.z = cameraFront.z + dz;
		direction = glm::vec3(cameraFront.x, cameraFront.y, cameraFront.z);

		firstCalculate = false;
	}
	else if(dx != 0)
	{
		direction += cameraRight * dx * cameraSpeed;
	}
	else if (dy != 0)
	{
		direction += cameraUp * dy * cameraSpeed;
	}
	
	if (dz != 0)
	{
		cameraUp += cameraRight * dz * cameraSpeed;
		cameraFront = getOrthogonalProjection(cameraUp, cameraFront);
		cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
	}
	else
	{
		cameraFront = glm::normalize(direction);
		cameraUp = getOrthogonalProjection(cameraFront, cameraUp);
		cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
	}
	

	std::cout << "F Vector: " << "<" << cameraFront.x << ", " << cameraFront.y << ", " << cameraFront.z << ">  |  ";
	std::cout << "U Vector: " << "<" << cameraUp.x << ", " << cameraUp.y << ", " << cameraUp.z << ">  |  ";
	std::cout << "R Vector: " << "<" << cameraRight.x << ", " << cameraRight.y << ", " << cameraRight.z << ">" << std::endl;


}

void Camera::update(GLFWwindow* window)
{
	glfwGetCursorPos(window, &xPos, &yPos);
	
}

// Calculates an orthogonal vector to the "line" (original vector) from a projectedVector (both must be linearly independent)
glm::vec3 Camera::getOrthogonalProjection(glm::vec3 L, glm::vec3 projectedVector)
{
	// This is a process to get the orthogonal diretion vector to the line
	// Calculate dot product between line and projectedVector
	float dot = glm::dot(L, projectedVector);
	// Now, Calculate the inner prodcut (line dotted with itself)
	float inner = glm::dot(L, L);
	// Next, we divide the dot by the inner product
	float division = dot / inner;
	// Finally, we multiply this by the line vector. THis creates the actual projection of the vector.
	glm::vec3 projection = L * division;
	
	// Next, we subtract the projection vector from the projected vector to get a direction vector orthogonal to our line (original vector). We return this vector as the orthonormal vector
	return glm::normalize(projectedVector - projection);
}

void Camera::printVector(glm::vec3 vector) const
{
	std::cout << "<" << vector.x << ", " << vector.y << ", " << vector.z << ">";
}
   // --------> Getters <--------- \\

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
}

