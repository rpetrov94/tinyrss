#include "helper.h"

#include <stdlib.h>
#include <string.h>

void set_string(char** target, const char* source)
{
  size_t len = strlen(source);
  *target = (char*) malloc(sizeof(char) * (len + 1));
  strcpy(*target, source);
}