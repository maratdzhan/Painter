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
	KK_values();

	void CalculateDev(const string & _polarity);
	void DevCycle(vector<double>& input_1, vector<double>& input_2);
	int HashFunction(const string& input);
	void HashingStringsValues(vector<double>& output, vector<string>& input);
	void Sort();
	void SetZeroGroup(int color_quantity);
	void Clear();
	
	double tvs_max;
	double tvs_min;
	int zero_group;
	double step_size;

	vector<double> main;
	vector<double> secondary;
	vector<string> main_s;
	vector<string> secondary_s;
	vector<double> dev;
	bool isDifference;
	bool isNumericalData;
	bool isLoaded;
};

KK_values::KK_values()
{
	tvs_max = 0;
	tvs_min = 0;
	zero_group = 0;
	int NUM_FA_ = 0;
	step_size = 0;
	isDifference = false;
	isLoaded = false;
}

void KK_values::CalculateDev(const string & _s)
{
	if (_s=="MAIN")
		DevCycle(main, secondary);
	else
		DevCycle(secondary, main);
}

void KK_values::DevCycle(vector<double>& input_1, vector<double>& input_2)
{
	//for (size_t i = 0; i < main.size(); i++)
	//{
	//	if (main[i] != 0)
	//		dev.push_back((secondary[i] - main[i]) * 100. / main[i]);
	//	else
	//	{
	//		dev.push_back(0);
	//	}
	//}

	for (size_t i = 0; i < input_2.size(); i++)
	{
		if (input_2[i] != 0)
			dev.push_back((input_1[i] - input_2[i]) * 100. / input_2[i]);
		else
		{
			dev.push_back(0);
		}
	}
}

int KK_values::HashFunction(const string& input)
{
	int res = 0;
	for (const auto& c : input)
	{
		res += (c / input.size()) * (c % input.size());
	}
	return res;
}

void KK_values::HashingStringsValues(vector<double>& output, vector<string>& input)
{
	for (auto& item : input)
	{
		item = ToUpperFunct(item);
		output.push_back((double)HashFunction(item));
	}
}

void KK_values::Sort()
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



void KK_values::SetZeroGroup(int colors_q)
{
	double step_size = (tvs_max - tvs_min)/(colors_q-1);

	if ((tvs_min* tvs_max< 0))
	{
		for (short i = 1; i < colors_q + 1; i++)
		{
			if (0 < (tvs_min + (i * step_size)))
			{
				zero_group = i - 1;
				break;
			}
		}
	}
	else
	{
		for (short i = 1; i < colors_q + 1; i++)
		{
			if (1 < (tvs_min + (i * step_size)))
			{
				if (i > 1) {
					zero_group = i - 1;
					break;
				}
				else
				{
					zero_group = colors_q / 2;
				}
			}
		}
	}
}

void KK_values::Clear()
{
	main.clear();
	secondary.clear();
	main_s.clear();
	secondary_s.clear();
	dev.clear();
}


#include "Handler.h"
#include "Initialize.h"
#include "GraphParameters.h"


