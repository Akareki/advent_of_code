#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

int game_possible(char *line) {
  int nb = 0;
  int i = 0;

  while (line[i] != ':')
    i++;
  while (line[i]) {
    while (line[i] && !ft_isdigit(line[i]))
      i++;
    nb = ft_atoi(line + i);
    while (ft_isdigit(line[i]))
      i++;
    i += 1;
    if (line[i] == 'r' && nb > 12)
      return 0;
    if (line[i] == 'g' && nb > 13)
      return 0;
    if (line[i] == 'b' && nb > 14)
      return 0;
  }
  return 1;
}

int main(void) {
  int fd;
  char buf[20000];
  char **lines;
  int i = 0;
  int count = 0;

  fd = open("day2_input.txt", O_RDONLY);
  buf[read(fd, buf, 20000)] = '\0';
  lines = ft_split(buf, '\n');
  while (lines[i]) {
    if (game_possible(lines[i]))
      count += i + 1;
    ft_printf("Game : %d Possible : %d\n", i + 1, game_possible(lines[i]));
    i++;
  }
  ft_printf("Count : %d\n", count);
}
