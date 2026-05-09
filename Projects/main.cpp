#include "Dev.h"
#include "Switch.h"
#include "Split.h"
#include "Word.h"
#include "Gate.h"
#include "Port.h"
#include "Socket.h"
#include "gates.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cctype>

using namespace cap;
using namespace std;

void buildRCircuit(Split &portA, Split &portB, Split &portCin, Split &op, Socket &outR)
{
	XORGate *xor1_R = new XORGate();
	XORGate *xor2_R = new XORGate();
	XORGate *xor3_R = new XORGate();

	xor1_R->input(portB);
	xor1_R->input(op);

	xor2_R->input(portA);
	xor2_R->input(*xor1_R);

	xor3_R->input(*xor2_R);
	xor3_R->input(portCin);

	outR.source(*xor3_R);
}

void buildCCircuit(Split &portA, Split &portB, Split &portCin, Split &op, Socket &outC)
{
	XORGate *xor_bop_C = new XORGate();
	ANDGate *and1_C = new ANDGate();
	Split *split_bop = new Split();
	ANDGate *and2_C = new ANDGate();
	ANDGate *and3_C = new ANDGate();
	ORGate *or_final_C = new ORGate();

	xor_bop_C->input(portB);
	xor_bop_C->input(op);
	split_bop->input(*xor_bop_C);

	and1_C->input(portA);
	and1_C->input(*split_bop);

	and2_C->input(portA);
	and2_C->input(portCin);

	and3_C->input(*split_bop);
	and3_C->input(portCin);

	or_final_C->input(*and1_C);
	or_final_C->input(*and2_C);
	or_final_C->input(*and3_C);

	outC.source(*or_final_C);
}

