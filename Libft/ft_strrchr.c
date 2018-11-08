#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;
	char *z;

	i = 0;
	z = "";
	if (c < 1)
	{
		return (z);
	}
	while (s[i])
		i++;
	while (i > 0)
	{
		if (s[i] == (char)(c))
			return (char*)&s[i];
		i--;
	}
	return (0);
}
