#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "Sample Window Class";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    //wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,                              
        CLASS_NAME,                     
        "Draw Shapes",                  
        WS_OVERLAPPEDWINDOW,            

        
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       
        NULL,       
        hInstance,  
        NULL        
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

void DrawShapes(HDC hdc) {
    
    COLORREF color1 = RGB(255, 217, 102); // #FFD966
    COLORREF color2 = RGB(255, 230, 153); // #FFE699
    COLORREF color3 = RGB(255, 192, 0);   // #FFC000
    COLORREF color4 = RGB(0, 0, 255);     // Blue

   
    HBRUSH hBrush1 = CreateSolidBrush(color1);
    HBRUSH hBrush2 = CreateSolidBrush(color2);
    HBRUSH hBrush3 = CreateSolidBrush(color3);
    HBRUSH hBrush4 = CreateSolidBrush(color4);

    
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); 
    SelectObject(hdc, hPen);

    
    SelectObject(hdc, hBrush1);
    Ellipse(hdc, 50, 50, 150, 150);

    
    SelectObject(hdc, hBrush2);
    Ellipse(hdc, 100, 100, 125, 125);

    
    SelectObject(hdc, hBrush3);
    Ellipse(hdc, 75, 75, 100, 100);

    
    SelectObject(hdc, hBrush4);
    Rectangle(hdc, 175, 50, 225, 100);

    
    DeleteObject(hBrush1);
    DeleteObject(hBrush2);
    DeleteObject(hBrush3);
    DeleteObject(hBrush4);
    DeleteObject(hPen);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        DrawShapes(hdc);
        EndPaint(hwnd, &ps);
    }
    return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
