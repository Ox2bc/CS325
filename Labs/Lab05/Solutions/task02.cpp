#include <iostream>
#include <string>
#include "Circuit.h"

std::string evaluate(const cal::Dev& obj)
{
	return (obj.output())?("T"):("F");
}

int main()
{
	cal::Switch a(true), c(true);
	cal::Split s;
	cal::NotGate n;
	cal::AndGate b;

	s.input(a);
	n.input(s);
	b.input(s);
	b.input(c);

	std::cout << "Not Truth Table\n";
	std::cout << a << " " << n  << " = " << evaluate(n) << "\n";
	a.invert();
	std::cout << a << " " << n  << " = " << evaluate(n) << "\n";

	a.invert();
	std::cout << "And Truth Table\n";
	std::cout << b  << " = " << evaluate(b) <<  "\n";
	c.invert();
	std::cout << b  << " = " << evaluate(b) <<  "\n";
	a.invert(); //F 
	c.invert(); //T
	std::cout << b  << " = " << evaluate(b) <<  "\n";
	c.invert();
	std::cout << b  << " = " << evaluate(b) <<  "\n";
	return 0;
}