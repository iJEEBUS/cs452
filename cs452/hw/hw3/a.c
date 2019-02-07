#include <stdio.h>
#include <unistd.h>

int main() {
  int i;
  int num_forks = 1;

  for (i = 0; i < 4; i++) {
    pid_t f = fork();

    num_forks += 1;
    //printf("Forks: %d\n ", (num_forks));
    printf("PIDs: %d\n", (f));
  }
  return 0;
}
