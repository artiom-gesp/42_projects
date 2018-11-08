/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainForMem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:41:56 by agesp             #+#    #+#             */
/*   Updated: 2018/11/08 12:30:18 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

struct myStruct
{
	int i;
	int j;
};

void printArray(int arr[], int n) 
{ 
	for (int i=0; i<n; i++) 
		printf("%d ", arr[i]); 
}

int main(int ac, char **av)
{
	int n = 10;
	int ar[n];
	int ar2[n];

	struct myStruct test;
	test.i = 1;
	test.j = 3;
	struct myStruct test2;
	test.i = 1;
	test.j = 3;

//	ft_memset(ar, 4, n*sizeof(ar[0]));
//	memset(ar2, 4, n*sizeof(ar[0]));
//	printArray(ar, n);
//	printArray(ar2, n);

//	char tab[50] = "je suis un caribou";
	ft_memset(&test, 3, sizeof(test));
	printf("ft_memset : %d\n%d\n\n",test.i, test.j);
	char tabi[50] = "je suis un caribou";
	memset(&test2, 3, sizeof(test2));
	printf("memset : %d\n%d\n\n",test2.i, test2.j);

//	printf("memset : %s\n", tabi);
//test bzero
	char bou[20] = "sfkjhskfhdkfhdkf";
	ft_bzero(bou, 2);
	printf("mon bzero : %s\n", bou);
	char bou2[20] = "sfkjhskfhdkfhdkf";
	bzero(bou2, 2);
	printf("bzero : %s\n", bou2);

	char cpy[40] = "Je susi";
	char cpy2[40] = "Je susi";
	printf("my memcpy : %s\n",ft_memcpy(cpy, av[1], atoi(av[2])));
	printf("memcpy : %s\n", memcpy(cpy, av[1], atoi(av[2])));

	//test memcpy
	char str[] = "je suis une chaine de test coucou";
	ft_memcpy (str, av[1], atoi(av[2]));
	char str1[] = "je suis une chaine de test coucou";
	memcpy (str1, av[1], atoi(av[2]));
	printf("ft_memcpy : %s\n",str);
	printf("memcpy : %s\n", str1);

	//test memccpy
	char str5[] = "je suis une chaine de test coucou";
	ft_memccpy (str5 , av[1], av[2][0], atoi(av[3]));
	char str6[] = "je suis une chaine de test coucou";
	memccpy (str6, av[1], av[2][0], atoi(av[3]));
	printf("ft_memccpy : %s\n",str5);
	printf("memccpy : %s\n", str6);

	//test memcmove
	char str3[] = "je suis une chaine de test coucou";
	ft_memmove (str3, av[1], atoi(av[2]));
	char str4[] = "je suis une chaine de test coucou";
	memmove (str4, av[1], atoi(av[2]));
	printf("ft_memmove : %s\n",str3);
	printf("memmove : %s\n", str4);
	
	//test memchr
	printf("memchr : %s\n", memchr(av[1], av[2][0], atoi(av[3])));
	printf("ft_memchr : %s\n", ft_memchr(av[1], av[2][0], atoi(av[3])));

	//test memcmp
	if (memcmp(av[1],av[2], atoi(av[3])) > 0)
		printf("memcmp : av[1] > av[2]\n");
	else if (memcmp(av[1], av[2], atoi(av[3])) == 0)
		printf("memcmp : av[1] == av[2]\n");
	else if(memcmp(av[1], av[2], atoi(av[3])) < 0)
		printf("memcmp : av[1] < av[2]\n");
	if (ft_memcmp(av[1],av[2], atoi(av[3])) > 0)
		printf("ft_memcmp : av[1] > av[2]\n");
	else if (ft_memcmp(av[1], av[2], atoi(av[3])) == 0)
		printf("ft_strcmp : av[1] == av[2]\n");
	else if (ft_memcmp(av[1], av[2], atoi(av[3])) < 0)
		printf("ft_memcmp : av[1] < av[2]\n\n");



	return 0;
}
