#ifndef BUS_H
#define BUS_H

#include <iostream>
#include <string>
#include "Word.h"
#include "Part.h"
#include "BusCom.h"

namespace cal
{

	void setData(BusCom &obj, std::string str)
	{
		Word temp(str);
		if (temp.size() == obj.data().size())
		{
			transfer(obj.data(), temp);
		}
	}

	void setAddr(BusCom &obj, std::string str)
	{
		Word temp(str);
		if (temp.size() == obj.addr().size())
		{
			transfer(obj.addr(), temp);
		}
	}

	void setCtrl(BusCom &obj, std::string str)
	{
		Word temp(str);
		if (temp.size() == obj.ctrl().size())
		{
			transfer(obj.ctrl(), temp);
		}
	}

}

#endif
