#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

int	do_move(char **lines, int line, int move)
{
	char *dest;
	int	i = 1;

	if (lines[0][move] == 'L')
		dest = lines[line] + 7;
	if (lines[0][move] == 'R')
		dest = lines[line] + 12;
	while (ft_strncmp(lines[i], dest, 3) != 0)
		i++;
	return (i);
}

int	all_on_Z(char **lines, int *line, int i)
{
	int j = 0;
	while (j < i)
	{
		if (lines[line[j]][2] != 'Z')
			return 0;
		j++;
	}
	return 1;
}

int main(void) {
	int fd;
	char buf[1000000];
	char **lines;
	int line[10];
	int	i = 0;
	int j = 0;
	int	move = 0;
	int	old_move[10];
	int loop[10];
	size_t count = 1;
	size_t tmp;

	fd = open("day8_input.txt", O_RDONLY);
	read(fd, buf, 1000000);
	lines = ft_split(buf, '\n');
	while (lines[i])
	{
		if (lines[i][2] == 'A')
		{
			loop[j] = 0;
			old_move[j] = 0;
			line[j] = i;
			j++;
		}
		i++;
	}
	i = j;
	while (move < 200000)
	{
		j = 0;
		while (j < i)
		{
			//ft_printf("Line : %s | Move : %c | Nb moves : %d\n", lines[line[j]], lines[0][move % ft_strlen(lines[0])], move);
			line[j] = do_move(lines, line[j], move % ft_strlen(lines[0]));
			if (lines[line[j]][2] == 'Z')
			{
				loop[j] = move - old_move[j];
				ft_printf("Start %d at %.3s in %d moves, loop is %d\n", j, lines[line[j]], move, loop[j]);
				old_move[j] = move;
			}
			j++;
		}
		move++;
	}
	j = 0;
	count = 1;
	while (j < i)
	{
		ft_printf("Loop for %d start : %d + %d\n", j, loop[j] / ft_strlen(lines[0]), loop[j] % ft_strlen(lines[0]));
		tmp = loop[j] / ft_strlen(lines[0]);
		printf("tmp : %lu", tmp);
		count = count * tmp;
		j++;
	}
	printf("Count : %lu", count * ft_strlen(lines[0]));
}
