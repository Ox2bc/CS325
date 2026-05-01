#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "Dev.h"
#include "Gate.h"
#include "Switch.h"
#include "Split.h"

namespace cal
{
    class NotGate : public Gate
    {
        private:
        NotGate(const NotGate&) = delete;
        NotGate& operator=(const NotGate&) = delete;

        public:
        NotGate() : Gate() {}

        bool output() const override 
        {
            if(valid()) {return !(at(0).output());}
            return false;
        }

        std::string toString() const override
        {
            if(valid())
            {
                std::stringstream out;

                out << "!(" << at(0) << ")";
                return out.str();
            }
            return "X";
        }

    };

    class AndGate : public Gate
    {
        private:
        AndGate(const AndGate&) = delete;
        AndGate& operator=(const AndGate&) = delete;

        public:
        AndGate() : Gate(2,10) {}

        bool output() const override 
        {
            if(valid()) 
            {
                for(int i = 0;i < count();i += 1)
                {
                    if(!at(i).output()) {return false;}
                }
                return true;
            }
            return false;
        }

        std::string toString() const override
        {
            if(valid())
            {
                std::stringstream out;
                out << "(";
                for(int i = 0;i < count();i += 1)
                {
                    out << at(i);
                    
                    if(i + 1 < count()) {out << " & ";}
                }
                out << ")";
                return out.str();
            }
            return "X";
        }
    };

}

#endif
