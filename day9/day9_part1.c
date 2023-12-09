#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int all_zero(int *seq, int size) {
  int i = 0;

  while (i < size) {
    if (seq[i] != 0)
      return (0);
    i++;
  }
  return (1);
}

int derive_add(int *seq, int size) {
  int i = 0;
  int *derived_seq;

  if (all_zero(seq, size)) {
    seq[size] = 0;
    return (0);
  }
  derived_seq = ft_calloc(size, sizeof(int));
  while (i < size - 1) {
    derived_seq[i] = seq[i + 1] - seq[i];
    i++;
  }
  seq[size] = seq[size - 1] + derive_add(derived_seq, size - 1);
  free(derived_seq);
  i = 0;
  return seq[size];
}

int interpolate(char *line) {
  int *seq;
  char **nb_str;
  int size;
  int i = 0;

  nb_str = ft_split(line, ' ');
  while (nb_str[i])
    i++;
  size = i;
  seq = ft_calloc(size + 1, sizeof(int));
  i = 0;
  while (i < size) {
    seq[i] = ft_atoi(nb_str[i]);
    i++;
  }
  return (derive_add(seq, size));
}

int main(void) {
  int fd;
  char *buf;
  char **lines;
  char *line;
  int i;
  int count;
  int line_sum;

  fd = open("day9_input.txt", O_RDONLY);
  buf = malloc(100000);
  read(fd, buf, 100000);
  lines = ft_split(buf, '\n');
  i = 0;
  count = 0;
  while (lines[i]) {
    count += interpolate(lines[i]);
    i++;
  }
  ft_printf("Count : %d\n", count);
}
