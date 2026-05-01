#include <iostream>
#include <string>
#include "Circuit.h"

std::string evaluate(cal::Dev &obj)
{
	return (obj.output()) ? "T" : "F";
}

int main()
{
	cal::Switch a, b, c;
	cal::NotGate na, nb, nc;
	na.input(a);
	nb.input(b);
	nc.input(c);
	cal::OrGate m1, m3, m6, m8;

	// Row 1: TTT -> (¬A v ¬B v ¬C)
	m1.input(na);
	m1.input(nb);
	m1.input(nc);
	// Row 3: TFT -> (¬A v B v ¬C)
	m3.input(na);
	m3.input(b);
	m3.input(nc);
	// Row 6: FTF -> (A v ¬B v C)
	m6.input(a);
	m6.input(nb);
	m6.input(c);
	// Row 8: FFF -> (A v B v C)
	m8.input(a);
	m8.input(b);
	m8.input(c);

	cal::AndGate circuit;
	circuit.input(m1);
	circuit.input(m3);
	circuit.input(m6);
	circuit.input(m8);

	std::cout << "POS Truth Table (Task 04)\n";
	std::cout << "A B C | Result\n";
	for (int i = 0; i < 8; i++)
	{
		std::cout << a << " " << b << " " << c << " |   " << evaluate(circuit) << "\n";

		c.invert();
		if ((i + 1) % 2 == 0)
			b.invert();
		if ((i + 1) % 4 == 0)
			a.invert();
	}
	return 0;
}