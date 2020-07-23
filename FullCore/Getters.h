#pragma once

int SCore::GetTextInitX()const
{
	return text_init_x;
}

int SCore::GetTextInitY()const
{
	return text_init_y;
}

bool SCore::GetTextStrikeout()const
{
	return text_strikeout;
}

bool SCore::GetTextUnderline()const
{
	return text_underline;
}

int SCore::GetTextThikness() const
{
	return text_thikness;
}

double SCore::GetGridPitch()const
{
	return grid_pitch;
}

int SCore::GetInitPosX()const
{
	return i_pos_x;
}

int SCore::GetInitPosY()const
{
	return i_pos_y;
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

int SCore::GetDebug()const
{
	return m_debug;
}

string SCore::GetPolarity() const
{
	return parameters.at("POLARITY");
}


int SCore::GetLegendShift() const
{
	return legend_shift;
}

int SCore::GetLegendHeight() const
{
	return legend_height;
}

int SCore::GetLegendTextShiftX() const
{
	return legend_text_shift_x;
}

int SCore::GetLegendTextShiftY() const
{
	return legend_text_shift_y;
}

int SCore::GetLegendTextSize() const
{
	return legend_text_size;
}

int SCore::GetCartShiftX() const
{
	return cart_shift_x;
}

int SCore::GetCartShiftY() const
{
	return cart_shift_y;
}

bool SCore::IsLegendRequired() const
{
	return isLegendRequired;
}
