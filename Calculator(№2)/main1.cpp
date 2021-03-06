#include "header.h" 

LONG WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS w;

	memset(&w, 0, sizeof(WNDCLASS));

	w.style = CS_HREDRAW | CS_VREDRAW;
	w.lpfnWndProc = WndProc;
	w.hInstance = hInstance;
	w.cbClsExtra = 0;
	w.cbWndExtra = 0;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	w.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	w.hCursor = LoadCursor(NULL, IDC_ARROW);
	w.lpszClassName = "My Class";

	RegisterClass(&w);

	hwnd = CreateWindow("My Class", "Calculator", WS_OVERLAPPED | WS_BORDER | WS_SYSMENU, 400, 250, 550, 350, NULL, NULL, hInstance, NULL);

	CreateWindow("button", "7", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 100, 55, 40, hwnd, (HMENU)7, hInstance, NULL);
	CreateWindow("button", "8", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 75, 100, 55, 40, hwnd, (HMENU)8, hInstance, NULL);
	CreateWindow("button", "9", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 140, 100, 55, 40, hwnd, (HMENU)9, hInstance, NULL);
	CreateWindow("button", "4", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 150, 55, 40, hwnd, (HMENU)4, hInstance, NULL);
	CreateWindow("button", "5", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 75, 150, 55, 40, hwnd, (HMENU)5, hInstance, NULL);
	CreateWindow("button", "6", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 140, 150, 55, 40, hwnd, (HMENU)6, hInstance, NULL);
	CreateWindow("button", "1", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 200, 55, 40, hwnd, (HMENU)1, hInstance, NULL);
	CreateWindow("button", "2", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 75, 200, 55, 40, hwnd, (HMENU)2, hInstance, NULL);
	CreateWindow("button", "3", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 140, 200, 55, 40, hwnd, (HMENU)3, hInstance, NULL);
	CreateWindow("button", "0", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 250, 55, 40, hwnd, (HMENU)10, hInstance, NULL);

	CreateWindow("button", "/", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 205, 100, 55, 40, hwnd, (HMENU)11, hInstance, NULL);
	CreateWindow("button", "*", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 205, 150, 55, 40, hwnd, (HMENU)12, hInstance, NULL);
	CreateWindow("button", "-", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 205, 200, 55, 40, hwnd, (HMENU)13, hInstance, NULL);
	CreateWindow("button", "+", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 205, 250, 55, 40, hwnd, (HMENU)14, hInstance, NULL);
	CreateWindow("button", "<=", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 400, 100, 55, 40, hwnd, (HMENU)15, hInstance, NULL);
	CreateWindow("button", "=", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 465, 250, 55, 40, hwnd, (HMENU)16, hInstance, NULL);
	CreateWindow("button", ".", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 75, 250, 55, 40, hwnd, (HMENU)17, hInstance, NULL);
	CreateWindow("button", "^", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 140, 250, 55, 40, hwnd, (HMENU)20, hInstance, NULL);
	CreateWindow("button", "C", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 465, 100, 55, 40, hwnd, (HMENU)21, hInstance, NULL);
	CreateWindow("button", "~", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 270, 100, 55, 40, hwnd, (HMENU)22, hInstance, NULL);
	CreateWindow("button", "&&", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 270, 150, 55, 40, hwnd, (HMENU)23, hInstance, NULL);
	CreateWindow("button", "|", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 270, 200, 55, 40, hwnd, (HMENU)24, hInstance, NULL);
	CreateWindow("button", "XOR", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 270, 250, 55, 40, hwnd, (HMENU)25, hInstance, NULL);
	CreateWindow("button", "<<", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 335, 100, 55, 40, hwnd, (HMENU)26, hInstance, NULL);
	CreateWindow("button", ">>", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 335, 150, 55, 40, hwnd, (HMENU)27, hInstance, NULL);
	CreateWindow("button", "!", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 335, 200, 55, 40, hwnd, (HMENU)28, hInstance, NULL);
	CreateWindow("button", "?(sqrt)", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 335, 250, 55, 40, hwnd, (HMENU)29, hInstance, NULL);
	CreateWindow("button", "BIN", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 400, 150, 55, 40, hwnd, (HMENU)30, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LONG WINAPI WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam)
{
	char oversize[] = "Error! Oversize: too much operations/numbers";
	static std::string WindowCalc;
	HDC hdc;
	PAINTSTRUCT ps;

	switch (Message)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);

		HFONT hfont = CreateFont(25, 10, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "myFont");
		SelectObject(hdc, hfont);
		TextOut(hdc, 5, 30, WindowCalc.c_str(), WindowCalc.size());
		DeleteObject(hfont);

		MoveToEx(hdc, 0, 22, NULL);
		LineTo(hdc, 550, 22);
		MoveToEx(hdc, 0, 58, NULL);
		LineTo(hdc, 550, 58);

		EndPaint(hwnd, &ps);
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wparam))
		{
		case ONE:
		{
			if (WindowCalc.size() + 1 > MAX_SIZE)
			{
				MessageBox(hwnd, oversize, "exception", Message);
				break;
			}

			if (WindowCalc.size())
				if (WindowCalc[WindowCalc.size() - 1] != '!' && WindowCalc[WindowCalc.size() - 1] != 'b')
					WindowCalc += "1";

			if (!WindowCalc.size())
				WindowCalc += "1";

			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case TWO:
		{
			if (WindowCalc.size() + 1 > MAX_SIZE)
			{
				MessageBox(hwnd, oversize, "exception", Message);
				break;
			}

			if (WindowCalc.size())
				if (WindowCalc[WindowCalc.size() - 1] != '!' && WindowCalc[WindowCalc.size() - 1] != 'b')
					WindowCalc += "2";

			if (!WindowCalc.size())
				WindowCalc += "2";
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case THREE:
		{
			if (WindowCalc.size() + 1 > MAX_SIZE)
			{
				MessageBox(hwnd, oversize, "exception", Message);
				break;
			}

			if (WindowCalc.size())
				if (WindowCalc[WindowCalc.size() - 1] != '!' && WindowCalc[WindowCalc.size() - 1] != 'b')
					WindowCalc += "3";

			if (!WindowCalc.size())
				WindowCalc += "3";
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case FOUR:
		{
			if (WindowCalc.size() + 1 > MAX_SIZE)
			{
				MessageBox(hwnd, oversize, "exception", Message);
				break;
			}

			if (WindowCalc.size())
				if (WindowCalc[WindowCalc.size() - 1] != '!' && WindowCalc[WindowCalc.size() - 1] != 'b')
					WindowCalc += "4";

			if (!WindowCalc.size())
				WindowCalc += "4";
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case FIVE:
		{
			if (WindowCalc.size() + 1 > MAX_SIZE)
			{
				MessageBox(hwnd, oversize, "exception", Message);
				break;
			}
			if (WindowCalc.size())
				if (WindowCalc[WindowCalc.size() - 1] != '!' && WindowCalc[WindowCalc.size() - 1] != 'b')
					WindowCalc += "5";

			if (!WindowCalc.size())
				WindowCalc += "5";
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case SIX:
		{
			if (WindowCalc.size() + 1 > MAX_SIZE)
			{
				MessageBox(hwnd, oversize, "exception", Message);
				break;
			}

			if (WindowCalc.size())
				if (WindowCalc[WindowCalc.size() - 1] != '!' && WindowCalc[WindowCalc.size() - 1] != 'b')
					WindowCalc += "6";

			if (!WindowCalc.size())
				WindowCalc += "6";
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case SEVEN:
		{
			if (WindowCalc.size() + 1 > MAX_SIZE)
			{
				MessageBox(hwnd, oversize, "exception", Message);
				break;
			}

			if (WindowCalc.size())
				if (WindowCalc[WindowCalc.size() - 1] != '!' && WindowCalc[WindowCalc.size() - 1] != 'b')
					WindowCalc += "7";

			if (!WindowCalc.size())
				WindowCalc += "7";
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case EIGHT:
		{
			if (WindowCalc.size() + 1 > MAX_SIZE)
			{
				MessageBox(hwnd, oversize, "exception", Message);
				break;
			}

			if (WindowCalc.size())
				if (WindowCalc[WindowCalc.size() - 1] != '!' && WindowCalc[WindowCalc.size() - 1] != 'b')
					WindowCalc += "8";

			if (!WindowCalc.size())
				WindowCalc += "8";
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case NINE:
		{
			if (WindowCalc.size() + 1 > MAX_SIZE)
			{
				MessageBox(hwnd, oversize, "exception", Message);
				break;
			}

			if (WindowCalc.size())
				if (WindowCalc[WindowCalc.size() - 1] != '!' && WindowCalc[WindowCalc.size() - 1] != 'b')
					WindowCalc += "9";

			if (!WindowCalc.size())
				WindowCalc += "9";
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case ZERO:
		{
			if (WindowCalc.size() + 1 > MAX_SIZE)
			{
				MessageBox(hwnd, oversize, "exception", Message);
				break;
			}

			if (WindowCalc.size())
				if (WindowCalc[WindowCalc.size() - 1] != '!' && WindowCalc[WindowCalc.size() - 1] != 'b')
					WindowCalc += "0";

			if (!WindowCalc.size())
				WindowCalc += "0";
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case DIV:
		{
			if (WindowCalc.size() + 1 > MAX_SIZE)
			{
				MessageBox(hwnd, oversize, "exception", Message);
				break;
			}

			if (WindowCalc.size())
				if (WindowCalc[WindowCalc.size() - 1] != '+' && WindowCalc[WindowCalc.size() - 1] != '-' && WindowCalc[WindowCalc.size() - 1] != '*'
					&& WindowCalc[WindowCalc.size() - 1] != '/' && WindowCalc[WindowCalc.size() - 1] != '.' && WindowCalc[WindowCalc.size() - 1] != '^'
					&& WindowCalc[WindowCalc.size() - 1] != '&' && WindowCalc[WindowCalc.size() - 1] != '|' && WindowCalc[WindowCalc.size() - 1] != '<'
					&& WindowCalc[WindowCalc.size() - 1] != '>' && WindowCalc[WindowCalc.size() - 1] != '~' && WindowCalc[WindowCalc.size() - 1] != 'X'
					&& WindowCalc[WindowCalc.size() - 1] != '!' && WindowCalc[WindowCalc.size() - 1] != '?' && WindowCalc[WindowCalc.size() - 1] != 'b')
					WindowCalc += "/";
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case MUL:
		{
			if (WindowCalc.size() + 1 > MAX_SIZE)
			{
				MessageBox(hwnd, oversize, "exception", Message);
				break;
			}

			if (WindowCalc.size())
				if (WindowCalc[WindowCalc.size() - 1] != '+' && WindowCalc[WindowCalc.size() - 1] != '-' && WindowCalc[WindowCalc.size() - 1] != '*'
					&& WindowCalc[WindowCalc.size() - 1] != '/' && WindowCalc[WindowCalc.size() - 1] != '.' && WindowCalc[WindowCalc.size() - 1] != '^'
					&& WindowCalc[WindowCalc.size() - 1] != '&' && WindowCalc[WindowCalc.size() - 1] != '|' && WindowCalc[WindowCalc.size() - 1] != '<'
					&& WindowCalc[WindowCalc.size() - 1] != '>' && WindowCalc[WindowCalc.size() - 1] != '~' && WindowCalc[WindowCalc.size() - 1] != 'X'
					&& WindowCalc[WindowCalc.size() - 1] != '!' && WindowCalc[WindowCalc.size() - 1] != '?' && WindowCalc[WindowCalc.size() - 1] != 'b')
					WindowCalc += "*";
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case MINUS:
		{
			if (WindowCalc.size() + 1 > MAX_SIZE)
			{
				MessageBox(hwnd, oversize, "exception", Message);
				break;
			}

			if (WindowCalc.size())
				if (WindowCalc[WindowCalc.size() - 1] != '+' && WindowCalc[WindowCalc.size() - 1] != '-' && WindowCalc[WindowCalc.size() - 1] != '*'
					&& WindowCalc[WindowCalc.size() - 1] != '/' && WindowCalc[WindowCalc.size() - 1] != '.' && WindowCalc[WindowCalc.size() - 1] != '^'
					&& WindowCalc[WindowCalc.size() - 1] != '&' && WindowCalc[WindowCalc.size() - 1] != '|' && WindowCalc[WindowCalc.size() - 1] != '<'
					&& WindowCalc[WindowCalc.size() - 1] != '>' && WindowCalc[WindowCalc.size() - 1] != '~' && WindowCalc[WindowCalc.size() - 1] != 'X'
					&& WindowCalc[WindowCalc.size() - 1] != '!' && WindowCalc[WindowCalc.size() - 1] != '?' && WindowCalc[WindowCalc.size() - 1] != 'b')
					WindowCalc += "-";
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case PLUS:
		{
			if (WindowCalc.size() + 1 > MAX_SIZE)
			{
				MessageBox(hwnd, oversize, "exception", Message);
				break;
			}

			if (WindowCalc.size())
				if (WindowCalc[WindowCalc.size() - 1] != '+' && WindowCalc[WindowCalc.size() - 1] != '-' && WindowCalc[WindowCalc.size() - 1] != '*'
					&& WindowCalc[WindowCalc.size() - 1] != '/' && WindowCalc[WindowCalc.size() - 1] != '.' && WindowCalc[WindowCalc.size() - 1] != '^'
					&& WindowCalc[WindowCalc.size() - 1] != '&' && WindowCalc[WindowCalc.size() - 1] != '|' && WindowCalc[WindowCalc.size() - 1] != '<'
					&& WindowCalc[WindowCalc.size() - 1] != '>' && WindowCalc[WindowCalc.size() - 1] != '~' && WindowCalc[WindowCalc.size() - 1] != 'X'
					&& WindowCalc[WindowCalc.size() - 1] != '!' && WindowCalc[WindowCalc.size() - 1] != '?' && WindowCalc[WindowCalc.size() - 1] != 'b')
					WindowCalc += "+";
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case DELETE:
		{
			if (WindowCalc.size())
				WindowCalc.pop_back();
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case EQUALLY:
		{
			if (WindowCalc.size() != 0)
			{
				std::stringstream ss;
				double result;

				try
				{
					result = calc(WindowCalc.c_str());
				}
				catch (std::exception const& ex)
				{
					MessageBeep(0);
					MessageBox(hwnd, ex.what(), "Error", 0);
					break;
				}

				WindowCalc.clear();
				ss << result;
				ss >> WindowCalc;
			}

			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case POINT:
		{
			if (WindowCalc.size() + 1 > MAX_SIZE)
			{
				MessageBox(hwnd, oversize, "exception", Message);
				break;
			}

			if (WindowCalc.size())
				if (WindowCalc[WindowCalc.size() - 1] != '+' && WindowCalc[WindowCalc.size() - 1] != '-' && WindowCalc[WindowCalc.size() - 1] != '*'
					&& WindowCalc[WindowCalc.size() - 1] != '/' && WindowCalc[WindowCalc.size() - 1] != '.' && WindowCalc[WindowCalc.size() - 1] != '^'
					&& WindowCalc[WindowCalc.size() - 1] != '&' && WindowCalc[WindowCalc.size() - 1] != '|' && WindowCalc[WindowCalc.size() - 1] != '<'
					&& WindowCalc[WindowCalc.size() - 1] != '>' && WindowCalc[WindowCalc.size() - 1] != '~' && WindowCalc[WindowCalc.size() - 1] != 'X'
					&& WindowCalc[WindowCalc.size() - 1] != '!' && WindowCalc[WindowCalc.size() - 1] != '?' && WindowCalc[WindowCalc.size() - 1] != 'b')
					WindowCalc += ".";
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}

		case DEG:
		{
			if (WindowCalc.size() + 1 > MAX_SIZE)
			{
				MessageBox(hwnd, oversize, "exception", Message);
				break;
			}

			if (WindowCalc.size())
				if (WindowCalc[WindowCalc.size() - 1] != '+' && WindowCalc[WindowCalc.size() - 1] != '-' && WindowCalc[WindowCalc.size() - 1] != '*'
					&& WindowCalc[WindowCalc.size() - 1] != '/' && WindowCalc[WindowCalc.size() - 1] != '.' && WindowCalc[WindowCalc.size() - 1] != '^'
					&& WindowCalc[WindowCalc.size() - 1] != '&' && WindowCalc[WindowCalc.size() - 1] != '|' && WindowCalc[WindowCalc.size() - 1] != '<'
					&& WindowCalc[WindowCalc.size() - 1] != '>' && WindowCalc[WindowCalc.size() - 1] != '~' && WindowCalc[WindowCalc.size() - 1] != 'X'
					&& WindowCalc[WindowCalc.size() - 1] != '!' && WindowCalc[WindowCalc.size() - 1] != '?' && WindowCalc[WindowCalc.size() - 1] != 'b')
					WindowCalc += "^";
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case DELETE_ALL:
		{
			WindowCalc.clear();
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case DENIAL:
		{
			if (WindowCalc.size() + 1 > MAX_SIZE)
			{
				MessageBox(hwnd, oversize, "exception", Message);
				break;
			}

			if (WindowCalc.size() == 0)
				WindowCalc += "~";
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case AND:
		{
			if (WindowCalc.size() + 1 > MAX_SIZE)
			{
				MessageBox(hwnd, oversize, "exception", Message);
				break;
			}

			if (WindowCalc.size())
				if (WindowCalc[WindowCalc.size() - 1] != '+' && WindowCalc[WindowCalc.size() - 1] != '-' && WindowCalc[WindowCalc.size() - 1] != '*'
					&& WindowCalc[WindowCalc.size() - 1] != '/' && WindowCalc[WindowCalc.size() - 1] != '.' && WindowCalc[WindowCalc.size() - 1] != '^'
					&& WindowCalc[WindowCalc.size() - 1] != '&' && WindowCalc[WindowCalc.size() - 1] != '|' && WindowCalc[WindowCalc.size() - 1] != '<'
					&& WindowCalc[WindowCalc.size() - 1] != '>' && WindowCalc[WindowCalc.size() - 1] != '~' && WindowCalc[WindowCalc.size() - 1] != 'X'
					&& WindowCalc[WindowCalc.size() - 1] != '!' && WindowCalc[WindowCalc.size() - 1] != '?' && WindowCalc[WindowCalc.size() - 1] != 'b')
					WindowCalc += "&";
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case OR:
		{
			if (WindowCalc.size() + 1 > MAX_SIZE)
			{
				MessageBox(hwnd, oversize, "exception", Message);
				break;
			}

			if (WindowCalc.size())
				if (WindowCalc[WindowCalc.size() - 1] != '+' && WindowCalc[WindowCalc.size() - 1] != '-' && WindowCalc[WindowCalc.size() - 1] != '*'
					&& WindowCalc[WindowCalc.size() - 1] != '/' && WindowCalc[WindowCalc.size() - 1] != '.' && WindowCalc[WindowCalc.size() - 1] != '^'
					&& WindowCalc[WindowCalc.size() - 1] != '&' && WindowCalc[WindowCalc.size() - 1] != '|' && WindowCalc[WindowCalc.size() - 1] != '<'
					&& WindowCalc[WindowCalc.size() - 1] != '>' && WindowCalc[WindowCalc.size() - 1] != '~' && WindowCalc[WindowCalc.size() - 1] != 'X'
					&& WindowCalc[WindowCalc.size() - 1] != '!' && WindowCalc[WindowCalc.size() - 1] != '?' && WindowCalc[WindowCalc.size() - 1] != 'b')
					WindowCalc += "|";
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case XOR:
		{
			if (WindowCalc.size() + 1 > MAX_SIZE)
			{
				MessageBox(hwnd, oversize, "exception", Message);
				break;
			}

			if (WindowCalc.size())
				if (WindowCalc[WindowCalc.size() - 1] != '+' && WindowCalc[WindowCalc.size() - 1] != '-' && WindowCalc[WindowCalc.size() - 1] != '*'
					&& WindowCalc[WindowCalc.size() - 1] != '/' && WindowCalc[WindowCalc.size() - 1] != '.' && WindowCalc[WindowCalc.size() - 1] != '^'
					&& WindowCalc[WindowCalc.size() - 1] != '&' && WindowCalc[WindowCalc.size() - 1] != '|' && WindowCalc[WindowCalc.size() - 1] != '<'
					&& WindowCalc[WindowCalc.size() - 1] != '>' && WindowCalc[WindowCalc.size() - 1] != '~' && WindowCalc[WindowCalc.size() - 1] != 'X'
					&& WindowCalc[WindowCalc.size() - 1] != '!' && WindowCalc[WindowCalc.size() - 1] != '?' && WindowCalc[WindowCalc.size() - 1] != 'b')
					WindowCalc += "X";
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case LEFT:
		{
			if (WindowCalc.size() + 1 > MAX_SIZE)
			{
				MessageBox(hwnd, oversize, "exception", Message);
				break;
			}

			if (WindowCalc.size())
				if (WindowCalc[WindowCalc.size() - 1] != '+' && WindowCalc[WindowCalc.size() - 1] != '-' && WindowCalc[WindowCalc.size() - 1] != '*'
					&& WindowCalc[WindowCalc.size() - 1] != '/' && WindowCalc[WindowCalc.size() - 1] != '.' && WindowCalc[WindowCalc.size() - 1] != '^'
					&& WindowCalc[WindowCalc.size() - 1] != '&' && WindowCalc[WindowCalc.size() - 1] != '|' && WindowCalc[WindowCalc.size() - 1] != '<'
					&& WindowCalc[WindowCalc.size() - 1] != '>' && WindowCalc[WindowCalc.size() - 1] != '~' && WindowCalc[WindowCalc.size() - 1] != 'X'
					&& WindowCalc[WindowCalc.size() - 1] != '!' && WindowCalc[WindowCalc.size() - 1] != '?' && WindowCalc[WindowCalc.size() - 1] != 'b')
					WindowCalc += "<";
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case RIGHT:
		{
			if (WindowCalc.size() + 1 > MAX_SIZE)
			{
				MessageBox(hwnd, oversize, "exception", Message);
				break;
			}

			if (WindowCalc.size())
				if (WindowCalc[WindowCalc.size() - 1] != '+' && WindowCalc[WindowCalc.size() - 1] != '-' && WindowCalc[WindowCalc.size() - 1] != '*'
					&& WindowCalc[WindowCalc.size() - 1] != '/' && WindowCalc[WindowCalc.size() - 1] != '.' && WindowCalc[WindowCalc.size() - 1] != '^'
					&& WindowCalc[WindowCalc.size() - 1] != '&' && WindowCalc[WindowCalc.size() - 1] != '|' && WindowCalc[WindowCalc.size() - 1] != '<'
					&& WindowCalc[WindowCalc.size() - 1] != '>' && WindowCalc[WindowCalc.size() - 1] != '~' && WindowCalc[WindowCalc.size() - 1] != 'X'
					&& WindowCalc[WindowCalc.size() - 1] != '!' && WindowCalc[WindowCalc.size() - 1] != '?' && WindowCalc[WindowCalc.size() - 1] != 'b')
					WindowCalc += ">";
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case FACTORIAL:
		{
			if (WindowCalc.size() + 1 > MAX_SIZE)
			{
				MessageBox(hwnd, oversize, "exception", Message);
				break;
			}

			if (WindowCalc.size())
				if (WindowCalc[WindowCalc.size() - 1] != '+' && WindowCalc[WindowCalc.size() - 1] != '-' && WindowCalc[WindowCalc.size() - 1] != '*'
					&& WindowCalc[WindowCalc.size() - 1] != '/' && WindowCalc[WindowCalc.size() - 1] != '.' && WindowCalc[WindowCalc.size() - 1] != '^'
					&& WindowCalc[WindowCalc.size() - 1] != '&' && WindowCalc[WindowCalc.size() - 1] != '|' && WindowCalc[WindowCalc.size() - 1] != '<'
					&& WindowCalc[WindowCalc.size() - 1] != '>' && WindowCalc[WindowCalc.size() - 1] != '~' && WindowCalc[WindowCalc.size() - 1] != 'X'
					&& WindowCalc[WindowCalc.size() - 1] != '!' && WindowCalc[WindowCalc.size() - 1] != '?' && WindowCalc[WindowCalc.size() - 1] != 'b')
					WindowCalc += "!";
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case SQRT:
		{
			if (WindowCalc.size() + 1 > MAX_SIZE)
			{
				MessageBox(hwnd, oversize, "exception", Message);
				break;
			}
			if (WindowCalc.size() == 0)
				WindowCalc += "?";
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case BIN:
		{
			if (WindowCalc.size() + 1 > MAX_SIZE)
			{
				MessageBox(hwnd, oversize, "exception", Message);
				break;
			}
			if (WindowCalc.size())
				if (WindowCalc[WindowCalc.size() - 1] != '+' && WindowCalc[WindowCalc.size() - 1] != '-' && WindowCalc[WindowCalc.size() - 1] != '*'
					&& WindowCalc[WindowCalc.size() - 1] != '/' && WindowCalc[WindowCalc.size() - 1] != '.' && WindowCalc[WindowCalc.size() - 1] != '^'
					&& WindowCalc[WindowCalc.size() - 1] != '&' && WindowCalc[WindowCalc.size() - 1] != '|' && WindowCalc[WindowCalc.size() - 1] != '<'
					&& WindowCalc[WindowCalc.size() - 1] != '>' && WindowCalc[WindowCalc.size() - 1] != '~' && WindowCalc[WindowCalc.size() - 1] != 'X'
					&& WindowCalc[WindowCalc.size() - 1] != '!' && WindowCalc[WindowCalc.size() - 1] != '?' && WindowCalc[WindowCalc.size() - 1] != 'b')
					WindowCalc += "b";
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		default:
		{
			break;
		}
		}
	}
	default:
	{
		return DefWindowProc(hwnd, Message, wparam, lparam);
	}
	}

	return 0;
}