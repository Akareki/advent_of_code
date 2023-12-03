#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int is_part(char **lines, int i, int j) {
  while (ft_isdigit(lines[i][j])) {
    if ((i != 0 && j != 0 && !ft_isdigit(lines[i - 1][j - 1]) &&
         lines[i - 1][j - 1] != '.') ||
        (i != 0 && !ft_isdigit(lines[i - 1][j]) && lines[i - 1][j] != '.') ||
        (j != 0 && !ft_isdigit(lines[i][j - 1]) && lines[i][j - 1] != '.') ||
        (i != 0 && lines[i - 1][j + 1] && !ft_isdigit(lines[i - 1][j + 1]) &&
         lines[i - 1][j + 1] != '.') ||
        (j != 0 && i < 139 && !ft_isdigit(lines[i + 1][j - 1]) &&
         lines[i + 1][j - 1] != '.') ||
        (i < 139 && lines[i + 1][j + 1] && !ft_isdigit(lines[i + 1][j + 1]) &&
         lines[i + 1][j + 1] != '.') ||
        (i < 139 && !ft_isdigit(lines[i + 1][j]) && lines[i + 1][j] != '.') ||
        (lines[i][j + 1] && !ft_isdigit(lines[i][j + 1]) &&
         lines[i][j + 1] != '.'))
      return 1;
    j++;
  }
  return 0;
}

int main(void) {
  int fd;
  char buf[1000000];
  char **lines;
  int i = 0;
  int j = 0;
  int count = 0;

  fd = open("day3_input.txt", O_RDONLY);
  buf[read(fd, buf, 1000000)] = '\0';
  lines = ft_split(buf, '\n');
  while (lines[i]) {
    j = 0;
    while (lines[i][j]) {
      if (!ft_isdigit(lines[i][j]))
        j++;
      if (ft_isdigit(lines[i][j]) && is_part(lines, i, j)) {
        printf("%d\n", ft_atoi(lines[i] + j));
        count += ft_atoi(lines[i] + j);
      }
      while (ft_isdigit(lines[i][j]))
        j++;
    }
    i++;
  }
  ft_printf("Count : %d\n", count);
}
