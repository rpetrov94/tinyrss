#include "rss.h"
#include "helper.h"

#define PP_RSS(a, b) (pretty_print_node(a, b, NULL))

RSS* create_rss()
{
  RSS* rss = malloc(sizeof(RSS));
  rss->items = NULL;
  rss->categories = NULL;
  rss->image = NULL;
  rss->num_items = 0;
  rss->num_categories = 0;
  rss->title = NULL;
  rss->link = NULL;
  rss->description = NULL;
  rss->language = NULL;
  rss->copyright = NULL;
  rss->pub_date = NULL;
  rss->managing_editor = NULL;
  rss->web_master = NULL;
  rss->last_build_date = NULL;
  rss->generator = NULL;
  rss->docs = NULL;
  rss->ttl = 0;

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

void rss_set_managing_editor(RSS* rss, const char* managing_editor)
{
  set_string(&rss->managing_editor, managing_editor);
}

void rss_set_web_master(RSS* rss, const char* web_master)
{
  set_string(&rss->web_master, web_master);
}

void rss_set_last_build_date(RSS* rss, const char* last_build_date)
{
  set_string(&rss->last_build_date, last_build_date);
}

void rss_set_generator(RSS* rss, const char* generator)
{
  set_string(&rss->generator, generator);
}

void rss_set_docs(RSS* rss, const char* docs)
{
  set_string(&rss->docs, docs);
}

void rss_set_ttl(RSS* rss, const char* ttl)
{
  rss->ttl = strtoul(ttl, NULL, 10);
}

void rss_set_image(RSS* rss, rss_image_t* image)
{
  rss->image = image;
}

void rss_add_category(RSS* rss, char* category)
{
  size_t new_size = rss->num_categories + 1;
  rss->categories = realloc(rss->categories, sizeof(char*) * new_size);
  set_string(&rss->categories[rss->num_categories++], category);
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

void rss_delete_categories(RSS* rss)
{
  int i;
  for (i = 0; i < rss->num_categories; i++)
  {
    free(rss->categories[i]);
  }

  free(rss->categories);
}

void delete_rss(RSS* rss)
{
  free(rss->title);
  free(rss->link);
  free(rss->description);
  free(rss->language);
  free(rss->copyright);
  free(rss->managing_editor);
  free(rss->web_master);
  free(rss->pub_date);
  free(rss->last_build_date);
  free(rss->generator);
  free(rss->docs);
  if (rss->image != NULL) delete_rss_image(rss->image);
  rss_delete_items(rss);
  rss_delete_categories(rss);

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
  PP_RSS("managing_editor", rss->managing_editor);
  PP_RSS("web_master", rss->web_master);
  PP_RSS("pub_date", rss->pub_date); 
  PP_RSS("last_build_date", rss->last_build_date);
  PP_RSS("generator", rss->generator);
  PP_RSS("docs", rss->docs);

  print_rss_image(rss->image);

  int i;
  for (i = 0; i < rss->num_items; i++)
  {
    print_rss_item(rss->items[i]);
  }
}