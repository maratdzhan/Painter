#pragma once


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

void SCore::SetTextStrikeout(int _b)
{
	text_strikeout = _b;
	parameters["TEXT_STRIKEOUT"] = to_string(text_strikeout);
}

void SCore::SetTextUnderline(bool _b)
{
	text_underline = _b;
	parameters["TEXT_UNDERLINE"] = to_string(text_underline);
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
	parameters["COLORS_QUANTITY"] = to_string(colors_quantity);
}

void SCore::SetPolarity(string & _s) {

	_s = ToUpperFunct(_s);
	if (_s != "MAIN" && _s != "SECONDARY") {
		cerr << "Enter\nMAIN - set on main.txt\nSECONDARY - set on secondary.txt\n";
		cin >> _s;
		SetPolarity(_s);
	}
	else
		parameters["POLARITY"] = _s;

	system("cls");
}

void SCore::SetDebug(int _i)
{
	m_debug = _i;
}

void SCore::SetLegendShift(int _v)
{
	legend_shift = _v;
	parameters["LEGEND_SHIFT"] = to_string(legend_shift);
}

void SCore::SetLegendHeight(int _v)
{
	legend_height = _v;
	parameters["LEGEND_HEIGHT"] = to_string(legend_height);
}

void SCore::SetLegendTextShiftX(int _v)
{
	legend_text_shift_x = _v;
	parameters["LEGEND_TEXT_SHIFT_X"] = to_string(legend_text_shift_x);
}

void SCore::SetLegendTextShiftY(int _v)
{
	legend_text_shift_y = _v;
	parameters["LEGEND_TEXT_SHIFT_Y"] = to_string(legend_text_shift_y);
}

void SCore::SetLegendTextSize(int _v)
{
	legend_text_size = _v;
	parameters["LEGEND_TEXT_SIZE"] = to_string(legend_text_size);
}

void SCore::SetCartShiftX(int _v)
{
	cart_shift_x = _v;
	parameters["CART_SHIFT_X"] = to_string(cart_shift_x);
}

void SCore::SetCartShiftY(int _v)
{
	cart_shift_y = _v;
	parameters["CART_SHIFT_Y"] = to_string(cart_shift_y);
}

void SCore::SetLegendRequired(bool _f)
{
	isLegendRequired = _f;
	parameters["LEGEND_REQUIRED"] = to_string(int(isLegendRequired));
}
