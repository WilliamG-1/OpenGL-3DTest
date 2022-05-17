#include "Renderer.h"
const int screenWidth = 720;
const int screenHeight = 660;
const float aspectRatio = screenWidth / screenHeight;
Renderer::Renderer()
	:
	shader("Shaders/Vertex.vert", "Shaders/Fragment.frag"), triangleCount(0),
	model(glm::mat4(1.0f)), view(glm::mat4(1.0f)), projection(glm::mat4(1.0f))
{
	
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
	view = camera.getViewMatrix();
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

void Renderer::initCube(int count, std::vector<glm::vec3> cubePositions)
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
	for (int i = 0; i < count; i++)
	{
		float angle = -20.0f;
		glm::mat4 m(1.0f);
		m = glm::translate(m, cubePositions[i]);
		//m = glm::rotate(m, glm::radians(-10.0f + angle * i), glm::vec3(0.2f, 0.2f, 0.2f));
		modelContainer.push_back(m);
	}
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
	shader.setUniformMat4f("model", model);
	shader.setUniformMat4f("view", view);
	shader.setUniformMat4f("projection", projection);



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
		camera.processInput(glm::vec3(0.0f, 0.0f, 1.0f), 1, deltaTime);
	// Left
	if (key == Input::A)
		camera.processInput(glm::vec3(1.0f, 0.0f, 0.0f), -1, deltaTime);
	// Backwards
	if (key == Input::S)
		camera.processInput(glm::vec3(0.0f, 0.0f, 1.0f), -1, deltaTime);
	// Right
	if (key == Input::D)
		camera.processInput(glm::vec3(1.0f, 0.0f, 0.0f), 1, deltaTime);
	// Down
	if (key == Input::SHIFT)
		camera.processInput(glm::vec3(0.0f, 1.0f, 0.0f), -1, deltaTime);
	// Up
	if (key == Input::SPACE)
		camera.processInput(glm::vec3(0.0f, 1.0f, 0.0f), 1, deltaTime);

	if (key == Input::LEFT_KEY)
		camera.changeView(-1, 0.0f, 0.0f);
	if (key == Input::RIGHT_KEY)
		camera.changeView(1, 0.0f, 0.0f);
	if (key == Input::DOWN_KEY)
		camera.changeView(0.0f, -1, 0.0f);
	if (key == Input::UP_KEY)
		camera.changeView(0.0f, 1, 0.0f);
	if (key == Input::U)
		camera.changeView(0, 0, -1);
	if (key == Input::I)
		camera.changeView(0, 0, 1);
	if (key == Input::T)
	{
		for (glm::mat4& mod : modelContainer)
		{
			mod = glm::rotate(mod, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		}
	}
	
}

void Renderer::render(GLFWwindow* window)
{
	deltaTime = (currentTime - lastTime) * 10;
	lastTime = currentTime;
	currentTime = glfwGetTime();

	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	shader.use();
	// Update Stuff Here -----------------------------------------------------|
	view = camera.getViewMatrix();

	
	shader.setUniformMat4f("view", view);
	//shader.setUniformMat4f("model", model);

	camera.update(window);
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
		for (const glm::mat4 model : modelContainer)
		{
			shader.setUniformMat4f("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
			
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

