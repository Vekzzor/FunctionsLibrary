#ifndef SORTING_H
#define SORTING_H
#include <vector>
#include <future>
#include <iostream>
#include <concrt.h>

class Sort
{
private:
	template <typename T> static void quickSortSeq(T theArray[], int start, int end, bool ascending = true);
	template <typename T> static void quickSortPara(T theArray[], int start, int end, int depthRemaining, bool ascending = true);
	template <typename T> static int partition(T theArray[], int start, int end, bool ascending = true);
	template <typename T> static int partition2(T theArray[], int start, int end);
	template <typename T> static void swapThem(T &item1, T &item2);
public:
	template <typename T> static void quickSort(T theArray[], int size, bool ascending = true);
	template <typename T> static void quickSort(std::vector<T> &vec, int size, bool ascending = true);
	template <typename T> static void insertionSort(T arr[], int n, bool ascending = true);
	template <typename T> static void insertionSort(std::vector<T> &vec, int n, bool ascending = true);
	template <typename T> static bool Sorted(T arr[], int n);
	template <typename T> static bool Sorted(std::vector<T> &vec, int n);
	
};
template<typename T>
int Sort::partition(T theArray[], int start, int end, bool ascending)
{
	T pivotValue = theArray[start];
	int pivotPosition = start;
	for (int i = (start + 1); i <= end; i++)
	{
		if (ascending)
		{
			if (theArray[i] < pivotValue)
			{
				swapThem(theArray[pivotPosition + 1], theArray[i]);
				swapThem(theArray[pivotPosition], theArray[pivotPosition + 1]);
				pivotPosition++;
			}
		}
		else
		{
			if (theArray[i] > pivotValue)
			{
				swapThem(theArray[pivotPosition + 1], theArray[i]);
				swapThem(theArray[pivotPosition], theArray[pivotPosition + 1]);
				pivotPosition++;
			}
		}
		
	}
	return pivotPosition;
}

template<typename T>
int Sort::partition2(T theArray[], int start, int end)
{
	T pivotValue = theArray[end];
	int pivotPosition = start - 1;
	for (int i = (start); i <= end - 1; i++)
	{
		if (theArray[i] < pivotValue)
		{
			pivotPosition++;
			swapThem(theArray[pivotPosition], theArray[i]);
		}
	}
	swapThem(theArray[pivotPosition + 1], theArray[end]);
	return pivotPosition + 1;
}

template<typename T>
void Sort::swapThem(T &item1, T &item2)
{
	T temp = item1;
	item1 = item2;
	item2 = temp;
}


template<typename T>
void Sort::quickSortSeq(T theArray[], int start, int end, bool ascending)
{
	if (start < end)
	{
		int pivotPos = Sort::partition(theArray, start, end);
		quickSortSeq(theArray, start, pivotPos - 1);
		quickSortSeq(theArray, pivotPos + 1, end);
	}

}
template<typename T>
void Sort::quickSortPara(T theArray[], int start, int end, int depthRemaining, bool ascending)
{
	if (start < end)
	{
		int pivotPos = Sort::partition(theArray, start, end, ascending);
		if (depthRemaining > 0)
		{
			auto future1 = std::async(std::launch::async, Sort::quickSortPara<T>, theArray, start, pivotPos - 1, depthRemaining - 1, ascending);
			auto future2 = std::async(std::launch::async, Sort::quickSortPara<T>, theArray, pivotPos + 1, end, depthRemaining - 1, ascending);
			future1.get();
			future2.get();
		}
		else
		{
			quickSortSeq(theArray, start, pivotPos - 1, ascending);
			quickSortSeq(theArray, pivotPos + 1, end, ascending);
		}
	}

}

template<typename T>
void Sort::quickSort(T theArray[], int size, bool ascending)
{
	const int maxTasks = Concurrency::CurrentScheduler::Get()->GetNumberOfVirtualProcessors();
	//(int)LogN(float(maxTasks), 2.0f) + 4   Depth remaining
	quickSortPara(theArray, 0, size - 1, maxTasks,ascending);
}

template<typename T>
void Sort::quickSort(std::vector<T> &vec, int size, bool ascending)
{
	const int maxTasks = Concurrency::CurrentScheduler::Get()->GetNumberOfVirtualProcessors();
	quickSortPara(vec.data(), 0, size - 1, maxTasks, ascending);
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
template<typename T>
bool Sort::Sorted(T arr[], int n)
{
	for (int i = 1; i < n; i++)
	{
		if (arr[i - 1] > arr[i])
		{
			return false;
		}
	}
	return true;
}

template<typename T>
bool Sort::Sorted(std::vector<T> &vec, int n)
{
	for (int i = 1; i < n; i++)
	{
		if (vec[i - 1] > vec[i])
		{
			return false;
		}
	}
	return true;
}
#endif
