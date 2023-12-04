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

int	line_worth(char **lines, int linenb)
{
	int i = 0;
	int j = 0;
	int *winnb;
	int	worth = 1;
	int next_line = linenb + 1;

	winnb = ft_calloc(10, sizeof(int));
	while (lines[linenb][i] != ':')
		i++;
	while (lines[linenb][i] != '|')
	{
		if (ft_isdigit(lines[linenb][i]))
		{
			winnb[j] = ft_atoi(&lines[linenb][i]);
			j++;
			while (ft_isdigit(lines[linenb][i]))
				i++;
		}
		i++;
	}
	while (lines[linenb][i])
	{
		if (ft_isdigit(lines[linenb][i]))
		{
			if (is_in(ft_atoi(&lines[linenb][i]), winnb, 10))
				worth += line_worth(lines, next_line++);
			if (linenb > 199)
				return worth;
			while (ft_isdigit(lines[linenb][i]))
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
		ft_printf("Line %d worth : %d \n", i, line_worth(lines, i));
		count += line_worth(lines, i);
		i++;
  }
  ft_printf("Count : %d\n", count);
}
