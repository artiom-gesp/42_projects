/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 17:52:33 by agesp             #+#    #+#             */
/*   Updated: 2018/11/07 15:37:17 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"
#include "ctype.h"
#include "stdlib.h"

int	main(int ac, char **av)
{
	printf("strlen: %zu\n", strlen(av[1]));
	printf("ft_strlen: %zu\n\n", ft_strlen(av[1]));
	printf("My toupper : %c\n", ft_toupper(av[1][0]));
	printf("toupper :  %c\n\n", toupper(av[1][0]));
	printf("My tolower : %c\n", ft_toupper(av[1][0]));
	printf("tolower :  %c\n\n", toupper(av[1][0]));
	//test isprint
	if (isprint(av[1][0]))
			printf("can print (isprint)\n");
	else if (!isprint(av[1][0]))
			printf("cannot print (isprint)\n");
	if (ft_isprint(av[1][0]))
			printf("can print (ft_isprint)\n");
	else if (!ft_isprint(av[1][0]))
			printf("cannot print (ft_isprint)\n\n");
	//test isascii
	if (isascii(av[1][0]))
			printf("can print (isascii)\n");
	else if (!isprint(av[1][0]))
			printf("cannot print (isascii)\n");
	if (ft_isprint(av[1][0]))
			printf("can print (ft_isascii)\n");
	else if (!ft_isprint(av[1][0]))
			printf("cannot print (ft_isascii)\n\n");
	//test isalpha
	if (isalpha(av[1][0]))
			printf("is alpha (isalpha)\n");
	else if (!isalpha(av[1][0]))
			printf("is not alpha (isalpha)\n");
	if (ft_isalpha(av[1][0]))
			printf("is alpha(ft_isalpha)\n");
	else if (!ft_isalpha(av[1][0]))
			printf("is not alpha (ft_isalpha)\n\n");
	//test isdigit
	if (isdigit(av[1][0]))
			printf("is digit (isdigit)\n");
	else if (!isdigit(av[1][0]))
			printf("is not digit (isdigit)\n");
	if (ft_isdigit(av[1][0]))
			printf("is digit (ft_isdigit)\n");
	else if (!ft_isdigit(av[1][0]))
			printf("is not digit (ft_isdigit)\n\n");
	//test isalnum
	if (isalnum(av[1][0]))
			printf("is alphanum (isalnum)\n");
	else if (!isalnum(av[1][0]))
			printf("is not alphamum (isalnum)\n");
	if (ft_isalnum(av[1][0]))
			printf("is alphanum (ft_isalnum)\n");
	else if (!ft_isalnum(av[1][0]))
			printf("is not alphanum (ft_isalnum)\n\n");
	//test atoi
	printf("atoi : %d\n", atoi(av[1]));
	printf("my atoi : %d\n\n", ft_atoi(av[1]));
	//test strdup
	printf("strdup : %s\n", strdup(av[1]));
	printf("ft_strdup : %s\n\n", ft_strdup(av[1]));

	if (ac > 2)
	{
		char tab1[100] = "je suis : ";
		char tab3[100] = "je suis : ";
		char tab7[100] = "je suis : ";
		char tab8[100] = "je suis : ";
		char tab9[100] = "je suis : ";
		char tab10[100] = "je suis : ";


		//test strncpy
		printf("strncpy : %s\n", strncpy(tab9, av[1], atoi(av[2])));
		printf("ft_strncpy : %s\n\n", ft_strncpy(tab10, av[1], atoi(av[2])));

		//test strchr && strrchr
		printf("strchr : %s\n", strchr(av[1], av[2][0]));
		printf("ft_strchr : %s\n", ft_strchr(av[1], av[2][0]));
		printf("strrchr : %s\n", strrchr(av[1], av[2][0]));
		printf("ft_strrchr : %s\n\n", ft_strrchr(av[1], av[2][0]));
		//test strcpy
		printf("strcpy : %s\n", strcpy(tab7, av[1]));
		printf("ft_strcpy : %s\n\n", ft_strcpy(tab8, av[1]));


		//test strcat
		printf("strcat : %s\n", strcat(tab1, av[2]));
		printf("ft_strcat : %s\n\n", ft_strcat(tab3, av[2]));

		//test strcmp && strncmp
		if (strcmp(av[1],av[2]) > 0)
			printf("strcmp : av[1] > av[2]\n");
		else if (strcmp(av[1], av[2]) == 0)
			printf("strcmp : av[1] == av[2]\n");
		else if(strcmp(av[1], av[2]) < 0)
			printf("strcmp : av[1] < av[2]\n");
		if (ft_strcmp(av[1],av[2]) > 0)
			printf("ft_strcmp : av[1] > av[2]\n");
		else if (ft_strcmp(av[1], av[2]) == 0)
			printf("ft_strcmp : av[1] == av[2]\n");
		else if (ft_strcmp(av[1], av[2]) < 0)
			printf("ft_strcmp : av[1] < av[2]\n\n");
		//test strstr
		printf("strstr : %s\n", strstr(av[1], av[2]));
		printf("ft_strstr : %s\n\n", ft_strstr(av[1], av[2]));

	}
	if (ac > 3)
	{
		char tab2[100] = "je suis : ";
		char tab4[100] = "je suis : ";
		char tab5[100] = "test";
		char tab6[100] = "test";


		//test strncat
		printf("strncat : %s\n", strncat(tab2, av[2], atoi(av[3])));
		printf("ft_strncat : %s\n\n", ft_strncat(tab4, av[2], atoi(av[3])));
		//test strlcat
		printf("strlcat : %zu\n%s\n", strlcat(tab5, av[1], atoi(av[2])), tab5);
		printf("ft_strlcat : %zu\n%s\n\n", ft_strlcat(tab6, av[1], atoi(av[2])), tab6);
		//test strcmp && strncmp
		if (strncmp(av[1],av[2], atoi(av[3])) > 0)
			printf("strncmp : av[1] > av[2]\n");
		else if (strncmp(av[1], av[2], atoi(av[3])) == 0)
			printf("strncmp : av[1] == av[2]\n");
		else if(strncmp(av[1], av[2], atoi(av[3])) < 0)
			printf("strncmp : av[1] < av[2]\n");
		if (ft_strncmp(av[1],av[2], atoi(av[3])) > 0)
			printf("ft_strncmp : av[1] > av[2]\n");
		else if (ft_strncmp(av[1], av[2], atoi(av[3])) == 0)
			printf("ft_strcmp : av[1] == av[2]\n");
		else if (ft_strncmp(av[1], av[2], atoi(av[3])) < 0)
			printf("ft_strncmp : av[1] < av[2]\n\n");
		//test strNstr
		printf("strnstr : %s\n", strnstr(av[1], av[2], atoi(av[3])));
		printf("ft_strnstr : %s\n\n", ft_strnstr(av[1], av[2], atoi(av[3])));

	}
	return 0;
}
