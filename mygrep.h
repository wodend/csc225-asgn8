#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
  char line[100];
  int linenum;
  int location;
  struct node* next;
};

struct LinkedList {
  struct node* head;
  struct node* tail;
};

void fileio(char* program, char* filename, char* search);
void readfile(FILE* stream, char* search);
void printlst(struct LinkedList* occlist);
/*
struct node* reverse(struct node* occlist);
void revllst(struct node* list);
*/
