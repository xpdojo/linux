/*
gcc -pg -g read.c

sudo uftrace record -K 30 -d read.uftrace.data a.out
uftrace replay -d read.uftrace.data | grep ext4

echo 3 | sudo tee /proc/sys/vm/drop_caches

sudo uftrace record -K 30 -d read2.uftrace.data a.out
uftrace replay -d read2.uftrace.data | grep ext4
*/
#include <stdio.h>
#include <stdlib.h>

// hello linux filesystem\n
#define SIZE 24

void main()
{
  FILE *fp = fopen("hello.txt", "r");
  char buf[BUFSIZ];

  if (fp)
  {
    fread(buf, SIZE, 1, fp);
    printf("%s", buf);
    fclose(fp);
  }
}
