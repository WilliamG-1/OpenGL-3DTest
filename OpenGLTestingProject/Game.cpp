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

    renderer.processInput(key);
}

void Game::composeFrame()
{
    glEnable(GL_DEPTH_TEST);
    float vertices[1] = { 0.0f };
    renderer.initCube(1, vertices, vertices);

    // Compose the renderer shit
    renderer.compose();

}