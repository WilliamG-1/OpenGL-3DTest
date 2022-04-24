#include "Renderer.h"
Renderer::Renderer()
	:
	shader("Shaders/Vertex.vert", "Shaders/Fragment.frag"), triangleCount(0)
{
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
}

Renderer::~Renderer()
{

}

void Renderer::initTriangles(int count, float starting_vertices[], float widthAndHeights[])
{
	triangleCount = count;
	
	
	if (!textureUse)
	{
		int j = 0;
		int k = 0;
		// i = x; i + 1 = y; i + 2 = z;\
	// Each loop initializes a triangle (composed of 3 vertices; 9 array elements)
		for (int i = 0; i < triangleCount * 9; i += 9)
		{

			// First Vertex
			vertices[i] = starting_vertices[j];
			vertices[i + 1] = starting_vertices[j + 1];
			vertices[i + 2] = starting_vertices[j + 2];

			// Second Vertex
			vertices[i + 3] = starting_vertices[j] + widthAndHeights[k];
			vertices[i + 4] = starting_vertices[j + 1];
			vertices[i + 5] = starting_vertices[j + 2];

			// Third Vertex
			vertices[i + 6] = starting_vertices[j];
			vertices[i + 7] = starting_vertices[j + 1] + widthAndHeights[k + 1];
			vertices[i + 8] = starting_vertices[j + 2];
			j += 3;
			k += 2;
		}


		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9 * triangleCount, vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(
			0,						// Layout Location
			3,						// Size of vector
			GL_FLOAT,				// Data Type of Vector Components
			GL_FALSE,				// Normalized
			3 * sizeof(float),		// Stride (How many stuff we skip to get to the next first element)
			(void*)0				// Offset
		);
	}
	
	
	shader.use();
	//shader.setUniformFloat4f("color", color);
	glEnableVertexAttribArray(0);
	mode = renderMode::TRIANGLE;
}

void Renderer::initSquare(float x, float y, float width, float height)
{
	int offset = squareCount * 30;
	// ----->First Triangle <---- \\
	
	// Top Left
	squareVertices[offset + 0] = x;
	squareVertices[offset + 1] = y + height;
	squareVertices[offset + 2] = 0;

	squareVertices[offset + 3] = 0.0f;
	squareVertices[offset + 4] = 1.0f;

	// Bottom Left
	squareVertices[offset + 5] = x;
	squareVertices[offset + 6] = y;
	squareVertices[offset + 7] = 0;

	squareVertices[offset + 8] = 0.0;
	squareVertices[offset + 9] = 0.0;

	// Bottom Right
	squareVertices[offset + 10] = x + width;
	squareVertices[offset + 11] = y;
	squareVertices[offset + 12] = 0;

	squareVertices[offset + 13] = 1.0f;
	squareVertices[offset + 14] = 0.0f;

	// ----> Second Triangle <---- \\

	// Top Left
	squareVertices[offset + 15] = x;
	squareVertices[offset + 16] = y + height;
	squareVertices[offset + 17] = 0;

	squareVertices[offset + 18] = 0.0f;
	squareVertices[offset + 19] = 1.0f;

	// Top Right
	squareVertices[offset + 20] = x + width;
	squareVertices[offset + 21] = y + height;
	squareVertices[offset + 22] = 0.0f;

	squareVertices[offset + 23] = 1.0f;
	squareVertices[offset + 24] = 1.0f;

	// Bottom Right
	squareVertices[offset + 25] = x + width;
	squareVertices[offset + 26] = y;
	squareVertices[offset + 27] = 0;

	squareVertices[offset + 28] = 1.0f;
	squareVertices[offset + 29] = 0.0f;

	squareCount++;

	mode = renderMode::SQUARE;
	
}

void Renderer::initCube(int count, float starting_vetices[], float widthHeightDepth[])
{
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 180, vertices, GL_STATIC_DRAW);

	mode = renderMode::CUBE;
}

void Renderer::processSquares()
{

	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 5 * 6 * squareCount, squareVertices, GL_STATIC_DRAW);
	// First Attributes (Triangle Vertices)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
	glEnableVertexAttribArray(0);

	// Second Attributes (Texture coordinates)
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	loadTex("Assets/DiamondOre.png", true);

	shader.use();

	shader.setUniformTex2f("texture1");
	shader.setUniformMat4f("model", camera.getModelMatrix());
	shader.setUniformMat4f("view", camera.getViewMatrix());
	shader.setUniformMat4f("projection", camera.getProjectionMatrix());



}

void Renderer::compose()
{
	// Do shit here before rendering
	
	processSquares();
}

void Renderer::processInput(Input key)
{
	// Forwards
	if (key == Input::W)
		camera.moveForwardsBackwards(0.1f);
	// Left
	if (key == Input::A)
		camera.moveLeftRight(0.01f);
	// Backwards
	if (key == Input::S)
		camera.moveForwardsBackwards(-0.1f);
	// Right
	if (key == Input::D)
		camera.moveLeftRight(-0.01f);
	// Down
	if (key == Input::SHIFT)
		camera.moveUpDown(0.01f);
	// Up
	if (key == Input::SPACE)
		camera.moveUpDown(-0.01f);

	if (key == Input::LEFT_KEY)
		camera.rotateLeftRight(-1.0f);
	if (key == Input::RIGHT_KEY)
		camera.rotateLeftRight(1.0f);
	if (key == Input::DOWN_KEY)
		camera.rotateUpDown(1.0f);
	if (key == Input::UP_KEY)
		camera.rotateUpDown(-1.0f);
}

void Renderer::render()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	shader.use();
	// Update Stuff Here -----------------------------------------------------|
	shader.setUniformMat4f("model", camera.getModelMatrix());
	shader.setUniformMat4f("view", camera.getViewMatrix());

	//camera.rotateLeftRight((float)sin(glfwGetTime()));
	//camera.rotateUpDown((float)cos(glfwGetTime()));
	// -----------------------------------------------------------------------|
	
	glBindVertexArray(VAO);
	switch (mode)
	{
	case renderMode::TRIANGLE:
		glDrawArrays(GL_TRIANGLES, 0, 3 * triangleCount);
		break;
	case renderMode::SQUARE:
		glDrawArrays(GL_TRIANGLES, 0, 6 * squareCount);
		break;
	case renderMode::CUBE:
		glDrawArrays(GL_TRIANGLES, 0, 36);
		break;
	}
	
	
}

void Renderer::loadTex(std::string filePath, bool alphaChannel)
{
	// Image gets flipped Y - Axis
	stbi_set_flip_vertically_on_load(true);

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	// Set all the parameters
	// Wrapping Parameters (If texture coordinates exceed those of object) -------------------------->
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	// ------------> Min/Mag filters When Scaling different size of the same resolution texture <-------------
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;

	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

	if (data && alphaChannel)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	
	else if (data && !alphaChannel)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	else {
		std::cout << "ERROR! Failed to load file path: " << filePath << std::endl;
	}

	stbi_image_free(data);

}

