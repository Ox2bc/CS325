#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>
#include <string>
#include "Node.h"
#include "Block.h"

namespace cal
{
	class HashMap
	{
	private:
		Node<Block> *data[50];

		static size_t hash(size_t key)
		{
			return key % 50;
		}

	public:
		// Deleted Methods:
		HashMap(const HashMap &) = delete;
		HashMap &operator=(const HashMap &) = delete;

		// Default Constructor
		HashMap()
		{
			for (size_t i = 0; i < 50; ++i)
			{
				data[i] = nullptr;
			}
		}

		// Destructor - Assigns null to each element of data
		~HashMap()
		{
			for (size_t i = 0; i < 50; ++i)
			{
				data[i] = nullptr;
			}
		}

		// bool contains(size_t key)
		bool contains(size_t key) const
		{
			size_t index = hash(key);
			Node<Block> *current = data[index];

			while (current != nullptr)
			{
				if (current->data().tag() == key)
				{
					return true;
				}
				current = current->next();
			}
			return false;
		}

		// Node<Block>*& operator[](size_t key)
		Node<Block> *&operator[](size_t key)
		{
			return data[hash(key)];
		}

		// const Node<Block>*& operator[](size_t key) const
		const Node<Block> *operator[](size_t key) const
		{
			return data[hash(key)];
		}

		// void put(Block& obj)
		void put(Block &obj)
		{
			size_t key = obj.tag();
			size_t index = hash(key);

			Node<Block> *current = data[index];

			while (current != nullptr)
			{
				if (current->data().tag() == key)
				{
					current->data().content() = obj.content();
					return;
				}
				current = current->next();
			}

			Node<Block> *newNode = new Node<Block>(obj);
			newNode->next() = data[index];
			if (data[index] != nullptr)
			{
				data[index]->prev() = newNode;
			}
			data[index] = newNode;
		}
	};
}

#endif
