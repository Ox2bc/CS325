#ifndef FIFO_H
#define FIFO_H

#include <iostream>
#include <string>
#include "Node.h"
#include "HashMap.h"

namespace cal
{
	class FIFOCache : public Cache
	{
	private:
		unsigned int size;

		FIFOCache(const FIFOCache &) = delete;
		FIFOCache &operator=(const FIFOCache &) = delete;

	public:
		FIFOCache() : Cache(5), size(0) {}

		virtual ~FIFOCache() {}

		Node<Block> *read(size_t key) override
		{
			Node<Block> *current = values[key];

			while (current != nullptr)
			{
				if (current->data().tag() == key)
				{
					return current;
				}
				current = current->next();
			}
			return nullptr;
		}

		void write(Block &o) override
		{
			size_t key = o.tag();

			Node<Block> *current = values[key];
			while (current != nullptr)
			{
				if (current->data().tag() == key)
				{
					current->data().content() = o.content();
					return;
				}
				current = current->next();
			}

			Node<Block> *newNode = new Node<Block>(o);
			newNode->prev() = tail;
			newNode->next() = nullptr;

			if (tail != nullptr)
				tail->next() = newNode;
			tail = newNode;

			if (head == nullptr)
				head = newNode;

			Node<Block> *&bucket = values[key];
			newNode->next() = bucket;
			bucket = newNode;

			size++;

			if (size == capacity())
			{
				Node<Block> *toRemove = head;

				head = head->next();
				if (head != nullptr)
					head->prev() = nullptr;
				else
					tail = nullptr;

				size_t removeKey = toRemove->data().tag();
				Node<Block> *&removeBucket = values[removeKey];
				Node<Block> *prev = nullptr;
				Node<Block> *curr = removeBucket;

				while (curr != nullptr)
				{
					if (curr == toRemove)
					{
						if (prev == nullptr)
							removeBucket = curr->next();
						else
							prev->next() = curr->next();
						break;
					}
					prev = curr;
					curr = curr->next();
				}

				delete toRemove;
				size--;
			}
		}
	};
}

#endif
