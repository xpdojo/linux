/*
$ ulimit -n 1024
$ prlimit -n

RESOURCE DESCRIPTION              SOFT    HARD UNITS
NOFILE   max number of open files 1024 1048576 files

$ gcc max_open_file_test.c
$ ./a.out

failed fd 995

$ rm -f max-hello*.txt
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void main()
{
  FILE *fp[4096];
  int i, files_max;
  char filename[128];

  for (i = 0; i < 4096; i++)
  {
    sprintf(filename, "max-hello%d.txt", i);
    fp[i] = fopen(filename, "w");

    if (fp[i])
    {
      fprintf(fp[i], "hello linux filesystem\n");
    }
    else
    {
      printf("failed fd %d\n", i);
      break;
    }
    printf("%s\n", filename);
  }

  files_max = i;

  for (i = 0; i < files_max; i++)
    fclose(fp[i]);
}
