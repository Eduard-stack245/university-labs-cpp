#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <string>
#include <clocale>
#include <iostream>
#include <vector>
#include <tchar.h>
//#include <graphics.h>
using namespace std;

WCHAR szTitle[] = L"Conhoid";
WCHAR szWindowClass[] = L"ConhoidWndClass";

// window coordinates
const int WND_X = 300;
const int WND_Y = 100;
const int WND_W = 300;
const int WND_H = 300;

ATOM MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI Draw(HDC hdc);

DWORD WINAPI Run(LPVOID lpThreadParameter)
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    HWND hCon = GetConsoleWindow();
    RECT rc;
    MSG msg;

    MyRegisterClass(hInstance); // initialise the window class 
    GetWindowRect(hCon, &rc); // get the position of the console window     

    // create the window
    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_BORDER, rc.left + WND_X, rc.top + WND_Y, WND_W, WND_H, hCon,
        nullptr, hInstance, nullptr);

    //SetWindowLong(hWnd, GWL_STYLE, 0); // remove the title bar

    if (hWnd == nullptr)
    {
        printf("Error CreateWindow\n");
        return 0;
    }

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    // start the message loop
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

    return RegisterClassExW(&wcex);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    switch (message)
    {
    case WM_PAINT:

        PAINTSTRUCT ps;
        hdc = BeginPaint(hWnd, &ps);
        Draw(hdc);
        EndPaint(hWnd, &ps);

        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

WCHAR szTitle1[] = L"Win";
WCHAR szWindowClass1[] = L"WinWndClass";

// window coordinates
const int WND_X1 = 600;
const int WND_Y1 = 100;
const int WND_W1 = 300;
const int WND_H1 = 200;

ATOM MyRegisterClass1(HINSTANCE hInstance);
LRESULT CALLBACK WndProc1(HWND, UINT, WPARAM, LPARAM);

DWORD WINAPI Run1(LPVOID lpThreadParameter)
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    HWND hCon = GetConsoleWindow();
    RECT rc;
    MSG msg;

    MyRegisterClass1(hInstance); // initialise the window class 
    GetWindowRect(hCon, &rc); // get the position of the console window     

    // create the window
    HWND hWnd = CreateWindowW(szWindowClass1, szTitle1, WS_BORDER, rc.left + WND_X1, rc.top + WND_Y1, WND_W1, WND_H1, hCon,
        nullptr, hInstance, nullptr);

    //SetWindowLong(hWnd, GWL_STYLE, 0); // remove the title bar

    if (hWnd == nullptr)
    {
        printf("Error CreateWindow\n");
        return 0;
    }

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    // start the message loop
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

ATOM MyRegisterClass1(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc1;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass1;
    wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

    return RegisterClassExW(&wcex);
}

LRESULT CALLBACK WndProc1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //HDC hdc;
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    std::vector<LPCWSTR> cpaText;
    switch (message)
    {
    case WM_PAINT: {
        // TODO: Add any drawing code that uses hdc here...
        cpaText = { L"Hello World!",L"Your Boy Made His First Window!",L"YEAH" };
        int iY = 5;
        for (int iLoopCounter = 0; iLoopCounter < cpaText.size(); iLoopCounter++, iY += 20)
        {
            TextOut(hdc, 5, iY, cpaText[iLoopCounter], _tcslen(cpaText[iLoopCounter]));
        }
        EndPaint(hWnd, &ps);
    }
                 break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

float f(float x) {
    float e = 2.718;
    return pow(e, x) - pow(e, -x) - 2;//cos(x)*10;
}

struct point {
    float x = 0;
    float y = 0;
};

vector<point> Conhoid(void) {
    /*float h = M_PI / 180, x, y, a = 20, r = 40;
    float f = -3;
    while (f <= 3) {
        x = a + r * cos(f);
        y = a * sin(f) / cos(f) + r * sin(f);
        printf("x = %f     y = %f\n", x, y);
        f += h;
    }*/
    vector<point> result;
    int const n = 20;
    float a = 1, b = 10, x = a, y = 0;
    //float result[n][2];
    float h = (b - a) / n;
    printf("_______________________________\n");
    printf("|      X      |       Y       |\n");
    int i = 0;//1
    while (i <= n) {
        x = x + h;
        y = f(x);
        if (result.size() < 1) {
            result.push_back({ x,y });
            result.push_back({ x,y });
        }else {
            if (result[0].y > y) {
                result[0].x = x;
                result[0].y = y;
            }
            if (result[1].y < y) {
                result[1].x = x;
                result[1].y = y;
            }
        }
        if (y < 0) {
            printf("|%5.3f       |%5.3f      |\n", x, y);
            printf("_______________________________\n");
        }
        else {
            printf("|%5.3f       |%5.3f      |\n", x, y);
            printf("_______________________________\n");
        }
        i++;
    }
    return result;
}


DWORD WINAPI Draw(HDC hdc) {
    int gx = 50, vy = 50, upx = 10, upy = 1;
    /*float h = M_PI / 180, x, y, a = 20, r = 40;
    float f = -3;

    x = a + r * cos(f);
    y = a * sin(f) / cos(f) + r * sin(f);*/
    float x0, y0;
    int const n = 10000;
    float a = 1, b = 5, x = a, y = 0;
    float h = (b - a) / n;
    int i = 0;//1

    x0 = x;
    y0 = f(x);
    SelectObject(hdc, GetStockObject(WHITE_PEN));
    // horizontal line
    MoveToEx(hdc, 0, WND_H - vy, nullptr);
    LineTo(hdc, WND_W, WND_H - vy);
    // vertical line
    MoveToEx(hdc, gx, 0, nullptr);
    LineTo(hdc, gx, WND_H);
    // origin of the graph
    MoveToEx(hdc, gx + x, WND_H - vy - y, nullptr);
    while (i <= n) {
        x = x + h;
        y = f(x);
        if (abs(y - y0) < WND_H) {
            LineTo(hdc, gx + x * upx, WND_H - vy - y * upy);
        }
        else {
            MoveToEx(hdc, gx + x * upx, WND_H - vy - y * upy, nullptr);
        }

        x0 = x; y0 = y;
        i++;
    }

    return 0;
}

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    DWORD dwStream = 1;
    HANDLE hStream, drawStream;
    vector<point> min_max = Conhoid();
    drawStream = CreateThread(NULL, 0, Run, &dwStream, 0, &dwStream);
    hStream = CreateThread(NULL, 0, Run1, &dwStream, 0, &dwStream);
    cout << "Max: (" << min_max[1].x << ", " << min_max[1].y << ")" << endl;
    cout << "Min: (" << min_max[0].x << ", " << min_max[0].y << ")" << endl;
    _getch();
    return 0;
}