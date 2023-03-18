/*
gcc memory_proc.c
https://www.reallinux.co.kr/
*/
#include <stdio.h>
#include <stdlib.h>

struct contact_info
{
  char *name;
  char *phone_number;
  struct contact_info *next;
};

void insert(struct contact_info **head)
{
  struct contact_info *new_node = (struct contact_info *)malloc(sizeof(struct contact_info));

  printf("\n(2) Start insert(&contact_head);\n");

  printf("'new_node' variable address(stack) : %p\n", &new_node);
  printf("'new_node' variable data(heap) : %p\n", new_node);

  *head = new_node;

  printf("'head' variable address(stack) : %p\n", &head);
  printf("'head' variable data: %p\n", head);
  printf("'contact_head' variable data: %p\n", *head);

  printf("\n(3) End insert(&contact_head);\n");
}

#define SIZE 2048
void main()
{
  /* head node for contacts list */
  struct contact_info *contact_head = NULL;
  int a = 1;
  char buf[SIZE] = {0};

  printf("'a' variable address(stack) : %p\n", &a);
  printf("'a' variable data: %d\n", a);

  printf("\n(1) Before insert(&contact_head);\n");
  printf("'contact_head' variable address(stack) : %p\n", &contact_head);
  printf("'contact_head' a variable data: %p\n", contact_head);

  insert(&contact_head);

  printf("\n(4) After insert(&contact_head);\n");
  printf("'contact_head' variable address(stack) : %p\n", &contact_head);
  printf("'contact_head' a variable data: %p\n", contact_head);

  printf("\n==== process memory map ====\n");
  FILE *fp = fopen("/proc/self/maps", "r");
  if (fp)
  {
    fread(buf, SIZE, 1, fp);
    printf("%s", buf);
    fclose(fp);
  }
}
