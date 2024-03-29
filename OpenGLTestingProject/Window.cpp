#include "Window.h"
#include <iostream>
Window::Window(const char* Title, int width, int height)
	:
	window(nullptr), screenHeight(height), screenWidth(width), title(Title)
{
	window = glfwCreateWindow(screenWidth, screenHeight, title, nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Error, could not create window!" << std::endl;
		glfwTerminate();
	}
	
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(this->window, [](GLFWwindow* window, int width, int height)
		{
			glViewport(0.0f, 0.0f, width, height);
		});
	init();
}

Window::~Window()
{
	window = nullptr;
	glfwDestroyWindow(window);
}



void Window::init()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize Glad" << std::endl;
	}
	

	glViewport(0, 0, screenWidth, screenHeight);
	
	
}

GLFWwindow* Window::getWindow() const
{
	return window;
} 