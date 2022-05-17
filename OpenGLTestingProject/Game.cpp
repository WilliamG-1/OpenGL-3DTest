#include "Game.h"
#include <iostream>
const int screenWidth = 720;
const int screenHeight = 660;

Game::Game()
    :
    window("My Game", screenWidth, screenHeight) // testTriangle(.3f, .3f, -0.5f, -0.5f, 0), test2(0.5f, 0.3f, 0.0f, 0.0f, 0)
{
   
}

Game::~Game()
{

}

void Game::run()
{
    //glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    composeFrame();
    while (gameRunning)
    {
        processInput(window.getWindow());

        glClearColor(.25f, .35f, .45f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        // Render stuff after clearing screen!
        renderer.render(window.getWindow());

        // Some Render Function Here


        glfwSwapBuffers(window.getWindow());
    }
    glfwTerminate();
}

void Game::processInput(GLFWwindow* window)
{
    Input key = Input::DEFAULT;
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == (GLFW_PRESS))
    {
        gameRunning = false;
    }

    // Keyboard input --------------------------------->
    if (glfwGetKey(window, GLFW_KEY_W) == (GLFW_PRESS))
    {
        key = Input::W;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == (GLFW_PRESS))
    {
        key = Input::A;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == (GLFW_PRESS))
    {
        key = Input::S;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == (GLFW_PRESS))
    {
        key = Input::D;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == (GLFW_PRESS))
    {
        key = Input::SPACE;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == (GLFW_PRESS))
    {
        key = Input::SHIFT;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == (GLFW_PRESS))
    {
        key = Input::CTRL;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == (GLFW_PRESS))
    {
        key = Input::LEFT_KEY;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == (GLFW_PRESS))
    {
        key = Input::RIGHT_KEY;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == (GLFW_PRESS))
    {
        key = Input::UP_KEY;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == (GLFW_PRESS))
    {
        key = Input::DOWN_KEY;
    }
    if (glfwGetKey(window, GLFW_KEY_T) == (GLFW_PRESS))
    {
        key = Input::T;
    }
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
    {
        key = Input::U;
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
    {
        key = Input::I;
    }
    renderer.processInput(key);
}

void Game::composeFrame()
{
    std::vector<glm::vec3> positions =
    {
        glm::vec3(1.0f, 1.0f, -1.0f),
        glm::vec3(2.0f, 2.0f, 4.0f),
        glm::vec3(0.0f, 5.0f, -12.0f),
        glm::vec3(0.0f, 2.0f, -4.0f),
        glm::vec3(-3.0f, -3.0f, -3.0f),
        glm::vec3(-5.0f, 4.0f, -8.0f)
    };
    
    // Floor Code
    for (int i = 0; i < 10; i++)
    {
        // Columns
        for (int k = 0; k < 15; k++)
        {
            positions.push_back(glm::vec3(-5.0f + (float)k, -2.0f, 1.0f - (float)i));
        }
    }
    // Wall
    for (int w = 0; w < 30; w++)
    {
        for (int x = 0; x < 20; x++)
        {
            positions.push_back(glm::vec3(-7.0f + (float)x, -2.0f + (float)w, -9.0f));
        }
    }

    glEnable(GL_DEPTH_TEST);
    float vertices[1] = { 0.0f };
    renderer.initCube(756, positions);
   
    // Compose the renderer shit
    renderer.compose();

}