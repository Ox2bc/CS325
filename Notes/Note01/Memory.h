#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <cmath>
#include "Object.h"

namespace can // computer architecture note
{
	bool isBinary(std::string str)
	{
		for (char ch : str)
		{
			if (ch != '0' && ch != '1')
			{
				return false;
			}
		}
		return true;
	}

	bool isHex(std::string str)
	{
		char i;

		for (char ch : str)
		{
			i = tolower(ch);
			if (!isdigit(i) && (i < 'a' || i > 'f'))
			{
				return false;
			}
		}
		return true;
	}

	int toDecimal(std::string str)
	{
		if (isBinary(str))
		{
			int i = 0;

			for (char ch : str)
			{
				i *= 2;
				if (ch == '1')
				{
					i += 1;
				}
			}
			return i;
		}
		return -1;
	}

	std::string toBinary(int obj)
	{
		if (obj < 0)
		{
			obj *= -1;
		}
		else if (obj == 0)
		{
			return "0";
		}
		std::string rslt;

		while (obj > 0)
		{
			rslt = std::to_string(obj % 2) + rslt;
			obj /= 2;
		}
		return rslt;
	}

	class Memory : public Object
	{
	private:
		std::string content;
		std::string id;
		bool flag;
		static const std::string digits[10];
		static const std::string letters[6];

		std::string toBinary(std::string str) const
		{
			char i;
			std::string rslt;

			for (char ch : str)
			{
				if (isdigit(ch))
				{
					rslt += digits[ch - '0'];
				}
				else
				{
					i = tolower(ch);
					rslt += letters[i - 'a'];
				}
			}
			return rslt;
		}

		std::string toHex(std::string str) const
		{
			std::string cstr, rslt, cp, hdg = "0123456789ABCDEF";
			// pad on zeroes so that cstr has a multiple of four number of character
			if (str.length() % 4 == 0)
			{
				cstr = str;
			}
			else
			{
				cstr = std::string(4 - str.length() % 4, '0') + str;
			}

			for (int i = 0; i < cstr.length(); i += 4)
			{
				cp = cstr.substr(i, 4);
				rslt += hdg[toDecimal(cp)];
			}
			return rslt;
		}

	public:
		// Default Constructor
		Memory()
		{
			content = "0";
			id = "1";
			flag = false;
		}

		// Copy Constructor
		Memory(const Memory &obj)
		{
			content = obj.content;
			id = obj.id;
			flag = obj.flag;
		}

		// Assignment Operator
		Memory &operator=(const Memory &rhs)
		{
			if (this != &rhs)
			{
				content = rhs.content;
				id = rhs.id;
				flag = rhs.flag;
			}
			return *this;
		}

		// Destructor
		~Memory() {}

		std::string read()
		{
			flag = false;
			return content;
		}

		void write(std::string obj)
		{
			if (isBinary(obj))
			{
				flag = true;
				content = obj;
			}
		}

		bool modified() const { return flag; }

		void edit(bool obj) { flag = obj; }

		std::string name() const { return id; }

		void name(std::string str) { id = str; }

		friend std::istream &operator>>(std::istream &i, Memory &obj)
		{
			std::string str;
			i >> str;

			if (isBinary(str))
			{
				obj.content = str;
			}
			else if (isHex(str))
			{
				obj.content = obj.toBinary(str);
			}
			else
			{
				obj.content = std::string(8, '0');
			}
			return i;
		}

		std::string toString() const override
		{
			return id + ": " + toHex(content);
		}
	};

	const std::string Memory::digits[10] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001"};
	const std::string Memory::letters[6] = {"1010", "1011", "1100", "1101", "1110", "1111"};
}

#endif