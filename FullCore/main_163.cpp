
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <tchar.h>


LRESULT CALLBACK WndGraph(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInst;
TCHAR WinClassGraphName[] = _T("CC");
HWND HGraph;
HANDLE GraphThread;

#include "163CommonHeader.h"
SCore sys;
#include "PaintFullCore.h"

ATOM RegisterGraphClass()
{
	WNDCLASSEX wcgraph = { 0 };
	wcgraph.hInstance = hInst;
	wcgraph.lpszClassName = WinClassGraphName;
	wcgraph.lpfnWndProc = WndGraph;
	wcgraph.style = CS_HREDRAW | CS_VREDRAW;
	wcgraph.hCursor = LoadCursor(NULL, IDC_CROSS);
	wcgraph.lpszMenuName = NULL;
	wcgraph.cbClsExtra = 0;
	wcgraph.cbSize = sizeof(WNDCLASSEX);
	wcgraph.hInstance = hInst;
	wcgraph.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	return RegisterClassEx(&wcgraph);
}


int main()
{
	HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hwnd = GetConsoleWindow();
	HMENU hmenu = GetSystemMenu(hwnd, FALSE);
	EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED);

	RegisterGraphClass();

	int command = 1;
	while (true)
	{
		command = sys.GetCommand();
		system("cls");
		switch (command)
		{
		case 1:
			sys.Paint();
			break;
		case 2:
			sys.Edit("");
			break;
		case 3:
			sys.GetPointData();
			break;
		case 5:
			sys.Update();
			break;
		case 6:
			sys.Close();
			break;
		case 7:
			sys.Store();
			break;
		case 8:
			sys.Save("backup");
			sys.Load();
			sys.Initialize();
			break;
		case 10:
			sys.Save("");
			return 0;
		case 9:
			sys.Save("");
			break;
		case -1:
			break;
		default:
			cerr << ">>> Unknown command\n";
			break;
		}
	}
	return 0;
}

