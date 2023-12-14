#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void	move_rocks(char **lines)
{
	int	i = 0;
	int	j = 0;
	int	k = 0;

	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] == '.')
			{
				k = i;
				while (lines[k] && lines[k][j] == '.')
					k++;
				if (lines[k] && lines[k][j] == 'O')
				{
					lines[i][j] = 'O';
					lines[k][j] = '.';
				}
			}
			j++;
		}
		i++;
	}
}

int	count_rock_weight(char **lines)
{
	int weight = 0;
	int i = 0;
	int j = 0;

	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] == 'O')
				weight += 100 - i;
			j++;
		}
		i++;
	}
	return (weight);
}

int main(void) {
	int fd;
	char *buf;
	char **lines;
	char *tmp;
	int line;
	int	i = 0;
	int	count = 0;

	fd = open("day14_input.txt", O_RDONLY);
	buf = malloc(100000);
	read(fd, buf, 100000);
	lines = ft_split(buf, '\n');
	move_rocks(lines);
	while (lines[i])
	{
		ft_printf("%s\n", lines[i++]);
	}
	count = count_rock_weight(lines);
	ft_printf("Count : %d", count);
}
