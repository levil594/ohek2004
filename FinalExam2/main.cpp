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

bool physicsAABB(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
    return (x1 < x2 + w2 &&
        x1 + w1 > x2 &&
        y1 < y2 + h2 &&
        y1 + h1 > y2);
}

void errorCallback(int error, const char* description)
{
    printf("GLFW Error: %s\n", description);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

bool isJumping = false;
bool isGameOver = false;
bool isSpacePressed = false;
float playerVelocityY = 0.0f;
float gravity = -0.01f; // 중력 가속도 (1N)
float jumpVelocity = 0.05f; // 점프 초기 속도
float maxJumpVelocity = 0.5f; // 최대 점프 속도
float jumpAcceleration = 0.01f; // 점프 가속도
float maxJumpTime = 0.5f; // 최대 점프 시간 (초)
float jumpTime = 0.0f; // 점프가 시작된 후 경과 시간


struct Player
{
    float x, y, width, height;
} player;

struct Obstacle
{
    float x, y, width, height;
};

const int NUM_OBSTACLES = 3; // 최대 장애물 개수
Obstacle obstacles[NUM_OBSTACLES];
float obstacleSpeed = 0.01f; // 장애물 이동 속도

void InitializeObstacles(int width, int height)
{
    float groundHeight = 100.0f / height * 2.0f; // Convert 100px to normalized device coordinates
    float groundYPosition = -1.0f; // Place ground at bottom

    for (int i = 0; i < NUM_OBSTACLES; ++i)
    {
        obstacles[i].width = 50.0f / (width / 2.0f);
        obstacles[i].height = (i % 2 == 0 ? 100.0f : 300.0f) / (height / 2.0f);
        obstacles[i].x = 1.0f + i * 0.75f; // 장애물들을 화면 밖 오른쪽에 배치
        obstacles[i].y = groundYPosition + groundHeight;
    }
}

void UpdateObstacles()
{
    for (int i = 0; i < NUM_OBSTACLES; ++i)
    {
        obstacles[i].x -= obstacleSpeed; // 왼쪽으로 이동

        // 화면 밖으로 나간 경우 다시 오른쪽으로 이동
        if (obstacles[i].x < -1.0f - obstacles[i].width)
        {
            obstacles[i].x = 1.0f; // 오른쪽 끝으로 재배치
        }
    }
}

void Jump()
{
    if (!isJumping && !isGameOver)
    {
        isJumping = true;
        playerVelocityY = jumpVelocity; // 점프 초기 속도 설정
        jumpTime = 0.0f; // 점프 시간 초기화
    }
}

int Physics()
{
    if (isGameOver) return 0;

    // 스페이스 바가 눌려 있는 동안 점프 속도를 증가시킴
    if (isSpacePressed && isJumping && playerVelocityY < maxJumpVelocity)
    {
        playerVelocityY += 0.01f;
    }

    // 중력 적용
    playerVelocityY += gravity;
    player.y += playerVelocityY;

    // 지면에 닿으면 멈추기
    float groundHeight = 50.0f / 600.0f * 2.0f;
    if (player.y < -1.0f + groundHeight + player.height)
    {
        player.y = -1.0f + groundHeight + player.height;
        playerVelocityY = 0;
        isJumping = false;
    }

    // 플레이어와 장애물의 충돌 감지
    for (int i = 0; i < NUM_OBSTACLES; ++i)
    {
        if (physicsAABB(player.x, player.y, player.width, player.height, obstacles[i].x, obstacles[i].y, obstacles[i].width, obstacles[i].height))
        {
            isGameOver = true;
            break;
        }
    }

    // 장애물의 이동 멈춤 처리
    if (isGameOver)
    {
        obstacleSpeed = 0.0f; // 장애물 이동 속도를 0으로 설정하여 멈추게 만듦
    }

    return 0;
}

int Initialize()
{
    // 플레이어 초기 위치 및 크기 설정
    player.width = 50.0f / 400.0f; // 너비
    player.height = 50.0f / 300.0f; // 높이
    player.x = -player.width / 2.0f; // 초기 위치 (x)
    player.y = -1.0f + (100.0f / 600.0f * 2.0f) + player.height; // 초기 위치 (y)

    return 0;
}

void RenderRectangle(float x, float y, float width, float height)
{
    // 채워진 사각형을 빨간색으로 그리기
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // 테두리를 검은색으로 그리기
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
    // 지면을 R:255, G:200, B:15 색상으로 그리기
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
    // 장애물을 R:0, G:255, B:0 색상으로 그리기
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

    // 뷰포트 설정
    glViewport(0, 0, width, height);

    // 화면 지우기
    glClearColor(0.0f, 0.1176f, 0.3922f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 플레이어 렌더링
    RenderRectangle(player.x, player.y, player.width, player.height);

    // 지면 위치와 크기 계산
    float groundHeight = 100.0f / height * 2.0f;
    float groundYPosition = -1.0f;

    // 지면 렌더링
    RenderGround(groundYPosition, groundHeight);

    // 장애물 업데이트 및 렌더링
    UpdateObstacles();
    for (int i = 0; i < NUM_OBSTACLES; ++i)
    {
        RenderObstacle(obstacles[i].x, obstacles[i].y, obstacles[i].width, obstacles[i].height);
    }

    return 0;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && !isJumping && !isGameOver)
    {
        playerVelocityY = jumpVelocity; // 점프 초기 속도
        isJumping = true;
        isSpacePressed = true;
    }

    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
    {
        isSpacePressed = false;
    }
}

int main(void)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // GLFW 라이브러리 초기화
    if (!glfwInit())
        return -1;

    // 윈도우와 OpenGL 컨텍스트 생성
    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "Google Dino Run Copy Game", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // 윈도우의 컨텍스트를 현재 컨텍스트로 설정
    glfwMakeContextCurrent(window);

    // GLFW 에러 콜백 설정
    glfwSetErrorCallback(errorCallback);

    // GLFW 키 콜백 설정
    glfwSetKeyCallback(window, keyCallback);

    // 애플리케이션 초기화
    Initialize();

    // 장애물 초기화
    InitializeObstacles(800, 600);

    // 윈도우가 닫힐 때까지 루프
    while (!glfwWindowShouldClose(window))
    {
        // 이벤트 처리
        glfwPollEvents();

        // 물리 계산 수행
        Physics();

        // 게임 상태 업데이트
        // Update();

        // 프레임 렌더링
        Render(window);

        // 프론트 버퍼와 백 버퍼 교환
        glfwSwapBuffers(window);
    }

    // GLFW 리소스 정리
    glfwTerminate();

    return 0;
}
