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

}

void SCore::Initialize()
{
	int sp = parameters.size();
	int i = 0;
	double d = 0;
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

		if (sp - parameters.size() != 0)
			log.Error("***something was added at input data", __FUNCTION__);
	}
	catch (exception & exc)
	{
		NullInitialize();
		cerr << "error at loading\n";
		log.Error("loading parameters", __FUNCTION__);
		Initialize();
	}
}

void SCore::SetTextInitX(int _i)
{
	text_init_x = _i;
	parameters["TEXT_INIT_X"] = to_string(text_init_x);
}

void SCore::SetTextInitY(int _i)
{
	text_init_y = _i;
	parameters["TEXT_INIT_Y"] = to_string(text_init_y);
}

int SCore::GetTextInitX()const
{
	return text_init_x;
}

int SCore::GetTextInitY()const
{
	return text_init_y;
}

void SCore::SetTextStrikeout(int _b)
{
	text_strikeout = _b;
	parameters["TEXT_STRIKEOUT"] = to_string(text_strikeout);
}

bool SCore::GetTextStrikeout()const
{
	return text_strikeout;
}

void SCore::SetTextUnderline(bool _b)
{
	text_underline = _b;
	parameters["TEXT_UNDERLINE"] = to_string(text_underline);
}

bool SCore::GetTextUnderline()const
{
	return text_underline;
}

void SCore::SetTextThikness(int _v)
{
	if (_v > 0 && _v<=1000)
		text_thikness = _v;
	else
	{
		log.Error("thikness", __FUNCTION__);
		text_thikness = 900;
	}
	parameters["TEXT_THIKNESS"] = to_string(text_thikness);
}

int SCore::GetTextThikness() const
{
	return text_thikness;
}

void SCore::SetGridPitch(double _v)
{
	if (_v > 0)
		grid_pitch = _v;
	else
	{
		log.Error("grid_pitch", __FUNCTION__);
		grid_pitch = 2;
	}
	parameters["GRID_PITCH"] = to_string(grid_pitch);
}



double SCore::GetGridPitch()const
{
	return grid_pitch;
}

void SCore::SetCellSize(int _v)
{
	if (_v > 0)
		cell_size = _v;
	else
	{
		cell_size = 1;
		log.Error("cell_size", __FUNCTION__);
	}
	parameters["CELL_SIZE"] = to_string(cell_size);
}

void SCore::SetColorVar(bool _b)
{
	colored = _b;
	parameters["COLOR_VAR"] = to_string(colored);
}

void SCore::SetFuelAssemblyQuantity(int _v)
{
	if (_v < 0 && _v != 163 && _v != 360
		&& _v != 28 && _v != 60
		&& _v != 55 && _v != 120) {
		log.Error("fuel assembly quantity", __FUNCTION__);
		printf("Wrong value. Allowed:\n163 or 360 for 360 deg\n28 or 60 for 60 deg\n55 or 120 for 120deg\nCancel\n");
		return;
	}
	if (_v == 60)
		_v = 28;
	else if (_v == 120)
		_v = 55;
	else if (_v == 360)
		_v = 163;
	fa_count = _v;
	parameters["FA_QUANTITY"] = to_string(fa_count);
}

void SCore::SetImageSizeX(int _v)
{
	if (_v < 0)
		log.Error("image size x", __FUNCTION__);
	_v > 100 ? sx = _v : sx = 100;
	parameters["IMAGE_SIZE_X"] = to_string(sx);
}

void SCore::SetImageSizeY(int _v)
{
	if (_v < 0)
		log.Error("image size y", __FUNCTION__);
	_v > 100 ? sy = _v : sy = 100;
	parameters["IMAGE_SIZE_Y"] = to_string(sy);

}

void SCore::SetScale(double _d)
{
	if (_d < 0)
		log.Error("scale", __FUNCTION__);
	_d >0 ? scale = _d : scale = 1;
	parameters["SCALE"] = to_string(scale);

}

void SCore::SetStringsQuantity(int _v)
{
	if (_v < 1 && _v>4) {
		log.Error("strings quantity", __FUNCTION__);
		_v = 2;
	}
	else
		strings_quantity = _v;
	parameters["STRINGS_QUANTITY"] = to_string(strings_quantity);

}

void SCore::SetTextLenght(size_t _l)
{
	if (_l < 1)
	{
		log.Error("text lenght", __FUNCTION__);
		_l = 2;
	}
	else
	{
		text_lenght = _l;
	}
	parameters["TEXT_LENGHT"] = to_string(text_lenght);
}

void SCore::SetTextSize(int _v)
{
	if (_v < 1)
	{
		log.Error("text size", __FUNCTION__);
		text_size = 8;
	}
	else
	{
		text_size = _v;
	}
	parameters["TEXT_SIZE"] = to_string(text_size);
}

void SCore::SetInitPosX(int _v)
{
	if (_v < 10 && _v>1200)
	{
		log.Error("initial position x", __FUNCTION__);
		i_pos_x = 100;
	}
	else
	{
		i_pos_x = _v;
	}
	parameters["INIT_X"] = to_string(text_size);
}

void SCore::SetInitPosY(int _v)
{
	if (_v < 10 && _v>1200)
	{
		log.Error("initial position y", __FUNCTION__);
		i_pos_y = 100;
	}
	else
	{
		i_pos_y = _v;
	}
	parameters["INIT_Y"] = to_string(text_size);
}

int SCore::GetInitPosX()const
{
	return i_pos_x;
}

int SCore::GetInitPosY()const
{
	return i_pos_y;
}

void SCore::SetTextYInterval(int _v)
{
	text_y_interval = _v;
	parameters["TEXT_Y_INTERVAL"] = to_string(text_y_interval);
}


void SCore::SetColorsQuantity(int _v)
{
	if (_v < 1)
	{
		log.Error("text size", __FUNCTION__);
		colors_quantity = 20;
	}
	else
	{
		colors_quantity = _v;
	}
}

int SCore::GetImageSizeX()const
{
	return sx;
}

int SCore::GetImageSizeY()const
{
	return sy;
}


int SCore::GetCellSize()const
{
	return cell_size;
}

bool SCore::GetColorVar()const
{
	return colored;
}

int SCore::GetFuelAssemblyQuantity()const
{
	return fa_count;
}

double SCore::GetScale()const
{
	return scale;
}

int SCore::GetStringsQuantity()const
{
	return strings_quantity;
}

size_t SCore::GetTextLenght()const
{
	return text_lenght;
}

int SCore::GetTextSize()const
{
	return text_size;
}

int SCore::GetTextYInterval()const
{
	return text_y_interval;
}

int SCore::GetColorsQuantity()const
{
	return colors_quantity;
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
		else if (r > 0 && r <= parameters.size())
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


