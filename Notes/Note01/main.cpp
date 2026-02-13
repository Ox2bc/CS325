#include "Memory.h"

int main()
{
	// Testing istream and toString()
	can::Memory mem;
	std::cout << "Enter memory content: ";
	std::cin >> mem;
	std::cout << mem.read() << "\n";
	std::cout << mem << "\n";
	std::cout << can::toDecimal(mem.read()) << "\n";

	int x;
	std::cout << "Enter an integer: ";
	std::cin >> x;
	std::cout << can::toBinary(x) << "\n";

	return 0;
}