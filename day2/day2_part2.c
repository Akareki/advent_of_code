#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

int game_power(char *line) {
  int nb = 0;
  int i = 0;
  int rpow = 0;
  int gpow = 0;
  int bpow = 0;

  while (line[i] != ':')
    i++;
  while (line[i]) {
    while (line[i] && !ft_isdigit(line[i]))
      i++;
    nb = ft_atoi(line + i);
    while (ft_isdigit(line[i]))
      i++;
    i += 1;
    if (line[i] == 'r' && nb > rpow)
      rpow = nb;
    if (line[i] == 'g' && nb > gpow)
      gpow = nb;
    if (line[i] == 'b' && nb > bpow)
      bpow = nb;
  }
  return rpow * bpow * gpow;
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
    count += game_power(lines[i]);
    ft_printf("Game : %d Power : %d\n", i + 1, game_power(lines[i]));
    i++;
  }
  ft_printf("Count : %d\n", count);
}
