#include <iostream>
#include <string>
#include "Word.h"
#include "Part.h"
#include "Memory.h"
#include "BusCom.h"
#include "Bus.h"

using namespace std;
using namespace cal;

void displayMenu()
{
	cout << "\n--- Memory Simulation Menu ---\n";
	cout << "1. Display the memory\n";
	cout << "2. Display the bus\n";
	cout << "3. Modify the data lines of the bus\n";
	cout << "4. Modify the address lines of the bus\n";
	cout << "5. Modify the control lines of the bus\n";
	cout << "6. Run the memory process\n";
	cout << "7. Quit the simulation\n";
	cout << "Enter choice: ";
}

int main()
{
	size_t bitSize, locCount, ctrlSize;

	// --- Configuration Phase ---
	cout << "--- System Configuration ---\n";
	cout << "Enter bit size per memory location [2-40]: ";
	cin >> bitSize;
	cout << "Enter number of memory locations [8-4096]: ";
	cin >> locCount;
	cout << "Enter size of the control sub-bus: ";
	cin >> ctrlSize;

	// Initialize Memory
	Memory mem(bitSize, locCount);

	// Determine Address Bus Size
	// To address N locations, we need ceil(log2(N)) bits.
	size_t addrSize = 0;
	size_t tempLoc = mem.locations() - 1;
	while (tempLoc > 0)
	{
		tempLoc >>= 1;
		addrSize++;
	}
	if (addrSize == 0)
		addrSize = 1; // Minimum 1 bit

	// Initialize Bus (Data, Address, Control)
	BusCom bus(mem.bits(), addrSize, ctrlSize);

	// Link them
	mem.link(&bus);

	// --- Simulation Phase ---
	int choice = 0;
	string inputStr;

	while (choice != 7)
	{
		displayMenu();
		if (!(cin >> choice))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		switch (choice)
		{
		case 1:
			cout << mem.toString() << endl;
			break;

		case 2:
		{
			cout << "[Data: ";
			for (size_t i = 0; i < bus.data().size(); ++i)
			{
				cout << (bus.data().get(i) ? '1' : '0');
			}

			cout << "][Addr: ";
			for (size_t i = 0; i < bus.addr().size(); ++i)
			{
				cout << (bus.addr().get(i) ? '1' : '0');
			}
			cout
				<< "][Ctrl: ";
			for (size_t i = 0; i < bus.ctrl().size(); ++i)
			{
				cout << (bus.ctrl().get(i) ? '1' : '0');
			}
			cout << "]" << endl;
			break;
		}

		case 3:
			cout << bus.data().size() << " bits: ";
			cin >> inputStr;
			setData(bus, inputStr);
			break;

		case 4:
			cout << bus.addr().size() << " bits: ";
			cin >> inputStr;
			setAddr(bus, inputStr);
			break;

		case 5:
			cout << bus.ctrl().size() << " bits: ";
			cin >> inputStr;
			setCtrl(bus, inputStr);
			break;

		case 6:
			mem.process();
			break;

		case 7:
			break;

		default:
			cout << "Choose another choice" << endl;
		}
	}

	return 0;
}
