#include "libft.h"

void 				ft_intcpy(int *s1, int *s2, int size)
{
	int i;

	i = -1;
	while (++i <= size)
		s1[i] = s2[i];
	i++;
	s1[i] = 0;
}