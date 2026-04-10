#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Word.h"
#include "Node.h"
#include "Block.h"
#include "Cache.h"
#include "LRU.h"
#include "FIFO.h"

using namespace cal;

int main()
{
	srand(time(nullptr));

	const int NUM_BLOCKS = 10;

	Block blocks[NUM_BLOCKS];
	for (int i = 0; i < NUM_BLOCKS; ++i)
	{
		blocks[i].tag() = i + 1;

		blocks[i].content() = Word("Content_" + std::to_string(i + 1));
	}

	LRUCache lruCache;
	FIFOCache fifoCache;

	for (int iteration = 1; iteration <= 20; ++iteration)
	{
		// Step 1
		int randomIndex = std::rand() % NUM_BLOCKS;
		Block selectedBlock = blocks[randomIndex];

		// Step 2
		lruCache.write(selectedBlock);
		fifoCache.write(selectedBlock);

		// Step 3
		std::cout << "Iteration: " << iteration << "\n";
		std::cout << "Selected Block: "
				  << selectedBlock.toString() << "\n\n";
		std::cout << "LRU Cache State:\n";
		std::cout << lruCache.toString() << "\n\n";
		std::cout << "FIFO Cache State:\n";
		std::cout << fifoCache.toString() << "\n";
	}
	return 0;
}
