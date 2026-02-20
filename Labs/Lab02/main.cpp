#include <iostream>
#include <fstream>
#include "IAS.h"
#include "Decode.h"
#include "Import.h"
#include "Memory.h"

using namespace cal;

void simulate(IAS &obj, std::ofstream &out)
{
	bool running = true;

	while (running)
	{

		obj(3).write(obj(0).read());
		out << obj << "\n";

		int addr = toDecimal(obj(3).read());
		obj(4).write(obj[addr].read());
		out << obj << "\n";

		obj(1).write(obj(4).read().substr(0, 8));
		out << obj << "\n";

		obj(3).write(obj(4).read().substr(8, 12));
		out << obj << "\n";

		obj(2).write(obj(4).read().substr(20, 20));
		out << obj << "\n";

		if (toDecimal(obj(1).read()) == 0)
		{
			Decode::execute(obj);
			out << obj << "\n";
			break;
		}

		Decode::execute(obj);
		out << obj << "\n";

		if (obj(2).read().find('1') != std::string::npos)
		{
			obj(1).write(obj(2).read().substr(0, 8));
			out << obj << "\n";

			obj(3).write(obj(2).read().substr(8, 12));
			out << obj << "\n";

			if (toDecimal(obj(1).read()) == 0)
			{
				Decode::execute(obj);
				out << obj << "\n";
				break;
			}

			Decode::execute(obj);
			out << obj << "\n";
		}

		int pc = toDecimal(obj(0).read());
		obj(0).write(toBinary(pc + 1));
		out << obj << "\n";
	}
}

int main()
{
	IAS obj;

	Import(obj, "program.txt");
	std::ofstream out("trace.txt");
	simulate(obj, out);
	out.close();
	return 0;
}