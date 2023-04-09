#include <windows.h>
#include <TCHAR.H>
#include <math.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND     hwnd;
	MSG		 msg;
	WNDCLASS WndClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("20193148 황진주 9주차 과제");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("20193148 황진주 9주차 과제"),
		_T("20193148 황진주 9주차 과제"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}




LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static POINT catPosition = { 100, 100 };
	static POINT downMousePoisiton = { -1, -1 };
	static bool keyDown = false;
	switch (iMsg)
	{
	case WM_CREATE:
		SetTimer(hwnd, 0, 50, NULL);
		break;
	case WM_LBUTTONDOWN:
		keyDown = true;
		break;
	case WM_MOUSEMOVE:
		if (keyDown) {
			downMousePoisiton.x = LOWORD(lParam);
			downMousePoisiton.y = HIWORD(lParam);
		}
		break;
	case WM_LBUTTONUP:
		keyDown = false;
		downMousePoisiton.x = -1;
		downMousePoisiton.y = -1;
		break;
	case WM_TIMER:
	{
		if (downMousePoisiton.x != -1 || downMousePoisiton.y != -1) {
			float dir[2] = { downMousePoisiton.x - catPosition.x, downMousePoisiton.y - catPosition.y };
			float norm[2] = { dir[0] / sqrt(dir[0] * dir[0] + dir[1] * dir[1]), dir[1] / sqrt(dir[0] * dir[0] + dir[1] * dir[1]) };
			LONG size = 50;
			float result[2] = { norm[0] * size , norm[1] * size };

			catPosition.x += result[0];
			catPosition.y += result[1];
		}
		InvalidateRgn(hwnd, NULL, TRUE);
	}
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, catPosition.x, catPosition.y, L"고양이", wcslen(L"고양이"));

		if (keyDown) {
			TextOut(hdc, downMousePoisiton.x, downMousePoisiton.y, L"쥐", wcslen(L"쥐"));
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
