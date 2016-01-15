#include "rss-item.h"
#include "helper.h"

#include <stdlib.h>

RSSItem* create_rss_item()
{
  RSSItem* item = (RSSItem*) malloc(sizeof(RSSItem));

  return item;
}

void set_title(RSSItem* rss_item, const char* title)
{
  set_string(&rss_item->title, title);
}

void delete_rss_item(RSSItem* rss_item)
{
  free(rss_item->title);
  free(rss_item);
}