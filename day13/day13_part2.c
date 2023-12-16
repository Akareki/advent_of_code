#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"


int	has_hor_reflection(char **lines, int i, int j)
{
	int	k = 0;
	int count = 0;

	while (i - k >= 0 && lines[i + k + 1] && lines[i - k][0] != '\n' && lines[i + k + 1][0] != '\n')
	{
		if (lines[i - k][j] != lines[i + k + 1][j])
			count ++;
		k++;
	}
	return (count);
}

int	hor_reflections(char **lines, int i)
{
	int	j = 0;
	int reflection = 0;
	int smudge;

	while (lines[i + 1][0] != '\n')
	{
		smudge = has_hor_reflection(lines, i, 0);
		if (smudge <= 1)
		{
			j = 1;
			while (lines[i][j])
			{
				smudge += has_hor_reflection(lines, i, j);
				j++;
			}
			if (smudge == 1)
				reflection = i + 1;
		}
		i++;
	}
	ft_printf("Hor ref : %d\n", reflection);
	return (reflection);
}


int	has_vert_reflection(char *line, int j)
{
	int	k = 0;
	int count = 0;

	while (j - k >= 0 && line[j + k + 1] != '\n')
	{
		if (line[j - k] != line[j + k + 1])
			count ++;
		k++;
	}
	return (count);
}

int	vert_reflections(char **lines, int i)
{
	int	j = 0;
	int reflection = 0;
	int	smudge;

	j = 0;
	while (lines[0][j + 1] != '\n')
	{
		i = 1;
		smudge = has_vert_reflection(lines[0], j);
		if (smudge <= 1)
		{
			while (lines[i][0] != '\n')
			{
				smudge += has_vert_reflection(lines[i], j);
				i++;
			}
			if (smudge == 1)
				reflection = j + 1;
		}
		j++;
	}
	ft_printf("Ver ref : %d\n", reflection);
	return (reflection);
}

int main(void) {
	int fd;
	char *buf;
	char **lines;
	char *tmp;
	char *line;
	int	i = 0;
	int count = 0;

	fd = open("day13_input.txt", O_RDONLY);
	lines = ft_calloc(100, sizeof(char *));
	line = get_next_line(fd);
	lines[0] = line;
	while (line)
	{
		i = 1;
		while (line[0] != '\n')
		{
			line = get_next_line(fd);
			lines[i] = line;
			i++;
		}
		i = 0;
		while (lines[i][0] != '\n')
		{
			ft_printf("%s", lines[i]);
			i++;
		}
		count += vert_reflections(lines, 0);
		count += 100 * hor_reflections(lines, 0);	
		line = get_next_line(fd);
		lines[0] = line;
	}
	ft_printf("Count : %d", count);
}
