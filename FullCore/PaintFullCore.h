#pragma once

unsigned __stdcall MyThread(void * param)
{
	MSG msg;
	HGraph = CreateWindow(WinClassGraphName, _T("Core"),
		WS_SYSMENU | WS_POPUP | WS_VISIBLE | WS_THICKFRAME | WS_CAPTION,
		sys.GetInitPosX(), sys.GetInitPosY(), sys.GetImageSizeX(), sys.GetImageSizeY(), HGraph, 0, hInst, NULL);
	sys.hwnd = HGraph;
	UpdateWindow(HGraph);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 1;
}


LRESULT CALLBACK WndGraph(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	////////////// LOCAL VARIABLES

	int sx = sys.GetImageSizeX();
	int sy = sys.GetImageSizeY();
	double cell_size_local = sys.GetCellSize();
	double scale = sys.GetScale();
	LONG x_1 = 0 * cell_size_local * scale, x_2 = 6.4 * cell_size_local * scale, y_1 = 8.0 * cell_size_local * scale, y_2 = 4.0 * cell_size_local * scale;
	LONG x_3 = 0 * cell_size_local * scale, x_4 = 6.6 * cell_size_local * scale, y_3 = 8.2 * cell_size_local * scale, y_4 = 4.2 * cell_size_local * scale;
	short NUMBER_OF_FA = sys.GetFuelAssemblyQuantity();
	double x, y = 0;
	double grid_pitch = sys.GetGridPitch();
	short numberOfStrings = sys.GetStringsQuantity();
	bool colored = sys.GetColorVar();

	///// CONST VARIABLES
	POINT pt[6] = { { x_1,y_1 },{ x_2,y_2 },{ x_2,-y_2 },{ x_1,-y_1 },{ -x_2,-y_2 },{ -x_2,y_2 } };
	const POINT pt_BOUND[6] = { { x_3,y_3 },{ x_4,y_4 },{ x_4,-y_4},{ x_3,-y_3 },{ -x_4,-y_4 },{ -x_4,y_4 } };

	PAINTSTRUCT ps;
	HDC hdc;
	static HBRUSH hBrush;
	static HBRUSH hColoredbrush;
	static HBRUSH hBoundBrush_FA = CreateSolidBrush(RGB(100, 100, 100));
	static HBRUSH hBoundBrush_FR = CreateSolidBrush(RGB(220, 220, 220));


	switch (message)
	{
	case WM_CREATE:

		break;
	case WM_SIZE:
		sys.SetImageSizeX(sx = LOWORD(lParam));
		sys.SetImageSizeY(sy = HIWORD(lParam));
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		sys.hdc = hdc;
		sys.paintstruct = ps;
		sys.hwnd = hWnd;
		SetMapMode(hdc, MM_ANISOTROPIC);

		SetViewportOrgEx(hdc, sx / 2, sy / 2, NULL);
		
		SetWindowExtEx(hdc, sx, sy, NULL);
		SetViewportExtEx(hdc, sx, sy, NULL);

		for (short i = 0; i < NUMBER_OF_FA; i++)
		{

			x = sys.GetCoordinates(i, true);
			y = sys.GetCoordinates(i, false);
			SetViewportOrgEx(hdc, int(sx / 2 + x), (int)(sy / 2 - y), NULL);


			// BOUND
			BeginPath(hdc);
			Polyline(hdc, pt_BOUND, 6);
			CloseFigure(hdc);
			EndPath(hdc);
			SelectObject(hdc, hBoundBrush_FA);
			SetPolyFillMode(hdc, WINDING);
			FillPath(hdc);

			BeginPath(hdc);
			Polyline(hdc, pt, 6);
			CloseFigure(hdc);
			EndPath(hdc);

			SetPolyFillMode(hdc, WINDING);


			if (colored)
			{
				hBrush = CreateSolidBrush(sys.ColorReference(i));
				SelectObject(hdc, hBrush);
			}
			else
			{
				hBrush = CreateSolidBrush(RGB(255, 255, 255));
				SelectObject(hdc, hBrush);
			}
			FillPath(hdc);
			DeleteObject(hBrush);

			if (numberOfStrings > 0)
			{
				sys.PrintText(i);
			}

		}
	
		EndPaint(hWnd, &ps);
		break;
	case WM_QUIT:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	default:
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}
}
	


void SCore::Paint()
{
	hdc = NULL;
	hwnd = NULL;
	if (IsLoaded() && !IsCoreActive())
	{
		if (TVS.main.size() >= fa_count && TVS.secondary.size() >= fa_count) {
			DefineMode();
			SetCoordinates(fa_count);
			GraphThread = (HANDLE)_beginthreadex(NULL, 0, MyThread, NULL, 0, NULL);
			SetCoreActive(true);
		}
		else
		{
			printf(">>>wrong geometry. Check fa quantity\n>>>current: %i && %i, but needs %i\n\n",
				TVS.main.size(), TVS.secondary.size(), fa_count);
		}
	}
	else
	{
		log.Console(0, "Core could not be builded -> input data has not been loaded");
		cerr << "First load data (key = 'get')\n";
	}
}

void SCore::Close()
{
	if (IsCoreActive()) {
		SetCoreActive(false);

		PostMessage(HGraph, WM_QUIT, 0, 0);
		WaitForSingleObject(GraphThread, INFINITE);
		//	DestroyWindow(HGraph);
			cerr << GetLastError() << endl;

		//	TerminateThread(GraphThread, 1);
		HGraph = NULL;
	}
}

void SCore::PrintText(int number)
{
	SetTextColor(hdc, 0);
	SetBkMode(hdc, TRANSPARENT);
	HFONT nf = CreateFont(GetTextSize(), 0, 0, 0, GetTextThikness(), 0, GetTextUnderline(), GetTextStrikeout(),
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial"));
	SelectObject(hdc, nf);

	stringsPosition.push_back(to_string(number + 1));

	if (TVS.isNumericalData) {
		stringsPosition.push_back(to_string(TVS.main[number]));
		stringsPosition.push_back(to_string(TVS.secondary[number]));	
	}
	else
	{
		stringsPosition.push_back((TVS.main_s[number]));
		stringsPosition.push_back((TVS.secondary_s[number]));
	}

	if (TVS.isDifference && TVS.isNumericalData)
		stringsPosition.push_back(to_string(TVS.dev[number]));
	else
		stringsPosition.push_back("VMN");


	for (int i = 0; i < strings_quantity; i++)
	{
		stringsPosition[i].resize(GetTextLenght());
		TextOut(hdc, 
			GetTextInitX()-GetTextSize()+2*GetTextSize()/10*(stringsPosition[i].size()-2)/10,
			0+i* GetTextYInterval()+GetTextInitY(), 
			stringsPosition[i].data(), stringsPosition[i].size());
	}

	stringsPosition.clear();
	DeleteObject((HFONT)nf);
}