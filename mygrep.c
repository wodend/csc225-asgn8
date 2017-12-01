#include "mygrep.h"

int main(int argc, char** argv) {
  if (argc != 3) {
    printf("myGrep: improper number of arguments\n");
    printf("Usage: ./mygrep <filename> <word>\n");
    return 1;
  } else {
    fileio(*argv, *(argv + 1), *(argv + 2));
  }
  return 0;
}

void fileio(char* program, char* filename, char* search) {
  FILE* stream = fopen(filename, "r");

  if (!stream) {
    printf("Unable to open file: %s\n", filename);
  } else { 
    printf("./mygrep %s %s\n", filename, search);
    readfile(stream, search);
  }
}

void readfile(FILE* stream, char* search) {
  int location;
  char line[100];
  char templine[100];
  struct node* current = (struct node*)malloc(sizeof(struct node)); 
  int numlines = 0;
  int occur = 0;
  char longest[100] = "\0";
  struct LinkedList* occlist = (struct LinkedList*)malloc(
      sizeof(struct LinkedList));
  char* temp = (char*)malloc(sizeof(char*) * 100);
  occlist->head = NULL;

  while (fgets(line, 100, stream)) {
    strcpy(templine, line);
    temp = strtok(templine, " \n");
    location = 0;
    while (temp) {
      if (strcmp(temp, search) == 0) {
        ++occur;
        current = (struct node*)malloc(sizeof(struct node));
        strcpy(current->line, line);
        current->linenum = numlines;
        current->location = location;
        if (!occlist->head) {
          occlist->head = current;
          occlist->tail = current;
        } else {
          occlist->tail->next = current;
          occlist->tail = current;
        }
      }
      temp = strtok(NULL, " \n");
      ++location;
    }
    if (strlen(line) > strlen(longest)) { strcpy(longest, line); }
    ++numlines;
  }
  fclose(stream);
  printf("longest line: %s", longest);
  printf("num chars: %lu\n", strlen(longest));
  printf("num lines: %d\n", numlines);
  printf("total occurrences of word: %d\n", occur);
  printlst(occlist);
  free(current);
  free(occlist);
}

void printlst(struct LinkedList* occlist) {
  struct node* current = occlist->head;
  while (current) {
    printf("line %d; word %d; %s", current->linenum, current->location,
        current->line);
    current = current->next;
  }
}
