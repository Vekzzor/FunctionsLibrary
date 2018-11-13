#include "FunctionsLibraryPCH.h"
#include <random>
#include <time.h>
#include <cmath>

struct Test
{
	int val;
	Test()
	{
		val = 1;
	};
	bool operator <(const Test& d)
	{
		if (this->val < d.val)
			return true;

		return false;
	};
	bool operator >(const Test& d)
	{
		if (this->val > d.val)
			return true;

		return false;
	};
};

int comparator(const void* a, const void* b) {
	if (*(float*)a < *(float*)b) return -1;
	if (*(float*)a == *(float*)b) return 0;
	if (*(float*)a > *(float*)b) return 1;
}

using namespace std;
int main()
{
	//int arr[] = { 5,2,7,3,9,1 }
	int values = 1000000;
	std::vector<int> v = { 5,2,7,3,9,1 };
	std::vector<Test> tes;
	double time1=0;
	double time2=0;

	Sort::quickSort(v.data(), (int)v.size());
	for (int val : v)
	{
		std::cout << val << std::endl;
	}
	for (int k = 0; k < 100; k++)
	{
		float* arr = new float[values];//{ 5, 2, 7, 3, 9, 1 };
		float* arr2 = new float[values];
		for (int i = 0; i < values; i++)
		{
			arr[i] = ((float)rand()) / ((float)RAND_MAX) * 99 + 1;
			arr2[i] = ((float)rand()) / ((float)RAND_MAX) * 99 + 1;
			//std::cout << arr[i] << std::endl;
			//tes.push_back(Test());
		}
		//Sort::quickSort(v, (int)v.size());
		//Sort::quickSort(tes, (int)tes.size());
		auto start = std::chrono::high_resolution_clock::now();
		Sort::quickSort(arr, values);
		if (!Sort::Sorted(arr, values))
		{
			std::cout << "you Cheat!" << std::endl;
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

//		std::cout << std::endl << "Personal Thread time: " << elapsed_seconds.count() << std::endl;
		time1 += elapsed_seconds.count();
		start = std::chrono::high_resolution_clock::now();
		std::qsort(arr2, values, sizeof(float), comparator);
		end = std::chrono::high_resolution_clock::now();
		elapsed_seconds = end - start;
		//std::cout << std::endl << "Library Thread time: " << elapsed_seconds.count() << std::endl;
		time2 += elapsed_seconds.count();
		delete[] arr;
		delete[] arr2;
	}
	time1 /= 100;
	time2 /= 100;
	std::cout << std::endl << "Personal Thread time: " << time1 << std::endl;
	std::cout << std::endl << "Library Thread time: " << time2 << std::endl;
	//A percentage increase of 236%
	system("pause");
	return 0;
}