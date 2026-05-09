#ifndef GATES_H
#define GATES_H

#include "Gate.h"
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <iostream>
#include <iomanip>

namespace cap
{
	// A XOR Gate Class Definition
	class XORGate : public Gate
	{
	private:
		XORGate(const XORGate &) = delete;
		XORGate &operator=(const XORGate &) = delete;

	public:
		// we need XOR to take 2 inputs only
		XORGate() : Gate(2, 2) {}

		bool output() const override
		{
			if (!valid())
				return false;

			// if the two values aren't the same, its returning true, if they are the same (0,0) or (1,1) it returns false
			return at(0).output() != at(1).output();
		}

		std::string toString() const override
		{
			std::stringstream out;
			if (valid())
			{
				out << at(0) << " XOR " << at(1);
			}
			else
			{
				out << "X";
			}
			return out.str();
		}
	};

	// A NOT Gate Class Definition
	class NOTGate : public Gate
	{
	private:
		NOTGate(const NOTGate &) = delete;
		NOTGate &operator=(const NOTGate &) = delete;

	public:
		// NOT gates always have 1 input only
		NOTGate() : Gate(1, 1) {}

		bool output() const override
		{
			if (!valid())
				return false;
			return !at(0).output(); // returns opposite of what it is
		}

		std::string toString() const override
		{
			std::stringstream out;
			if (valid())
			{
				out << "NOT " << at(0);
			}
			else
			{
				out << "X";
			}
			return out.str();
		}
	};

	// An AND Gate Class Definition
	class ANDGate : public Gate
	{
	private:
		ANDGate(const ANDGate &) = delete;
		ANDGate &operator=(const ANDGate &) = delete;

	public:
		// AND can take 2-3 inputs
		ANDGate() : Gate(2, 3) {}

		bool output() const override
		{
			if (!valid())
				return false;

			// and returns true if all values are true
			bool result = true;
			for (size_t i = 0; i < count(); i++)
			{
				result = result && at(i).output();
			}
			return result;
		}

		std::string toString() const override
		{
			std::stringstream out;
			if (valid())
			{
				for (size_t i = 0; i < count(); i++)
				{
					out << at(i);
					if (i + 1 < count())
						out << " & ";
				}
			}
			else
			{
				out << "X";
			}
			return out.str();
		}
	};

	// An OR Gate Class Definition
	class ORGate : public Gate
	{
	private:
		ORGate(const ORGate &) = delete;
		ORGate &operator=(const ORGate &) = delete;

	public:
		// OR takes 2-3 inputs
		ORGate() : Gate(2, 3) {}

		bool output() const override
		{
			if (!valid())
				return false;

			// returns true if any inputs are true
			bool result = false;
			for (size_t i = 0; i < count(); i++)
			{
				result = result || at(i).output();
			}
			return result;
		}

		std::string toString() const override
		{
			std::stringstream out;
			if (valid())
			{
				for (size_t i = 0; i < count(); i++)
				{
					out << at(i);
					if (i + 1 < count())
						out << " | ";
				}
			}
			else
			{
				out << "X";
			}
			return out.str();
		}
	};
}

#endif