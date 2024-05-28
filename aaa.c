#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 101
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void perm(char *list, int i, int n) {
  /* generate all the permutations of list[i] to list[n] */
  int j, temp;
  if (i == n) {
    for (j = 0; j <= n; j++) printf("%c", list[j]);
    printf("\n"); // Add a newline character at the end
  } else { /* list[i] to list[n] has more than one permutation, generate these
              recursively*/
    for (j = i; j <= n; j++) {
      SWAP(list[i], list[j], temp);
      perm(list, i + 1, n);
      SWAP(list[i], list[j], temp);
    }
  }
}

int main() {
  char list[MAX_SIZE] = "ABC"; // Example list
  int n = strlen(list) - 1;
  perm(list, 0, n);
  return 0;
}
