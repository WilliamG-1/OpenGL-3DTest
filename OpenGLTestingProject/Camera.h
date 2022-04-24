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

	void processInput(char input);
	void rotateLeftRight(float degrees);
	void rotateUpDown(float degrees);
	void moveLeftRight(float deltaX);
	void moveUpDown(float deltaY);
	void moveForwardsBackwards(float deltaZ);
	void update();
	// Getters
	glm::mat4 getModelMatrix() const;
	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;
private:
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;


	float angle = -55.0f;
	const int PI = 3.14159;
};