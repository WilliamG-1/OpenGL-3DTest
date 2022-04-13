#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "Triangle.h"
class Game
{
public:
	Game();
	~Game();
	 void run();
	void processInput(GLFWwindow* window);
private:
	Window window;
	bool gameRunning = true;	
	Triangle testTriangle;
	Triangle test2;
};

