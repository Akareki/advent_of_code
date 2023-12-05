#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void	map(char *line, long long *seeds, int *mapped)
{
	long long *maparam;
	int j = 0;
	int i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
			i++;
		if (ft_isdigit(line[i]))
		{
			maparam[j] = strtoll(&line[i], NULL, 10);
			j++;
			while (ft_isdigit(line[i]))
				i++;
		}
	}
	while (j < 20)
	{
		if (seeds[j] >= maparam[1] && seeds[j] < maparam[1] + maparam[2] && mapped[j] == 0)
		{
			seeds[j] = seeds[j] - maparam[1] + maparam[0];
			mapped[j] = 1;
		}
		j++;
	}
}

int main(void) {
  int fd;
  char *buf;
  char **lines;
  char *line;
	int i = 0;
	long long *seeds;
	int *mapped;
	int j = 0;

	seeds = ft_calloc(20, sizeof(long long));
	mapped = ft_calloc(20, sizeof(int));
  fd = open("day5_input.txt", O_RDONLY);
  buf = malloc(1000000);
  read(fd, buf, 1000000);
  lines = ft_split(buf, '\n');
	while (lines[0][i])
	{
		i++;
		if (ft_isdigit(lines[0][i]))
		{
			seeds[j] = strtoll(&lines[0][i], NULL, 10);
			j++;
			while (ft_isdigit(lines[0][i]))
				i++;
		}
	}
	i = 0;
	j = 0;
	while (j < 20)
	{
		printf("Seed : %lld\n", seeds[j]);
		j++;
	}
	j = 0;
	while (lines[i])
	{
		if (!ft_isdigit(lines[i][0]))
		{
			j = 0;
			while (j < 20)
			{
				mapped[j] = 0;
				j++;
			}
			i++;
		}
		else
		{
			map(lines[i], seeds, mapped);
			i++;
		}
	}
	j = 0;
	while (j < 20)
	{
		printf("Location : %lld\n", seeds[j]);
		j++;
	}
}
