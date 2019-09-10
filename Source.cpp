#include<windows.h>
#include<stdio.h>
#define MYTIMER 200
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCndShow)
{

	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndClass;
	TCHAR szAppName[] = TEXT("MyApp");
	fopen_s(&log, TEXT("MYLOG.txt"), "W");
	FILE *log;

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wndClass);

	hwnd = CreateWindow(szAppName, "My Application", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCndShow);
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
	static RECT rc;
	static RECT tempRc;
	PAINTSTRUCT ps;
	static int iPaintFlag = 0;
	static int rcFlag = 0;
	static HBRUSH hBrush;

	

	switch (iMsg)
	{

	case WM_CREATE:
		SetTimer(hwnd, MYTIMER, 2000, NULL);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_TIMER:
		KillTimer(hwnd, MYTIMER);
		iPaintFlag++;
		if (iPaintFlag > 8)
			iPaintFlag = 0;
		InvalidateRect(hwnd, NULL, TRUE);
		SetTimer(hwnd, MYTIMER, 2000, NULL);
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);

		tempRc.top = rc.top;
		tempRc.bottom = rc.bottom;
		if (iPaintFlag == 0) {
			tempRc.left = rc.left;
			tempRc.right = rc.right / 9;
		}
		if (iPaintFlag > 0) {
			tempRc.left = tempRc.left + rc.right / 9;
			tempRc.right = tempRc.right + rc.right / 9;
		}

		switch (iPaintFlag)
		{

		case 8:

			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &tempRc, hBrush);
			tempRc.left = tempRc.left - rc.right / 9;
			tempRc.right = tempRc.right - rc.right / 9;
			++rcFlag;
		

		case 7:

			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &tempRc, hBrush);
			tempRc.left = tempRc.left - rc.right / 9;
			tempRc.right = tempRc.right - rc.right / 9;
			++rcFlag;

		case 6:

			hBrush = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &tempRc, hBrush);
			tempRc.left = tempRc.left - rc.right / 9;
			tempRc.right = tempRc.right - rc.right / 9;
			++rcFlag;

		case 5:

			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &tempRc, hBrush);
			tempRc.left = tempRc.left - rc.right / 9;
			tempRc.right = tempRc.right - rc.right / 9;
			++rcFlag;

		case 4:

			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &tempRc, hBrush);
			tempRc.left = tempRc.left - rc.right / 9;
			tempRc.right = tempRc.right - rc.right / 9;
			++rcFlag;

		case 3:

			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &tempRc, hBrush);
			tempRc.left = tempRc.left - rc.right / 9;
			tempRc.right = tempRc.right - rc.right / 9;
			++rcFlag;

		case 2:

			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &tempRc, hBrush);
			tempRc.left = tempRc.left - rc.right / 9;
			tempRc.right = tempRc.right - rc.right / 9;
			++rcFlag;

		case 1:

			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &tempRc, hBrush);
			tempRc.left = tempRc.left - rc.right / 9;
			tempRc.right = tempRc.right - rc.right / 9;
			++rcFlag;

		case 0:

			hBrush = CreateSolidBrush(RGB(255, 165, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &tempRc, hBrush);
			tempRc.left = tempRc.left + rcFlag*(rc.right / 9);
			tempRc.right = tempRc.right + rcFlag*(rc.right / 9);
			rcFlag=0;

			break;

		}

		EndPaint(hwnd, &ps);
		break;


	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}