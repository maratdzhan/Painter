#pragma once



std::string SCore::GraphParameters(std::string parameter_name)
{
	if (!parameters[parameter_name].empty())
		return parameters[parameter_name];
	else
		std::cout << "PARAMETER ''" << parameter_name << "'' NOT LOADED << ReturnParameters \n";
	return "-72";
}

void SCore::TextOutCoord()
{
	// Полный размер области с текстом
	int count = strings_quantity;
	int step = (int)((1 + (1 / scale)) * (stoi(parameters["TEXT_SIZE"])));
	int full_size = (count - 1) * (step);
	// Верхняя позиция
	int st_pos = -1 * (step / 3 + full_size - (full_size / 2)+30);
	text_coords.push_back(st_pos);
	// Начиная со второго элемента - прибавляем
	for (short i = 1; i < count; i++)
	{
		text_coords.push_back((text_coords[i - 1] + 2*step));
	}
}

void SCore::Load()
{
	std::ifstream inputFile(parameters_file);
	std::string str;
	short tempSumma = 0;
	short stringsCount = 0;

	if (!inputFile.is_open())
		log.Console(1, "Cant open parameters file for full core\n");
	else
	{
		while (!inputFile.eof())
		{
			getline(inputFile, str);
			if (!str.empty())
			{
				parameters[GetParamS(str, 1)] = GetParamS(str, 2);
			}
		}
	}
	cerr << "Configuration loaded\n";
	inputFile.close();
}

COLORREF SCore::ColorReference(short number)
{
	COLORREF cellColor;

	double min_value = 0;
	double max_value = 0;

	min_value = TVS.tvs_min;
	max_value = TVS.tvs_max;
	double current_value = (TVS.isDifference ? TVS.dev[number] : TVS.main[number]);

	double range = max_value - min_value;
//	double step_size = range / (colors_quantity - 1);

	short group_number = -1;

	unsigned short stColorVal = 120;
	unsigned short endColorVal = 255;

//	short zero_group = 0;

	// Вычисление группы, к которой принадлежит текущий элемент

	group_number = (int)((current_value - TVS.tvs_min) * colors_quantity / (TVS.tvs_max - TVS.tvs_min));

	// Старый алгоритм вычисления. Сейчас он используется в KK_value::SetZeroGroup()
	//// Вычисление нулевой группы
	//if ((min_value * max_value < 0))
	//{
	//	for (short i = 1; i < colors_quantity + 1; i++)
	//	{
	//		if (0 < (min_value + (i * step_size)))
	//		{
	//			zero_group = i - 1;
	//			break;
	//		}
	//	}
	//}
	//else
	//{
	//	for (short i = 1; i < colors_quantity + 1; i++)
	//	{
	//		if (1 < (min_value + (i * step_size)))
	//		{
	//			if (i > 1) {
	//				zero_group = i - 1;
	//				break;
	//			}
	//			else
	//			{
	//				zero_group = colors_quantity / 2;
	//			}
	//		}
	//	}
	//}

	unsigned short gr = 0;
	unsigned short bl = 0;
	unsigned short rd = 0;

	int inner_pt = 0;
	short rd_step_1 = 0, gr_step_1 = 0, bl_step_1 = 0, gr_step_2 = 0;

	if (group_number < TVS.zero_group)
	{
		rd = 0;
		gr = 135;
		bl = 255;
		rd_step_1 = (250 / (TVS.zero_group - 1));
		gr_step_1 = (120 / (TVS.zero_group - 1));
		inner_pt = 1;
		rd += (rd_step_1 * group_number);
		gr += (gr_step_1 * group_number);
	}
	else
	{
		rd = 255;
		gr = 255;
		bl = 255;
		if (group_number < (colors_quantity+ TVS.zero_group) / 2)
		{
			bl -= (255 / (colors_quantity - TVS.zero_group)) * (group_number - TVS.zero_group);
		}
		else
		{
			bl = 130 - (130 / (colors_quantity - TVS.zero_group - 1)) * (group_number - TVS.zero_group + 1);
			gr = 255 - (255 / (colors_quantity - TVS.zero_group - 1)) * (group_number - TVS.zero_group + 1);
		}
	}

	//// BLUE - VALID
	//bl = (group_number <= TVS.zero_group ? 255 : 255 * (1 - ((double)group_number / colors_quantity)));

	//// GREEN - VALID
	//gr = (group_number <= TVS.zero_group ? (120 + (135. * ((double)group_number / TVS.zero_group))) : (255 - 205. * ((double)group_number - TVS.zero_group) / (colors_quantity - TVS.zero_group)));
	//
	//// RED - VALID
	//rd = (group_number > TVS.zero_group ? 255 : 255 * ((double)group_number / TVS.zero_group));

	cellColor = RGB(rd, gr, bl);
	return cellColor;
}

