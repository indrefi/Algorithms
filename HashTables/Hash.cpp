/*
Ionut Indre
 
Hash Tables

*/

# include <stdio.h>
# include <conio.h>
#include <math.h>
#include "Profiler.h"

#define hashTableSize 9973
int hashTable[hashTableSize];
int vector[hashTableSize];
int Umplere;
#define c1 5
#define c2 7

int foundE = 0;
int foundI = 0;
int countEffort = 0;
double avgEffort;
int maxEffort;

//Worst case O(n)
//Avegrage O(1)

int h (int k, int i) {
	return ((k % hashTableSize + c1*i + c2*(int)pow(i, 2)) % hashTableSize);
}

int hashInsert (int hashTable[], int k ) {

	int i, j;
	i = 0;

	do {

       j = h(k, i); 
	   if (hashTable[j] == 0) {

		   hashTable[j] = k;
		   return j;
	   }
	   else i++;
	} while (i <= hashTableSize);
	//printf(" Hash Table Overflow" );
}

int hashSearch(int hashTable[], int k) {

	int i, j;
	i = 0;

	do {

		j = h(k, i);
		i++;
		if (hashTable[j] == k) {
			countEffort += 1;
			if (i > maxEffort) maxEffort = i;
			return j;
		}
		
	} while ((hashTable[j] != 0) && (i <= hashTableSize));

	countEffort += i;
	//if (i > maxEffort) maxEffort = i;
	return 0;
}

void main() {
	
	int selectie;
	/*int i= 0;
	do {
		printf("%d\n",i++);
	}while(i<=2);
	exit(1);
	*/
	printf("1- Demonstratie 2- HashTable \n");
	scanf("%d", &selectie);

	switch(selectie) {
		
		case 1:{

				int cauta;

				hashInsert(hashTable, 84); 
				hashInsert(hashTable, 36); 
				hashInsert(hashTable, 15);
				hashInsert(hashTable, 23);
				hashInsert(hashTable, 18);
				//hashInsert(hashTable, 23);

				for (int i = 0; i < hashTableSize; i++) {
					if (hashTable[i] != 0)
						printf("%d: %d \n", i , hashTable[i]);
				}

				cauta = hashSearch(hashTable, 23);
				printf("cauta = %d \n", cauta);

				cauta = hashSearch(hashTable, 22);
				printf("cauta = %d \n", cauta);

				getch();
		}
		break;
		
		case 2: {
			
				float factori[5] = {0.8, 0.85, 0.9, 0.95, 0.99 };
	
				int inexistente[1500]; 
				FillRandomArray(inexistente, 1500, 20000, 50000, false, 0);
	
				for ( int i = 0; i < 5; i++) {

					maxEffort=0;
					countEffort = 0;
					foundI =0;
					foundE = 0;
					
					printf("\n Factor de umplere: %0.2f ", factori[i]);

					Umplere = (int) ( factori[i] * hashTableSize );
					FillRandomArray(vector, hashTableSize, 1, 9973, true, 0 );

					for (int i = 0; i < Umplere; i++) {
						hashInsert (hashTable, vector[i]);
					}

					for ( int i = 0; i < 1500 ; i++) {
						int cauta;
						cauta = hashSearch(hashTable, vector[i]);
						if (cauta != 0 ) foundE++;
		
					}

					avgEffort = (double)countEffort / (double)1500;
					printf("\n Afg.Effort: %0.2f", avgEffort);
					printf("\n MaxEffort: %0.2f", maxEffort);
					printf("\n Nr. de elem gasite: %d", foundE);
	
					maxEffort = 0;
					countEffort = 0;
					foundE = 0;
					foundI = 0;
	
					for ( int i = 0; i < 1500 ; i++) {
						int cauta;
						cauta = hashSearch(hashTable, inexistente[i]);
						if (cauta == 0 ) foundI++;
					
					}

					avgEffort = (double)countEffort / (double)1500;
					printf("\n Avg.Effort:%0.2f", avgEffort);
					printf("\n MaxEffort: %0.2f", maxEffort);
					printf("\n Nr. de elemente negasite: %d", foundI);

				}// rep 5

		}//case 2
		break;

		default:
			printf("Selectie invalida! \n");
		break;
	}//switch
	getch();
}//main