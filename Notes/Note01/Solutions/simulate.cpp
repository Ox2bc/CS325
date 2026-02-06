#include "Memory.h"
#include <fstream>

void LMA(can::Memory regs[],can::Memory locs[])
{
    regs[5].write(regs[6].read());
}

void LDM(can::Memory regs[],can::Memory locs[])
{
    int i = can::toDecimal(regs[3].read());
    regs[6].write(locs[i].read());
}

void STA(can::Memory regs[],can::Memory locs[])
{
    int i = can::toDecimal(regs[3].read());
    locs[i].write(regs[5].read());
}

void LDA(can::Memory regs[],can::Memory locs[])
{
    int i = can::toDecimal(regs[3].read());
    regs[5].write(locs[i].read());
}

std::string twoscom(std::string str)
{
    if(!can::isBinary(str)) {return "";}
    std::string cstr = str;
    bool carry;

    for(int i = 0;i < cstr.length();i += 1)
    {
        if(cstr[i] == '0') {cstr[i] = '1';}
        else {cstr[i] = '0';}
    }

    int n = cstr.length() - 1;

    if(cstr[n] == '1') 
    {
        cstr[n] = '0';
        carry = true;
    }
    else 
    {
        cstr[n] = '1';
        carry = false;
    }
    n -= 1;

    while(carry && n > 0)
    {
        if(cstr[n] == '1') 
        {
            cstr[n] = '0';
        }
        else 
        {
            cstr[n] = '1';
            carry = false;
        }
        n -= 1;
    }

    return cstr;
}

void LDN(can::Memory regs[],can::Memory locs[])
{
    int i = can::toDecimal(regs[3].read());
    regs[5].write(twoscom(locs[i].read()));
}

void ALD(can::Memory regs[],can::Memory locs[])
{
    int i = can::toDecimal(regs[3].read());
    if(locs[i].read()[0] == '0') 
    {
        regs[5].write(locs[i].read());    
    }
    else
    {
        regs[5].write(twoscom(locs[i].read()));
    }
}

void ALN(can::Memory regs[],can::Memory locs[])
{
    int i = can::toDecimal(regs[3].read());
    if(locs[i].read()[0] == '1') 
    {
        regs[5].write(locs[i].read());    
    }
    else
    {
        regs[5].write(twoscom(locs[i].read()));
    }
}

void BRL(can::Memory regs[],can::Memory locs[])
{
    int i = can::toDecimal(regs[3].read());
    regs[2].write(locs[i].read().substr(0,20));    
}

void BRR(can::Memory regs[],can::Memory locs[])
{
    int i = can::toDecimal(regs[3].read());
    regs[2].write(locs[i].read().substr(20,20));    
}

int main()
{
    std::fstream fout("output.txt",std::fstream::out);

    can::Memory regs[7], locs[4096];
    std::string names[7] = {"PC","IR","IBR","MAR","MBR","AC","MQ"};
    
    for(int i = 0;i < 7;i += 1)
    {
        regs[i].name(names[i]);
        fout << regs[i] << "\n";
    }

    for(int i = 0;i < 4096;i += 1)
    {
        if(i < 10) 
        {
            locs[i].name("000" + std::to_string(i));
        }
        else if(i < 100)
        {
            locs[i].name("00" + std::to_string(i));
        }
        else if(i < 1000)
        {
            locs[i].name("0" + std::to_string(i));
        }
        else 
        {
            locs[i].name(std::to_string(i));
        }
    }

    for(int i = 0;i < 4096;i += 1)
    {
        fout << locs[i] << "\n";
    }
    fout.close();
    return 0;
}