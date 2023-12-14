#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void	move_rocks(char **lines, int ns, int eo)
{
	int	i = 0;
	int	j = 0;
	int	k = 0;
	int l = 0;

	i = (ns == -1) * 99;
	j = (eo == -1) * 99;
	while (i >= 0 && lines[i])
	{
		j = (eo == -1) * 99;
		while (j >= 0 && lines[i][j])
		{
			if (lines[i][j] == '.')
			{
				k = i;
				l = j;
				while (k >= 0 && l >= 0 && lines[k] && lines[k][l] && lines[k][l] == '.')
				{
					k += ns;
					l += eo;
				}
				if (k >= 0 && l >= 0 && lines[k] && lines[k][l] == 'O')
				{
					lines[i][j] = 'O';
					lines[k][l] = '.';
				}
			}
			j += (eo == 1) + (eo == 0) - (eo == -1);
		}
		i += (ns == 1) + (ns == 0) - (ns == -1);
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

int	cmp_lines(char **lines, char **lines_dup)
{
	int	i = 0;

	while (lines[i])
	{
		if (ft_strncmp(lines[i], lines_dup[i], 100) != 0)
			return (i + 1);
		i++;
	}
	return (0);
}

int main(void) {
	int fd;
	char *buf;
	char **lines;
	char **lines_dup;
	char *tmp;
	int line;
	int	i = 0;
	int j = 1;
	int	count = 0;

	fd = open("day14_input.txt", O_RDONLY);
	buf = malloc(100000);
	read(fd, buf, 100000);
	lines = ft_split(buf, '\n');
	lines_dup = ft_split(buf, '\n');
	while (i < 13000 && j != 0)
	{
		j = 0;
		while (lines[j])
		{
			lines_dup[j] = ft_strdup(lines[j]);
			j++;
		}
		move_rocks(lines, 1, 0);
		move_rocks(lines, 0, 1);
		move_rocks(lines, -1, 0);
		move_rocks(lines, 0, -1);
		i++;
		j = cmp_lines(lines, lines_dup);
		ft_printf("i = %d\n", i);
		ft_printf("diff = %d\n", j);
	}
	while (i < 13000 + ((1000000000 - 13000) % 26) && j != 0)
	{
		j = 0;
		while (lines[j])
		{
			lines_dup[j] = ft_strdup(lines[j]);
			j++;
		}
		move_rocks(lines, 1, 0);
		move_rocks(lines, 0, 1);
		move_rocks(lines, -1, 0);
		move_rocks(lines, 0, -1);
		i++;
		j = cmp_lines(lines, lines_dup);
		ft_printf("i = %d\n", (i - 13000) % 26);
		count = count_rock_weight(lines);
		ft_printf("Count : %d\n", count);
	}
	/*i = 0;
	while (lines[i])
	{
		ft_printf("%s\n", lines[i++]);
	}
	count = count_rock_weight(lines);
	ft_printf("Count : %d", count);*/
}
