#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rss.h"
#include "rss-item.h"
#include "parser.h"
#include "fetcher.h"

void usage();

int
main(int argc, const char* argv[])
{
  if (argc < 2)
  {
    usage();
    return 1;
  }

  fetch_data_t* fetch_data = fetch_document(argv[1]);
  rss_t* rss = parse_string(fetch_data->data);
  print_rss(rss);

  delete_fetch_data(fetch_data);
  delete_rss(rss);

  return 0;
}

void
usage()
{
  printf("usage: tinyrss <URL>\n");
}