#ifndef SORTING_H
#define SORTING_H
#include <vector>
class Sort
{
private:
	template<typename T> static int partition(T theArray[], int start, int end);
	template<typename T> static int partition(std::vector<T> &vec, int start, int end);
	template<typename T> static void swapThem(T &item1, T &item2);
public:
	template <typename T> static void quickSort(T theArray[], int start, int end);
	template <typename T> static void quickSort(std::vector<T> &vec, int start, int end);
	template <typename T> static void insertionSort(T arr[], int n, bool ascending);
	template <typename T> static void insertionSort(std::vector<T> &vec, int n, bool ascending);

	
};

template<typename T>
int Sort::partition(T theArray[], int start, int end)
{
	T pivotValue = theArray[start];
	int pivotPosition = start;
	for (int i = (start + 1); i <= end; i++)
	{
		if (theArray[i] < pivotValue)
		{
			swapThem(theArray[pivotPosition + 1], theArray[i]);
			swapThem(theArray[pivotPosition], theArray[pivotPosition + 1]);
			pivotPosition++;
		}
	}
	return pivotPosition;
}

template<typename T>
int Sort::partition(std::vector<T> &vec, int start, int end)
{
	T pivotValue = vec.at(start);
	int pivotPosition = start;
	for (int i = (start + 1); i <= end; i++)
	{
		if (vec.at(i) < pivotValue)
		{
			Sort::swapThem(vec.at(pivotPosition + 1), vec.at(i));
			Sort::swapThem(vec.at(pivotPosition), vec.at(pivotPosition + 1));
			pivotPosition++;
		}
	}
	return pivotPosition;
}

template<typename T>
void Sort::swapThem(T &item1, T &item2)
{
	T temp = item1;
	item1 = item2;
	item2 = temp;
}


template<typename T>
void Sort::quickSort(T theArray[], int start, int end)
{
	if (start < end)
	{
		int pivotPos = Sort::partition(theArray, start, end);
		quickSort(theArray, start, pivotPos - 1);
		quickSort(theArray, pivotPos + 1, end);
	}

}

template<typename T>
void Sort::quickSort(std::vector<T> &vec, int start, int end)
{
	if (start < end)
	{
		int pivotPos = Sort::partition(vec, start, end);
		quickSort(vec, start, pivotPos - 1);
		quickSort(vec, pivotPos + 1, end);
	}

}

template<typename T>
void Sort::insertionSort(T arr[], int n, bool ascending)
{
	int j = 0;
	T key;
	for (int i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;
		if (ascending)
		{ 
			while (j >= 0 && arr[j] > key)
			{
				arr[j + 1] = arr[j];
				j = j - 1;
			}
			arr[j + 1] = key;
		}
		else
		{
			while (j >= 0 && arr[j] < key)
			{
				arr[j + 1] = arr[j];
				j = j - 1;
			}
			arr[j + 1] = key;
		}
	}
}
template<typename T>
void Sort::insertionSort(std::vector<T> &vec, int n, bool ascending)
{
	int j = 0;
	T key;
	for (int i = 1; i < n; i++)
	{
		key = vec.at(i);
		j = i - 1;

		if (ascending)
		{
			while (j >= 0 && vec.at(j) > key)
			{
				vec.at(j + 1) = vec.at(j);
				j = j - 1;
			}
		}
		else
		{
			while (j >= 0 && vec.at(j) < key)
			{
				vec.at(j + 1) = vec.at(j);
				j = j - 1;
			}
		}
		vec.at(j + 1) = key;
	}
}
#endif
