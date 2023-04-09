#include <windows.h>
#include <TCHAR.H>
#include <string>

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
	WndClass.lpszClassName = _T("20193148 황진주");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("20193148 황진주"),
		_T("20193148 황진주"),
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

void readShapePos(TCHAR input[], int& type, int pos[]);
std::wstring setOutputText(int type, int pos[]);

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static std::wstring output;
	static RECT viewSize;
	static TCHAR input[100] = { 0 };
	static int index = 0;
	static SIZE size;
	static int shapePos[4] = { 0 };
	static int shapeType = 0;

	switch (iMsg)
	{
	case WM_CREATE:
		CreateCaret(hwnd, NULL, 1, 15);		// 캐럿생성
		ShowCaret(hwnd);
		break;
	case WM_CHAR:
		hdc = GetDC(hwnd);
		// 백스페이스
		if (wParam == VK_BACK) {
			// 지우기가 가능한가
			if (index > 0) {
				index--;
				input[index] = NULL;
			}
		}
		// 엔터
		else if (wParam == VK_RETURN) {
			readShapePos(input, shapeType, shapePos);
			for (int i = 0; input[i] != NULL; i++) { input[i] = NULL; }
			index = 0;
			output = setOutputText(shapeType, shapePos);
		}
		// 그 외 입력
		else {
			// 입력가능 여부 확인
			if (index < 100) {
				input[index++] = wParam;
			}
		}
		InvalidateRgn(hwnd, NULL, TRUE);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		if (shapeType == 1) {
			MoveToEx(hdc, shapePos[0], shapePos[1], NULL);
			LineTo(hdc, shapePos[2], shapePos[3]);
		}
		if (shapeType == 2) {
			Ellipse(hdc, shapePos[0], shapePos[1], shapePos[2], shapePos[3]);
		}
		if (shapeType == 3) {
			Rectangle(hdc, shapePos[0], shapePos[1], shapePos[2], shapePos[3]);
		}

		GetClientRect(hwnd, &viewSize);													// 화면크기 구함
		GetTextExtentPoint(hdc, input, _tcslen(input), &size);							// 캐럿위치 구함
		Rectangle(hdc, viewSize.right / 2 - 150, 400, viewSize.right / 2 + 150, 425);	// 글상자
		TextOut(hdc, viewSize.right / 2 - 145, 405, input, _tcslen(input));				// 입력글자 출력
		SetCaretPos(viewSize.right / 2 - 145 + size.cx, 405);							// 캐럿위치 변경

		TextOutW(hdc, viewSize.right / 2 - 150, 435, output.c_str(), output.length());
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

void readShapePos(TCHAR input[], int& type, int pos[]) {
	TCHAR sPos[100] = { 0 };
	TCHAR sType[10] = { 0 };
	int idx = 0;
	bool meet = false;
	for (int i = 0; i <= _tcslen(input); i++) {
		if (input[i] == L'(') {
			meet = true;
		}
		if (meet) {
			sPos[idx++] = input[i];
		}
		else {
			sType[i] = input[i];
		}
	}

	for (int i = 0; i < 4; i++) { pos[i] = 0; }

	// 좌표지정
	_stscanf_s(sPos, _T("(%d, %d, %d, %d)"), &pos[0], &pos[1], &pos[2], &pos[3]);

	// 모양 타입 지정
	if (!_tcscmp(sType, _T("Line"))) { type = 1; }
	else if (!_tcscmp(sType, _T("Ellipse"))) { type = 2; }
	else if (!_tcscmp(sType, _T("Rectangle"))) { type = 3; }
	else { type = 0; }
}

std::wstring setOutputText(int type, int pos[]) {
	std::wstring text;
	bool vlaue = true;

	if (type == 1) { text += L"Draw a Line at "; }
	else if (type == 2) { text += L"Draw a Ellipse at "; }
	else if (type == 3) { text += L"Draw a Rectangle at "; }
	else if (type == 0) { text += L"Please enter the correct command"; return text; }

	text += L"(";
	for (int i = 0; i < 4; i++) {
		text += std::to_wstring(pos[i]);
		if (i < 3) { text += L", "; }
	}
	text += L")";
	return text;
}