#ifndef BUSCOM_H
#define BUSCOM_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <fstream>
#include <cctype>
#include <cmath>
#include "Word.h"
#include "Part.h"

namespace cal
{			
	class BusCom : public Word 
	{
		private:
		std::string toString() const override 
		{
			std::ostringstream out;
			out << "[";
			for(size_t i = 0;i < 3;i += 1)
			{
				out << lines[i];
				if((i + 1) < 3) {out << "][";}
			}
			out << "]";
			return out.str();
		}
		Part lines[3];

		using Word::extended;
		using Word::appended;
		using Word::join;
		using Word::unbind;
		using Word::bounded;
		using Word::empty;

   		public:
		BusCom() : Word(24)
		{
			fix();
			frozen = true;

			for(size_t i = 0;i < 3;i += 1)
			{
				lines[i] = Part(*this,8*i,8*i+7);
			}	
		}

		BusCom(size_t d,size_t a,size_t c) 
		{
			size_t ls[4] = {d,a,c}, id[4] = {0}, s = 0;

			for(size_t i = 0;i < 3;i += 1)
			{
				if(ls[i] == 0) {ls[i] = 8;}
				s += ls[i];
				id[i+1] = s;
			}
			static_cast<Word&>(*this) = Word(s);
			fix();
			frozen = true;
			
			for(size_t i = 0;i < 3;i += 1)
			{
				lines[i] = Part(*this,id[i],id[i+1]-1);
			}
		}
		
		BusCom(const BusCom& obj) {*this = obj;}
		
		BusCom& operator=(const BusCom& rhs)
		{
			if(this != &rhs) 
			{
				stable = false;
				Word::operator=(rhs);
				size_t id[4] = {0}, s = 0;

				for(size_t i = 0;i < 3;i += 1)
				{
					s += rhs.lines[i].size();
					id[i+1] = s;
					lines[i] = Part(*this,id[i],id[i+1]-1);
				}
			}
			return *this;
		}

		virtual ~BusCom() {}
		const Part& data() const {return lines[0];}
		const Part& addr() const {return lines[1];}
		const Part& ctrl() const {return lines[2];}
		Part& data() {return lines[0];}
		Part& addr() {return lines[1];}
		Part& ctrl() {return lines[2];}
	};
}

#endif
