#ifndef FETCHER_H
#define FETCHER_H

#include <stdlib.h>

typedef struct
{
  char* data;
  size_t size;
} FetchData;

FetchData* fetch_document(const char* uri);

void delete_fetch_data(FetchData*);

#endif