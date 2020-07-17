#pragma once
#include <direct.h>

TCHAR current_library_path[80] = "/lib/";
//const double tvs_size = 236; // Nominal

std::vector<std::pair<double, double>> ReturnCoordinatesTvs(short quantity, int mode, bool dbg)
{
	//static HINSTANCE hLibrary_163;
	HMODULE hLibrary_163;

	// ѕри загрузке мен€етс€ текуща€ директори€ и библиотека грузитс€ оттуда, где ее нет.


	//_chdir(current_library_path);

	hLibrary_163 = LoadLibrary(_T("Coordinates_Definition"));
	

	std::pair<double, double>(*pFunction) (double, int, int, bool);
	

	if (hLibrary_163 && quantity)
	{
		try {
			(FARPROC&)pFunction = GetProcAddress(hLibrary_163, "cdefine");

			if (pFunction == NULL)
			{	
				std::string msg = "NOT FIND cdefine at Coordinates_definition at ''ReturnCoordinates function\n";
				std::cerr << msg;
				system("pause");
				throw(1);
			}
			else
			{

				std::vector<std::pair<double, double>> value;
				for (int i = 0; i < quantity; i++)
				{
					std::pair<double, double> v = pFunction(tvs_size, i + 1, mode, dbg);
					value.push_back(v);
				}

				return value;
			}
		}
		catch (std::exception & e)
		{
			std::cerr << e.what();
			system("pause");
			throw(2);
		}
	}
	else
	{
		std::string err = "ERROR OPENING LIBRARY => COORDINATES_DEFINITION.dll\n";
		cout << err;
		system("pause");
		throw(3);

	}
	throw(4);
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

