#pragma once




class SCore
{
public:
	SCore()
	{
		parameters_file = "parameters.ini";
		Load();
		Initialize();
	}



	void Load();
	void Initialize();
	void NullInitialize();
	void GetPointData();
	void GetKq(int tParam, int isMain);
	void TextOutCore(HDC hdc, int number);
	COLORREF ColorReference(short number);
	std::string GraphParameters(std::string parameter_name);
	void TextOutCoord();

	int GetTextCommand(const string& cmd);

	// SetCoreParameters
	void SetCellSize(int _v);
	void SetColorVar(bool _b);
	void SetFuelAssemblyQuantity(int _v);
	void SetImageSizeX(int _v);
	void SetImageSizeY(int _v);
	void SetScale(double _d);
	void SetStringsQuantity(int _v);
	void SetTextLenght(size_t _l);
	void SetTextSize(int _v);
	void SetTextYInterval(int _v);
	void SetColorsQuantity(int _v);
	void Edit(string v);
	void SetGridPitch(double _v);
	void CurrentValues(int param);
	void SetInitPosX(int _v);
	void SetInitPosY(int _v);
	void SetTextThikness(int _v);
	void SetTextUnderline(bool _b);
	void SetTextStrikeout(int _b);
	void SetTextInitX(int _i);
	void SetTextInitY(int _i);

	// GetCoreParameters
	int GetCellSize()const;
	bool GetColorVar()const;
	int GetFuelAssemblyQuantity()const;
	int GetImageSizeX()const;
	int GetImageSizeY()const;
	double GetScale()const;
	int GetStringsQuantity()const;
	size_t GetTextLenght()const;
	int GetTextSize()const;
	int GetTextYInterval()const;
	int GetColorsQuantity()const;
	double GetGridPitch()const;
	int GetInitPosX()const;
	int GetInitPosY()const;
	int GetTextThikness()const;
	bool GetTextUnderline()const;
	bool GetTextStrikeout()const;
	int GetTextInitX()const;
	int GetTextInitY()const;
	void SetCoordinates(int fa_quantity);
	double GetCoordinates(int fa_quantity, bool isX);

	// Text
	void EditCommonInfo();
	void CommandsList();


	//Save
	void Save(const std::string& s);
	void PrintText(int number);

	int GetMainCommand(const string & input)
	{
		
		if (input == "PRINT") return 1;
		if (input == "EDIT") return 2;
		if (input == "GET") return 3;
		if (input == "END") return 10;
		if (input == "SAVE") return 9;
		if (input == "GRAB") return 8;
		if (input == "STORE") return 7;
		if (input == "CLOSE") return 6;
		if (input == "UPDATE") return 5;
		return 0;
	}

	int GetCommand();


	void Update()
	{
		InvalidateRect(HGraph, NULL, TRUE);
		UpdateWindow(HGraph);
		
	}

	~SCore()
	{
		DestroyWindow(HGraph);

	}

	void Store()
	{
		if (IsCoreActive()) {
			string _name = GetSimpleDate();
			_name += ".bmp";
			StoreClientWindowBitmap(HGraph, _name.data());
		}
	}

	bool IsLoaded()const {
		return TVS.isLoaded;
	}

	bool IsCoreActive() const
	{
		return isCoreActive;
	}

	void SetCoreActive(bool _b) 
	{
		isCoreActive = _b;
	}

	




	void Paint();
	void Close();

private:
	void EditValues(int param);
	void DefineMode();

public:
	HDC hdc;
	PAINTSTRUCT paintstruct;
	HWND hwnd;

private:
	int cell_size;
	double grid_pitch;
	int text_y_interval;
	double scale;
	size_t text_lenght;
	int strings_quantity;
	int text_size;
	bool colored;
	int colors_quantity;
	int fa_count;
	int sx;
	int sy;
	int i_pos_x;
	int i_pos_y;
	int text_thikness;
	bool text_underline;
	bool text_strikeout;
	int text_init_x;
	int text_init_y;
	vector<int> text_coords;
	vector<string> stringsPosition;
	Logging log;
	KK_values TVS;
	string parameters_file;
	map<string, string> parameters;
	bool isCoreActive;
	int mode;
	vector<pair<double, double>> coordinates;
};