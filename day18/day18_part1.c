#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define MAP_SIZE 1000

typedef struct{
	int i;
	int j;
} pixel;

void	fill_map(char map[MAP_SIZE][MAP_SIZE], int i, int j)
{
	t_list *pixels;
	pixel	*pix;

	pixels = NULL;
	pix = malloc(sizeof(pixel));
	pix->i = i;
	pix->j = j;
	ft_lstadd_back(&pixels, ft_lstnew(pix));
	while (pixels)
	{
		i = ((pixel *)pixels->content)->i;
		j = ((pixel *)pixels->content)->j;
		ft_printf("i : %d j : %d\n", i, j);
		map[i][j] = '#';
		if (map[i - 1][j] == '.')
		{
			map[i - 1][j] = '#';
			pix = malloc(sizeof(pixel));
			pix->i = i - 1;
			pix->j = j;
			ft_lstadd_back(&pixels, ft_lstnew(pix));
		}
		if (map[i + 1][j] == '.')
		{
			map[i + 1][j] = '#';
			pix = malloc(sizeof(pixel));
			pix->i = i + 1;
			pix->j = j;
			ft_lstadd_back(&pixels, ft_lstnew(pix));
		}
		if (map[i][j - 1] == '.')
		{
			map[i][j - 1] = '#';
			pix = malloc(sizeof(pixel));
			pix->i = i;
			pix->j = j - 1;
			ft_lstadd_back(&pixels, ft_lstnew(pix));
		}
		if (map[i][j + 1] == '.')
		{
			map[i][j + 1] = '#';
			pix = malloc(sizeof(pixel));
			pix->i = i;
			pix->j = j + 1;
			ft_lstadd_back(&pixels, ft_lstnew(pix));
		}
		pixels = pixels->next;
	}
}

void	dig_trenches(char **lines, char map[MAP_SIZE][MAP_SIZE])
{
	int i = 300;
	int j = 300;
	int moves = 0;
	int line = 0;

	while (lines[line])
	{
		if (i < 0 || j < 0 || i >= MAP_SIZE || j >= MAP_SIZE)
		{
			ft_printf("Out bounds i : %d j : %d", i, j);
			return;
		}
		if (lines[line][0] == 'R')
		{
			moves = ft_atoi(lines[line] + 1);
			while (moves)
			{
				map[i][j] = '#';
				j++;
				moves--;
			}
		}
		if (lines[line][0] == 'L')
		{
			moves = ft_atoi(lines[line] + 1);
			while (moves)
			{
				map[i][j] = '#';
				j--;
				moves--;
			}
		}
		if (lines[line][0] == 'D')
		{
			moves = ft_atoi(lines[line] + 1);
			while (moves)
			{
				map[i][j] = '#';
				i++;
				moves--;
			}
		}
		if (lines[line][0] == 'U')
		{
			moves = ft_atoi(lines[line] + 1);
			while (moves)
			{
				map[i][j] = '#';
				i--;
				moves--;
			}
		}
		line++;
	}
	return;
}

int main(void) {
	int fd;
	char *buf;
	char **lines;
	char *tmp;
	int line;
	int	move = 0;
	int i = 0;
	int j = 0;
	int count = 0;
	char map[MAP_SIZE][MAP_SIZE];

	while (i < MAP_SIZE)
	{
		j = 0;
		while (j < MAP_SIZE)
		{
			map[i][j] = '.';
			j++;
		}
		i++;
	}
	fd = open("day18_input.txt", O_RDONLY);
	buf = malloc(100000);
	read(fd, buf, 100000);
	lines = ft_split(buf, '\n');
	dig_trenches(lines, map);
	fill_map(map, 301, 301);
	i = 0;
	j = 0;
	while (i < MAP_SIZE)
	{
		j = 0;
		while (j < MAP_SIZE)
		{
			if (map[i][j] == '#')
				count++;
			j++;
		}
		i++;
	}
	ft_printf("Count : %d\n", count);
}
