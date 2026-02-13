#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>

bool IsBinaryString(const std::string& str) 
{
	if(str.empty()) {return false;}

	for(auto ch : str)
	{
		if(ch != '0' && ch != '1') {return false;}
	}
	return true;
}

size_t ToInteger(const std::string& str) 
{
	if(IsBinaryString(str) && str.length() <= 10)
	{
		size_t r = 0;

		for(auto ch : str) 
		{
			r *= 2;
			if(ch == '1') {r += 1;}
		}
		return r;
	}
	return 0;
}

#endif
