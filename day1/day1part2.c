#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char *digify(char *line) {
  char *digiline;
  int i = 0;
  int j = 0;
  int digit = 0;
  char **digits;

  digiline = malloc(1000);
  digits = malloc(9 * sizeof(char *));
  digits[0] = "one";
  digits[1] = "two";
  digits[2] = "three";
  digits[3] = "four";
  digits[4] = "five";
  digits[5] = "six";
  digits[6] = "seven";
  digits[7] = "eight";
  digits[8] = "nine";
  while (i < ft_strlen(line)) {
    digit = 0;
    while (digit < 9) {
      if (ft_strncmp(line + i, digits[digit], ft_strlen(digits[digit])) == 0) {
        digiline[j] = 1 + digit + '0';
        j++;
        break;
      }
      digit++;
    }
    digiline[j] = line[i];
    i++;
    j++;
  }
  digiline[j] = '\0';
  return (digiline);
}

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
    line = ft_strtrim(digify(lines[i]), "azertyuiopqsdfghjklmwxcvbn");
    line_sum = 10 * (line[0] - '0') + line[ft_strlen(line) - 1] - '0';
    ft_printf("Line %d : %s Digiline : %s Sum = %d\n", i, lines[i], line,
              line_sum);
    count += line_sum;
    i++;
  }
  ft_printf("Count : %d\n", count);
}
