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

void color_fill(char **lines, int i, int j) {
  lines[i][j] = '0';
  if (lines[i + 1] && lines[i + 1][j] == '.')
    color_fill(lines, i + 1, j);
  if (i > 0 && lines[i - 1][j] == '.')
    color_fill(lines, i - 1, j);
  if (lines[i][j + 1] && lines[i][j + 1] == '.')
    color_fill(lines, i, j + 1);
  if (j > 0 && lines[i][j - 1] == '.')
    color_fill(lines, i, j - 1);
}

int count_pipes(char **lines, int i, int j) {
  int count = 0;

  while (j >= 0 && lines[i][j] != '0') {
    if (lines[i][j] == '|')
      count++;
    if (lines[i][j] == '7') {
      j--;
      while (lines[i][j] == '-')
        j--;
      if (lines[i][j] == 'L')
        count++;
    }
    if (lines[i][j] == 'J') {
      j--;
      while (lines[i][j] == '-')
        j--;
      if (lines[i][j] == 'F')
        count++;
    }
    j--;
  }
  return (count);
}

int main(void) {
  int fd;
  char *buf;
  char **lines;
  char **lines_dup;
  char *line;
  int i = 0;
  int j = 0;
  int count;

  fd = open("day10_input.txt", O_RDONLY);
  buf = malloc(100000);
  read(fd, buf, 100000);
  lines = ft_split(buf, '\n');
  lines_dup = ft_split(buf, '\n');
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
  count = 0;
  i = 0;
  j = 0;
  while (lines[i]) {
    j = 0;
    while (lines[i][j]) {
      if (lines[i][j] != '0')
        lines_dup[i][j] = '.';
      j++;
    }
    i++;
  }
  color_fill(lines_dup, 0, 0);
  i = 0;
  j = 0;
  while (lines_dup[i]) {
    j = 0;
    while (lines_dup[i][j]) {
      if (lines_dup[i][j] == '.' && count_pipes(lines_dup, i, j) % 2) {
        lines_dup[i][j] = 'I';
        count++;
      } else if (lines_dup[i][j] == '.')
        lines_dup[i][j] = '0';
      j++;
    }
    i++;
  }
  i = 0;
  while (lines_dup[i]) {
    ft_printf("%s\n", lines_dup[i]);
    i++;
  }
  ft_printf("Count = %d", count);
}
