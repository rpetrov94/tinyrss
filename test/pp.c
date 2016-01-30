#include "pp.h"
#include "helper.h"

#include <stdio.h>

#define PP_RSS(a, b) (pretty_print_node(a, b, NULL))
#define PP_RSS_ITEM(a, b) (pretty_print_node(a, b, "\t"))
#define PP_RSS_IMAGE(a, b) (pretty_print_node(a, b, "\t"))

void
pp_rss_image(rss_image_t* image)
{
  PP_RSS_IMAGE("url", image->url);
  PP_RSS_IMAGE("title", image->title);
  PP_RSS_IMAGE("link", image->link);
  PP_RSS_IMAGE("description", image->description);
}

void
print_rss_item_categories(rss_item_t* rss_item)
{
  int i;
  printf("-- categories --\n");
  for (i = 0; i < rss_item->num_categories; i++)
  {
    pretty_print_node("", rss_item->categories[i], "\t\t");
  }
}

void
pp_rss_item(rss_item_t* rss_item)
{
  PP_RSS_ITEM("title", rss_item->title);
  PP_RSS_ITEM("description", rss_item->description);
  PP_RSS_ITEM("link", rss_item->link);
  PP_RSS_ITEM("author", rss_item->author);
  PP_RSS_ITEM("guid", rss_item->guid);
  PP_RSS_ITEM("pub_date", rss_item->pub_date);
  print_rss_item_categories(rss_item);
}

void
pp_rss(rss_t* rss)
{
  PP_RSS("title", rss->title);
  PP_RSS("link", rss->link);
  PP_RSS("description", rss->description);
  PP_RSS("language", rss->language);
  PP_RSS("copyright", rss->copyright);
  PP_RSS("pub_date", rss->pub_date);
  PP_RSS("managing_editor", rss->managing_editor);
  PP_RSS("web_master", rss->web_master);
  PP_RSS("pub_date", rss->pub_date);
  PP_RSS("last_build_date", rss->last_build_date);
  PP_RSS("generator", rss->generator);
  PP_RSS("docs", rss->docs);

  printf("%s\n", "maybe printing image");
  if (rss->image != NULL) pp_rss_image(rss->image);

  int i;
  for (i = 0; i < rss->num_items; i++)
  {
    pp_rss_item(rss->items[i]);
  }
}
