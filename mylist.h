#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;
template <typename C>
struct Node {
	C data;
	struct Node* next;
	struct Node* prev;

	Node():next(nullptr),prev(nullptr) {}
	Node(C data):data(data),next(nullptr),prev(nullptr)
	{}
};

template <typename C>
class IdxList {

	C head, tail;
	int _size;

	// friend class IdxListHelper<C>;
public:
	IdxList():head(),tail()
	{
		_size = 0;
		head.next = &tail;
		tail.prev = &head;
		head.prev = &head;
		tail.next = &tail;
	}

	C * begin()
	{
		return head.next;
	}

	C * end()
	{
		return & tail;
	}

	C * rbegin()
	{
		return tail.prev;
	}

	C * rend()
	{
		return & head;
	}

	void push_back(C* data)
	{
		data->next = &tail;
		data->prev = tail.prev;
		data->prev->next = data;
		tail.prev = data;
		_size++;
	}
	
	void push_front(C* data)
	{
		data->prev = &head;
		data->next = head.next;
		data->next->prev = data;
		head.next = data;
		_size++;
	}

	C* erase(C* p)
	{
		C* temp = p->next;
		p->next->prev = p->prev;
		p->prev->next = p->next;
		_size--;
		return temp;
	}

	C* find_prev(C* p)
	{
		if (p != nullptr)
			return p->prev;
		else return nullptr;
	}

	C* find_next(C* p)
	{
		if (p != nullptr)
			return p->next;
		else return nullptr;
	}

	void clear()
	{
		C* p = head.next;

		while (p != &tail)
		{
			p->next->prev = p->prev;
			p->prev->next = p->next;
			p = p->next;
			_size--;
		}
	}

	void unlink()
	{
		head.next = &tail;
		tail.prev = &head;
	}

	int size()
	{
		return _size;
	}

};
template <typename C>
class MyList {

	Node<C> head, tail;
	int _size;
public:
	MyList()
	{
		_size = 0;
		head.next = &tail;
		tail.prev = &head;
		head.prev = &head;
		tail.next = &tail;
	}

	Node<C> * begin()
	{
		return head.next;
	}

	Node<C> * end()
	{
		return & tail;
	}

	Node<C> * rbegin()
	{
		return tail.prev;
	}

	Node<C> * rend()
	{
		return & head;
	}

	void push_back(C data)
	{
		Node<C> * p = new Node<C>(data);
		p->next = &tail;
		p->prev = tail.prev;
		p->prev->next = p;
		tail.prev = p;
		_size++;
	}
	
	void push_front(C data)
	{
		Node<C> * p = new Node<C>(data);
		p->prev = &head;
		p->next = head.next;
		p->next->prev = p;
		head.next = p;
		_size++;
	}

	void erase(Node<C> * p)
	{
		p->next->prev = p->prev;
		p->prev->next = p->next;
		delete(p);
		_size--;
	}

	Node<C>* find_prev(Node<C> * p)
	{
		if (p != nullptr)
			return p->prev;
		else return nullptr;
	}

	Node<C>* find_next(Node<C> * p)
	{
		if (p != nullptr)
			return p->next;
		else return nullptr;
	}

	void clear()
	{
		Node<C> * p = head.next;

		while (p != &tail)
		{
			Node<C> * temp = p;
			p->next->prev = p->prev;
			p->prev->next = p->next;
			p = p->next;
			delete(temp);
			_size--;
		}
	}

	void unlink()
	{
		head.next = nullptr;
		tail.prev = nullptr;
	}

	int size()
	{
		return _size;
	}

};

template <typename C>
class IdxListHelper
{
public:
	static C* ListObjMove(C* p, IdxList<C>& src, IdxList<C>& dst)
	{
		C* pnext = src.erase(p);
		dst.push_front(p);
		return pnext;
	}
};

template <typename C>
struct SkipListNode {
	C data;
	int level;
	struct SkipListNode** next;
	struct SkipListNode** prev;

