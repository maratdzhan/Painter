#pragma once

void SCore::NullInitialize()
{
	parameters["CELL_SIZE"] = "1";
	parameters["FA_QUANTITY"] = "163";
	parameters["IMAGE_SIZE_X"] = "700";
	parameters["IMAGE_SIZE_Y"] = "700";
	parameters["STRINGS_QUANTITY"] = "1";
	parameters["TEXT_LENGHT"] = "4";
	parameters["TEXT_Y_INTERVAL"] = "1";
	parameters["TEXT_SIZE"] = "15";
	parameters["SCALE"] = "2";
	parameters["COLOR_VAR"] = "1";
	parameters["COLORS_QUANTITY"] = "100";
	parameters["GRID_PITCH"] = "0.08";
	parameters["TEXT_THIKNESS"] = "1";
	parameters["TEXT_UNDERLINE"] = "0";
	parameters["TEXT_STRIKEOUT"] = "0";
	parameters["TEXT_INIT_X"] = "-10";
	parameters["TEXT_INIT_Y"] = "-5";
	parameters["POLARITY"] = "MAIN";
	parameters["DEBUG"] = "0";
	parameters["LEGEND_REQUIRED"] = "0";
	parameters["CART_SHIFT_X"] = "0";
	parameters["CART_SHIFT_Y"] = "0";
	parameters["LEGEND_HEIGHT"] = "20";
	parameters["LEGEND_SHIFT"] = "0";
	parameters["LEGEND_TEXT_SIZE"] = "10";
	parameters["LEGEND_TEXT_SHIFT_X"] = "0";
	parameters["LEGEND_TEXT_SHIFT_Y"] = "0";
}

void SCore::Initialize()
{
	int sp = parameters.size();
	int i = 0;
	double d = 0;
	bool b = false;
	try {
		i = stoi(parameters["CELL_SIZE"]);
		SetCellSize(i);

		i = stoi(parameters["FA_QUANTITY"]);
		SetFuelAssemblyQuantity(i);

		i = stoi(parameters["IMAGE_SIZE_X"]);
		SetImageSizeX(i);

		i = stoi(parameters["IMAGE_SIZE_Y"]);
		SetImageSizeY(i);

		i = stoi(parameters["STRINGS_QUANTITY"]);
		SetStringsQuantity(i);

		i = stoi(parameters["TEXT_LENGHT"]);
		SetTextLenght(static_cast<size_t>(i));

		i = stoi(parameters["TEXT_Y_INTERVAL"]);
		SetTextYInterval(i);

		i = stoi(parameters["TEXT_SIZE"]);
		SetTextSize(i);

		d = stod(parameters["SCALE"]);
		SetScale(d);

		i = stoi(parameters["COLOR_VAR"]);
		SetColorVar(static_cast<bool>(i));

		i = stoi(parameters["COLORS_QUANTITY"]);
		SetColorsQuantity(i);

		d = stod(parameters["GRID_PITCH"]);
		SetGridPitch(d);

		i = stoi(parameters["TEXT_THIKNESS"]);
		SetTextThikness(i);

		i = stoi(parameters["TEXT_UNDERLINE"]);
		SetTextUnderline(i);

		i = stoi(parameters["TEXT_STRIKEOUT"]);
		SetTextStrikeout(i);

		i = stoi(parameters["TEXT_INIT_X"]);
		SetTextInitX(i);

		i = stoi(parameters["TEXT_INIT_Y"]);
		SetTextInitY(i);

		i = stoi(parameters["DEBUG"]);
		SetDebug(i);

		b = stoi(parameters["LEGEND_REQUIRED"]);
		SetLegendRequired(b);

		i = stoi(parameters["CART_SHIFT_X"]);
		SetCartShiftX(i);

		i = stoi(parameters["CART_SHIFT_Y"]);
		SetCartShiftY(i);

		i = stoi(parameters["LEGEND_HEIGHT"]);
		SetLegendHeight(i);

		i = stoi(parameters["LEGEND_SHIFT"]);
		SetLegendShift(i);

		i = stoi(parameters["LEGEND_TEXT_SIZE"]);
		SetLegendTextSize(i);

		i = stoi(parameters["LEGEND_TEXT_SHIFT_X"]);
		SetLegendTextShiftX(i);

		i = stoi(parameters["LEGEND_TEXT_SHIFT_Y"]);
		SetLegendTextShiftY(i);

		SetPolarity(parameters["POLARITY"]);

		if (sp - parameters.size() != 0)
			log.Error("***something was added at input data", __FUNCTION__);
	}
	catch (exception & exc)
	{
		NullInitialize();
		cerr <<exc.what()<< " => error at loading\n";
		log.Error("loading parameters", __FUNCTION__);
		Initialize();
	}
}

