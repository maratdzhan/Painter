#pragma once
#include <string>

template<typename K>
K GetParam(string & s, int num)
{
	string resStr;
	K locNum;

	for (unsigned int pos = 0; pos < s.size(); pos++)
	{
		if (s[pos] != ',')
		{
			resStr += s[pos];
		}
		else
		{
			if (num == locNum)
			{
				locNum = stoi(resStr);
				return locNum;
			}
			else
			{
				locNum++;
				resStr.clear();
			}
		}
	}
	if (!resStr.empty())
	{
		locNum = static_cast<K>(resStr);
	}
	return locNum;
}


string GetParamS(string s, int num)
{
	string resStr;
	int counter = 1;

	for (unsigned int pos = 0; pos < s.size(); pos++)
	{
		if ((s[pos] != ',') && (s[pos] != ' '))
		{
			resStr += s[pos];
		}
		else
		{
			if (num == counter)
			{
				return resStr;
			}
			else
			{
				counter++;
				resStr.clear();
			}
		}
	}
	if (!resStr.empty())
	{
		resStr;
	}
	return resStr;
}


string ReturnNumbers(string str)
{
	string result;
	if (!str.empty())
	{
		for (size_t i = 0; i < str.size(); i++)
		{
			if (((char(str[i]) > 47) && (char(str[i]) < 58)) || (char(str[i] == 44)) || (char(str[i] == 46)) || (char(str[i]) == 45))
			{
				if ((char(str[i] == 44)))
					result += ".";
				else
					result += str[i];
			}
		}
	}
	try
	{
		(stod(result));
	}
	catch (const invalid_argument & EX)
	{
		printf("%s", EX.what());
		result = "0";
	}
	return result;
}

string ToUpperFunct(string str)
{
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	return str;
}


int GetNumberFromCommand(const std::string& s)
{
	int rs = -1;
	try {
		rs = stoi(s);
	}
	catch (exception & ex)
	{
		cerr <<ex.what()<< " => Wrong stoi argument "<<s<<" at " << __FUNCTION__ << endl;
	}

	return rs;
}