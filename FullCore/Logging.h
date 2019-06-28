#pragma once
#include <time.h>

string GetDate()
{
	time_t t;
	t = time(NULL);
	return (ctime(&t));
}

string GetSimpleDate()
{
	time_t t;
	t = time(NULL);
	struct tm* tim;
	tim = localtime(&t);
	string result;
	result = (to_string(tim->tm_hour)) + (to_string(tim->tm_min)) + (to_string(tim->tm_sec)) + (to_string(tim->tm_mday)) + (to_string(tim->tm_mon));
	return (result);
}

class Logging
{
public:
	Logging()
	{
		Message("### Session start");
		Message(GetDate());
	}

	void Message(const string& input)
	{
		ofstream f("log.txt", ios::app);
		f << input << "\n";
		f.close();
	}

	void MessageC(const string& input)
	{
		ofstream f("log.txt", ios::app);
		f << "---->" << input << "\n";
		f.close();

	}

	void Console(int isConsoleInput, const string& value)
	{
		if (isConsoleInput == 1)
			MessageC(value);
		else
			Message(value);
	}

	void Error(string error, string function)
	{
		Message(function);
		error+= " *error*";
		Message(error);
	}

	void SetLastmessage(const string& s)
	{
		lastMessage = s;
	}

	string LastMessage()const
	{
		return lastMessage;
	}

private:
	string lastMessage;
};