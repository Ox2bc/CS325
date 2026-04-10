#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <string>
#include "HashMap.h"

namespace cal
{
	class Cache : public Object
	{
	protected:
		Node<Block> *head;
		Node<Block> *tail;
		HashMap values;

	private:
		unsigned int CAP;

		Cache(const Cache &) = delete;
		Cache &operator=(const Cache &) = delete;

	public:
		Cache() : head(nullptr), tail(nullptr), values(), CAP(50) {}

		Cache(unsigned int cap) : head(nullptr), tail(nullptr), values()
		{
			if (cap >= 2 && cap <= 50)
				CAP = cap;
			else
				CAP = 50;
		}

		virtual ~Cache()
		{
			Node<Block> *current = head;
			while (current != nullptr)
			{
				Node<Block> *temp = current;
				current = current->next();
				delete temp;
			}
			head = nullptr;
			tail = nullptr;
		}

		size_t capacity() const
		{
			return CAP;
		}

		std::string toString() const override
		{
			std::stringstream out;
			Node<Block> *current = head;

			while (current != nullptr)
			{
				out << current->data().toString();
				if (current->next() != nullptr)
					out << '\n';
				current = current->next();
			}
			return out.str();
		}

		virtual Node<Block> *read(size_t key) = 0;
		virtual void write(Block &o) = 0;
	};
}

#endif
