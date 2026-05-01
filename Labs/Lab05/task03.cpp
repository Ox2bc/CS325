#include <iostream>
#include <string>
#include "Circuit.h"

std::string evaluate(cal::Dev &obj)
{
	return (obj.output()) ? "T" : "F";
}

int main()
{
	// NOT Equivalent (1 NOR)
	// Rule: Input A into both ports of a NOR gate
	cal::Switch swA(false);
	cal::NorGate notEquiv;
	notEquiv.input(swA);
	notEquiv.input(swA);

	std::cout << "--- NOT Truth Table (NOR Only) ---\n";
	std::cout << swA << " | Output: " << evaluate(notEquiv) << "\n";
	swA.invert();
	std::cout << swA << " | Output: " << evaluate(notEquiv) << "\n\n";

	// OR Equivalent (2 NORs)
	// Rule: OR(A, B) = NOT(NOR(A, B))
	cal::Switch a(false), b(false);
	cal::NorGate norAB, orFinal;

	norAB.input(a);
	norAB.input(b);
	orFinal.input(norAB);
	orFinal.input(norAB);

	std::cout << "--- OR Truth Table (NOR Only) ---\n";
	std::cout << a << " " << b << " = " << evaluate(orFinal) << "\n";
	b.invert(); // FT
	std::cout << a << " " << b << " = " << evaluate(orFinal) << "\n";
	a.invert();
	b.invert(); // TF
	std::cout << a << " " << b << " = " << evaluate(orFinal) << "\n";
	b.invert(); // TT
	std::cout << a << " " << b << " = " << evaluate(orFinal) << "\n\n";

	// AND Equivalent (3 NORs)
	// Rule: AND(A, B) = NOR(NOT(A), NOT(B))
	cal::Switch x(false), y(false);
	cal::NorGate invX, invY, andFinal;

	invX.input(x);
	invX.input(x);
	invY.input(y);
	invY.input(y);

	andFinal.input(invX);
	andFinal.input(invY);

	std::cout << "--- AND Truth Table (NOR Only) ---\n";
	std::cout << x << " " << y << " = " << evaluate(andFinal) << "\n";
	y.invert();
	std::cout << x << " " << y << " = " << evaluate(andFinal) << "\n";
	x.invert();
	y.invert();
	std::cout << x << " " << y << " = " << evaluate(andFinal) << "\n";
	y.invert();
	std::cout << x << " " << y << " = " << evaluate(andFinal) << "\n";

	return 0;
}