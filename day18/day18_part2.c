
#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define MAP_SIZE 1000

typedef struct{
	long long i;
	long long j;
} pixel;

int main(void) {
	int fd;
	char *buf;
	char **lines;
	char *tmp;
	int line = 0;
	int i = 0;
	int j = 0;
	int c = 0;
	long long count = 0;
	long long area = 0;
	char dir = 0;
	t_list	*vertexes = NULL;
	pixel	*vertex;
	
	fd = open("day18_input.txt", O_RDONLY);
	//fd = open("test.txt", O_RDONLY);
	buf = malloc(100000);
	read(fd, buf, 100000);
	lines = ft_split(buf, '\n');
	vertex = malloc(sizeof(pixel));
	vertex->i = i;
	vertex->j = j;
	ft_lstadd_back(&vertexes, ft_lstnew(vertex));
	while (lines[line])
	{
		c = 0;
		while (lines[line][c] != ')')
			c++;
		dir = lines[line][c - 1];
		lines[line][c - 1] = '\0';
		c = 0;
		while (lines[line][c] != '#')
			c++;
		if (dir == '0')
			j = j + strtoll(lines[line] + c + 1, NULL, 16);
		if (dir == '1')
			i = i + strtoll(lines[line] + c + 1, NULL, 16);
		if (dir == '2')
			j = j - strtoll(lines[line] + c + 1, NULL, 16);
		if (dir == '3')
			i = i - strtoll(lines[line] + c + 1, NULL, 16);
		vertex = malloc(sizeof(pixel));
		vertex->i = i;
		vertex->j = j;
		count += strtoll(lines[line] + c + 1, NULL, 16);
		ft_lstadd_back(&vertexes, ft_lstnew(vertex));
		line++;
	}
	while (vertexes->next)
	{
		area += ((pixel *)vertexes->content)->i * ((pixel *)vertexes->next->content)->j -
			((pixel *)vertexes->next->content)->i * ((pixel *)vertexes->content)->j;
		printf("i : %lld j : %lld\n", ((pixel *)vertexes->content)->i,
		((pixel *)vertexes->content)->j);
		vertexes = vertexes->next;
	}
	if (area < 0)
		area = -area;
	printf("Count : %lld\n", (count + area) / 2);
	
}
