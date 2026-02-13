#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>

// IsBinaryString function
bool IsBinaryString(const std::string &s)
{
	if (s.length() == 0)
	{
		return false;
	}
	for (char c : s)
	{
		if (c != '0' && c != '1')
		{
			return false;
		}
	}

	return true;
}

// ToInteger function
unsigned int ToInteger(const std::string &s)
{
	if (s.length() > 10 || !IsBinaryString(s))
	{
		return 0;
	}

	unsigned int converted = 0;
	for (char c : s)
	{
		converted = converted * 2 + (c - '0');
	}
	return converted;
}

#endif