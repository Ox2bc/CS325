#ifndef PART_H
#define PART_H

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "Word.h"

namespace cal
{
	class Part : public Object
	{
		private:
		Word* link;
		size_t bd[2];

		std::string toString() const override 
		{
			std::stringstream out;
			size_t n = size();

			if(n == 0) {return "nil";}

			for(size_t i = 0;i < n;i += 1)
			{
				out << get(i);
			}
			return out.str();
		}

		bool valid() const 
		{
			return (link != nullptr && !link->bounded());
		}	

		public:
		Part() : link(nullptr), bd{0,0} {}

		Part(Word& obj,size_t i,size_t j) : Part() 
		{
			if(!obj.empty() && !obj.bounded()) 
			{
				size_t m = obj.size();

				if(i < m && j < m) 
				{
					link = &obj;
					link->fix();
					size_t s = i + j;
					
					if(i < j) {bd[0] = i;}
					else {bd[0] = j;}
					bd[1] = s - bd[0];
				}
			}
		}	
					
		Part(const Part& obj) : Part() {*this = obj;}

		Part& operator=(const Part& rhs) 
		{
			if(this != &rhs && rhs.link != nullptr) 
			{
				link = rhs.link;
				for(size_t i = 0;i < 2;i += 1) 
				{
					bd[i] = rhs.bd[i];
				}
			}
			return *this;
		}

		virtual ~Part() {link = nullptr;}

		bool empty() const {return !valid();}
	
		size_t size() const 
		{
			if(!valid()) {return 0;}
			return (bd[1] - bd[0] + 1);
		}

		bool get(size_t idx) const
		{
			if(idx < size()) {return link->get(bd[0]+idx);}
			return false;
		}

		void set(size_t idx,bool bit) 
		{
			if(idx < size()) {link->set(bd[0]+idx,bit);}
			else if(size() == 0) {link = nullptr;}
		}
		
		void set(bool bit)
		{
			if(size() > 0)
			{
				for(size_t i = bd[0];i <= bd[1];i += 1)
				{
					link->set(i,bit);
				}
			}
			else {link = nullptr;}
		}

		friend void transfer(Word& lhs,const Part& rhs) 
		{
			if(&lhs != rhs.link && lhs.size() == rhs.size())
			{
				size_t m = lhs.size(), i = 0;
 
				while(i < m)
				{
					lhs.set(i,rhs.get(i));
					i += 1;
				}
			}
		}
		
		friend void transfer(Part& lhs,const Word& rhs) 
		{
			if(lhs.link != &rhs && lhs.size() == rhs.size())
			{
				size_t m = lhs.size(), i = 0;
 
				while(i < m)
				{
					lhs.set(i,rhs.get(i));
					i += 1;
				}
			}
		}

		friend size_t value(const Part& obj) 
		{
			size_t v = 0, m = obj.size(), n = m, i = 0;
			
			if(m != 0)
			{
				m -= 1;	
				while(m > 32) 
				{
					if(obj.get(i)) {return 0;}
					i += 1;
					m -= 1;
				}	

				while(i < n)
				{
					if(obj.get(i)) {v = v ^ (1 << m);}
					m -= 1;
					i += 1;
				}
			}
			return v;
		}
	};
}

#endif
