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
	cal::AndGate m2, m4, m5, m7;

	// Row 2: TTF -> (A ^ B ^ ¬C)
	m2.input(a);
	m2.input(b);
	m2.input(nc);
	// Row 4: TFF -> (A ^ ¬B ^ ¬C)
	m4.input(a);
	m4.input(nb);
	m4.input(nc);
	// Row 5: FTT -> (¬A ^ B ^ C)
	m5.input(na);
	m5.input(b);
	m5.input(c);
	// Row 7: FFT -> (¬A ^ ¬B ^ C)
	m7.input(na);
	m7.input(nb);
	m7.input(c);

	// Final Sum (OR gate)
	cal::OrGate circuit;
	circuit.input(m2);
	circuit.input(m4);
	circuit.input(m5);
	circuit.input(m7);

	std::cout << "SOP Truth Table (Task 05)\n";
	std::cout << "A B C | Result\n";
	a.invert();
	b.invert();
	c.invert();

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