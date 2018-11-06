#include "Graph.h"
#include <fstream>
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
void Graph<T>::addEdge(T from, T to, int distance)
{
	int column = getPos(to);
	int row = getPos(from);
	if (column != -1 && row != -1)
	{
		this->connections[column][row] = distance;
		
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
	
	return (this->connections[column][row] !=-1);
}

template <typename T>
void Graph<T>::shortestPath(int source) const
{
	if(this->nodeSelector->size() != 0)
	{
		DataNode *currNode = this->path[source];
		currNode->weight = this->nodeSelector->dequeue();
		for (int i = 0; i < this->nrOfNodes; i++)
		{
			if (this->hasEdge(this->nodes[currNode->entityIndex], this->nodes[i]))
			{
				int distance = this->connections[currNode->entityIndex][i];
				DataNode *linkedNode = this->path[i];
				if (distance != 0 && (linkedNode->weight > currNode->weight+ distance || linkedNode->weight == -1))
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
		cout <<"- " << this->nodes[walker->entityIndex] << " -" << this->path[walker->entityIndex]->weight;
		walker = walker->prev;
	}
	cout <<endl << "Total cost: " <<this->path[this->getPos(to)]->weight << endl;
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