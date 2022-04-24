#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Game.h"
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Game game;
	game.run();

	std::cin.get();
}