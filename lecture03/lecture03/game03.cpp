#include <iostream>
#include <Windows.h>

using namespace std;

void drawBrick(COLORREF brickColor, COLORREF fillColor) {
    HWND hwnd = GetConsoleWindow();
    HDC hdc = GetDC(hwnd);

    
    RECT brickRect = { 100, 100, 200, 150 }; 
    HBRUSH brickBrush = CreateSolidBrush(brickColor);
    FillRect(hdc, &brickRect, brickBrush);
    DeleteObject(brickBrush);

    RECT fillRect = { 105, 105, 195, 145 }; 
    HBRUSH fillBrush = CreateSolidBrush(fillColor);
    FillRect(hdc, &fillRect, fillBrush);
    DeleteObject(fillBrush);

    ReleaseDC(hwnd, hdc);
}

int main() {
    int input;
    cout << "화면에 그림을 그리는 프로그램입니다.\n학번 : 202327028\n이름 : 오은규\n\n화면에 그릴 물체코드를 입력하세요 : ";
    cin >> input;

    COLORREF brickColor, fillColor;
    switch (input) {
    case 30:
        brickColor = RGB(0, 0, 0); // Black
        fillColor = RGB(0, 0, 0); // Black
        break;
    case 31:
        brickColor = RGB(255, 0, 0); // Red
        fillColor = RGB(255, 0, 0); // Red
        break;
    case 32:
        brickColor = RGB(0, 255, 0); // Green
        fillColor = RGB(0, 255, 0); // Green
        break;
    case 33:
        brickColor = RGB(255, 255, 0); // Yellow
        fillColor = RGB(255, 255, 0); // Yellow
        break;
    case 34:
        brickColor = RGB(0, 0, 255); // Blue
        fillColor = RGB(0, 0, 255); // Blue
        break;
    case 35:
        brickColor = RGB(255, 0, 255); // Magenta
        fillColor = RGB(255, 0, 255); // Magenta
        break;
    case 36:
        brickColor = RGB(0, 255, 255); // Cyan
        fillColor = RGB(0, 255, 255); // Cyan
        break;
    case 37:
        brickColor = RGB(255, 255, 255); // White
        fillColor = RGB(255, 255, 255); // White
        break;
    default:
        cout << "Invalid input." << endl;
        return 1;
    }

    drawBrick(brickColor, fillColor);

    return 0;
}
