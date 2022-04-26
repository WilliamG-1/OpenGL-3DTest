#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera
{
public:
	Camera();

	void processInput(glm::vec3 axis, int direction, float deltaTime);
	void update(GLFWwindow* window);

	// Getters
	glm::mat4 getViewMatrix() const;
private:
	
	// Position Vectors
	glm::vec3 cameraPosition;
	glm::vec3 cameraTarget;

	// Axes of Camera (basis originating from camera position)
	glm::vec3 cameraDirection; // Vector pointing from the origin to the camera

	glm::vec3 cameraRight; // Vector ponting to the right of our camera
	glm::vec3 cameraUp;	// Vector pointing on top of the camera
	glm::vec3 cameraFront; // Vector pointing to the front of camera

	float cameraSpeed = 1.3f;
	double xPos;
	double yPos;
	float angle = -55.0f;
	const int PI = 3.14159;

	
};