#pragma once

#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <thread>

#define tvs_size 236



using namespace std;

#include "Coordinates.h"
#include "GetParam.h"
#include "Logging.h"
#include "Store.h"

class KK_values
{
public:
	KK_values()
	{
		tvs_max = 0;
		tvs_min = 0;
		int NUM_FA_ = 0;
		isDifference = false;
		isLoaded = false;
	}

	void CalculateDev()
	{
		for (size_t i = 0; i < main.size(); i++)
		{
			if (main[i] != 0)
				dev.push_back((secondary[i] - main[i]) * 100. / main[i]);
			else
			{
				dev.push_back(0);
			}

		}
	}

	int HashFunction(const string & input)
	{
		int res = 0;
		for (const auto& c : input)
		{
			res += (c / input.size())*(c % input.size());
		}
		return res;
	}

	void HashingStringsValues(vector<double>& output, vector<string>& input)
	{
		for (auto& item : input)
		{
			item = ToUpperFunct(item);
			output.push_back((double)HashFunction(item));
		}
	}

	void Sort()
	{
		vector<double> cp;
		if (isDifference)
			cp = dev;
		else
			cp = main;

		sort(cp.begin(), cp.end());
		tvs_max = cp[cp.size() - 1];
		tvs_min = cp[0];

	}

	bool isLoaded;
	
	double tvs_max;
	double tvs_min;

	vector<double> main;
	vector<double> secondary;
	vector<string> main_s;
	vector<string> secondary_s;
	vector<double> dev;
	bool isDifference;
	bool isNumericalData;
};




#include "Handler.h"
#include "Initialize.h"
#include "GraphParameters.h"


