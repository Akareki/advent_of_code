#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int	HASH(char *line)
{
	int i = 0;
	int	count = 0;

	while (line[i] && line[i] != '\n')
	{
		count += (int) line[i];
		count *= 17;
		count = count % 256;
		i++;
	}
	ft_printf("HASH : %d\n", count);
	return (count);
}

int main(void) {
	int fd;
	char *buf;
	char **lines;
	char *tmp;
	int line;
	int	i = 0;
	int	count = 0;

	fd = open("day15_input.txt", O_RDONLY);
	buf = malloc(100000);
	read(fd, buf, 100000);
	lines = ft_split(buf, ',');
	while (lines[i])
	{
		count += HASH(lines[i]);
		i++;
	}
	ft_printf("Count : %d\n", count);
}
