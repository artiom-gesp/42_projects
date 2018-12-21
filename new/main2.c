#include "ft_printf.h"

int	main(int ac, char **av)
{
	printf(" %d\n", ft_printf(av[1], atoi(av[2])));
	printf(" %d\n", printf(av[1], atoi(av[2])));
}