	void construct_pointer()
	{
		next = new SkipListNode*[level+1];
		prev = new SkipListNode*[level+1];
	}
	SkipListNode(int level):level(level)
	{
		construct_pointer();
	}
	SkipListNode():level(0)
	{
		construct_pointer();
	}
	SkipListNode(C data, int level):data(data),level(level)
	{
		construct_pointer();
	}
};

template <typename C>
class MySkipList {

	SkipListNode<C> head, tail;
	int max_level;
	int _size;

public:
	MySkipList()
	{
		_size = 0;
		max_level = 11;
		head = SkipListNode<C>(max_level);
		tail = SkipListNode<C>(max_level);
		for (int i = 0; i <= max_level; ++i)
		{
			head.next[i] = &tail;
			tail.prev[i] = &head;
			head.prev[i] = &head;
			tail.next[i] = &tail;
		}
	}

	int size()
	{
		return _size;
	}

	int getMaxLevel()
	{
		return max_level;
	}

	int randomLevelGenerator()
	{
		int level = 0;
		while(rand() % 2 && level < max_level - 1)
		    ++level;
		return level;
	}

	SkipListNode<C> * begin()
	{
		return head.next[0];
	}

	SkipListNode<C> * end()
	{
		return & tail;
	}

	SkipListNode<C> * rbegin()
	{
		return tail.prev[0];
	}

	SkipListNode<C> * rend()
	{
		return & head;
	}

	SkipListNode<C> * begin(int level)
	{
		return head.next[level];
	}

	SkipListNode<C>* push_back(C data)
	{
		int level = randomLevelGenerator();
		SkipListNode<C> * p = new SkipListNode<C>(data, level);
		if (tail.prev[0] != rend() && tail.prev[0]->data >= data)
		{
			cerr << "Can't push back: lexicographical order should be maintained in skip list." << endl;
			return nullptr;
		}

		for (int i = 0; i <= level; ++i)
		{
			p->next[i] = &tail;
			p->prev[i] = tail.prev[i];
			p->prev[i]->next[i] = p;
			tail.prev[i] = p;
		}
		_size++;
		return p;
	}
	
	SkipListNode<C>* push_front(C data)
	{
		int level = randomLevelGenerator();
		SkipListNode<C> * p = new SkipListNode<C>(data, level);
		if (head.next[0] != end() && head.next[0]->data <= data)
		{
			cerr << "Can't push front: lexicographical order should be maintained in skip list." << endl;
			return nullptr;
		}

		for (int i = 0; i <= level; ++i)
		{
			p->prev[i] = &head;
			p->next[i] = head.next[i];
			p->next[i]->prev[i] = p;
			head.next[i] = p;
		}
		_size++;
		return p;
	}

	void erase(SkipListNode<C> * p)
	{
		if (p == end() || p == rend())
			cerr << "cann't del head or tail" << endl;
		for (int i = 0; i <= p->level; ++i)
		{
			p->next[i]->prev[i] = p->prev[i];
			p->prev[i]->next[i] = p->next[i];
		}
		delete[](p->next);
		delete[](p->prev);
		delete(p);
		_size--;
	}

	SkipListNode<C>* find_prev(SkipListNode<C> * p)
	{
		if (p != nullptr)
			return p->prev[0];
		else return nullptr;
	}

	SkipListNode<C>* find_next(SkipListNode<C> * p)
	{
		if (p != nullptr)
			return p->next[0];
		else return nullptr;
	}

	SkipListNode<C>* insert(C data)
	{
    	SkipListNode<C> *update[max_level];
    	SkipListNode<C> *curr = &head;

		for (int i = max_level; i >= 0; --i) {
			if (curr->next[i] == &tail || curr->next[i]->data > data)
				update[i] = curr;
			else {
				while (curr->next[i] != &tail && curr->next[i]->data < data)
					curr = curr->next[i];
				if (curr->next[i] != &tail && curr->next[i]->data == data)
					return nullptr;
				update[i] = curr;
			}
		}

		int level = randomLevelGenerator();
		SkipListNode<C> *temp = new SkipListNode<C>(data, level);

		for(int i = 0; i <= level; ++i) {
			temp->next[i] = update[i]->next[i];
			temp->prev[i] = update[i];
			update[i]->next[i] = temp;
			temp->next[i]->prev[i] = temp;
		}
		_size++;
		return temp;
	}

