#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(const char* Title, int width, int height);
	~Window();
	
	void init();
	// Getters
	GLFWwindow* getWindow() const;
	
private:
	GLFWwindow* window;
	int screenWidth;
	int screenHeight;
	const char* title;
};

