#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX(a,b) ((a) > (b) ? a : b)
#define MIN(a,b) ((a) < (b) ? a : b)

void reverse_snail(char **map, int heigh, int width, int x, int y)
{

}

void forward_snail(char **map, int heigh, int width, int x, int y)
{

}

void check_neighbors(char **map, int heigh, int width, int x, int y)
{
    for (int i = MAX(0, y - 1); i < MIN(heigh, y + 2); ++i)
    {
        for (int j = MAX(0, x - 1); j < MIN(width, x + 2); ++j)
        {
          if ((i == y - 1 && j == x - 1) || (i == y + 1 && j == x + 1)
          || (i == y - 1 && j == x + 1) || (i == y + 1 && j == x - 1))
                continue;
            if (map[i][j] == '.')
            {
                map[y][x] = '1';
                return ;
            }
            map[y][x] = map[y][x] == '#' || (map[i][j] < map[y][x] && map[i][j] != '#')
            ? map[i][j] + 1: map[y][x];
        }
    }
}

void pmap(char **map, int heigh, int width)
{
  for (int k = 0; k < heigh; ++k)
  {
      for (int l = 0; l < width; ++l)
      {
          // fprintf(stderr, "%d ", map[k][l] - '0');
          fprintf(stderr, "%c ", map[k][l]);
      }
      fprintf(stderr, "\n");
  }
}

void update_map(char **map, int heigh, int width)
{
    int max = 0;
    for (int i = 0; i < heigh; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (map[i][j] != '.')
                check_neighbors(map, heigh, width, j, i);
        }
    }
    // pmap(map, heigh, width);

    for (int i = heigh - 1; i >= 0; --i)
    {
        for (int j = width - 1; j >= 0; --j)
        {
            if (map[i][j] != '.')
            {
                check_neighbors(map, heigh, width, j, i);
                max = map[i][j] - '0' > max ? map[i][j] - '0': max;
            }
        }
    }
    for (int k = 0; k < heigh; ++k)
    {
        for (int l = 0; l < width; ++l)
        {
            // fprintf(stderr, "%d ", map[k][l] - '0');
            fprintf(stderr, "%c ", map[k][l]);
        }
        fprintf(stderr, "\n");
    }
    printf("%d\n", max);
}

int main() {
   char s[1024];
   char **map;
   int heigh = -1;
   int width = -1;
   int index = 0;

    // fprintf(stderr, "\n");
	while (scanf("%s", &s) != EOF) {
	    if (width == -1 && heigh != -1)
		{
			width = atoi(s);
// 			printf("here %d %d\n", heigh, width);
			if (width < 3 || width > 40 || heigh < 3 || heigh > 40)
				return -1;
			if (!(map = malloc(sizeof(char*) * heigh)))
				return -1;
		}
		else if (heigh == -1)
		{
			heigh = atoi(s);
		}
		else if (index < heigh)
		{
			if (!(map[index] = malloc(sizeof(char) * (width + 1))))
				return -1;
			strcpy(map[index], s);
			if (strlen(map[index]) != width)
				return -1;
			map[index][width] = 0;
// 			fprintf(stderr, "%s\n", map[index]);
			++index;
		}
		//
		// Lisez les données ici et effectuez votre traitement ici
		//
	}
	update_map(map, heigh, width);

	// Vous pouvez aussi effectuer votre traitement ici après avoir lu toutes les données
	return 0;
}
