#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <iostream>
#include "PriorityQueue.h"

using namespace std;

class PathData
{
public:
	int weight;
	int entityIndex;
	PathData() { this->entityIndex = 0; this->weight = 0; }
	PathData(int weight, int entityIndex) { this->entityIndex = entityIndex; this->weight = weight; }
	~PathData() {};
};

template <typename T>
class Graph
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
	int getPos(T node) const;
public:
	Graph();
	Graph(T nodes[], int nrOfNodes);
	Graph(const Graph& g); // obs! att det verkligen blir en kopia
	virtual ~Graph();
	Graph &operator=(const Graph<T>& g); // obs! att det verkligen
	//blir en kopia
	void addEdge(T from, T to, int cost);
	bool removeEdge(T from, T to);
	bool hasEdge(T from, T to) const;
	void shortestPath(int source) const;
	//Ska skriva ut kortaste vägen
	void printShortestPath(T from, T to) const;
	PathData* getShortestPath(T from, T to, int pathSize);
	int getNumberOfNodes() const;

};

template <typename T>
Graph<T>::Graph()
{
	this->nodeSelector = new PriorityQueue<int>();
	this->nodes = nullptr;
	this->nrOfNodes = 0;
	this->path = nullptr;
	this->connections = nullptr;
}

template <typename T>
Graph<T>::Graph(T nodes[], int nrOfNodes)
{
	this->nodeSelector = new PriorityQueue<int>();
	this->nodes = nodes;
	this->nrOfNodes = nrOfNodes;
	this->path = new DataNode*[this->nrOfNodes];
	this->connections = new int*[this->nrOfNodes];
	for (int i = 0; i < this->nrOfNodes; i++)
	{
		this->connections[i] = new int[this->nrOfNodes];
		this->path[i] = new DataNode(-1, i, nullptr);
		for (int k = 0; k < this->nrOfNodes; k++)
		{
			this->connections[i][k] = -1;
		}
		this->connections[i][i] = 0;
	}
}

template <typename T>
Graph<T>::Graph(const Graph& g)
{
	this->nrOfNodes = g.getNumberOfNodes();
	this->nodeSelector = new PriorityQueue<int>();
	this->nodes = new T[this->nrOfNodes];
	this->path = new DataNode*[this->nrOfNodes];
	this->connections = new int*[this->nrOfNodes];
	for (int i = 0; i < this->nrOfNodes; i++)
	{
		this->nodes[i] = g.nodes[i];
		this->path[i] = new DataNode(-1, i, nullptr);
		this->connections[i] = new int[this->nrOfNodes];
		for (int k = 0; k < this->nrOfNodes; k++)
		{
			this->connections[i][k] = g.connections[i][k];
		}
	}
}// obs! att det verkligen blir en kopia

template <typename T>
Graph<T>::~Graph()
{
	for (int i = 0; i < this->nrOfNodes; i++)
	{
		delete this->path[i];
		delete[] this->connections[i];
	}
	delete this->nodeSelector;
	delete[]this->path;
	delete[]this->nodes;
	delete[]this->connections;
}

template <typename T>
Graph<T>& Graph<T>::operator=(const Graph<T>& g)
{
	if (this != &g)
	{
		if (this->nrOfNodes != g.getNumberOfNodes())
		{
			delete[] this->nodes;
			for (int i = 0; i < this->nrOfNodes; i++)
			{
				delete[] this->path[i];
				delete[] this->connections[i];
			}
			delete[] this->path;
			delete[] this->connections;
			this->nrOfNodes = g.getNumberOfNodes();
			this->nodes = new T[this->nrOfNodes];

			this->path = new DataNode*[this->nrOfNodes];
			this->connections = new int*[this->nrOfNodes];
			for (int i = 0; i < this->nrOfNodes; i++)
			{
				this->path[i] = new DataNode(-1, i, nullptr);
				this->connections[i] = new int[this->nrOfNodes];
			}
		}

		for (int i = 0; i < this->nrOfNodes; i++)
		{
			this->nodes[i] = g.nodes[i];
			for (int k = 0; k < this->nrOfNodes; k++)
			{
				this->connections[i][k] = g.connections[i][k];
			}
		}
	}
	return *this;
}// obs! att det verkligen
 //blir en kopia

