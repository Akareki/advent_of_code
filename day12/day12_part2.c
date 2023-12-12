#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

unsigned long long dyn_rec(int i, int j, int group, char *line, int groups[50],
                           unsigned long long *sol_space) {
  unsigned long long res = 0;

  if (group > 16)
    return 0;
  if (i == ft_strlen(line)) {
    if (sol_space[i * 50 * 50 + j * 50 + group] == -1)
      sol_space[i * 50 * 50 + j * 50 + group] =
          (group == groups[j]) && (groups[j + 1] == 0);
    return (sol_space[i * 50 * 50 + j * 50 + group]);
  }
  if (line[i] == '#' || line[i] == '?') {
    if (sol_space[(i + 1) * 50 * 50 + j * 50 + group + 1] == -1)
      sol_space[(i + 1) * 50 * 50 + j * 50 + group + 1] =
          dyn_rec(i + 1, j, group + 1, line, groups, sol_space);
    res += sol_space[(i + 1) * 50 * 50 + j * 50 + group + 1];
  }
  if (line[i] == '.' || line[i] == '?') {
    if (group == 0) {
      if (sol_space[(i + 1) * 50 * 50 + j * 50 + group] == -1)
        sol_space[(i + 1) * 50 * 50 + j * 50 + group] =
            dyn_rec(i + 1, j, 0, line, groups, sol_space);
      res += sol_space[(i + 1) * 50 * 50 + j * 50 + group];
    }
    if (group && group == groups[j]) {
      if (sol_space[(i + 1) * 50 * 50 + (j + 1) * 50 + 0] == -1)
        sol_space[(i + 1) * 50 * 50 + (j + 1) * 50 + 0] =
            dyn_rec(i + 1, j + 1, 0, line, groups, sol_space);
      res += sol_space[(i + 1) * 50 * 50 + (j + 1) * 50 + 0];
    }
  }
  return res;
}

unsigned long long dynamic_arr(char *line, int groups[50],
                               unsigned long long *sol_space) {
  int i = 0;
  int j = 0;
  int k = 0;

  while (i < 200 * 50 * 50) {
    sol_space[i] = -1;
    i++;
  }
  return (dyn_rec(0, 0, 0, line, groups, sol_space));
}

unsigned long long count_arrangements(char *line,
                                      unsigned long long *sol_space) {
  char *ext_line;
  char **split_line;
  int groups[50];
  int i = 0;
  int j = 0;

  split_line = ft_split(line, ' ');
  ext_line = split_line[0];
  while (i < 4) {
    ext_line = ft_strjoin(ext_line, ft_strjoin("?", split_line[0]));
    i++;
  }
  i = 0;
  while (split_line[1][i]) {
    groups[j] = ft_atoi(&split_line[1][i]);
    j++;
    while (ft_isdigit(split_line[1][i]))
      i++;
    if (split_line[1][i])
      i++;
  }
  i = j;
  while (i < 5 * j) {
    groups[i] = groups[i % j];
    i++;
  }
  while (i < 50) {
    groups[i] = 0;
    i++;
  }
  return (dynamic_arr(ext_line, groups, sol_space));
}

int main(void) {
  int fd;
  char *buf;
  char **lines;
  char *line;
  int i = 0;
  unsigned long long count = 0;
  unsigned long long *sol_space;

  sol_space = malloc(200 * 50 * 50 * sizeof(unsigned long long));
  fd = open("day12_input.txt", O_RDONLY);
  buf = malloc(100000);
  read(fd, buf, 100000);
  lines = ft_split(buf, '\n');
  i = 0;
  while (lines[i]) {
    count += count_arrangements(lines[i], sol_space);
    i++;
  }
  printf("Count : %llu\n", count);
}
