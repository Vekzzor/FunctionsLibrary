#ifndef MATH_H
#define MATH_H
#pragma once
#include "PriorityQueue.h"
class Math
{
private:
public:
	Math();
	virtual ~Math();
};

#endif // !MATH_H

/*template <typename T>
	class Dijkstras
	{
	private:
		class DataNode
		{
		public:
			int weight;
			int entityIndex;
			DataNode *prev;
			DataNode(int weight, int entityIndex, DataNode *prev) { this->entityIndex = entityIndex; this->weight = weight; this->prev = prev; }
			~DataNode() {};
		};
		int **connections;
		T *nodes;
		PriorityQueue<int> *nodeSelector;
		DataNode **path;
		int nrOfNodes;
	public:
		Dijkstras();
		virtual ~Dijkstras();
	};*/