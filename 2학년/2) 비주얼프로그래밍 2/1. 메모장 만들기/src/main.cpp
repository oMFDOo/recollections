#include <windows.h>
#include <TCHAR.H>

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
	WndClass.lpszClassName = _T("Window Class Name");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),
		_T("20193148 비주얼 4주차 과제"),
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
	static TCHAR input[10][11] = { 0 };
	static int index = 0;
	static int idxY = 0;
	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CHAR:
		hdc = GetDC(hwnd);
		// 백스페이스
		if (wParam == VK_BACK) {
			// 한 칸 지우기가 가능할 때
			if (index > 0) {
				index--;
				input[idxY][index] = NULL;
			}
			// 줄을 넘겨서 지워야 할 때
			else if (idxY > 0) {
				idxY--;
				index = _tcslen(input[idxY]);
				input[idxY][index] = NULL;
			}
		}
		// 엔터
		else if (wParam == VK_RETURN) {
			// 입력 공간 제한
			if (idxY < 9) {
				index = 0;
				idxY++;
			}
		}
		// 그 외 입력
		else {
			// 일반 입력
			if (index < 10) {
				input[idxY][index++] = wParam;
			}
			// 10자 넘김
			else {
				if (idxY < 9) {
					index = 0;
					idxY++;
					input[idxY][index++] = wParam;
				}
			}
		}

		InvalidateRgn(hwnd, NULL, TRUE);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		for (int i = 0; i <= idxY; i++) {
			TextOut(hdc, 0, i * 20, input[i], _tcslen(input[i]));
		}
		EndPaint(hwnd, &ps);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}