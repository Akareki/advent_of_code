#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

int main(void) {
  int fd;
  char *buf;
  char **lines;
  char *line;
  int i;
  int count;
  int line_sum;

  fd = open("day11_input.txt", O_RDONLY);
  buf = malloc(100000);
  read(fd, buf, 100000);
  lines = ft_split(buf, '\n');
  i = 0;
  count = 0;
  while (i < 1000) {
    line = ft_strtrim(lines[i], "azertyuiopqsdfghjklmwxcvbn");
    line_sum = 10 * (line[0] - '0') + line[ft_strlen(line) - 1] - '0';
    ft_printf("Line %d : %s Count : %d\n", i, line, line_sum);
    count += line_sum;
    i++;
  }
  ft_printf("Count : %d\n", count);
}
