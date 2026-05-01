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
	// NotGate
	class NotGate : public Gate
	{
	private:
		NotGate(const NotGate &) = delete;
		NotGate &operator=(const NotGate &) = delete;

	public:
		NotGate() : Gate() {}

		bool output() const override
		{
			if (valid())
			{
				return !at(0).output();
			}
			return false;
		}

		std::string toString() const override
		{
			if (valid())
			{
				std::stringstream out;

				out << "!(" << at(0) << ")";
				return out.str();
			}
			return "x";
		}
	};
	// AndGate
	class AndGate : public Gate
	{
	private:
		AndGate(const AndGate &) = delete;
		AndGate &operator=(const AndGate &) = delete;

	public:
		AndGate() : Gate(2, 10) {}

		bool output() const override
		{
			if (valid())
			{
				for (int i = 0; i < count(); i += 1)
				{
					if (!at(i).output())
					{
						return false;
					}
				}
				return true;
			}
			return false;
		}

		std::string toString() const override
		{
			if (valid())
			{
				std::stringstream out;
				out << "(";
				for (int i = 0; i < count(); i += 1)
				{
					out << at(i);
					if (i + 1 < count())
					{
						out << " & ";
					}
				}
				out << ")";
				return out.str();
			}
			return "x";
		}
	};
	// OrGate
	class OrGate : public Gate
	{
	private:
		OrGate(const OrGate &) = delete;
		OrGate &operator=(const OrGate &) = delete;

	public:
		OrGate() : Gate(2, 10) {}

		bool output() const override
		{
			if (valid())
			{
				for (int i = 0; i < count(); i += 1)
				{
					if (at(i).output())
					{
						return true;
					}
				}
				return false;
			}
			return false;
		}

		std::string toString() const override
		{
			if (valid())
			{
				std::stringstream out;
				out << "(";
				for (int i = 0; i < count(); i += 1)
				{
					out << at(i);
					if (i + 1 < count())
					{
						out << " | ";
					}
				}
				out << ")";
				return out.str();
			}
			return "x";
		}
	};
	// NandGate
	class NandGate : public Gate
	{
	private:
		NandGate(const NandGate &) = delete;
		NandGate &operator=(const NandGate &) = delete;

	public:
		NandGate() : Gate(2, 10) {}

		bool output() const override
		{
			if (valid())
			{
				for (int i = 0; i < count(); i += 1)
				{
					if (!at(i).output())
					{
						return true;
					}
				}
				return false;
			}
			return false;
		}

		std::string toString() const override
		{
			if (valid())
			{
				std::stringstream out;
				out << "(";
				for (int i = 0; i < count(); i += 1)
				{
					out << at(i);
					if (i + 1 < count())
					{
						out << " $ ";
					}
				}
				out << ")";
				return out.str();
			}
			return "x";
		}
	};
	// NorGate
	class NorGate : public Gate
	{
	private:
		NorGate(const NorGate &) = delete;
		NorGate &operator=(const NorGate &) = delete;

	public:
		NorGate() : Gate(2, 10) {}

		bool output() const override
		{
			if (valid())
			{
				for (int i = 0; i < count(); i += 1)
				{
					if (at(i).output())
					{
						return false;
					}
				}
				return true;
			}
			return false;
		}

		std::string toString() const override
		{
			if (valid())
			{
				std::stringstream out;
				out << "(";
				for (int i = 0; i < count(); i += 1)
				{
					out << at(i);
					if (i + 1 < count())
					{
						out << " % ";
					}
				}
				out << ")";
				return out.str();
			}
			return "x";
		}
	};
	// XorGate
	class XorGate : public Gate
	{
	private:
		XorGate(const XorGate &) = delete;
		XorGate &operator=(const XorGate &) = delete;

	public:
		XorGate() : Gate(2, 10) {}

		bool output() const override
		{
			if (valid())
			{
				bool result = false;
				for (int i = 0; i < count(); i++)
				{
					result = result ^ at(i).output();
				}
				return result;
			}
			return false;
		}

		std::string toString() const override
		{
			if (valid())
			{
				std::stringstream out;
				out << "(";

				for (int i = 0; i < count(); i++)
				{
					out << at(i).toString();
					if (i + 1 < count())
					{
						out << " # ";
					}
				}

				out << ")";
				return out.str();
			}
			return "x";
		}
	};
}

#endif
