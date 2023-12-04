#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	is_in(int nb, int *tab, int size)
{
	int i = 0;

	while (i < size)
	{
		if (nb == tab[i])
			return 1;
		i++;
	}
	return 0;
}

int	line_worth(char *line)
{
	int i = 0;
	int j = 0;
	int *winnb;
	int	worth = 0;

	winnb = ft_calloc(10, sizeof(int));
	while (line[i] != ':')
		i++;
	while (line[i] != '|')
	{
		if (ft_isdigit(line[i]))
		{
			winnb[j] = ft_atoi(&line[i]);
			j++;
			while (ft_isdigit(line[i]))
				i++;
		}
		i++;
	}
	while (line[i])
	{
		if (ft_isdigit(line[i]))
		{
			if (is_in(ft_atoi(&line[i]), winnb, 10))
			{
				if (worth == 0)
					worth = 1;
				else
					worth *= 2;
			}
			while (ft_isdigit(line[i]))
				i++;
		}
		i++;
	}
	return worth;
}

int main(void) {
  int fd;
  char buf[1000000];
  char **lines;
  int i = 0;
  int count = 0;

  fd = open("day4_input.txt", O_RDONLY);
  buf[read(fd, buf, 1000000)] = '\0';
  lines = ft_split(buf, '\n');
  while (lines[i]) {
		ft_printf("Line %d worth : %d \n", i, line_worth(lines[i]));
		count += line_worth(lines[i]);
		i++;
  }
  ft_printf("Count : %d\n", count);
}
