#include "libft.h"

int	ft_nbrlen(long long nbr)
{
	int i;
	i = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		nbr *= -1;
	while (nbr)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}