template <typename T>
void Graph<T>::addEdge(T from, T to, int cost)
{
	int column = getPos(to);
	int row = getPos(from);
	if (column != -1 && row != -1)
	{
		this->connections[column][row] = cost;

	}

}

template <typename T>
bool Graph<T>::removeEdge(T from, T to)
{
	int column = getPos(to);
	int row = getPos(from);
	bool result = false;
	//this->connections[column][row].city ="";

	if (column != -1 && row != -1)
	{
		this->connections[column][row] = -1;
		result = true;
	}
	//this->connections[column][row].to = "";
	return result;
}

template <typename T>
bool Graph<T>::hasEdge(T from, T to) const
{
	int column = getPos(to);
	int row = getPos(from);

	return (this->connections[column][row] != -1);
}

template <typename T>
void Graph<T>::shortestPath(int source) const
{
	if (this->nodeSelector->size() != 0)
	{
		DataNode *currNode = this->path[source];
		currNode->weight = this->nodeSelector->dequeue();
		for (int i = 0; i < this->nrOfNodes; i++)
		{
			if (this->hasEdge(this->nodes[currNode->entityIndex], this->nodes[i]))
			{
				int distance = this->connections[currNode->entityIndex][i];
				DataNode *linkedNode = this->path[i];
				if (distance != 0 && (linkedNode->weight > currNode->weight + distance || linkedNode->weight == -1))
				{
					linkedNode->weight = currNode->weight + distance;
					linkedNode->prev = currNode;
					this->nodeSelector->enqueue(linkedNode->weight);
				}
			}
		}
		bool result = false;
		for (int i = 0; i < this->nrOfNodes && result != true; i++)
		{
			if (this->path[i]->weight == this->nodeSelector->peek())
			{
				this->shortestPath(this->path[i]->entityIndex);
				result = true;
			}
		}

	}

}

template <typename T>
//Ska skriva ut kortaste vägen
void Graph<T>::printShortestPath(T from, T to) const
{
	for (int i = 0; i < this->nrOfNodes; i++)
	{
		this->path[i]->weight = -1;
		this->path[i]->entityIndex = i;
		this->path[i]->prev = nullptr;
	}
	this->path[this->getPos(from)]->weight = 0;

	this->nodeSelector->enqueue(this->path[this->getPos(from)]->weight);
	this->shortestPath(this->getPos(from));

	DataNode *walker = this->path[this->getPos(to)];
	cout << "From: " << from << "   To: " << to << endl;
	while (walker != nullptr)
	{
		cout << "- " << this->nodes[walker->entityIndex] << " -" << this->path[walker->entityIndex]->weight;
		walker = walker->prev;
	}
	cout << endl << "Total cost: " << this->path[this->getPos(to)]->weight << endl;
}

template <typename T>
PathData* Graph<T>::getShortestPath(T from, T to, int pathSize)
{
	for (int i = 0; i < this->nrOfNodes; i++)
	{
		this->path[i]->weight = -1;
		this->path[i]->entityIndex = i;
		this->path[i]->prev = nullptr;
	}
	this->path[this->getPos(from)]->weight = 0;

	this->nodeSelector->enqueue(this->path[this->getPos(from)]->weight);
	this->shortestPath(this->getPos(from));

	DataNode *walker = this->path[this->getPos(to)];
	int i = 0;
	while (walker != nullptr)
	{
		walker = walker->prev;
		i++;
	}

	PathData* result = new PathData[i];// = new PathData<T>(0, this->path[this->getPos(to)]);
	walker = this->path[this->getPos(to)];
	for (int k = 0; k < i; k++)
	{
		result[k].entityIndex = walker->entityIndex;
		result[k].weight = this->path[walker->entityIndex]->weight;
		walker = walker->prev;
	}
	pathSize = i;
	return result;
}



template <typename T>
int Graph<T>::getNumberOfNodes() const
{
	return this->nrOfNodes;
}

template <typename T>
int Graph<T>::getPos(T node) const
{
	int result = -1;
	for (int i = 0; i < this->nrOfNodes && (result == -1); i++)
	{
		if (this->nodes[i] == node)
		{
			result = i;
		}
	}
	return result;
}

#endif
