#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

void printCache(ofstream &out, int cache[], int currentSize)
{
	out << "[";
	for (int i = 0; i < currentSize; i++)
	{
		out << cache[i];
		if (i != currentSize - 1)
			out << ",";
	}
	out << "]";
}

int main()
{
	int cacheSize;
	string line;

	cout << "Enter cache size (3-8): ";
	cin >> cacheSize;

	if (cacheSize <= 2 || cacheSize > 8)
	{
		cout << "Invalid cache size.\n";
		return 1;
	}

	cin.ignore();

	cout << "Enter sequence of digits (space-separated): ";
	getline(cin, line);

	stringstream ss(line);

	int sequence[100];
	int seqSize = 0;
	string token;

	while (ss >> token)
	{
		for (int i = 0; i < token.length(); i++)
		{
			if (!isdigit(token[i]))
			{
				cout << "Invalid sequence.\n";
				return 1;
			}
		}
		sequence[seqSize++] = atoi(token.c_str());
	}

	if (seqSize == 0)
	{
		cout << "Invalid sequence.\n";
		return 1;
	}

	ofstream outFile("lru_output.txt");
	if (!outFile)
	{
		cout << "Error opening file.\n";
		return 1;
	}

	int cache[8];
	int currentSize = 0;

	printCache(outFile, cache, currentSize);

	// Main loop
	for (int i = 0; i < seqSize; i++)
	{
		int block = sequence[i];
		outFile << " -> ";

		int foundIndex = -1;

		for (int j = 0; j < currentSize; j++)
		{
			if (cache[j] == block)
			{
				foundIndex = j;
				break;
			}
		}
		// HIT
		if (foundIndex != -1)
		{
			int temp = cache[foundIndex];
			for (int j = foundIndex; j > 0; j--)
			{
				cache[j] = cache[j - 1];
			}
			cache[0] = temp;
		}
		else
		{
			// MISS
			if (currentSize < cacheSize)
			{
				for (int j = currentSize; j > 0; j--)
				{
					cache[j] = cache[j - 1];
				}
				cache[0] = block;
				currentSize++;
			}
			else
			{
				for (int j = cacheSize - 1; j > 0; j--)
				{
					cache[j] = cache[j - 1];
				}
				cache[0] = block;
			}
		}

		printCache(outFile, cache, currentSize);
	}

	outFile.close();

	return 0;
}