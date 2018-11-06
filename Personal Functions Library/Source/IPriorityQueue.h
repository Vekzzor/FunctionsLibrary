#ifndef IPRIORITYQUEUE_H
#define IPRIORITYQUEUE_H
template <typename T>
class IPriorityQueue
{
public:
	virtual ~IPriorityQueue() = 0 {};
	virtual void enqueue(const T& element) = 0;
	virtual T dequeue() throw(...) = 0;
	virtual T peek() const throw(...) = 0;
	virtual int size() const = 0;
};

#endif