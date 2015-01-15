/*
Indre Ionut

Comparatie intre BottomUp si Top-down Build Heap

Se poate observa ca abordarea de tip BottonUp este mai eficienta decat TopDown datorita
faptului ca are mai putine apeluri recursive si implicit mai putine operatii efectuate.
Referitor la complexitatea acestora se poate observa ca este aproximativ lineara in cazul average.
Diferenta dintre cele doua fiind data de o constanta,ceea ce face  ca abordarea de tip TopDown sa fie constituita din mai multe operatii efectuate.
Abordarea TopDown este eficienta atunci cand vrem sa inseram valorile dinamic.
*/

#include <iostream>
#include "Profiler.h"

Profiler profiler("profiler");
using namespace std;

int heapSize;
int vectorSize;

void MaxHeapify(int vector[], int i)
{
	int left = ((2 * i) + 1);     
	int right = ((2 * i) + 2);
	int largest;
	if ((left < heapSize))
	{
		profiler.countOperation("TotalOperatiiBottomUP", vectorSize);
		if (vector[left] > vector[i])
		{
			largest = left;
		}
		else
		{
			largest = i;
		}
	
	}
	else
	{
		largest = i;
	}

	if ((right < heapSize))
	{
		profiler.countOperation("TotalOperatiiBottomUP", vectorSize);
		if (vector[right] > vector[largest])
		{
			largest = right;
		}
	}

	if (largest != i)
	{
		int swap = vector[i];
		vector[i] = vector[largest];
		vector[largest] = swap;
		profiler.countOperation("TotalOperatiiBottomUP", vectorSize, 3);
		MaxHeapify(vector, largest);
	}
}

void BuildMaxHeapBOTTOM(int vector[])
{
	for (int i = (heapSize - 1) / 2; i >= 0; i--)
	{
		MaxHeapify(vector, i);
	}
}

void HeapIncreaseKey(int vector[], int i, int key)
{
	profiler.countOperation("TotalOperatiiTopDown", vectorSize);
	if (key < vector[i])
	{
		cout << "Error - Noua Cheie mai mica decat cea curenta";
	}

	profiler.countOperation("TotalOperatiiTopDown", vectorSize);
	vector[i] = key;

	while ((i > 0) && (vector[(i - 1) / 2] < vector[i]))
	{
		profiler.countOperation("TotalOperatiiTopDown", vectorSize);
		int swap = vector[i];
		vector[i] = vector[(i - 1) / 2];
		vector[(i - 1) / 2] = swap;
		profiler.countOperation("TotalOperatiiTopDown", vectorSize,3);
		i = ((i - 1) / 2);
	}
	profiler.countOperation("TotalOperatiiTopDown", vectorSize);
}

void MaxHeapInsert(int vector[], int key)
{
	heapSize = heapSize + 1; 
	profiler.countOperation("TotalOperatiiTopDown", vectorSize);
	vector[heapSize] = INT_MIN;
	HeapIncreaseKey(vector, heapSize, key);
}

void BuildMaxHeapTOP(int vector[])
{
	heapSize = 0;
	for (int i = 1; i <= vectorSize; i++)
	{
		MaxHeapInsert(vector, vector[i]);
	}
}

void main()
{

	//int vector1[10000], vector2[10000];
	int size;

	
	//Demonstratie 
	int i;
	int vector1[]= {5, 13, 2, 25, 7, 17, 20, 8, 4};
	int vector2[]= {5, 13, 2, 25, 7, 17, 20, 8, 4};
	heapSize = 9;
	vectorSize = 9;
	
	cout << "BOTTOM" << endl; 
	BuildMaxHeapBOTTOM(vector1);
	for (i = 0; i < vectorSize; i++)
	{
	cout << vector1[i] << " ";
	}
	cout << " " << endl;
	cout << "TOP" << endl;
	BuildMaxHeapTOP(vector2);
	for (i = 1; i < vectorSize; i++)
	{
		cout << vector2[i] << " ";
	}
	print(vector1);
	system("PAUSE");
	/*
	for (size = 100; size <= 10000; size += 100)
	{
		for (int repeat = 0; repeat < 5; repeat++)
		{
			heapSize = size;
			vectorSize = size;

			FillRandomArray(vector1, size, 0, 10000, false, 0);

			for (int i = 0; i < size; i++)
			{
				vector2[i] = vector1[i];
			}

			BuildMaxHeapBOTTOM(vector1);
			BuildMaxHeapTOP(vector2);
		}
	}
	profiler.createGroup("TotalOperatii - AverageCase", "TotalOperatiiTopDown", "TotalOperatiiBottomUP");
	profiler.showReport();*/
}