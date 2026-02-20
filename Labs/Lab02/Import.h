#ifndef IMPORT_H
#define IMPORT_H

#include <fstream>
#include <algorithm>
#include <string>
#include "IAS.h"
#include "Memory.h"

namespace cal
{
    inline void Import(IAS &obj, const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file)
            return;

        std::string line;
        int address = 0;

        while (address < 4096 && std::getline(file, line))
        {
            line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
            if (line.empty())
                break;

            if (!isHex(line) || line.length() > 10)
                break;

            Memory temp;
            std::stringstream ss(line);
            ss >> temp;

            std::string binary = temp.read();

            if (binary.length() < 40)
                binary = std::string(40 - binary.length(), '0') + binary;

            obj[address].write(binary);

            if (binary.find('1') == std::string::npos)
                obj[address].change(false);
            else
                obj[address].change(true);

            address++;
        }
    }
}

#endif