#include <iostream>
#include <string>
#include "Circuit.h"

std::string evaluate(cal::Dev &obj)
{
	return (obj.output()) ? "T" : "F";
}

int main()
{
	// NOT Equivalent (1 NAND)
	// A single NAND with one input split into both ports acts as a NOT
	cal::Switch swA(false);
	cal::NandGate notEquiv;
	notEquiv.input(swA);
	notEquiv.input(swA);

	std::cout << "--- NOT Truth Table (NAND Only) ---\n";
	std::cout << swA << " | Output: " << evaluate(notEquiv) << "\n";
	swA.invert();
	std::cout << swA << " | Output: " << evaluate(notEquiv) << "\n\n";

	// AND Equivalent (2 NANDs)
	// Rule: AND(A, B) = NOT(NAND(A, B))
	cal::Switch a(false), b(false);
	cal::NandGate nandAB, andFinal;

	nandAB.input(a);
	nandAB.input(b);
	andFinal.input(nandAB);
	andFinal.input(nandAB);

	std::cout << "--- AND Truth Table (NAND Only) ---\n";
	// Sequence: FF, FT, TF, TT
	std::cout << a << " " << b << " = " << evaluate(andFinal) << "\n";
	b.invert(); // FT
	std::cout << a << " " << b << " = " << evaluate(andFinal) << "\n";
	a.invert();
	b.invert(); // TF
	std::cout << a << " " << b << " = " << evaluate(andFinal) << "\n";
	b.invert(); // TT
	std::cout << a << " " << b << " = " << evaluate(andFinal) << "\n\n";

	// OR Equivalent (3 NANDs)
	// Rule: OR(A, B) = NAND(NOT(A), NOT(B))
	cal::Switch x(false), y(false);
	cal::NandGate invX, invY, orFinal;

	invX.input(x);
	invX.input(x);
	invY.input(y);
	invY.input(y);

	orFinal.input(invX);
	orFinal.input(invY);

	std::cout << "--- OR Truth Table (NAND Only) ---\n";
	// Sequence: FF, FT, TF, TT
	std::cout << x << " " << y << " = " << evaluate(orFinal) << "\n";
	y.invert();
	std::cout << x << " " << y << " = " << evaluate(orFinal) << "\n";
	x.invert();
	y.invert();
	std::cout << x << " " << y << " = " << evaluate(orFinal) << "\n";
	y.invert();
	std::cout << x << " " << y << " = " << evaluate(orFinal) << "\n";

	return 0;
}