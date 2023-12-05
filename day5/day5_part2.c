#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void	map(char *line, long long *seed, int *mapped)
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
	if (*seed >= maparam[0] && *seed < maparam[0] + maparam[2] && *mapped == 0)
	{
		*seed = *seed - maparam[0] + maparam[1];
		*mapped = 1;
	}
}

int main(void) {
  int fd;
  char *buf;
  char **lines;
  char *line;
	int i = 0;
	long long *seeds;
	int mapped = 0;
	int j = 0;
	long long loc =0;
	int linemax;
	long long seed;
	int found = 0;

	seeds = ft_calloc(20, sizeof(long long));
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
	while (lines[i])
	{
		i++;
	}
	linemax = i - 1;
	while (!found)
	{
		loc++;
		i = linemax;
		seed = loc;
		while (i > 0)
		{
			if (!ft_isdigit(lines[i][0]))
			{
				mapped = 0;
			}
			if (ft_isdigit(lines[i][0]))
			{
				map(lines[i], &seed, &mapped);
			}
			i--;
		}
		j = 0;
		while (j < 20)
		{
			if (seed >= seeds[j] && seed < seeds[j] + seeds[j + 1])
			{
				found = 1;
				break;
			}
			j += 2;
		}
	}
	printf("Loc : %lld\n", loc);
}
