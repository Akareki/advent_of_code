#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_beam_dir {
  int up;
  int down;
  int right;
  int left;
} beam_dir;

int already_passed(beam_dir *dir, int down, int right) {
  int passed = 0;

  passed = (dir->down && down == 1) || (dir->right && right == 1) ||
           (dir->left && right == -1) || (dir->up && down == -1);
  if (down == 1)
    dir->down = 1;
  if (right == 1)
    dir->right = 1;
  if (down == -1)
    dir->up = 1;
  if (right == -1)
    dir->left = 1;
  return (passed);
}

void beam(char **lines, beam_dir ***energy, int i, int j, int down, int right) {
  char tile;

  if (i < 0 || j < 0 || !lines[i] || !lines[i][j] ||
      already_passed(energy[i][j], down, right))
    return;
  tile = lines[i][j];
  if (tile == '.')
    return (beam(lines, energy, i + down, j + right, down, right));
  if (tile == '\\')
    return (beam(lines, energy, i + right, j + down, right, down));
  if (tile == '/')
    return (beam(lines, energy, i - right, j - down, -right, -down));
  if (tile == '|') {
    if (down)
      return (beam(lines, energy, i + down, j + right, down, right));
    else if (right) {
      beam(lines, energy, i + 1, j, 1, 0);
      beam(lines, energy, i - 1, j, -1, 0);
      return;
    }
  }
  if (tile == '-') {
    if (right)
      return (beam(lines, energy, i + down, j + right, down, right));
    else if (down) {
      beam(lines, energy, i, j + 1, 0, 1);
      beam(lines, energy, i, j - 1, 0, -1);
      return;
    }
  }
}

int main(void) {
  int fd;
  char *buf;
  char **lines;
  beam_dir ***energy;
  beam_dir *tmp;
  char *line;
  int i = 0;
  int j = 0;
  int count = 0;
  int line_sum;

  fd = open("day16_input.txt", O_RDONLY);
  // fd = open("test.txt", O_RDONLY);
  buf = malloc(100000);
  read(fd, buf, 100000);
  lines = ft_split(buf, '\n');
  energy = ft_calloc(110, sizeof(beam_dir **));
  i = 0;
  while (lines[i]) {
    j = 0;
    energy[i] = ft_calloc(110, sizeof(beam_dir *));
    while (lines[i][j]) {
      tmp = ft_calloc(1, sizeof(beam_dir));
      energy[i][j] = tmp;
      j++;
    }
    i++;
  }
  i = 0;
  beam(lines, energy, 0, 0, 0, 1);
  while (energy[i]) {
    j = 0;
    while (energy[i][j]) {
      count += energy[i][j]->down || energy[i][j]->right || energy[i][j]->up ||
               energy[i][j]->left;
      j++;
    }
    i++;
  }
  ft_printf("Count : %d\n", count);
}
