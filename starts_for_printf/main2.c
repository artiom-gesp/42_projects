#include <float.h>
#include <stdint.h>
#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>
int	main(int ac, char **av)
{
	int a;

	a = 2;
	printf("p %d\n", printf(av[1], av[2]));
	printf("m %d\n", ft_printf(av[1], av[1]));
	printf("p %d\n", printf(av[1], atoi(av[2])));
	printf("p %d\n", printf(av[1], atoi(av[2])));
}
