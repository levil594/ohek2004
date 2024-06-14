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
// #include <Object.h>

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

void RenderRectangle(float x, float y, float width, float height)
{
    // Draw filled rectangle (red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // Draw border (black)
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
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

int Render(GLFWwindow* window)
{
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    // Set up the viewport
    glViewport(0, 0, width, height);

    // Clear the screen
    glClearColor(0.0f, 0.1176f, 0.3922f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Calculate normalized coordinates for the rectangle
    float rectWidth = 50.0f;
    float rectHeight = 50.0f; // Original height (50) + 150
    float normalizedWidth = rectWidth / (width / 2.0f);
    float normalizedHeight = rectHeight / (height / 2.0f);

    float playerX = -normalizedWidth / 2.0f; // Centered at (0, 0)
    float playerY = -1.0f + (100.0f / height * 2.0f) + normalizedHeight; // Above the ground

    // Render the player (rectangle)
    RenderRectangle(playerX, playerY, normalizedWidth, normalizedHeight);

    // Calculate ground position and size
    float groundHeight = 100.0f / height * 2.0f; // Convert 100px to normalized device coordinates
    float groundYPosition = -1.0f; // Place ground at bottom

    // Render the ground
    RenderGround(groundYPosition, groundHeight);

    // Calculate obstacle positions and sizes
    float obstacleWidth = 50.0f / (width / 2.0f);
    float obstacleHeight1 = 100.0f / (height / 2.0f);
    float obstacleHeight2 = 300.0f / (height / 2.0f);

    float obstacleX1 = playerX + normalizedWidth * 2; // Some position for first obstacle
    float obstacleY1 = groundYPosition + groundHeight; // Just above the ground

    float obstacleX2 = playerX + normalizedWidth * 4; // Some position for second obstacle
    float obstacleY2 = groundYPosition + groundHeight; // Just above the ground

    float obstacleX3 = playerX + normalizedWidth * 6; // Some position for third obstacle
    float obstacleY3 = groundYPosition + groundHeight; // Just above the ground

    float obstacleX4 = playerX + normalizedWidth * 8; // Some position for fourth obstacle
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

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "Google Dino Run Copy Game", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Set GLFW error callback
    glfwSetErrorCallback(errorCallback);

    // Set GLFW key callback
    glfwSetKeyCallback(window, keyCallback);

    // Initialize your application
    Initialize();

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Poll for and process events
        glfwPollEvents();

        // Perform physics calculations
        Physics();

        // Update game state
        // Update();

        // Render frame
        Render(window);

        // Swap front and back buffers
        glfwSwapBuffers(window);
    }

    // Clean up GLFW resources
    glfwTerminate();

    return 0;
}
