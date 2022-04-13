#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "stb_image.h"
#include "Shader.h"
class Triangle
{
public:
	Triangle();
	// Width of object, Height of Object, Starting Coordinate, rotation of triangle
	Triangle(int in_width, int in_height, float x, float y, int rotation);
	~Triangle();
	void draw();
	void init();
private:
	int width;
	int height;
	int rotation;
	glm::vec3 vert[3];
	GLuint VAO;
	GLuint VBO;	
	Shader shader;
	float vertices[9];
		
};

