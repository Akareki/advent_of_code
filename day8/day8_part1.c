#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int	do_move(char **lines, int line, int move)
{
	char *dest;
	int	i = 1;

	if (lines[0][move % ft_strlen(lines[0])] == 'L')
		dest = lines[line] + 7;
	if (lines[0][move % ft_strlen(lines[0])] == 'R')
		dest = lines[line] + 12;
	while (ft_strncmp(lines[i], dest, 3) != 0)
		i++;
	return (i);
}

int main(void) {
	int fd;
	char *buf;
	char **lines;
	char *tmp;
	int line;
	int	move = 0;

	fd = open("day8_input.txt", O_RDONLY);
	buf = malloc(100000);
	read(fd, buf, 100000);
	lines = ft_split(buf, '\n');
	while (ft_strncmp(lines[line], "AAA", 3) != 0)
		line++;
	while (ft_strncmp(lines[line], "ZZZ", 3) != 0)
	{
		ft_printf("Line : %s | Move : %c | Nb moves : %d\n", lines[line], lines[0][move % ft_strlen(lines[0])], move);
		line = do_move(lines, line, move);
		move++;
	}
	ft_printf("Moves : %d", move);
}
