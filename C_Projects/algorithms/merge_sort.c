/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 11:11:12 by agesp             #+#    #+#             */
/*   Updated: 2019/08/09 13:02:21 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#define N 16

typedef struct t_pos
{
	int start;
	int end;
	int med;
}				s_pos;

void merge(int arr[], int tmp[], s_pos *pos)
{
	int start = pos->start;
	int med = pos->med + 1;
	int tmp_start = pos->start;

	printf("%d %d %d\n",pos->start, pos->end, pos->med);

	while (start <= pos->med && med <= pos->end)
	{
		if (arr[start] < arr[med])
			tmp[tmp_start++] = arr[start++];
		else
			tmp[tmp_start++] = arr[med++];
	}
	while (start <= pos->med)
	{
		tmp[tmp_start++] = arr[start++];
	}
	
	start = pos->start;
	while (start <= pos->end)
	{
		arr[start] = tmp[start++];
//		start++;
	}
	
	/*
	for (int i = pos->start; i <= pos->end; i++)
		arr[i] = tmp[i];
		*/
}

void sort(int arr[], int tmp[], int start, int end, char *lol)
{
	int med;

	if (start == end)
		return ;
	med = (start + end) / 2;
	printf("sem %d %d %d %s\n", start, end, med, lol);
	sort(arr, tmp, start, med, "l1");
	sort(arr, tmp, med + 1, end, "l2");

	merge(arr, tmp, &(s_pos){.start = start, .end = end, .med = med});
}

/*
   int main(void)
   {
   int arr[10] = {1, 2, 5, 1, 6, 1, 6, 0, -2, 0};
   int tmp[10] = {1,2,5,1,6,1,6,0,-2,0};

   sort(arr, tmp, 0, 9, "lol");
   for (int i = 0; i < 10; i++)
   {
   printf("%d ", arr[i]);
   }
   printf("%d\n", 1 / 2);

   }
   */

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


	sort(arr, aux, 0, N - 1, "lol");

	if (isSorted(arr)) {
		for (int i = 0; i < N; i++)
			printf("%d ", arr[i]);
	}
	return 0;
}
