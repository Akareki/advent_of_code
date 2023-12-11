#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

unsigned int count_paths(char **galaxy, int x, int y) {
  int count = 0;
  int i = x;
  int j = y + 1;

  while (galaxy[i]) {
    while (galaxy[i][j]) {
      if (galaxy[i][j] == '#')
        count += i - x + ((j - y) * (j > y) + (y - j) * (j < y));
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
  char **galaxy;
  char *line;
  int i;
  int j;
  int *empty_lines;
  int *empty_cols;
  int x = 0;
  int y = 0;
  int y_tmp = 0;
  unsigned int count = 0;

  fd = open("day11_input.txt", O_RDONLY);
  read(fd, buf, 100000);
  lines = ft_split(buf, '\n');
  galaxy = ft_calloc(200, sizeof(char *));
  while (x < 200) {
    galaxy[x] = ft_calloc(200, sizeof(char));
    x++;
  }
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
  i = 0;
  j = 0;
  x = 0;
  y = 0;
  while (lines[i]) {
    j = 0;
    y = 0;
    while (lines[i][j]) {
      galaxy[x][y] = lines[i][j];
      y++;
      j++;
      if (empty_cols[j]) {
        galaxy[x][y] = '.';
        y++;
      }
    }
    x++;
    if (empty_lines[i]) {
      galaxy[x] = ft_strdup(galaxy[x - 1]);
      x++;
    }
    i++;
  }
  galaxy[x] = NULL;
  x = 0;
  while (galaxy[x])
    ft_printf("%s\n", galaxy[x++]);
  x = 0;
  y = 0;
  count = 0;
  while (galaxy[x]) {
    y = 0;
    while (galaxy[x][y]) {
      if (galaxy[x][y] == '#')
        count += count_paths(galaxy, x, y);
      y++;
    }
    x++;
  }
  ft_printf("Count : %d\n", count);
}
