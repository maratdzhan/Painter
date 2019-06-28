#pragma once
#include <direct.h>

TCHAR current_library_path[80] = "/lib/";
// const double tvs_size = 234.6; //tutnov
const double tvs_size = 236; // Nominal

double ReturnCoordinatesTvs(short tvs, bool x)
{
	//static HINSTANCE hLibrary_163;
	HMODULE hLibrary_163;

	// ѕри загрузке мен€етс€ текуща€ директори€ и библиотека грузитс€ оттуда, где ее нет.


	_chdir(current_library_path);

	hLibrary_163 = LoadLibrary(_T("Coordinates_Definition"));
	double(*pFunction) (double, int, bool);

	if (hLibrary_163)
	{
		(FARPROC&)pFunction = GetProcAddress(hLibrary_163, "cdefine");
		if (pFunction == NULL)
			cout << "NOT FIND cdefine at Coordinates_definition at ''ReturnCoordinates function\n";
		else
		{
			if (x)
				return pFunction(tvs_size, tvs, x);
			else
				return pFunction(tvs_size, tvs, false);
		}
	}
	else
	{
		cout << "ERROR OPENING LIBRARY => COORDINATES_DEFINITION.dll\n";
	}
	return 0;
}

double ReturnCoordinatesTvel(short tvel, bool x)
{
	//static HINSTANCE hLibrary_163;
	HMODULE hLibrary_331;

	// ѕри загрузке мен€етс€ текуща€ директори€ и библиотека грузитс€ оттуда, где ее нет.


	_chdir(current_library_path);

	hLibrary_331 = LoadLibrary(_T("FR_Coords"));
	double(*pFunctionFR) (bool, int);

	if (hLibrary_331)
	{
		(FARPROC&)pFunctionFR = GetProcAddress(hLibrary_331, "RetFrCoord");
		if (pFunctionFR == NULL)
			cout << "NOT FIND cdefine at Coordinates_definition at ''ReturnCoordinates function\n";
		else
		{
			if (x)
				return pFunctionFR(true, tvel);
			else
				return pFunctionFR(false, tvel);
		}
	}
	else
	{
		cout << "ERROR OPENING LIBRARY => COORDINATES_DEFINITION.dll\n";
	}
	return 0;
}

