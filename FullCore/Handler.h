#pragma once

string VARIABLE_NAME = "NULL";

#define SAVE_VARIBLE_NAME(varible) VARIABLE_NAME = string(#varible);




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
	void SetDebug(int _i);
	void SetPolarity(string &_s);

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
	int GetDebug()const;
	string GetPolarity() const;

	// Text
	void EditCommonInfo();
	void CommandsList();
	void DebugInfo();


	//Interface
	void Save(const std::string& s);
	void PrintText(int number);
	void Paint();
	void Close();

	// Handle
	int GetCommand();
	~SCore() { DestroyWindow(HGraph); }
	int GetMainCommand(const string& input);
	bool IsLoaded()const;
	bool IsCoreActive() const;
	void SetCoreActive(bool _b);
	void Update();
	void Store();
	void SelectAssemblies();
	void Cut(std::vector<double>& input);
	void ToLog(const std::string&);

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
	int m_debug;
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


int SCore::GetMainCommand(const string& input)
{

	if (input == "PRINT") return 1;
	if (input == "EDIT") return 2;
	if (input == "GET") return 3;
	if (input == "DEBUG_INFO") return 11;
	if (input == "END") return 10;
	if (input == "SAVE") return 9;
	if (input == "GRAB") return 8;
	if (input == "STORE") return 7;
	if (input == "CLOSE") return 6;
	if (input == "UPDATE") return 5;
	return 0;
}

void SCore::Update()
{
	InvalidateRect(HGraph, NULL, TRUE);
	UpdateWindow(HGraph);

}

void SCore::Store()
{
	if (IsCoreActive()) {
		string _name = GetSimpleDate();
		_name += ".bmp";
		StoreClientWindowBitmap(HGraph, _name.data());
	}
}

bool SCore::IsLoaded()const {
	return TVS.isLoaded;
}

bool SCore::IsCoreActive() const
{
	return isCoreActive;
}

void SCore::SetCoreActive(bool _b)
{
	isCoreActive = _b;
}

void SCore::SelectAssemblies()
{
	if ((int)TVS.main.size() > GetFuelAssemblyQuantity()) {
		SAVE_VARIBLE_NAME(TVS.main);
		Cut(TVS.main);
	}

	if ((int)TVS.secondary.size() > GetFuelAssemblyQuantity()) {
		SAVE_VARIBLE_NAME(TVS.secondary);
		Cut(TVS.secondary);
	}
}

void SCore::Cut(std::vector<double> & input)
{
	std::cerr <<">>>"<< VARIABLE_NAME << " :: more than " << GetFuelAssemblyQuantity() << " points\n";
	std::cerr << "defined as <FuelAssemblyQuantity()>\n";
	std::cerr << "Would you like select cut the assemblies array? (1 - Y, 0 - N)\n";

	std::string ch;
	
	while (1) {
		std::cerr << ">> ";
		std::cin >> ch;
		if (ch == "1")
			break;
		if (ch == "0")
			//return;
			std::cerr << "command disabled. Cut an array\n";
		std::cerr << "unknown. repeat\n";
	}

	int _sample = input.size() / GetFuelAssemblyQuantity();
	std::cerr << "samples quantity: " << _sample 
		<< std::endl<< "\nwich sample you want to observe? (-1 - quit)\n";
	int sq = _sample;
	std::string s_sample;
	while (1) {
		std::cerr << ">>";
		std::cin >> s_sample;
		if (s_sample == "-1")
			//return;
			std::cerr << "command disabled. Cut an array\n";
		_sample = stoi(s_sample);
		if (_sample <= 0 || _sample > sq)
			std::cerr << "wrong "<<__FUNCTION__<<"\n";
		else
			break;
	}

	if (_sample > 1)
		for (int i = 0; i < GetFuelAssemblyQuantity(); i++)
			input[i] = input[(i)+(_sample - 1) * GetFuelAssemblyQuantity()];


	input.resize(GetFuelAssemblyQuantity());
	
}


void SCore::DebugInfo() {
	system("cls");
	cerr << "Debug info:\n";
	cerr << "KQ MAX: " << TVS.tvs_max << endl;
	cerr << "KQ_MIN: "<<TVS.tvs_min << endl;
	cerr << "Colors quantity: " << colors_quantity << endl;
	cerr << "Zero group in: " << TVS.zero_group << endl;
	cerr << "Group step is: " << TVS.step_size << endl;
	cerr << "=========\nGraph parameters:\n";
	cerr << "Cell size: " << cell_size << endl;
	cerr << "Grid pitch: " << grid_pitch << endl;
	cerr << "Text Y interval: " << text_y_interval << endl;
	cerr << "Scale: " << scale << endl;
	cerr << "Text symbol count: " << text_lenght << endl;
	cerr << "Strings quantity: " << strings_quantity << endl;
	cerr << "Font size: " << text_size << endl;
	cerr << "Use color? " << colored << endl;
	cerr << "Color group quantity:" << colors_quantity << endl;
	cerr << "Geometry: " << fa_count << endl;
	cerr << "Size X/Y: " << sx << " / " << sy << endl;
	cerr << "Initial position (X/Y): " << i_pos_x << " / " << i_pos_y << endl;
	cerr << "Text thickness: " << text_thikness << endl;
	cerr << "Text underline/strikeout: " << text_underline << " / " << text_strikeout << endl;
	cerr << "Text initial position (X/Y): " << text_init_x << " / " << text_init_y << endl;
}


void SCore::ToLog(const std::string& str)
{
	log.Console(0, str);
}