void SCore::EditCommonInfo()
{

	cerr << "Enter command:\n";
	cerr << "SetCS (cell size)\n";
	cerr << "SetGP (grid pitch)\n";
	cerr << "SetFAQ (fuel assembly quantity)\n";
	cerr << "SetSizeX(Y) (image size x (y))\n";
	cerr << "SetSQ (strings quantity)\n";
	cerr << "SetTE (text lenght)\n";
	cerr << "SetTS (text size)\n";
	cerr << "SetTI (text Y axis interval)\n";
	cerr << "SetS (scale)\n";
	cerr << "SetCQ (color groups quantity)\n";
	cerr << "SetCV (color variable)\n";
	cerr << "SetTT (text thikness)\n";
	cerr << "SetTU (text underline)\n";
	cerr << "SetTS (text strikeout)\n";
	cerr << "SetTIX (text initial X pos)\n";
	cerr << "SetTIY (text initial Y pos)\n";
	// LEGEND
	cerr << "SetLegShift (legend shift (Y only))\n";
	cerr << "SetLegH (legend height)\n";
	cerr << "SetLTSize (legend text size)\n";
	cerr << "SetLTShiftX (legend text shift X)\n";
	cerr << "SetLTShiftY (legend text shift Y)\n";
	cerr << "ShowLegend (0 - no/ 1 - yes)\n";
	///
	cerr << "SetCSX (cart shift -> X)\n";
	cerr << "SetCSY (cart shift -> Y)\n";
	///
	cerr << "Polarity (values polarity)\n";
	cerr << "0 - Cancel\n";
	cerr << "\n";

}

void SCore::CommandsList()
{
	cerr << "Commands: \n";
	cerr << "edit - edit cartogram parameters\n";
	cerr << "print - print cartogram in window\n";
	cerr << "save - save parameters\n";
	cerr << "grab 'name' - load parameters from 'name' (<grab my.ini> - load my.ini)\n";
	cerr << "get - load data\n";
	cerr << "close - close core window\n";
	cerr << "store - save core in bmp-file\n";
	cerr << "update - update core image\n";
	cerr << "debug_info - get some variables information \n";
	cerr << "end - exit from program\n";
	cerr << "\n\n>>> ";

}

void SCore::Edit(string _v)
{
	string com;
	int r = 0;
	system("cls");
	while (1)
	{
		if (_v.empty()) {
			EditCommonInfo();
			cin >> _v;
			_v = ToUpperFunct(_v);
		}
		r = GetTextCommand(_v);
		if (r == 0) {
			cerr << "Cancel\n";
			return;
		}
		else if (r > 0 && r <= (int)parameters.size())
		{
			CurrentValues(r);
			EditValues(r);
			return;
		}
		else {
			system("cls");
			cerr << "Unknown command\n";
			_v.clear();
		}
	}

}

int SCore::GetCommand()
{
	CommandsList();
	cerr << "Select command:\n";
	string input;
	cin >> input;
	input = ToUpperFunct(input);
	int val = GetMainCommand(input);
	
	if (val > 0)
		return val;
	else {
		val = GetTextCommand(input);
		if (val >= 0) {
			Edit(input);
			return -1;
		}
	}
	return -7;
}

int SCore::GetTextCommand(const string& cmd)
{
	if (cmd == "SETCS") return 1;
	if (cmd == "SETGP") return 2;
	if (cmd == "SETFAQ") return 3;
	if (cmd == "SETSIZEX") return 4;
	if (cmd == "SETSIZEY") return 5;
	if (cmd == "SETSQ") return 6;
	if (cmd == "SETTE") return 7;
	if (cmd == "SETTS") return 8;
	if (cmd == "SETTI") return 9;
	if (cmd == "SETS") return 10;
	if (cmd == "SETCQ") return 11;
	if (cmd == "SETCV") return 12;
	if (cmd == "SETTT") return 13;
	if (cmd == "SETTU") return 14;
	if (cmd == "SETTSO") return 15;
	if (cmd == "SETTIX") return 16;
	if (cmd == "SETTIY") return 17;
	if (cmd == "SETD") return 18;
	if (cmd == "POLARITY") return 19;
	if (cmd == "SETLEGSHIFT") return 20;
	if (cmd == "SETLEGH") return 21;
	if (cmd == "SETLTSIZE") return 22;
	if (cmd == "SETLTSHIFTX") return 23;
	if (cmd == "SETLTSHIFTY") return 24;
	if (cmd == "SETCSX") return 25;
	if (cmd == "SETCSY") return 26;
	if (cmd == "SHOWLEGEND") return 27;
	if (cmd == "0") return 0;

	return -1;
}

