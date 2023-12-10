#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int follow_loop(char **lines, int i, int j) {
  char tile;

  tile = lines[i][j];
  lines[i][j] = '0';
  if (tile == 'S')
    return (1 + follow_loop(lines, i - 1, j));
  if (tile == '|') {
    if (lines[i - 1][j] != '0')
      return 1 + follow_loop(lines, i - 1, j);
    if (lines[i + 1][j] != '0')
      return 1 + follow_loop(lines, i + 1, j);
  }
  if (tile == '-') {
    if (lines[i][j - 1] != '0')
      return 1 + follow_loop(lines, i, j - 1);
    if (lines[i][j + 1] != '0')
      return 1 + follow_loop(lines, i, j + 1);
  }
  if (tile == 'L') {
    if (lines[i][j + 1] != '0')
      return 1 + follow_loop(lines, i, j + 1);
    if (lines[i - 1][j] != '0')
      return 1 + follow_loop(lines, i - 1, j);
  }
  if (tile == 'J') {
    if (lines[i][j - 1] != '0')
      return 1 + follow_loop(lines, i, j - 1);
    if (lines[i - 1][j] != '0')
      return 1 + follow_loop(lines, i - 1, j);
  }
  if (tile == '7') {
    if (lines[i][j - 1] != '0')
      return 1 + follow_loop(lines, i, j - 1);
    if (lines[i + 1][j] != '0')
      return 1 + follow_loop(lines, i + 1, j);
  }
  if (tile == 'F') {
    if (lines[i][j + 1] != '0')
      return 1 + follow_loop(lines, i, j + 1);
    if (lines[i + 1][j] != '0')
      return 1 + follow_loop(lines, i + 1, j);
  }
  return (0);
}

int main(void) {
  int fd;
  char *buf;
  char **lines;
  char *line;
  int i = 0;
  int j = 0;
  int count;

  fd = open("day10_input.txt", O_RDONLY);
  buf = malloc(100000);
  read(fd, buf, 100000);
  lines = ft_split(buf, '\n');
  while (lines[i]) {
    j = 0;
    while (lines[i][j]) {
      if (lines[i][j] == 'S')
        break;
      j++;
    }
    if (lines[i][j] == 'S')
      break;
    i++;
  }
  ft_printf("i : %d j : %d\n", i, j);
  count = follow_loop(lines, i, j);
  i = 0;
  while (lines[i]) {
    ft_printf("%s\n", lines[i]);
    i++;
  }
  ft_printf("Count = %d", count / 2 + 1);
}
