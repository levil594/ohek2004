#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>

float moveFactor = 0.0f;
float scaleFactor = 1.0f;
float triangleX = 0.0f;
float triangleY = 0.0f;
float triangleSize = 0.1f;

void errorCallback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << std::endl;
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
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	static double lastX = xpos;
	static double lastY = ypos;

	// 왼쪽 버튼 클릭 시
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		double deltaX = xpos - lastX;
		double deltaY = ypos - lastY;
		triangleX += deltaX;
		triangleY -= deltaY; // Y축 방향이 반대이므로 빼줍니다.
	}
	// 오른쪽 버튼 클릭 시
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		double deltaX = xpos - lastX;
		double deltaY = ypos - lastY;
		float scaleFactor = 0.001f;

		if (deltaX > 0)
			triangleSize += scaleFactor;
		else if (deltaX < 0)
			triangleSize -= scaleFactor;
	}

	lastX = xpos;
	lastY = ypos;
}


int render()
{
	// 삼각형 1
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(1.0f * scaleFactor, (0.3f + moveFactor) * scaleFactor);
	
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-1.0f * scaleFactor, (0.3f + moveFactor) * scaleFactor);
	
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0f * scaleFactor, (-0.4f + moveFactor) * scaleFactor);
	glEnd();
	// 삼각형 2
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0f * scaleFactor, (-1.1f + moveFactor) * scaleFactor);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.6f * scaleFactor, (0.9f + moveFactor) * scaleFactor);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.4f * scaleFactor, (-0.1f + moveFactor) * scaleFactor);
	glEnd();
	// 삼각형 3
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.4f * scaleFactor, (-0.1f + moveFactor) * scaleFactor);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0f * scaleFactor, (-0.4f + moveFactor) * scaleFactor);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.5f * scaleFactor, (0.9f + moveFactor) * scaleFactor);
	glEnd();

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

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		render();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;

}