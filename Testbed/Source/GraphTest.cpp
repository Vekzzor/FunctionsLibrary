#include <fstream>
#include <iostream>
#include <string>
#include "Graph.h"

std::string* getCities(std::string citiesFile, int &nrOfCities);
void setConnections(Graph<std::string> &graph, std::string connectionsFile);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int nrOfCities = 0;
	std::string *cities = getCities("C:\\Users\\vikzz\\Desktop\\Visual Studio Projects\\FunctionsLibrary\\Testbed\\Data\\cities.txt", nrOfCities);
	Graph<std::string> test(cities, nrOfCities);
	setConnections(test, "C:\\Users\\vikzz\\Desktop\\Visual Studio Projects\\FunctionsLibrary\\Testbed\\Data\\connections.txt");
	Graph<std::string> test2(test);
	Graph<std::string> test3;
	test3 = test;
	//test3.printShortestPath("Sstad", "Astad");
	int size = 0;
	PathData* res = test3.getShortestPath("Sstad", "Astad", size);
	std::cout << "From: " << "Sstad" << "   To: " << "Astad" << std::endl;
	if (size != 0)
	{
		std::cout << cities[res[0].entityIndex] << " - " << res[0].weight;
		for (int i = 1; i < size; i++)
		{
				std::cout << " - " << cities[res[i].entityIndex] << " - " << res[i].weight;
		}
		std::cout << std::endl << "Total cost: " << res[0].weight << std::endl;
	}
	delete[] res;
	return 0;
}
std::string* getCities(std::string citiesFile, int &nrOfCities)
{
	std::ifstream inFileCities;
	std::string city = "";
	int citynr = 0;
	inFileCities.open(citiesFile);
	bool test = inFileCities.is_open();
	inFileCities >> citynr;
	nrOfCities = citynr;

	std::string *cities = new std::string[nrOfCities];
	for (int i = 0; i < nrOfCities; i++)
	{
		inFileCities >> city;
		cities[i] = city;
	}
	inFileCities.close();
	return cities;
}

void setConnections(Graph<std::string> &graph, std::string connectionsFile)
{
	std::ifstream inFileConnections;
	int nrOfConnections= 0;
	std::string from = " ";
	std::string to = " ";
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