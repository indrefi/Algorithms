/*
Indre Ionut Grupa 30223

QuickSort si HeapSort

Se poate observa din rezultatele grafice ca metoda QuickSort este mult mai rapida
decat cea HeapSort datorita faptului ca efectueaza mult mai putine operatii ceea 
ce reduce considerabil complexitatea aceteia. 
Se poate observa ca metoda QuickSort are complexitatea in caz average si best de O(n log n)
in cazul worst cand pivotul este primul si elementele sunt ordonate crescator
(ceea ce face ca algoritmul sa efectueze operatii multiple pe fiecare element) 
face ca aceasta sa creasca la O(n^2).

*/
# include <stdio.h>
# include <conio.h>
# include "profiler.h"
Profiler profiler("profiler");

int heapSize;
int vectorSize;

// Worst Case O(n^2) O (n log n)  
void QuickSort(int vector[], int st, int dr)
{
 int pivot, j, temp, i;

 profiler.countOperation("Comparatii QuickSort", vectorSize);
 if(st < dr)
 {

  pivot = st;
  i = st;
  j = dr;

  while(i<j)
  {
   while( (vector[i] <= vector[pivot]) && (i<dr) )
   {
    i++;
   }
   while(vector[j] > vector[pivot])
   {
    j--;
   }
	
   profiler.countOperation("Comparatii QuickSort", vectorSize);
   
   if(i < j)
   {
	profiler.countOperation("Atrbuiri QuickSort", vectorSize, 3);
    temp = vector[i];
    vector[i] = vector[j];
    vector[j] = temp;
   }

  } // while i-j
 
  temp = vector[pivot];
  vector[pivot] = vector[j];
  vector[j] = temp;
  profiler.countOperation("Atrbuiri QuickSort", vectorSize, 3);
  
  QuickSort(vector, st, j-1);
  QuickSort(vector, j+1, dr);

 } //if st-dr
} //quick


int Partition(int vector[], int p, int r) 
{
	int x = vector[r];
	profiler.countOperation("Atribuiri QuickSort", vectorSize);
	int j = p - 1;
	for (int i = p; i < r; i++) 
	{
		profiler.countOperation("Comparatii QuickSort", vectorSize);
		if (vector[i] <= x) 
		{
			j = j + 1;
			int temp = vector[j];
			vector[j] = vector[i];
			vector[i] = temp;
			profiler.countOperation("Atribuiri QuickSort",vectorSize, 3);
		}
	}

	vector[r] = vector[j + 1];
	vector[j + 1] = x;
	profiler.countOperation("Atribuiri QuickSort",vectorSize, 2);
	return (j + 1);
}

void QuickSort2(int vector[], int p, int r) 
{
	if (p < r) 
	{
		int q = Partition(vector, p, r);
		QuickSort(vector, p, q - 1);
		QuickSort(vector, q + 1, r);
	}
}

// O(lg n)
void MaxHeapify(int vector[], int i)
{
	int left = ((2 * i) + 1);     
	int right = ((2 * i) + 2);
	int largest;

	if ((left < heapSize))
	{
		profiler.countOperation("Comparatii HeapSort", vectorSize);
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
		profiler.countOperation("Comparatii HeapSort", vectorSize);
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
		profiler.countOperation("Atribuiri HeapSort", vectorSize, 3);
		MaxHeapify(vector, largest);
	}
}

// O(n)
void BuildMaxHeapBOTTOM(int vector[])
{
	for (int i = (heapSize - 1) / 2; i >= 0; i--)
	{
		MaxHeapify(vector, i);
	}
}
// O(n lg n)
void HeapSort(int vector[])
{
	BuildMaxHeapBOTTOM(vector);

	for (int i = heapSize; i > 0; i--)
	{
		int swap = vector[0];
		vector[0] = vector[heapSize - 1];
		vector[heapSize - 1] = swap;
		heapSize = heapSize - 1;
		profiler.countOperation("Atribuiri HeapSort", vectorSize, 3);
		MaxHeapify(vector, 0);
	}
}

int main()
{
	int selectie, i;
	
	printf("1- Demonstratie 2-Best Case 3-Average Case 4- Worst Case \n");
	scanf("%d", &selectie);

	switch(selectie)
	{
	case 1:
		{
			int vector1[10] = {6,97,48,45,2,86,267,3,5,23}, vector2[10] = {6,97,48,45,2,86,267,3,5,23};
			heapSize = 10;
			vectorSize = 10;
			
			printf(" HeapSort \n");
			HeapSort(vector1);
			for (i = 1; i < vectorSize; i++)
	        {
			printf("%d ", vector1[i]);
			}

			printf("\n QuickSort \n");
			QuickSort2(vector2,0,9);
			for (i = 1; i < vectorSize; i++)
	        {
			printf("%d ", vector2[i]);
			}

		} //case1
		break;
	case 2:
		{
			// Best case pt quickSort trebuie creat manual pentru a face alegerea pivotului cat mai eficienta
			// Ex: 4 1 3 2 6 5 7

			int vector1[7] = {4,1,3,2,6,5,7}, vector2[7] = {4,1,3,2,6,5,7};
			heapSize = 7;
			vectorSize = 7;

			printf(" HeapSort \n");
			HeapSort(vector1);
			for (i = 1; i < vectorSize; i++)
	        {
			printf("%d ", vector1[i]);
			}

			printf("\n QuickSort \n");
			QuickSort2(vector2,0,6);
			for (i = 1; i < vectorSize; i++)
	        {
			printf("%d ", vector2[i]);
			}

		} //case2
		break;
	case 3:
		{
			int size;
			int vector1[10000], vector2[10000];

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
					
				HeapSort(vector1);
				QuickSort2(vector2,0,size);
				printf("apelat");
				}
			}
		} //case3
		break;
	case 4:
		{
			//elementele sunt gata sortate crescator
			int size;
			int vector1[10000], vector2[10000];

			for (size = 100; size <= 10000; size += 100)
			{
				for (int repeat = 0; repeat < 5; repeat++)
				{
					heapSize = size;
					vectorSize = size;

					FillRandomArray(vector1, size, 0, 10000, false, 1);

					for (int i = 0; i < size; i++)
					{
						vector2[i] = vector1[i];
					}
					
				HeapSort(vector1);
				QuickSort2(vector2,0,size);
				printf("apelat");
				}
			}
		} //case4
		break;
	default:
		printf("Selectie invalida! \n");
		break;
	} // switch
	
	profiler.createGroup("Comparatii","Comparatii QuickSort","Comparatii HeapSort");
	profiler.createGroup("Atribuiri","Atribuiri QuickSort","Atribuiri HeapSort");
	profiler.addSeries("Total operatii QuickSort","Comparatii QuickSort","Atribuiri QuickSort");
	profiler.addSeries("Total operatii HeapSort","Comparatii HeapSort","Atribuiri HeapSort");
	profiler.createGroup("Total operatii","Total operatii QuickSort","Total operatii HeapSort");
	profiler.showReport();

	getch();
	return(0);
} //main