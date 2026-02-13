#include "IAS.h"
#include "Decode.h"

int main()
{
	cal::IAS com;
	// Display active memory and registers
	// The default constructor disactivates all memory and registers
	std::cout << com << "\n";

	// Modifies third memory location and makes it active
	com[2].write("1110111101010110100111010100001111010101");
	com[1].write("00001001");	  // IR
	com[3].write("000000000010"); // MAR
	std::cout << com << "\n";

	std::string a;
	std::cin >> a;

	if (cal::isHex(a) && a.length() < 10)
		cal::Decode::execute(com);
	std::cout << com << "\n";
	return 0;
}