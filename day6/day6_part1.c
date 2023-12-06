#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int i = 1;
  long long j = 0;
  long long ways = 0;
  long long count = 1;

  while (i < argc) {
    ways = 0;
    j = 0;
    while (j < atoll(argv[i])) {
      if (j * (atoll(argv[i]) - j) > atoll(argv[i + 1])) {
        ways++;
      }
      j++;
    }
    printf("Ways : %lld\n", ways);
    printf("i : %d\n", i);
    count = ways * count;
    i += 2;
  }
  printf("Count : %lld\n", count);
}
