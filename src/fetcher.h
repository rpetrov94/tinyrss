#ifndef FETCHER_H
#define FETCHER_H

#include <stdlib.h>

typedef struct
{
  char* data;
  size_t size;
} fetch_data_t;

fetch_data_t* fetch_document(const char* uri);

void delete_fetch_data(fetch_data_t*);

#endif