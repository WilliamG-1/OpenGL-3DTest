#include "Game.h"
#include <iostream>
const int screenWidth = 720;
const int screenHeight = 660;
Game::Game()
    :
    window("My Game", screenWidth, screenHeight), testTriangle(.3f, .3f, -0.5f, -0.5f, 0), test2(0.5f, 0.3f, 0.0f, 0.0f, 0)
{
   
}

Game::~Game()
{

}

void Game::run()
{
    //glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    while (gameRunning)
    {
        processInput(window.getWindow());

        glClearColor(.25f, .35f, .45f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // Render stuff after clearing screen!
        testTriangle.draw();
        test2.draw();
        // Some Render Function Here
        glfwSwapBuffers(window.getWindow());
    }
    glfwTerminate();
}

void Game::processInput(GLFWwindow* window)
{
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == (GLFW_PRESS))
    {
        gameRunning = false;
    }
    
}