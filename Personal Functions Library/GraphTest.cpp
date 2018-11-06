#include <fstream>
#include "Source/Graph.h"
#include <iostream>
#include <string>
#include <crtdbg.h>
using namespace std;

string* getCities(string citiesFile, int &nrOfCities /*string cities[]*/);
void setConnections(Graph<string> &graph, string connectionsFile);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int nrOfCities = 0;
	string *cities = getCities("cities.txt", nrOfCities);
	Graph<string> test(cities, nrOfCities);
	setConnections(test, "connections.txt");
	Graph<string> test2(test);
	Graph<string> test3;
	test3 = test;
	//test3.printShortestPath("Sstad", "Astad");
	int size = 0;
	PathData* res = test3.getShortestPath("Sstad", "Astad", size);
	cout << "From: " << "Sstad" << "   To: " << "Astad" << endl;
	for (int i = 0; i < size; i++)
	{
			cout << "- " << cities[res[i].entityIndex] << " -" << res[i].weight;
	}
	cout << endl << "Total cost: " << res[0].weight << endl;
	delete[] res;
	return 0;
}
string* getCities(string citiesFile, int &nrOfCities)
{
	ifstream inFileCities;
	string city = "";
	int citynr = 0;
	inFileCities.open(citiesFile);
	inFileCities >> citynr;
	nrOfCities = citynr;

	string *cities = new string[nrOfCities];
	for (int i = 0; i < nrOfCities; i++)
	{
		inFileCities >> city;
		cities[i] = city;
	}
	inFileCities.close();
	return cities;
}

void setConnections(Graph<string> &graph, string connectionsFile)
{
	ifstream inFileConnections;
	int nrOfConnections= 0;
	string from = " ";
	string to = " ";
	int distance = 0;
	inFileConnections.open(connectionsFile);
	inFileConnections >> nrOfConnections;
	for (int i = 0; i < nrOfConnections; i++)
	{
		inFileConnections.ignore();
		inFileConnections >> from;
		inFileConnections >> to;
		inFileConnections >> distance;
		graph.addEdge(from, to, distance);
		graph.addEdge(to, from, distance);
	}
	inFileConnections.close();
}