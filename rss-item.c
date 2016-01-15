#include "rss-item.h"
#include "helper.h"

#include <stdlib.h>

#define PP_RSS_ITEM(a, b) (pretty_print_node(a, b, "\t"))

RSSItem* create_rss_item()
{
  RSSItem* item = malloc(sizeof(RSSItem));
  item->title = NULL;
  item->description = NULL;
  item->link = NULL;
  item->author = NULL;
  item->guid = NULL;
  item->pub_date = NULL;

  return item;
}

void rss_item_set_title(RSSItem* rss_item, const char* title)
{
  set_string(&rss_item->title, title);
}

void rss_item_set_description(RSSItem* rss_item, const char* description)
{
  set_string(&rss_item->description, description);
}

void rss_item_set_link(RSSItem* rss_item, const char* link)
{
  set_string(&rss_item->link, link);
}

void rss_item_set_author(RSSItem* rss_item, const char* author)
{
  set_string(&rss_item->author, author);
}

void rss_item_set_guid(RSSItem* rss_item, const char* guid)
{
  set_string(&rss_item->guid, guid);
}

void rss_item_set_pub_date(RSSItem* rss_item, const char* pub_date)
{
  set_string(&rss_item->pub_date, pub_date);
}

void delete_rss_item(RSSItem* rss_item)
{
  free(rss_item->title);
  free(rss_item->description);
  free(rss_item->link);
  free(rss_item->author);
  free(rss_item->guid);
  free(rss_item->pub_date);
  free(rss_item);
}

void print_rss_item(RSSItem* rss_item)
{
  PP_RSS_ITEM("title", rss_item->title);
  PP_RSS_ITEM("description", rss_item->description);
  PP_RSS_ITEM("link", rss_item->link);
  PP_RSS_ITEM("author", rss_item->author);
  PP_RSS_ITEM("guid", rss_item->guid);
  PP_RSS_ITEM("pub_date", rss_item->pub_date);
}