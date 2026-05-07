#include "Dev.h"
#include "Switch.h"
#include "Split.h"
#include "Word.h"
#include "Gate.h"
#include "Port.h"
#include "Socket.h"
#include <iostream>
#include <string>

//A XNOR Gate Class Definition
class XNORGate : public cap::Gate
{
	private:
	XNORGate(const XNORGate&) = delete;
	XNORGate& operator=(const XNORGate&) = delete;

	public:
	XNORGate() : cap::Gate(2,3) {}
	
	bool output() const override 
	{
		bool res = false;

		if(valid()) 
		{
			res = at(0).output();

			for(size_t i = 1;i < count();i += 1)
			{
				res = (res == at(i).output());
			}
		}
		return res;
	}

	std::string toString() const override 
	{
		std::stringstream out;

		if(valid()) 
		{
			for(size_t i = 0;i < count();i += 1)
			{
				out << at(i);

				if(i + 1 < count()) {out << " / ";}
			}
		}
		else {out << "X";}
		return out.str();
	}
};

int main()
{
	//Input Word Declarations
	cap::Word I[3] = {cap::Word("11110000"), cap::Word("11001100"), cap::Word("10101010")};

	//Output Word
	cap::Word R(8);

	//Circuits Development
	XNORGate op;
	cap::Port inputs[3];
	cap::Socket output;

	for(size_t i = 0;i < 3;i += 1)
	{
		inputs[i].input(I[i]);
		op.input(inputs[i]);
	}

	//Linking word and dev to the socket
	output.source(op);
	output.destination(R);

	//Evaluate the circuit
	for(size_t i = 0;i < 8;i += 1)
	{
		for(size_t j = 0;j < 3;j += 1)
		{
			inputs[j].set(i);
		}
		output.set(i);
		output.evaluate();
		std::cout << op << " = " << output << "\n";
	}
	std::cout << "\n";

	//Display Truth Table 
	for(size_t i = 0;i < 8;i += 1)
	{
		for(size_t j = 0;j < 3;j += 1)
		{
			std::cout << I[j].get(i) << " | ";
		}
		std::cout << R.get(i) << "\n";
	}

	return 0;
}

