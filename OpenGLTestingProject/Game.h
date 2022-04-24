#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


#include "Window.h"
#include "Triangle.h"
#include "Renderer.h"
#include "Camera.h"
class Game
{
public:
	Game();
	~Game();
	void run();
	void processInput(GLFWwindow* window);
	
private:
	// Member Variables
	Window window;
	Renderer renderer;
	
	bool gameRunning = true;		
	// Class Methods
	void composeFrame();
};

