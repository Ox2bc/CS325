#include "Dev.h"
#include "Gate.h"
#include "Port.h"
#include "Word.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace cae;
using namespace std;

// Part (a): F2 Gate Class
class F2 : public Gate
{
private:
    F2(const F2 &) = delete;
    F2 &operator=(const F2 &) = delete;

public:
    F2() : Gate(3, 3) {}

    ~F2() {}

    bool output() const override
    {
        if (!valid())
            return false;

        bool A = at(0).output();
        bool B = at(1).output();
        bool C = at(2).output();

        // F2 = ABC + AB'C + A'BC + A'BC'
        return (A && B && C) || (A && !B && C) || (!A && B && C) || (!A && B && !C);
    }

    string toString() const override
    {
        if (output())
            return "T";
        else
            return "F";
    }
};

int main()
{
    Word word1("11110000");
    Word word2("11001100");
    Word word3("10101010");

    Port portA, portB, portC;
    portA.input(word1);
    portB.input(word2);
    portC.input(word3);

    F2 f2_gate;
    f2_gate.input(portA);
    f2_gate.input(portB);
    f2_gate.input(portC);

    cout << "Truth Table:" << endl;
    cout << "A   B   C   | F2" << endl;
    cout << "------------|----" << endl;

    for (size_t i = 0; i < 8; i++)
    {
        portA.set(i);
        portB.set(i);
        portC.set(i);

        cout << portA << "   "
             << portB << "   "
             << portC << "   | "
             << f2_gate << endl;
    }

    return 0;
}