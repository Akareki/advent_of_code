
#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define MAP_SIZE 1000

void	walk_the_plots(char **lines0, char **lines1, int steps)
{
	int i = 0;
	int j = 0;

	while (steps)
	{
		i = 0;
		while (lines0[i])
		{
			j = 0;
			while (lines0[i][j])
			{
				if (lines1[i][j] == 'O')
					lines1[i][j] = '.';
				if (lines1[i][j] == '.')
				{
					if (i > 0 && (lines0[i - 1][j] == 'O'))
						lines1[i][j] = 'O';
					if (j > 0 && (lines0[i][j - 1] == 'O'))
						lines1[i][j] = 'O';
					if (lines0[i + 1] && (lines0[i + 1][j] == 'O'))
						lines1[i][j] = 'O';
					if (lines0[i][j + 1] && (lines0[i][j + 1] == 'O'))
						lines1[i][j] = 'O';			
				}
				j++;
			}
			i++;
		}
		i = 0;
		while (lines1[i])
		{
			j = 0;
			while (lines1[i][j])
			{
				if (lines0[i][j] == 'O')
					lines0[i][j] = '.';
				if (lines0[i][j] == '.')
				{
					if (i > 0 && (lines1[i - 1][j] == 'O'))
						lines0[i][j] = 'O';
					if (j > 0 && (lines1[i][j - 1] == 'O'))
						lines0[i][j] = 'O';
					if (lines1[i + 1] && (lines1[i + 1][j] == 'O'))
						lines0[i][j] = 'O';
					if (lines1[i][j + 1] && (lines1[i][j + 1] == 'O'))
						lines0[i][j] = 'O';
				}
				j++;
			}
			i++;
		}
		steps--;
	}
	
}

int main(int argc, char **argv) {
	int fd;
	char *buf;
	char **lines0;
	char **lines1;
	char *tmp;
	int line;
	int	move = 0;
	int i = 0;
	int j = 0;
	int count = 0;
	long long	longcount;
	int steps = 33;
	if (argc > 1)
		steps = ft_atoi(argv[1]);
	fd = open("day21_input.txt", O_RDONLY);
	buf = malloc(1000000);
	read(fd, buf, 1000000);
	lines0 = ft_split(buf, '\n');
	lines1 = ft_split(buf, '\n');
	walk_the_plots(lines0, lines1, steps);
	i = 0;
	j = 0;
	while (lines1[i])
	{
		j = 0;
		while (lines1[i][j])
		{
			if (lines1[i][j] == 'O')
				count++;
			j++;
		}
		i++;
	}
	i = 0;
	while (lines1[i])
	{
		ft_printf("%s\n", lines1[i]);
		i++;
	}
	ft_printf("Steps : %d\n", steps * 2 - 1);
	ft_printf("Count : %d\n", count);
	count = 0;
	i = 0;
	j = 0;
	while (lines0[i])
	{
		j = 0;
		while (lines0[i][j])
		{
			if (lines0[i][j] == 'O')
				count++;
			j++;
		}
		i++;
	}
	i = 0;
	while (lines0[i])
	{
		ft_printf("%s\n", lines0[i]);
		i++;
	}
	ft_printf("Count : %d\n", count);
	ft_printf("Steps : %d\n", steps * 2);
	//longcount =(long long)202299 * 202299 * 7577 +  (long long)202300 * 202300 * 7596 + (long long)4 * 202299 * 7596 + 5664 + 5672;
	//longcount = (long long) ((long long) (2 * 202230 + 1) * (2 * 202230 + 1)) * 3740;
	//longcount = 197 * 197 - (2 * 507 + 2 * 499 + 4 * 497 + 485);
	longcount = ((long long) 26501366 * 26501366) - ((long long) 202300 * 202300 * 497) - ((long long) 202301 * 202301 * 485) - ((long long) 202300 * 202300 + (long long)202301 * 202301) * (507 + 499) / 2;
	printf("Count : %lld\n", longcount);

}
