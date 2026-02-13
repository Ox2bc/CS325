#ifndef DECODE_H
#define DECODE_H

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <cctype>
#include "Object.h"
#include "Memory.h"
#include "IAS.h"

namespace cal
{
	class Decode
	{
	private:
		static void LMA(IAS &obj)
		{
			// AC:5, MQ:6
			obj(5).write(obj(6).read());
		}

		static void LDM(IAS &obj)
		{
			// MAR:3, MQ:6
			int i = toDecimal(obj(3).read());
			// MQ = M(MAR)
			obj(6).write(obj[i].read());
		}

		static void STA(IAS &obj)
		{
			int i = toDecimal(obj(3).read());
			obj[i].write(obj(5).read());
		}

		static void LDA(IAS &obj)
		{
			int i = toDecimal(obj(3).read());
			obj(5).write(obj[i].read());
		}

		static void LDN(IAS &obj)
		{
			int i = toDecimal(obj(3).read());
			obj(5).write(negate(obj[i].read()));
		}

		static void ALD(IAS &obj)
		{
			int i = toDecimal(obj(3).read());
			if (obj[i].read()[0] == '0')
			{
				obj(5).write(obj[i].read());
			}
			else
			{
				obj(5).write(negate(obj[i].read()));
			}
		}

		static void ALN(IAS &obj)
		{
			int i = toDecimal(obj(3).read());
			if (obj[i].read()[0] == '1')
			{
				obj(5).write(obj[i].read());
			}
			else
			{
				obj(5).write(negate(obj[i].read()));
			}
		}

		static void BRL(IAS &obj)
		{
			int i = toDecimal(obj(3).read());
			obj(2).write(obj[i].read().substr(0, 20));
		}

		static void BRR(IAS &obj)
		{
			int i = toDecimal(obj(3).read());
			obj(2).write(obj[i].read().substr(20, 20));
		}

		static void BPL(IAS &obj)
		{
			if (obj(5).read()[0] == '0')
			{
				int i = toDecimal(obj(3).read());
				obj(2).write(obj[i].read().substr(0, 20));
			}
		}

		static void BPR(IAS &obj)
		{
			if (obj(5).read()[0] == '0')
			{
				int i = toDecimal(obj(3).read());
				obj(2).write(obj[i].read().substr(20, 20));
			}
		}

		// Add M(X) to AC; put result in AC
		static void ADD(IAS &obj)
		{
			int i = toDecimal(obj(3).read());
			int a = toDecimal(obj(5).read());
			int b = toDecimal(obj[i].read());
			obj(5).write(toBinary(a + b));
		}

		// Add |M(X)| to AC; put result in AC
		static void AAD(IAS &obj)
		{
			int i = toDecimal(obj(3).read());
			int a = toDecimal(obj(5).read());
			int b = toDecimal(obj[i].read());
			if (b < 0)
			{
				b = std::abs(b);
			}
			obj(5).write(toBinary(a + b));
		}

		// Subtract M(X) to AC; put result in AC
		static void SUB(IAS &obj)
		{
			int i = toDecimal(obj(3).read());
			int a = toDecimal(obj(5).read());
			int b = toDecimal(obj[i].read());
			obj(5).write(toBinary(a - b));
		}

		// Subtract |M(X)| to AC; put result in AC
		static void ASB(IAS &obj)
		{
			int i = toDecimal(obj(3).read());
			int a = toDecimal(obj(5).read());
			int b = toDecimal(obj[i].read());
			if (b < 0)
			{
				b = std::abs(b);
			}
			obj(5).write(toBinary(a - b));
		}

		// Multiply M(X) by MQ; put the most significant bits of result in AC, least significant in MQ
		static void MUL(IAS &obj)
		{
			int i = toDecimal(obj(3).read());
			long long a = toDecimal(obj(6).read());
			long long b = toDecimal(obj[i].read());
			long long product = a * b;

			std::string p = toBinary(product);
			obj(5).write(p.substr(0, 40));
			obj(6).write(p.substr(40, 40));
		}

		static void DIV(IAS &obj)
		{
			int i = toDecimal(obj(3).read());
			long long a = toDecimal(obj(6).read());
			long long b = toDecimal(obj[i].read());
			long long q = a / b;
			long long r = a % b;

			obj(6).write(toBinary(q));
			obj(5).write(toBinary(r));
		}

		static void LSH(IAS &obj)
		{
			long long ac = toDecimal(obj(5).read());
			obj(5).write(toBinary(ac * 2));
		}

		static void RSH(IAS &obj)
		{
			long long ac = toDecimal(obj(5).read());
			obj(5).write(toBinary(ac / 2));
		}

		static void STL(IAS &obj)
		{
			int i = toDecimal(obj(3).read());

			std::string ac = obj(5).read();
			std::string mx = obj[i].read();

			std::string slice = ac.substr(28, 12);
			mx.replace(8, 12, slice);

			obj[i].write(mx);
		}

		static void STR(IAS &obj)
		{
			int i = toDecimal(obj(3).read());

			std::string ac = obj(5).read();
			std::string mx = obj[i].read();

			std::string slice = ac.substr(28, 12);
			mx.replace(28, 12, slice);

			obj[i].write(mx);
		}

		static void HLT(IAS &obj)
		{
			std::exit(0);
		}

	public:
		static void
		execute(IAS &obj)
		{
			int i = toDecimal(obj(1).read());
			if (i == 10)
			{
				LMA(obj);
			}
			else if (i == 9)
			{
				LDM(obj);
			}
			else if (i == 33)
			{
				STA(obj);
			}
			else if (i == 1)
				LDA(obj);
			else if (i == 2)
				LDN(obj);
			else if (i == 3)
				ALD(obj);
			else if (i == 4)
				ALN(obj);
			else if (i == 13)
				BRL(obj);
			else if (i == 14)
				BRR(obj);
			else if (i == 15)
				BPL(obj);
			else if (i == 16)
				BPR(obj);
			else if (i == 5)
				ADD(obj);
			else if (i == 7)
				AAD(obj);
			else if (i == 6)
				SUB(obj);
			else if (i == 8)
				ASB(obj);
			else if (i == 11)
				MUL(obj);
			else if (i == 12)
				DIV(obj);
			else if (i == 18)
				STL(obj);
			else if (i == 19)
				STR(obj);
			else if (i == 20)
				LSH(obj);
			else if (i == 21)
				RSH(obj);
			else if (i == 0)
				HLT(obj);
		}
	};
}

#endif DECODE_H