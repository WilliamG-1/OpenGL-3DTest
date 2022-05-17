#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "stb_image.h"
#include "Shader.h"
#include "Camera.h"
#include <vector>
// Input/Keys Enum
enum class Input
{
    DEFAULT = 0, W, A, S, D, CTRL, SPACE, SHIFT, LEFT_KEY, RIGHT_KEY, UP_KEY, DOWN_KEY, T, U, I
};

class Renderer
{
public:
	Renderer();
	~Renderer();
	void render(GLFWwindow* window);
    void initTriangles(int count, float starting_vertices[], float widthAndHeights[]);
    void initSquare(float x, float y, float width, float height);
	void initCube(int count, std::vector<glm::vec3> cubePositions);
    void loadTex(std::string filePath, bool alphaChannel);

    void processInput(Input key);
    void compose();

private:
    enum class renderMode {
        TRIANGLE = 0, SQUARE, CUBE
    } mode = renderMode::TRIANGLE;
	GLuint VBO;
	GLuint VAO;
	Shader shader;
    GLuint texture1;
    Camera camera;

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    std::vector<glm::mat4> modelContainer;
    std::vector<glm::vec3> cubePositions;

    int renderShape; // 0 = Triangles, 1 = Square, 2 = Cube

	float vertices[180] = {0.0f};
    float squareVertices[210] = { 0.0f };
	float cubeVertices[180] = {
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

    bool firstSquare = true;
    bool firstTriangle = true;

	int triangleCount = 0;
    int squareCount = 0;
    int cubeCount = 0;

    bool textureUse = false;

    // Delta Time Stuff $*$*$**$*$*$*$*$
    float deltaTime = 0.0f;
    float lastTime = 0.0f;
    float currentTime = glfwGetTime();

    void processSquares();
  
};

