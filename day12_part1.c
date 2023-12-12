#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

int all_filled(char *line) {
  int i = 0;

  while (line[i] != ' ') {
    if (line[i] == '?')
      return (0);
    i++;
  }
  return (1);
}

int is_valid(char *line, int groups[10]) {
  int i = 0;
  int group = 0;
  int j = 0;

  while (line[i] != ' ') {
    while (line[i] == '.')
      i++;
    while (line[i] == '#') {
      i++;
      group++;
    }
    if (group != groups[j])
      return (0);
    j++;
    group = 0;
  }
  if (groups[j] == 0) {
    ft_printf("Valid line : %s\n", line);
    return (1);
  }
  return (0);
}

int backtrack_arrangements(char *line, int groups[10]) {
  int i = 0;
  int count = 0;
  char *line_dup;

  if (all_filled(line))
    return (is_valid(line, groups));
  line_dup = ft_strdup(line);
  while (line_dup[i] != ' ' && line_dup[i] != '?')
    i++;
  if (line_dup[i] == '?') {
    line_dup[i] = '.';
    count += backtrack_arrangements(line_dup, groups);
    line_dup[i] = '#';
    count += backtrack_arrangements(line_dup, groups);
  }
  return (count);
}

int count_arrangements(char *line) {
  int groups[10];
  int i = 0;
  int j = 0;

  while (i < 10) {
    groups[i] = 0;
    i++;
  }
  i = 0;
  while (line[i] && line[i] != ' ')
    i++;
  i++;
  while (line[i]) {
    groups[j] = ft_atoi(&line[i]);
    j++;
    while (ft_isdigit(line[i]))
      i++;
    if (line[i])
      i++;
  }
  return (backtrack_arrangements(line, groups));
}

int main(void) {
  int fd;
  char *buf;
  char **lines;
  char *line;
  int i;
  int count = 0;
  int line_sum;

  fd = open("day12_input.txt", O_RDONLY);
  buf = malloc(100000);
  read(fd, buf, 100000);
  lines = ft_split(buf, '\n');
  i = 0;
  while (lines[i]) {
    ft_printf("Origi line : %s\n", lines[i]);
    count += count_arrangements(lines[i]);
    i++;
  }
  ft_printf("Count : %d\n", count);
}
