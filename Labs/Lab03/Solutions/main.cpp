#include <iostream>
#include <string>
#include "Word.h"
#include "Part.h"
#include "Memory.h"
#include "BusCom.h"
#include "Bus.h"

int main()
{
	/*
	cal::Word w;
	cal::Part p;
	size_t i, j;

	std::cout << "Enter a binary word: ";
	std::cin >> w;

	std::cout << "The word you provided is " << w << "\n";

	std::cout << "Enter the endpoints of the partial: ";
	std::cin >> i >> j;

	p = cal::Part(w,i,j);

	std::cout << "The partial is " << p << "\n";

	p.set(0,!p.get(0));
	p.set(p.size()-1,!p.get(p.size()-1));

	std::cout << "The partial is now " << p << "\n";
	std::cout << "The partial as an unsigned integer is " << value(p) << "\n";
	std::cout << "The word afterward is " << w << "\n";
	

	cal::BusCom b(10,6,2);
	cal::Part p[3];
	cal::Word w;

	std::cout << b << "\n";
	p[0] = b.data();
	p[1] = b.addr();
	p[2] = b.ctrl();

	for(int i = 0;i < 3;i += 1)
	{
		std::cout << "Currently the lines are " << p[i] << "\n";
		std::cout << "Enter new lines: ";
		std::cin >> w;
		transfer(p[i],w);
		std::cout << "New lines are " << p[i] << "\n";
	}

	std::cout << "\nThe bus is now " << b << "\n";
	*/
	cal::Word* locs;

	locs = new cal::Word[256];

	for(size_t i = 0;i < 256;i += 1) {locs[i] = cal::Word(16);}

	for(size_t i = 0;i < 256;i += 1)
	{
		std::cout << i << ": " << locs[i] << "\n";
	}

	delete[] locs;
	return 0;
}