void SCore::CurrentValues(int param)
{
	system("cls");
	cerr << "Current value: ";
	switch (param)
	{
	case 1:
		cerr << GetCellSize();
		break;
	case 2:
		cerr << GetGridPitch();
		break;
	case 3:
		cerr << GetFuelAssemblyQuantity();
		break;
	case 4:
		cerr << GetImageSizeX();
		break;
	case 5:
		cerr << GetImageSizeY();
		break;
	case 6:
		cerr << GetStringsQuantity();
		break;
	case 7:
		cerr << GetTextLenght();
		break;
	case 8:
		cerr << GetTextSize();
		break;
	case 9:
		cerr << GetTextYInterval();
		break;
	case 10:
		cerr << GetScale();
		break;
	case 11:
		cerr << GetColorsQuantity();
		break;
	case 12:
		cerr << GetColorVar();
		break;
	case 13:
		cerr << GetTextThikness();
		break;
	case 14:
		cerr << GetTextUnderline();
		break;
	case 15:
		cerr << GetTextStrikeout();
		break;
	case 16:
		cerr << GetTextInitX();
		break;
	case 17:
		cerr << GetTextInitY();
		break;
	case 18:
		cerr << GetDebug();
		break;
	case 19:
		cerr << GetPolarity();
		break;
	case 20:
		cerr << GetLegendShift();
		break;
	case 21:
		cerr << GetLegendHeight();
		break;
	case 22:
		cerr << GetLegendTextSize();
		break;
	case 23:
		cerr << GetLegendTextShiftX();
		break;
	case 24:
		cerr << GetLegendTextShiftY();
		break;
	case 25:
	case 26:
		cerr << "(X;Y)"<< GetCartShiftX() << ";" << GetCartShiftY();
		break;
	case 27:
		cerr << IsLegendRequired();
		break;
	}
	cerr << endl;

}

void SCore::EditValues(int param)
{
	cerr << "Input new value:\n";
	string s;
	while (true) {
		cerr << ">>> ";
		cin >> s;
		try {
			if (param == 2 || param == 10)
			{
				double nv = stod(s);
				if (param == 10)
					SetScale(nv);
				else
					SetGridPitch(nv);

				if (IsCoreActive())
					Update();
				break;

			}
			else
			{
				int val = GetNumberFromCommand(s);
				switch (param)
				{
				case 1:
					SetCellSize(val);
					break;
				case 3:
					SetFuelAssemblyQuantity(val);
					break;
				case 4:
					SetImageSizeX(val);
					break;
				case 5:
					SetImageSizeY(val);
					break;
				case 6:
					SetStringsQuantity(val);
					break;
				case 7:
					SetTextLenght(val);
					break;
				case 8:
					SetTextSize(val);
					break;
				case 9:
					SetTextYInterval(val);
					break;
				case 11:
					SetColorsQuantity(val);
					break;
				case 12:
					SetColorVar(val);
					break;
				case 13:
					SetTextThikness(val);
					break;
				case 14:
					SetTextUnderline(val);
					break;
				case 15:
					SetTextStrikeout(val);
					break;
				case 16:
					SetTextInitX(val);
					break;
				case 17:
					SetTextInitY(val);
					break;
				case 18:
					SetDebug(val);
					break;
				case 19:
					TVS.dev.clear();
					SetPolarity(s);
					TVS.CalculateDev(parameters["POLARITY"]);
					break;
				case 20:
					SetLegendShift(val);
					break;
				case 21:
					SetLegendHeight(val);
					break;
				case 22:
					SetLegendTextSize(val);
					break;
				case 23:
					SetLegendTextShiftX(val);
					break;
				case 24:
					SetLegendTextShiftY(val);
					break;
				case 25:
					SetCartShiftX(val);
					break;
				case 26:
					SetCartShiftY(val);
					break;
				case 27:
					SetLegendRequired(val);
					break;
				}
				if (IsCoreActive())
					Update();
				break;

			}
			cerr << "Wrong value\n";
		}
		catch (invalid_argument & ia)
		{
			cerr << ia.what() << " - wrong value\n";
		}
	}

}

void SCore::Save(const std::string& s)
{
	ofstream ofs;
	string name;
	if (s.empty())
		name = "parameters.ini";
	else
		name = s + "_" + GetSimpleDate() + "_parameters.ini";
	ofs.open(name);
	for (const auto& item : parameters)
	{
		ofs << item.first << "," << item.second << ",\n";
	}
	cerr << "Configuration saved!\n";

	ofs.close();
}

