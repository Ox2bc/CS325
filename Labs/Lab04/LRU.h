#ifndef LRU_H
#define LRU_H

#include <iostream>
#include <string>
#include "Node.h"
#include "HashMap.h"

namespace cal
{
	class LRUCache : public Cache
	{
	private:
		unsigned int size;

		LRUCache(const LRUCache &) = delete;
		LRUCache &operator=(const LRUCache &) = delete;

		// Helper Func.
		void moveToHead(Node<Block> *node)
		{
			if (node == nullptr || node == head)
				return;

			if (node->prev() != nullptr)
				node->prev()->next() = node->next();
			if (node->next() != nullptr)
				node->next()->prev() = node->prev();

			if (node == tail)
				tail = node->prev();

			node->prev() = nullptr;
			node->next() = head;
			if (head != nullptr)
				head->prev() = node;

			head = node;

			if (tail == nullptr)
				tail = head;
		}

	public:
		LRUCache() : Cache(5), size(0) {}

		virtual ~LRUCache() {}

		Node<Block> *read(size_t key) override
		{
			Node<Block> *current = values[key];

			while (current != nullptr)
			{
				if (current->data().tag() == key)
				{
					moveToHead(current);
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
					moveToHead(current);
					return;
				}
				current = current->next();
			}

			Node<Block> *newNode = new Node<Block>(o);
			newNode->prev() = nullptr;
			newNode->next() = head;

			if (head != nullptr)
				head->prev() = newNode;
			head = newNode;

			if (tail == nullptr)
				tail = newNode;

			Node<Block> *&bucket = values[key];
			newNode->next() = bucket;
			bucket = newNode;

			size++;

			if (size == capacity())
			{
				Node<Block> *toRemove = tail;

				if (tail->prev() != nullptr)
				{
					tail = tail->prev();
					tail->next() = nullptr;
				}
				else
				{
					head = tail = nullptr;
				}

				size_t removeKey = toRemove->data().tag();
				Node<Block> *&bucket = values[removeKey];
				Node<Block> *prev = nullptr;
				Node<Block> *curr = bucket;

				while (curr != nullptr)
				{
					if (curr == toRemove)
					{
						if (prev == nullptr)
							bucket = curr->next();
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