void SCore::GetKq(int tParam, int isMain)
{
	try {
		ifstream ifs;
		if (!isMain)
			ifs.open("main.txt");
		else
			ifs.open("secondary.txt");

		if (ifs.is_open())
		{
			string svalue;
			while (!ifs.eof())
			{
				getline(ifs, svalue);
				if (!svalue.empty())
				{
					switch (tParam)
					{
					case 0:
						TVS.main.push_back(stod(svalue));
						break;
					case 1:
						TVS.secondary.push_back(stod(svalue));
						break;
					case 2:
						TVS.main_s.push_back((svalue));
						break;
					case 3:
						TVS.secondary_s.push_back((svalue));
						break;
					}
				}
			}
		}
		else
			printf("file was not open\n");
	}
	catch (exception & y)
	{
		cerr << y.what() << endl;
	}

}

void SCore::GetPointData()
{
	try 
	{
		TVS.Clear();


		system("cls");

		string _key;
		int loadVal = 0;
		printf("Is load numerical data?\n (1 - yes, 2 - no, this is string-data\n");
		while (1)
		{

			cin >> _key;
			if (_key == "1") {
				loadVal =0;
				break;
			}
			if (_key == "2") {
				loadVal = 2;
				break;
			}
			cerr << "unknown command\n";
		}

		GetKq(loadVal + 0, 0);
		GetKq(loadVal +  1,1);
		
		printf("Color by difference(1) or set on main value(2)?\n");
		while (1) 
		{
			cin >> _key;
			if (_key == "1") {
				TVS.isDifference = 1;
				break;
			}
			if (_key == "2") {
				TVS.isDifference = 0;
				break;
			}
			cerr << "unknown command\n";
		}


		if (loadVal != 0) {
			TVS.HashingStringsValues(TVS.main, TVS.main_s);
			TVS.HashingStringsValues(TVS.secondary, TVS.secondary_s);
		}

		if (!TVS.main.size()) {
			system("cls");
			log.Error("! ! !no selected data types in files. break.\n", __FUNCTION__);
			printf("! ! !no selected data types in files. break.\n");
			return;
		}


		SelectAssemblies();

		if (TVS.isDifference)
			TVS.CalculateDev();
		TVS.Sort();
		TVS.SetZeroGroup(colors_quantity);
		TVS.isNumericalData = loadVal - 2;
		TVS.isLoaded = true;

	}
	catch (exception & gkq)
	{
		log.Error(gkq.what(), __FUNCTION__);
	}
}

void SCore::DefineMode()
{
	if (fa_count == 163)
		mode = 0;
	if (fa_count == 28)
		mode = 1;
	if (fa_count == 55)
		mode = 2;
}

void SCore::SetCoordinates(int fa_quantity)
{
	coordinates.clear();
	coordinates = ReturnCoordinatesTvs(fa_quantity, mode);
}

double SCore::GetCoordinates(int fa, bool isX)
{
	double _c = 0;
	if (isX)
		_c = coordinates[fa].first;
	else
		_c = coordinates[fa].second;

	return _c * grid_pitch * scale;

}

