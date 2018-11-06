#include "Source/Sorting.h"

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


int main()
{
	int arr[] = { 5,2,7,3,9,1 };
	std::vector<int> v = { 5,2,7,3,9,1 };
	std::vector<Test> tes;

	for (int i = 0; i < 10; i++)
	{
		tes.push_back(Test());
	}

	Sort::insertionSort(v, v.size(), 0);
	Sort::insertionSort(arr, v.size(), 1);
	Sort::insertionSort(tes, tes.size(), 0);

	return 0;
}