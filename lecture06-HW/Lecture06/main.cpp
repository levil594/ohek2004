//과제물
// 1. 이클래스 숙지하고 프로젝트를 생성하시오
// 2. #include <vector>    대신에 #include "MSList.h" 를 만드시오. (MSList.h, MSList.cpp)
//    ( Musoen(무소은엔진용) Struct(자료구조) List(리스트) )
//    ( vector는 절대 쓰지 마시오)
// 3. MSList 헤더파일 참조해서 cpp 만들것.
// 4. cpp파일에 함수 구현 내용을 작성하시오. ( ObjectTest처럼 )
// 
// 5. 게임에 5주차 과제였던 별을 손톱크기로 조그맣게 그릴 수 있도록 star.hpp의 크리스탈 수정.
// 6. 랜덤하게 화면에 위치와 색을 바꿔가며 별 300 개를 그릴 수 있도록 작성하시오.
//    (List에 모든 Star객체들을 담아주세요)
//    (화면에 알록달록한 별이 가득하게 random 이라는 stl을 사용해서 만들어주세요.)



#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
//#include <vector>

#include "MSList.h"
#include "Star.hpp"

const int numRectangles = 300;
const int rectWidth = 20;
const int rectHeight = 20;

float moveFactor = 0.0f;
float scaleFactor = 1.0f;

void errorCallback(int error, const char* description)
{
	std::cerr << "\033[1;31mGLFW Error: " << description << "\033[0m" << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		moveFactor += 0.01f;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		scaleFactor += 0.1f;
	}
}
void DrawRandomRectangles(HWND hwnd, HDC hdc) {
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);

	for (int i = 0; i < numRectangles; ++i) {
		int randX = rand() % (clientRect.right - rectWidth);
		int randY = rand() % (clientRect.bottom - rectHeight);
		int randColor = RGB(rand() % 256, rand() % 256, rand() % 256);

		HBRUSH hBrush = CreateSolidBrush(randColor);
		SelectObject(hdc, hBrush);

		Rectangle(hdc, randX, randY, randX + rectWidth, randY + rectHeight);

		DeleteObject(hBrush);
	}
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		DrawRandomRectangles(hwnd, hdc);

		EndPaint(hwnd, &ps);
	}
	return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

std::vector<MObject*> list;

int initialize()
{
	
	MObject* temp[4];
	temp[0] = new Star();
	temp[1] = new Star();
	temp[2] = new Star();
	temp[3] = new Star();

	list.push_back(temp[0]);
	list.push_back(temp[1]);
	list.push_back(temp[2]);
	list.push_back(temp[3]);
		
	return 0;
}
int release() 
{	
	return 0;
}

int update()
{	
	return 0;
}

int render()
{
	glClearColor(0.1f, 0.2f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i=0;i<4;i++)
	{
		MObject* a = list[i];
		a->render();
	}

	

	return 0;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	srand(static_cast<unsigned int>(time(nullptr)));

	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Random Rectangles",           // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (hwnd == NULL) {
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

int main(void)
{
	//glfw라이브러리 초기화
	if (!glfwInit())
		return -1;

	GLFWwindow* window;
	window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetErrorCallback(errorCallback);
	glfwSetKeyCallback(window, keyCallback);

	initialize();
	WINAPI WinMain();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		update();
		render();
		glfwSwapBuffers(window);
	}

	release();

	glfwTerminate();
	return 0;

}