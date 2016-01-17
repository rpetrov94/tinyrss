#ifndef RSS_ITEM_H
#define RSS_ITEM_H

#include <stdlib.h>

typedef struct
{
  char* title;
  char* description;
  char* link;
  char* author;
  char* guid;
  char* pub_date;
  char** categories;
  size_t num_categories;
} RSSItem;

RSSItem* create_rss_item();

void rss_item_set_title(RSSItem*, const char*);
void rss_item_set_description(RSSItem*, const char*);
void rss_item_set_link(RSSItem*, const char*);
void rss_item_set_author(RSSItem*, const char*);
void rss_item_set_guid(RSSItem*, const char*);
void rss_item_set_pub_date(RSSItem*, const char*);
void rss_item_add_category(RSSItem*, char*);

void delete_rss_item(RSSItem*);

void print_rss_item(RSSItem*);

#endif