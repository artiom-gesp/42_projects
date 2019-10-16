#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct queue
{
	int x;
	int y;
	int distance;
	struct queue *next;
}             queue;

int search_path(char **map, int width, int heigh, int x_start)
{
	queue *q;
	int distance = 0;
	int visited[heigh][width];
	queue *end;
	memset(visited, 0, heigh * width * sizeof(int));

	if (map[0][x_start] == 'X')
		return -1;
	visited[0][x_start] = 1;
	if (!(q = malloc(sizeof(queue))))
		return -1;
	q->x = x_start;
	q->y = 0;
	q->distance = 0;
	q->next = NULL;

	end = q;

	while (q && q->y != heigh - 1)
	{
		if (q->x > 0 && map[q->y][q->x - 1] == '.' && !visited[q->y][q->x - 1])
		{
			end->next = malloc(sizeof(queue));
			end = end->next;
			end->x = q->x - 1;
			end->y = q->y;
			end->distance = q->distance + 1;
			visited[q->y][q->x - 1] = 1;
			end->next = NULL;
		}
		if (q->x < width - 1 && map[q->y][q->x + 1] == '.' && !visited[q->y][q->x + 1])
		{
			end->next = malloc(sizeof(queue));
			end = end->next;
			end->x = q->x + 1;
			end->y = q->y;
			end->distance = q->distance + 1;
			visited[q->y][q->x + 1] = 1;
			end->next = NULL;
		}
		if (q->y < heigh - 1 && map[q->y + 1][q->x] == '.' && !visited[q->y + 1][q->x])
		{
			end->next = malloc(sizeof(queue));
			end = end->next;
			end->x = q->x;
			end->y = q->y + 1;
			end->distance = q->distance + 1;
			visited[q->y + 1][q->x] = 1;
			end->next = NULL;
		}
		++distance;
		q = q->next;
	}
	if (!q)
		return -1;
	else
		return q->distance;
}

int main()
{
	int index = 0;
	int width = -1;
	int heigh = -1;
	char **map;

	char s[1024];
	while (scanf("%s", &s) != EOF)
	{
		if (width == -1 && heigh != -1)
		{
			width = atoi(s);
			printf("here %d %d\n", heigh, width);
			if (width < 2 || width > 1000 || heigh < 2 || heigh > 1000)
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
			fprintf(stderr, "line %s\n", map[index]);
			++index;
		}
	}
	int tmp;
	int ret = -1;
	for (int i = 0; i < width; ++i)
	{
		tmp = search_path(map, width, heigh, i);
		printf("tmp %d\n", tmp);
		ret = tmp < ret || ret == -1 ? tmp : ret;
	}

	printf("%d\n", ret);

}