int main()
{
	// Part D
	Word A_input("11110000");
	Word B_input("11001100");
	Word Cin_input("10101010");

	// Part E
	Word R(8);
	Word C(8);

	// Parts F & G
	Port portA_raw, portB_raw, portCin_raw;
	portA_raw.input(A_input);
	portB_raw.input(B_input);
	portCin_raw.input(Cin_input);

	Split splitA_main, splitB_main, splitCin_main;
	splitA_main.input(portA_raw);
	splitB_main.input(portB_raw);
	splitCin_main.input(portCin_raw);

	Split splitA_R, splitB_R, splitCin_R;
	splitA_R.input(splitA_main);
	splitB_R.input(splitB_main);
	splitCin_R.input(splitCin_main);

	Split splitA_C, splitB_C, splitCin_C;
	splitA_C.input(splitA_main);
	splitB_C.input(splitB_main);
	splitCin_C.input(splitCin_main);

	Switch op_switch(false);
	Split split_op_main;
	split_op_main.input(op_switch);

	Split split_op_R, split_op_C;
	split_op_R.input(split_op_main);
	split_op_C.input(split_op_main);

	Socket socketR, socketC;

	buildRCircuit(splitA_R, splitB_R, splitCin_R, split_op_R, socketR);
	buildCCircuit(splitA_C, splitB_C, splitCin_C, split_op_C, socketC);

	socketR.destination(R);
	socketC.destination(C);

	// Part H - TEST CASE 1: Addition
	cout << "TEST CASE 1: Addition (op = 0)" << endl;
	cout << "A   B   Cin | R   C" << endl;
	cout << "------------|------" << endl;

	ofstream file1("test_case_1.txt");
	file1 << "TEST CASE 1: Addition (op = 0)" << endl;
	file1 << "A   B   Cin | R   C" << endl;
	file1 << "------------|------" << endl;

	for (size_t i = 0; i < 8; i++)
	{
		portA_raw.set(i);
		portB_raw.set(i);
		portCin_raw.set(i);
		socketR.set(i);
		socketC.set(i);

		socketR.evaluate();
		socketC.evaluate();

		cout << A_input.get(i) << "   "
			 << B_input.get(i) << "   "
			 << Cin_input.get(i) << "   | "
			 << R.get(i) << "   "
			 << C.get(i) << endl;

		file1 << A_input.get(i) << "   "
			  << B_input.get(i) << "   "
			  << Cin_input.get(i) << "   | "
			  << R.get(i) << "   "
			  << C.get(i) << endl;
	}

	cout << "\nResult R: " << R << endl;
	cout << "Carry C:  " << C << endl
		 << endl;

	file1 << "\nResult R: " << R << endl;
	file1 << "Carry C:  " << C << endl;
	file1.close();

	// Part I - TEST CASE 2: Subtraction
	op_switch.invert();

	Word R_sub(8);
	Word C_sub(8);

	Socket socketR_sub, socketC_sub;

	buildRCircuit(splitA_R, splitB_R, splitCin_R, split_op_R, socketR_sub);
	buildCCircuit(splitA_C, splitB_C, splitCin_C, split_op_C, socketC_sub);

	socketR_sub.destination(R_sub);
	socketC_sub.destination(C_sub);

	cout << "TEST CASE 2: Subtraction (op = 1)" << endl;
	cout << "A   B   Cin | R   C" << endl;
	cout << "------------|------" << endl;

	ofstream file2("test_case_2.txt");
	file2 << "TEST CASE 2: Subtraction (op = 1)" << endl;
	file2 << "A   B   Cin | R   C" << endl;
	file2 << "------------|------" << endl;

	for (size_t i = 0; i < 8; i++)
	{
		portA_raw.set(i);
		portB_raw.set(i);
		portCin_raw.set(i);
		socketR_sub.set(i);
		socketC_sub.set(i);

		socketR_sub.evaluate();
		socketC_sub.evaluate();

		cout << A_input.get(i) << "   "
			 << B_input.get(i) << "   "
			 << Cin_input.get(i) << "   | "
			 << R_sub.get(i) << "   "
			 << C_sub.get(i) << endl;

		file2 << A_input.get(i) << "   "
			  << B_input.get(i) << "   "
			  << Cin_input.get(i) << "   | "
			  << R_sub.get(i) << "   "
			  << C_sub.get(i) << endl;
	}

	cout << "\nResult R: " << R_sub << endl;
	cout << "Carry C:  " << C_sub << endl
		 << endl;

	file2 << "\nResult R: " << R_sub << endl;
	file2 << "Carry C:  " << C_sub << endl;
	file2.close();

	// Parts J & K
	cout << "=== 4-BIT ALU ===" << endl
		 << endl;

	Word A_4bit("0101");
	Word B_4bit("0011");

	Switch op_4bit(false);

	Port portsA_raw[4], portsB_raw[4];
	for (int i = 0; i < 4; i++)
	{
		portsA_raw[i].input(A_4bit);
		portsB_raw[i].input(B_4bit);
		portsA_raw[i].set(3 - i);
		portsB_raw[i].set(3 - i);
	}

	Split splitsA[4], splitsB[4];
	for (int i = 0; i < 4; i++)
	{
		splitsA[i].input(portsA_raw[i]);
		splitsB[i].input(portsB_raw[i]);
	}

	Split split_op_4bit_main;
	split_op_4bit_main.input(op_4bit);
	Split splits_op[4];
	for (int i = 0; i < 4; i++)
	{
		splits_op[i].input(split_op_4bit_main);
	}

	// Part L - TEST CASE 3: 4-bit Addition
	Word R_4bit_add(4);

	cout << "TEST CASE 3: 4-bit Addition" << endl;
	cout << "A = " << A_4bit << " (" << value(A_4bit) << ")" << endl;
	cout << "B = " << B_4bit << " (" << value(B_4bit) << ")" << endl;
	cout << "op = 0 (addition)" << endl;

	Word carry_add[4];
	Port *carry_ports_add[4];
	Split *carry_splits_add[4];
	Socket *result_sockets_add[4];
	Socket *carry_sockets_add[3];

	for (int i = 0; i < 4; i++)
	{
		carry_add[i] = Word(1);
		carry_add[i].set(0, false);
	}

	for (int i = 0; i < 4; i++)
	{
		carry_ports_add[i] = new Port();
		carry_ports_add[i]->input(carry_add[i]);
		carry_ports_add[i]->set(0);
		carry_splits_add[i] = new Split();
		carry_splits_add[i]->input(*carry_ports_add[i]);

		result_sockets_add[i] = new Socket();
		buildRCircuit(splitsA[i], splitsB[i], *carry_splits_add[i], splits_op[i], *result_sockets_add[i]);
		result_sockets_add[i]->destination(R_4bit_add);
		result_sockets_add[i]->set(3 - i);
		result_sockets_add[i]->evaluate();

		if (i < 3)
		{
			carry_sockets_add[i] = new Socket();
			buildCCircuit(splitsA[i], splitsB[i], *carry_splits_add[i], splits_op[i], *carry_sockets_add[i]);
			carry_sockets_add[i]->destination(carry_add[i + 1]);
			carry_sockets_add[i]->set(0);
			carry_sockets_add[i]->evaluate();
		}
	}

	cout << "Result: " << A_4bit << " + " << B_4bit << " = " << R_4bit_add
		 << " (" << value(R_4bit_add) << ")" << endl
		 << endl;

	ofstream file3("test_case_3.txt");
	file3 << "TEST CASE 3: 4-bit Addition" << endl;
	file3 << A_4bit << " + " << B_4bit << " = " << R_4bit_add << endl;
	file3 << value(A_4bit) << " + " << value(B_4bit) << " = " << value(R_4bit_add) << endl;
	file3.close();

	// Part M - TEST CASE 4: 4-bit Subtraction
	op_4bit.invert();
	Word R_4bit_sub(4);

	cout << "TEST CASE 4: 4-bit Subtraction" << endl;
	cout << "A = " << A_4bit << " (" << value(A_4bit) << ")" << endl;
	cout << "B = " << B_4bit << " (" << value(B_4bit) << ")" << endl;
	cout << "op = 1 (subtraction)" << endl;

	Word carry_sub[4];
	Port *carry_ports_sub[4];
	Split *carry_splits_sub[4];
	Socket *result_sockets_sub[4];
	Socket *carry_sockets_sub[3];

	for (int i = 0; i < 4; i++)
	{
		carry_sub[i] = Word(1);
		carry_sub[i].set(0, (i == 0) ? true : false);
	}

	for (int i = 0; i < 4; i++)
	{
		carry_ports_sub[i] = new Port();
		carry_ports_sub[i]->input(carry_sub[i]);
		carry_ports_sub[i]->set(0);
		carry_splits_sub[i] = new Split();
		carry_splits_sub[i]->input(*carry_ports_sub[i]);

		result_sockets_sub[i] = new Socket();
		buildRCircuit(splitsA[i], splitsB[i], *carry_splits_sub[i], splits_op[i], *result_sockets_sub[i]);
		result_sockets_sub[i]->destination(R_4bit_sub);
		result_sockets_sub[i]->set(3 - i);
		result_sockets_sub[i]->evaluate();

		if (i < 3)
		{
			carry_sockets_sub[i] = new Socket();
			buildCCircuit(splitsA[i], splitsB[i], *carry_splits_sub[i], splits_op[i], *carry_sockets_sub[i]);
			carry_sockets_sub[i]->destination(carry_sub[i + 1]);
			carry_sockets_sub[i]->set(0);
			carry_sockets_sub[i]->evaluate();
		}
	}

	cout << "Result: " << A_4bit << " - " << B_4bit << " = " << R_4bit_sub
		 << " (" << value(R_4bit_sub) << ")" << endl
		 << endl;

	ofstream file4("test_case_4.txt");
	file4 << "TEST CASE 4: 4-bit Subtraction" << endl;
	file4 << A_4bit << " - " << B_4bit << " = " << R_4bit_sub << endl;
	file4 << value(A_4bit) << " - " << value(B_4bit) << " = " << value(R_4bit_sub) << endl;
	file4.close();

	return 0;
}