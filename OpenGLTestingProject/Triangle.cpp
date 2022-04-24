#include "Triangle.h"

Triangle::Triangle()
	:
	shader("Shaders/Vertex.vert", "Shaders/Fragment.frag"), VBO(0), VAO(0)

{
	
	vertices[0] = -0.5f;
	vertices[1] = -0.5f;
	vertices[2] =  0.0f;
	vertices[3] = -0.5f;
	vertices[4] =  0.5f;
	vertices[5] =  0.0f;
	vertices[6] =  0.5f;
	vertices[7] =  0.0f;
	vertices[8] =  0.0f;
	
	vertices[9] = 0.5f;
	vertices[10] = 0.5f;
	vertices[11] = 0.0f;
	vertices[12] = 0.5f;
	vertices[13] = -0.5f;
	vertices[14] = 0.0f;
	vertices[15] =- 0.5f;
	vertices[16] = 0.0f;
	vertices[17] = 0.0f;
	init();
	
}

Triangle::Triangle(int in_width, int in_height, float x, float y, int rotation)
	:
	shader("Shaders/Vertex.vert", "Shaders/Fragment.frag"), VBO(0), VAO(0), width(in_width), height(in_height), rotation(rotation)
{
	vertices[0] = x;
	vertices[1] = y;
	for (int k = 2; k < 9; k += 3)
	{
		vertices[k] = 0;
	}
	vertices[3] = x + width;
	vertices[4] = 0;
	vertices[6] = 0;
	vertices[7] = y + height;

	init();

}

Triangle::~Triangle()
{

}

void Triangle::init()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,					// Layout Location
		3,					// Size of vector
		GL_FLOAT,			// Data Type of Vector Components
		GL_FALSE,			// Normalized
		3 * sizeof(float),	// Stride (How many stuff we skip to get to the next first element)
		(void*)0			// Offset
	);
	glEnableVertexAttribArray(0);
	shader.use();
}
void Triangle::draw()
{
	shader.use();
	glBindVertexArray(VAO);
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
