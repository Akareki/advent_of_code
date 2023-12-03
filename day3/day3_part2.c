#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int gear_ratio(char **lines, int i, int j) {
  int *parts;
  int x = 0;
  int y = 0;
  int y2;
  int nb = 0;

  if (i != 0)
    x = i - 1;
  parts = ft_calloc(2, sizeof(int));
  while (x < 140 && x <= i + 1) {
    if (j != 0)
      y = j - 1;
    else
      y = 0;
    while (y <= j + 1) {
      if (ft_isdigit(lines[x][y]) && nb < 2) {
        y2 = y;
        while (y2 >= 0 && ft_isdigit(lines[x][y2]))
          y2--;
        if (ft_atoi(&lines[x][y2 + 1]) != parts[0]) {
          ft_printf("%d  ", ft_atoi(&lines[x][y2 + 1]));
          parts[nb] = ft_atoi(&lines[x][y2 + 1]);
          nb++;
        }
      }
      y++;
    }
    x++;
  }
  return parts[0] * parts[1];
}

int main(void) {
  int fd;
  char buf[1000000];
  char **lines;
  int i = 0;
  int j = 0;
  int count = 0;
  int g;

  fd = open("day3_input.txt", O_RDONLY);
  buf[read(fd, buf, 1000000)] = '\0';
  lines = ft_split(buf, '\n');
  while (lines[i]) {
    j = 0;
    while (lines[i][j]) {
      if (lines[i][j] == '*') {
        g = gear_ratio(lines, i, j);
        ft_printf("%d\n", g);
        count += g;
      }
      j++;
    }
    i++;
  }
  ft_printf("Count : %d\n", count);
}
