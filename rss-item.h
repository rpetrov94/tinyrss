#ifndef RSS_ITEM_H
#define RSS_ITEM_H

typedef struct
{
  char* title;
  char* description;
  char* link;
  char* author;
  char* guid;
  char* pubDate;
} RSSItem;

RSSItem* create_rss_item();

void set_title(RSSItem* rss_item, const char* title);

void delete_rss_item(RSSItem* rss_item);

#endif