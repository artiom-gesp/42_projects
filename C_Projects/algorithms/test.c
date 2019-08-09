#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 15


void Merge(int arr[], int aux[], int low, int mid, int high)
{
	int k = low, i = low, j = mid + 1;


	while (i <= mid && j <= high) 
	{
		if (arr[i] < arr[j])
			aux[k++] = arr[i++];
		else
			aux[k++] = arr[j++];
	}


	while (i <= mid)
		aux[k++] = arr[i++];




	for (int i = low; i <= high; i++)
		arr[i] = aux[i];
}


void MergeSort(int arr[], int aux[], int low, int high)
{

	if (high == low)    // if run size == 1
		return;


	int mid = ((high + low) / 2);
	printf("%d %d %d\n", mid, low, high);




	MergeSort(arr, aux, low, mid);     // split / merge left half
	MergeSort(arr, aux, mid + 1, high); // split / merge right half

	Merge(arr, aux, low, mid, high);    // merge the two half runs
}


int isSorted(int arr[])
{
	int prev = arr[0];
	for (int i = 1; i < N; i++) {
		if (prev > arr[i]) {
			printf("MergeSort Fails!!");
			return 0;
		}
		prev = arr[i];
	}

	return 1;
}


int main()
{
	int arr[N], aux[N];
	srand(time(NULL));


	for (int i = 0; i < N; i++)
		aux[i] = arr[i] = (rand() % 100) - 50;


	MergeSort(arr, aux, 0, N - 1);

	if (isSorted(arr)) {
		for (int i = 0; i < N; i++)
			printf("%d ", arr[i]);
	}
	return 0;
}
