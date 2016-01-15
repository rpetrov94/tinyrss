#include "helper.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void set_string(char** target, const char* source)
{
  size_t len = strlen(source);
  *target = (char*) malloc(sizeof(char) * (len + 1));
  strcpy(*target, source);
}

void pretty_print_node(char* name, char* content, char* optional)
{
  if (optional == NULL) optional = "";
  printf("%s%s: %s\n", optional, name, content);
}