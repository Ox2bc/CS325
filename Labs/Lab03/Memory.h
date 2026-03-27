#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <sstream>
#include "Word.h"
#include "Part.h"
#include "BusCom.h"

namespace cal
{

	class Memory : public Object
	{
	public:
		Memory() : m_bitSize(16), m_locationCount(256), m_bus(nullptr)
		{
			m_storage = new uint64_t[m_locationCount]();
		}

		Memory(size_t bitSize) : m_locationCount(256), m_bus(nullptr)
		{
			m_bitSize = (bitSize >= 8 && bitSize <= 40) ? bitSize : 8;
			m_storage = new uint64_t[m_locationCount]();
		}

		Memory(size_t bitSize, size_t locationCount) : m_bus(nullptr)
		{
			m_bitSize = (bitSize >= 2 && bitSize <= 40) ? bitSize : 2;
			m_locationCount = (locationCount >= 8 && locationCount <= 4096) ? locationCount : 8;
			m_storage = new uint64_t[m_locationCount]();
		}

		Memory(const Memory &other)
			: m_bitSize(other.m_bitSize), m_locationCount(other.m_locationCount), m_bus(nullptr)
		{
			m_storage = new uint64_t[m_locationCount];
			for (size_t i = 0; i < m_locationCount; ++i)
			{
				m_storage[i] = other.m_storage[i];
			}
		}

		Memory &operator=(const Memory &rhs)
		{
			if (this != &rhs)
			{
				delete[] m_storage;
				m_bitSize = rhs.m_bitSize;
				m_locationCount = rhs.m_locationCount;
				m_storage = new uint64_t[m_locationCount];
				for (size_t i = 0; i < m_locationCount; ++i)
				{
					m_storage[i] = rhs.m_storage[i];
				}
				m_bus = nullptr;
			}
			return *this;
		}

		virtual ~Memory()
		{
			delete[] m_storage;
		}

		size_t locations() const { return m_locationCount; }
		size_t bits() const { return m_bitSize; }

		void link(BusCom *bus)
		{
			if (bus && bus->addr().size() <= m_locationCount && bus->data().size() == m_bitSize)
			{
				m_bus = bus;
			}
		}

		void unlink()
		{
			m_bus = nullptr;
		}

		bool configured() const
		{
			return (m_storage != nullptr && m_bus != nullptr);
		}

		void process()
		{
			if (configured())
			{
				if ((value(m_bus->ctrl()) & 1) == 0)
				{
					read();
				}
				else
				{
					write();
				}
			}
		}

		std::string toString() const override
		{
			std::ostringstream out;
			for (size_t i = 0; i < m_locationCount; ++i)
			{
				out << i << ": " << m_storage[i] << "\n";
			}
			return out.str();
		}

	private:
		size_t m_bitSize;
		size_t m_locationCount;
		uint64_t *m_storage;
		BusCom *m_bus;

		void read()
		{
			if (configured())
			{
				size_t address = value(m_bus->addr());
				if (address < m_locationCount)
				{
					m_storage[address] = value(m_bus->data());
				}
			}
		}

		void write()
		{
			if (configured())
			{
				size_t address = value(m_bus->addr());
				if (address < m_locationCount)
				{
					uint64_t val = m_storage[address];
					size_t dataSize = m_bus->data().size();
					for (size_t i = 0; i < dataSize; ++i)
					{
						bool bit = (val >> (dataSize - 1 - i)) & 1;
						m_bus->data().set(i, bit);
					}
				}
			}
		}
	};
}

#endif