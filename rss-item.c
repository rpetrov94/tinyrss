#include "rss-item.h"
#include "helper.h"

#include <stdio.h>
#include <stdlib.h>

#define PP_RSS_ITEM(a, b) (pretty_print_node(a, b, "\t"))

RSSItem* create_rss_item()
{
  RSSItem* item = malloc(sizeof(RSSItem));
  item->categories = NULL;
  item->num_categories = 0;
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

void rss_item_add_category(RSSItem* rss_item, char* category)
{
  size_t new_size = rss_item->num_categories + 1;
  rss_item->categories = realloc(rss_item->categories, sizeof(char*) * new_size);
  set_string(&rss_item->categories[rss_item->num_categories++], category);
}

void delete_rss_item_categories(RSSItem* rss_item)
{
  int i;
  for (i = 0; i < rss_item->num_categories; i++)
  {
    free(rss_item->categories[i]);
  }
  free(rss_item->categories);
}

void delete_rss_item(RSSItem* rss_item)
{
  free(rss_item->title);
  free(rss_item->description);
  free(rss_item->link);
  free(rss_item->author);
  free(rss_item->guid);
  free(rss_item->pub_date);
  delete_rss_item_categories(rss_item);
  
  free(rss_item);
}

void print_rss_item_categories(RSSItem* rss_item)
{
  int i;
  printf("-- categories --\n");
  for (i = 0; i < rss_item->num_categories; i++)
  {
    pretty_print_node("", rss_item->categories[i], "\t\t");
  }
}

void print_rss_item(RSSItem* rss_item)
{
  PP_RSS_ITEM("title", rss_item->title);
  PP_RSS_ITEM("description", rss_item->description);
  PP_RSS_ITEM("link", rss_item->link);
  PP_RSS_ITEM("author", rss_item->author);
  PP_RSS_ITEM("guid", rss_item->guid);
  PP_RSS_ITEM("pub_date", rss_item->pub_date);
  print_rss_item_categories(rss_item);
}