	SkipListNode<C> * checkNode()
	{
		for (SkipListNode<C>* node = &head; node != &tail; node = node->next[0])
		{
			if (node->next[0] == nullptr || node->prev[0] == nullptr)
				return node;
		}
		return nullptr;
	}

	// insert a vector behind the element vec[0];
	void insert_back(const std::vector<C>& vec, int k, SkipListNode<C>* begin, SkipListNode<C>* end)
	{
		C data = vec[0];
    	SkipListNode<C> *update[max_level];
    	SkipListNode<C> *curr = &head;

		// find previous hull & update
		for (int i = max_level; i >= 0; --i) {
			if (curr->next[i] == &tail || curr->next[i]->data > data)
				update[i] = curr;
			else {
				while (curr->next[i] != &tail && curr->next[i]->data < data)
					curr = curr->next[i];
				if (curr->next[i] != &tail && curr->next[i]->data == data)
					update[i] = curr->prev[i];
				update[i] = curr;
			}
		}

		// erase from previous to p
		SkipListNode<C>* q = begin;
		while ( q != end )
		{
			if (q == rend())
			{
				q = q->next[0];
				continue;
			}
			SkipListNode<C>* temp = q->next[0];
			erase(q);
			q = temp;
		}

		for (int i = 0; i <= k-1; ++i)
		{
			if (begin == rend())
				continue;
			int level = randomLevelGenerator();
			SkipListNode<C> *temp = new SkipListNode<C>(vec[i], level);

			for(int i = 0; i <= level; ++i) {
				temp->next[i] = update[i]->next[i];
				temp->prev[i] = update[i];
				update[i]->next[i] = temp;
				temp->next[i]->prev[i] = temp;

				update[i] = temp;
			}
			_size++;
		}
	}

	bool remove(C data)
	{
    	SkipListNode<C> *update[max_level];
    	SkipListNode<C> *curr = &head;

		for (int i = max_level; i >= 0; --i) {
			if (curr->next[i] == &tail || curr->next[i]->data > data)
				update[i] = nullptr;
			else {
				while (curr->next[i] != &tail && curr->next[i]->data < data)
					curr = curr->next[i];
				if (curr->next[i] != &tail && curr->next[i]->data == data)
					update[i] = curr;
				else
					update[i] = nullptr;
			}
		}

		SkipListNode<C> *p = nullptr;
		for (int i = 0; i <= max_level; i++)
		{
			if (update[i] != nullptr)
			{
				p = update[i]->next[i];
				update[i]->next[i] = p->next[i];
				update[i]->next[i]->prev[i] = update[i];
			}
		}

		if (p != nullptr)
		{
			delete[](p->next);
			delete[](p->prev);
			delete(p);
			_size --;
			return true;
		} else {
			return false;
		}
	}

	SkipListNode<C>* find(C data)
	{
    	SkipListNode<C> *curr = &head;

		for (int i = max_level; i >= 0; --i) {
			if (curr->next[i] == &tail || curr->next[i]->data > data)
				continue;
			else {
				while (curr->next[i] != &tail && curr->next[i]->data < data)
					curr = curr->next[i];
				if (curr->next[i] != &tail && curr->next[i]->data == data)
					return curr->next[i];
			}
		}

		return nullptr;
	}

	SkipListNode<C>* search(C data)
	{
		return find(data);
	}

	void clear()
	{
		SkipListNode<C>* p = head.next[0];
		SkipListNode<C>* q = p->next[0];
		while (p != end())
		{
			delete[](p->next);
			delete[](p->prev);
			delete(p);
			p = q;
			q = p->next[0];
		}
		_size = 0;
		for (int i = 0; i <= max_level; i++)
		{
			head.next[i] = &tail;
			tail.prev[i] = &head;
		}
	}
};

#endif
