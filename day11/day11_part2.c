#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

unsigned long int	galaxy_distance(int x, int y, int i, int j, int *empty_cols, int *empty_lines)
{
	unsigned long int count = 0;

	while (x < i)
	{
		if (empty_lines[x])
			count += 1000000;
		else
			count += 1;
		x++;
	}
	while (y != j)
	{
		if (empty_cols[y])
			count += 1000000;
		else
			count += 1;
		y = y + (y < j) - (y > j);
	}
	return (count);
}

unsigned long int count_paths(char **galaxy, int x, int y, int *empty_cols, int *empty_lines) {
  unsigned long int count = 0;
  int i = x;
  int j = y + 1;

  while (galaxy[i]) {
    while (galaxy[i][j]) {
      if (galaxy[i][j] == '#')
				count += galaxy_distance(x, y, i, j, empty_cols, empty_lines);
      j++;
    }
    i++;
    j = 0;
  }
  return (count);
}

int main(void) {
  int fd;
  char buf[100000];
  char **lines;
  char *line;
  int i;
  int j;
  int *empty_lines;
  int *empty_cols;
  int x = 0;
  int y = 0;
  int y_tmp = 0;
  unsigned long int count = 0;

  fd = open("day11_input.txt", O_RDONLY);
  read(fd, buf, 100000);
  lines = ft_split(buf, '\n');
  x = 0;
  empty_lines = ft_calloc(150, sizeof(int));
  empty_cols = ft_calloc(150, sizeof(int));
  i = 0;
  while (lines[i]) {
    count = 0;
    j = 0;
    while (lines[i][j]) {
      if (lines[i][j] == '#')
        count++;
      j++;
    }
    if (count == 0) {
      empty_lines[i] = 1;
    }
    i++;
  }
  i = 0;
  j = 0;
  while (lines[i][j]) {
    count = 0;
    while (lines[i]) {
      if (lines[i][j] == '#')
        count++;
      i++;
    }
    if (count == 0) {
      empty_cols[j] = 1;
    }
    j++;
    i = 0;
  }
  x = 0;
  y = 0;
  count = 0;
  while (lines[x]) {
    y = 0;
    while (lines[x][y]) {
      if (lines[x][y] == '#')
        count += count_paths(lines, x, y, empty_cols, empty_lines);
      y++;
    }
    x++;
  }
  printf("Count : %lu\n", count);
}
