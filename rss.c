#include "rss.h"
#include "helper.h"

#define PP_RSS(a, b) (pretty_print_node(a, b, NULL))

RSS* create_rss()
{
  RSS* rss = malloc(sizeof(RSS));
  rss->items = malloc(sizeof(RSSItem**));
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
  size_t new_size = rss->num_items + 1;
  rss->items = realloc(rss->items, sizeof(RSSItem*) * new_size);
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

void print_rss(RSS* rss)
{
  PP_RSS("title", rss->title);
  PP_RSS("link", rss->link);
  PP_RSS("description", rss->description);
  PP_RSS("language", rss->language);
  PP_RSS("copyright", rss->copyright);
  PP_RSS("pub_date", rss->pub_date);

  int i;
  for (i = 0; i < rss->num_items; i++)
  {
    print_rss_item(rss->items[i]);
  }
}