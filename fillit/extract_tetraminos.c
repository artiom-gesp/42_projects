#include "fillit.h"

void	is_sqare(int tab[], char **tetr, int i)
{
	int j;

	j = 0;
	while (tetr[i][j] != '#')
	{
		if (j == 4)
		{
			i++;
			j = 0;
		}
		else
			j++;
	}
	if (tetr[i + 1][j] == '#' && tetr[i][j + 1] == '#'
			&& tetr[i + 1][j + 1] == '#')
		tab[18] += 1;
}

int		get_nb_tetr(char **tetr, int tab[])
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (tetr[i])
	{
		if (ft_strcmp(tetr[i], "\n") == 0)
			j++;
		i++;
	}
	i = -1;
	while (++i < 19)
	{
		k += tab[i];
	}
	printf("J:%d\nK:%d\n", j , k);
	if (k == j)
		return (1);
	return (0);
}

void	extr_tetr(char **tetr, int tab[])
{
	int i;
	int *ret;

	i = -1;
	while (i++ < 19)
		tab[i] = 0;
	i = 0;
	while (tetr[i])
	{
		is_bc(tab, tetr, i);
		is_z(tab, tetr, i);
		is_mp(tab, tetr, i);
		is_l(tab, tetr, i);
		is_rev_l(tab, tetr, i);
		is_sqare(tab, tetr, i);
		while ((i + 1) % 5 != 0)
			i++;
		i++;
	}
}



int main(int argc, char *argv[])
{
	char **tab;
	int	ret[19];

	if (!(tab = make_tab(argv[1])))
		return (0);
	extr_tetr(tab, ret);
	int i = -1;

	if (get_nb_tetr(tab, ret))
		while (++i < 19)
			printf("%d\n", ret[i]);
	else
		printf("error");
	return 0;
}
