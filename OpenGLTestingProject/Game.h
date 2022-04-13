#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.h"
class Game
{
public:
	Game();
	~Game();
	void run();
	void processInput(GLFWwindow* window);
private:
	bool gameRunning = true;

	Window window;
};

