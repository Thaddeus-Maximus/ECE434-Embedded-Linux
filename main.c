#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv) {
  int rows = 8;
  if (argc > 1)
    rows = atoi(argv[1]);
  int cols = rows;
  if (argc > 2)
    cols = atoi(argv[2]);

  short *output = malloc(rows*cols*sizeof(short));
  
  printf("Making a board that is %d x %d:\n", rows, cols);

  free(output);
  return 0;
}
