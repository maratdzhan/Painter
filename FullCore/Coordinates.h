#pragma once
#include <direct.h>

TCHAR current_library_path[80] = "/lib/";
//const double tvs_size = 236; // Nominal

std::vector<std::pair<double, double>> ReturnCoordinatesTvs(short quantity, int mode)
{
	//static HINSTANCE hLibrary_163;
	HMODULE hLibrary_163;

	// ѕри загрузке мен€етс€ текуща€ директори€ и библиотека грузитс€ оттуда, где ее нет.


	_chdir(current_library_path);

	hLibrary_163 = LoadLibrary(_T("Coordinates_Definition"));
	std::pair<double, double>(*pFunction) (double, int, int, bool);
	//step,quantity,mode, debug_mode

	if (hLibrary_163)
	{
		(FARPROC&)pFunction = GetProcAddress(hLibrary_163, "cdefine");
		if (pFunction == NULL)
			cout << "NOT FIND cdefine at Coordinates_definition at ''ReturnCoordinates function\n";
		else
		{
			std::vector<std::pair<double, double>> value;
			for (int i = 0; i < quantity; i++)
			{
				std::pair<double, double> v = pFunction(tvs_size, i, mode, true);
				value.push_back(v);
			}
				
			return value;
		}
	}
	else
	{
		cout << "ERROR OPENING LIBRARY => COORDINATES_DEFINITION.dll\n";
	}
	return { {0,0} };
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

