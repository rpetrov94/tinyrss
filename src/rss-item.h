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
} rss_item_t;

rss_item_t* create_rss_item();

void rss_item_set_title(rss_item_t*, const char*);
void rss_item_set_description(rss_item_t*, const char*);
void rss_item_set_link(rss_item_t*, const char*);
void rss_item_set_author(rss_item_t*, const char*);
void rss_item_set_guid(rss_item_t*, const char*);
void rss_item_set_pub_date(rss_item_t*, const char*);
void rss_item_add_category(rss_item_t*, char*);

void delete_rss_item(rss_item_t*);

#endif
