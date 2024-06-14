#pragma comment(lib, "Opengl32.lib")

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <cmath>

void errorCallback(int error, const char* description)
{
    printf("GLFW Error: %s", description);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}

int Physics()
{
    return 0;
}

int Initialize()
{
    return 0;
}

int Update()
{
    return 0;
}

void RenderSquare(float x, float y, float size)
{
    // Draw filled square (red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + size, y);
    glVertex2f(x + size, y + size);
    glVertex2f(x, y + size);
    glEnd();

    // Draw border (black)
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + size, y);
    glVertex2f(x + size, y + size);
    glVertex2f(x, y + size);
    glEnd();
}

void RenderGround(float yPosition, float height)
{
    // Draw ground (R:255, G:200, B:15)
    glColor3f(1.0f, 0.7843f, 0.0588f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, yPosition);
    glVertex2f(1.0f, yPosition);
    glVertex2f(1.0f, yPosition + height);
    glVertex2f(-1.0f, yPosition + height);
    glEnd();
}

void RenderObstacle(float x, float y, float width, float height)
{
    // Draw obstacle (R:0, G:255, B:0)
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

int Render()
{
    int width, height;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);

    // Set up the viewport
    glViewport(0, 0, width, height);

    // Clear the screen
    glClearColor(0.0f, 0.1176f, 0.3922f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Calculate normalized coordinates for the square
    float size = 50.0f;
    float normalizedSizeX = size / (width / 2.0f);
    float normalizedSizeY = size / (height / 2.0f);

    float playerX = -normalizedSizeX / 2.0f; // Centered at (0, 0)
    float playerY = -1.0f + (100.0f / height * 2.0f) + normalizedSizeY; // Above the ground

    // Render the player
    RenderSquare(playerX, playerY, normalizedSizeX);

    // Calculate ground position and size
    float groundHeight = 100.0f / height * 2.0f; // Convert 100px to normalized device coordinates
    float groundYPosition = -1.0f; // Place ground at bottom

    // Render the ground
    RenderGround(groundYPosition, groundHeight);

    // Calculate obstacle positions and sizes
    float obstacleWidth = 50.0f / (width / 2.0f);
    float obstacleHeight1 = 100.0f / (height / 2.0f);
    float obstacleHeight2 = 300.0f / (height / 2.0f);

    float obstacleX1 = playerX + normalizedSizeX * 2; // Some position for first obstacle
    float obstacleY1 = groundYPosition + groundHeight; // Just above the ground

    float obstacleX2 = playerX + normalizedSizeX * 4; // Some position for second obstacle
    float obstacleY2 = groundYPosition + groundHeight; // Just above the ground

    float obstacleX3 = playerX + normalizedSizeX * 6; // Some position for third obstacle
    float obstacleY3 = groundYPosition + groundHeight; // Just above the ground

    float obstacleX4 = playerX + normalizedSizeX * 8; // Some position for fourth obstacle
    float obstacleY4 = groundYPosition + groundHeight; // Just above the ground

    // Render the obstacles
    RenderObstacle(obstacleX1, obstacleY1, obstacleWidth, obstacleHeight1);
    RenderObstacle(obstacleX2, obstacleY2, obstacleWidth, obstacleHeight2);
    RenderObstacle(obstacleX3, obstacleY3, obstacleWidth, obstacleHeight1);
    RenderObstacle(obstacleX4, obstacleY4, obstacleWidth, obstacleHeight2);

    return 0;
}

int main(void)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // Initialize the GLFW library
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(800, 800, "Google Dino Run Copy Game", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    Initialize();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        Physics();
        Update();
        Render();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
