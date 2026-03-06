#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>
#include <string>
#include <cctype>
#include "Word.h"
#include "IAS.h"

namespace cae
{
	// TASK #1
	Word negate(const Word &word)
	{
		if (word.empty())
		{
			return word;
		}

		size_t size = word.size(); // get size of inputed word
		Word negated(size);		   // create new same sized word

		for (size_t i = 0; i < size; ++i)
		{
			negated.set(i, !word.get(i)); // set each bit to the opposite of original bit
		}

		bool carrybit = true;
		for (size_t i = 0; i < size && carrybit == true; ++i)
		{
			bool current = negated.get(i);
			negated.set(i, current ^ carrybit);
			carrybit = current && carrybit;
		}

		return negated;
	}

	// TASK #2
	void LDM(IAS &obj)
	{
		int address = value(obj(3));
		transfer(obj[address], obj(5));
	}

	// TASK #3
	void LSH(IAS &obj)
	{
		Word &ac = obj(5);
		size_t size = ac.size();
		for (size_t i = size - 1; i > 0; --i)
		{
			ac.set(i, ac.get(i - 1));
		}
		ac.set(0, false);
	}

	// TASK #4
	bool ADD(IAS &obj)
	{
		Word &A = obj(5);
		Word &B = obj(4);

		size_t sizeA = A.size();
		bool carry = false;
		bool signA = A.get(sizeA - 1);
		bool signB = B.get(sizeA - 1);

		for (size_t i = 0; i < sizeA; ++i)
		{
			bool bitA = A.get(i);
			bool bitB = B.get(i);
			A.set(i, bitA ^ bitB ^ carry);
			carry = (bitA && bitB) || (carry && (bitA ^ bitB));
		}

		bool overflow = false;
		if ((signA == signB) && (A.get(sizeA - 1) != signA))
		{
			overflow = true;
		}

		return overflow;
	}
}

#endif
