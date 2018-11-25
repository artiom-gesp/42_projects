#include "fillit.h"

void	is_bc(int tab[], char **tetr, int i)
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
	if (tetr[i + 1][j] == '#' && tetr[i + 2][j] == '#' && tetr[i + 3][j] == '#')
		tab[0] += 1;
	if (tetr[i][j + 1] == '#' && tetr[i][j + 2] == '#' && tetr[i][j + 3] == '#')
		tab[1] += 1;
}

void	is_z(int tab[], char **tetr, int i)
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
 	if (tetr[i][j + 1] == '#' && tetr[i + 1][j + 1] == '#'
			&& tetr[i + 1][j + 2] == '#')
		tab[2] += 1;
	if (tetr[i][j + 1] == '#' && tetr[i + 1][j] == '#'
			&& tetr[i + 1][j - 1] == '#')
		tab[3] += 1;
	if (tetr[i + 1][j] == '#' && tetr[i + 1][j + 1] == '#'
			&& tetr[i + 2][j + 1] == '#')
		tab[4] += 1;
	if (tetr[i + 1][j] == '#' && tetr[i + 1][j - 1] == '#'
			&& tetr[i + 2][j - 1] == '#')
		tab[5] += 1;
}

void	is_mp(int tab[], char **tetr, int i)
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
 	if (tetr[i + 1][j] == '#' && tetr[i + 1][j + 1] == '#'
			&& tetr[i + 1][j - 1] == '#')
		tab[6] += 1;
	if (tetr[i][j + 1] == '#' && tetr[i][j + 2] == '#'
			&& tetr[i + 1][j + 1] == '#')
		tab[7] += 1;
	if (tetr[i + 1][j] == '#' && tetr[i + 1][j + 1] == '#'
			&& tetr[i + 2][j] == '#')
		tab[8] += 1;
	if (tetr[i + 1][j] == '#' && tetr[i + 1][j - 1] == '#'
			&& tetr[i + 2][j] == '#')
		tab[9] += 1;

}

void	is_l(int tab[], char **tetr, int i)
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
 	if (tetr[i][j + 1] == '#' && tetr[i + 1][j] == '#'
			&& tetr[i + 2][j] == '#')
		tab[10] += 1;
	if (tetr[i + 1][j] == '#' && tetr[i + 1][j + 1] == '#'
			&& tetr[i + 1][j + 2] == '#')
		tab[11] += 1;
	if (tetr[i + 1][j] == '#' && tetr[i + 2][j] == '#'
			&& tetr[i + 2][j - 1] == '#')
		tab[12] += 1;
	if (tetr[i][j + 1] == '#' && tetr[i][j + 1] == '#'
			&& tetr[i + 1][j + 2] == '#')
		tab[13] += 1;
}

void	is_rev_l(int tab[], char **tetr, int i)
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
 	if (tetr[i][j + 1] == '#' && tetr[i + 1][j + 1] == '#'
			&& tetr[i + 2][j + 1] == '#')
		tab[14] += 1;
	if (tetr[i + 1][j] == '#' && tetr[i][j + 1] == '#'
			&& tetr[i][j + 2] == '#')
		tab[15] += 1;
	if (tetr[i + 1][j] == '#' && tetr[i + 2][j] == '#'
			&& tetr[i + 2][j + 1] == '#')
		tab[16] += 1;
	if (tetr[i + 1][j] == '#' && tetr[i + 1][j - 1] == '#'
			&& tetr[i + 1][j - 2] == '#')
		tab[17] += 1;
}
