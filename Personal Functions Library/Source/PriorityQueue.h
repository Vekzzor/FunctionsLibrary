#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include "IPriorityQueue.h"
//#include "List.h"
template <typename T>
class PriorityQueue : public IPriorityQueue<T>
{

private:
	class Node
	{
	public:
		T element;
		//int priority;
		Node *next;
		Node(T element){ this->element = element; this->next = nullptr;  }
		~Node(){}
	};
	int nrOfNodes;
	Node *first;
	//Node *last;
public:
	PriorityQueue();
	~PriorityQueue();
	void enqueue(const T& element);
	T dequeue() throw(...);
	T peek() const throw(...);
	int size() const;
};

template <typename T>
PriorityQueue<T>::PriorityQueue()
{
	this->nrOfNodes = 0;
	this->first = nullptr;

}
template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
	Node *toDelete = this->first;
	while (this->first != nullptr)
	{
		this->first = this->first->next;
		delete toDelete;
		toDelete = this->first;
	}
}
template <typename T>
void PriorityQueue<T>::enqueue(const T& element)
{
	Node *e = new Node(element);
	if (this->first != nullptr)
	{
		if (element < this->first->element)
		{
			e->next = this->first;
			this->first = e;
		}
		else
		{

			Node *walker = this->first;
			while (walker->next != nullptr && walker->next->element < e->element) //obs ordningen
			{
				walker = walker->next;
			}
			e->next = walker->next;
			walker->next = e;
		}
	}
	else
	{
		this->first = e;
	}
	this->nrOfNodes++;
}

template <typename T>
T PriorityQueue<T>::dequeue() throw(...)
{
	if (this->first == nullptr)
	{
		throw "Queue is already empty.";
	}
	else
	{
		Node *toDelete = this->first;
		this->first = this->first->next;
		T result = toDelete->element;
		delete toDelete;
		this->nrOfNodes--;
		return result;
	}
}

template <typename T>
T PriorityQueue<T>::peek() const throw(...)
{
	if (this->first == nullptr)
	{
		throw "Queue is empty";
	}
	return this->first->element;
}

template <typename T>
int PriorityQueue<T>::size()const
{
	return this->nrOfNodes;
}

#endif