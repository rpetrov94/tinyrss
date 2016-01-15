#ifndef RSS_H
#define RSS_H

#include "rss-item.h"

#include <stdlib.h>

typedef struct
{
  char* title;
  char* link;
  char* description;
  char* language;
  char* copyright;
  char* pub_date;
  RSSItem** items;
  size_t num_items;
} RSS;

RSS* create_rss();

void rss_set_title(RSS*, const char*);
void rss_set_link(RSS*, const char*);
void rss_set_description(RSS*, const char*);
void rss_set_language(RSS*, const char*);
void rss_set_copyright(RSS*, const char*);
void rss_set_pub_date(RSS*, const char*);
void rss_add_rss_item(RSS*, RSSItem*);

void delete_rss(RSS*);

void print_rss(RSS*);

#endif