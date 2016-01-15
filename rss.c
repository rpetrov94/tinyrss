#include "rss.h"
#include "helper.h"

RSS* create_rss()
{
  RSS* rss = (RSS*) malloc(sizeof(RSS));
  rss->num_items = 0;

  return rss;
}

void rss_set_title(RSS* rss, const char* title)
{
  set_string(&rss->title, title);
}

void rss_set_link(RSS* rss, const char* link)
{
  set_string(&rss->link, link);
}

void rss_set_description(RSS* rss, const char* description)
{
  set_string(&rss->description, description);
}

void rss_set_language(RSS* rss, const char* language)
{
  set_string(&rss->language, language);
}

void rss_set_copyright(RSS* rss, const char* copyright)
{
  set_string(&rss->copyright, copyright);
}

void rss_set_pub_date(RSS* rss, const char* pub_date)
{
  set_string(&rss->pub_date, pub_date);
}

void rss_add_rss_item(RSS* rss, RSSItem* rss_item)
{
  rss->items = (RSSItem**) realloc(rss->items, rss->num_items + 1);
  rss->items[rss->num_items++] = rss_item;
}

void rss_delete_items(RSS* rss)
{
  int i;
  for (i = 0; i < rss->num_items; i++)
  {
    delete_rss_item(rss->items[i]);
  }

  free(rss->items);
}

void delete_rss(RSS* rss)
{
  free(rss->title);
  free(rss->link);
  free(rss->description);
  free(rss->language);
  free(rss->copyright);
  free(rss->pub_date);
  rss_delete_items(rss);

  free(rss);
}