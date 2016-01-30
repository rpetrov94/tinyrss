#include "rss.h"
#include "common.h"

rss_t*
create_rss()
{
  rss_t* rss = malloc(sizeof(rss_t));
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

void
rss_set_title(rss_t* rss, const char* title)
{
  set_string(&rss->title, title);
}

void
rss_set_link(rss_t* rss, const char* link)
{
  set_string(&rss->link, link);
}

void
rss_set_description(rss_t* rss, const char* description)
{
  set_string(&rss->description, description);
}

void
rss_set_language(rss_t* rss, const char* language)
{
  set_string(&rss->language, language);
}

void
rss_set_copyright(rss_t* rss, const char* copyright)
{
  set_string(&rss->copyright, copyright);
}

void
rss_set_pub_date(rss_t* rss, const char* pub_date)
{
  set_string(&rss->pub_date, pub_date);
}

void
rss_set_managing_editor(rss_t* rss, const char* managing_editor)
{
  set_string(&rss->managing_editor, managing_editor);
}

void
rss_set_web_master(rss_t* rss, const char* web_master)
{
  set_string(&rss->web_master, web_master);
}

void
rss_set_last_build_date(rss_t* rss, const char* last_build_date)
{
  set_string(&rss->last_build_date, last_build_date);
}

void
rss_set_generator(rss_t* rss, const char* generator)
{
  set_string(&rss->generator, generator);
}

void
rss_set_docs(rss_t* rss, const char* docs)
{
  set_string(&rss->docs, docs);
}

void
rss_set_ttl(rss_t* rss, const char* ttl)
{
  rss->ttl = strtoul(ttl, NULL, 10);
}

void
rss_set_image(rss_t* rss, rss_image_t* image)
{
  rss->image = image;
}

void
rss_add_category(rss_t* rss, char* category)
{
  size_t new_size = rss->num_categories + 1;
  rss->categories = realloc(rss->categories, sizeof(char*) * new_size);
  set_string(&rss->categories[rss->num_categories++], category);
}

void
rss_add_rss_item(rss_t* rss, rss_item_t* rss_item)
{
  size_t new_size = rss->num_items + 1;
  rss->items = realloc(rss->items, sizeof(rss_item_t*) * new_size);
  rss->items[rss->num_items++] = rss_item;
}

void
rss_delete_items(rss_t* rss)
{
  int i;
  for (i = 0; i < rss->num_items; i++)
  {
    delete_rss_item(rss->items[i]);
  }

  free(rss->items);
}

void
rss_delete_categories(rss_t* rss)
{
  int i;
  for (i = 0; i < rss->num_categories; i++)
  {
    FREE(rss->categories[i]);
  }

  FREE(rss->categories);
}

void
delete_rss(rss_t* rss)
{
  FREE(rss->title);
  FREE(rss->link);
  FREE(rss->description);
  FREE(rss->language);
  FREE(rss->copyright);
  FREE(rss->managing_editor);
  FREE(rss->web_master);
  FREE(rss->pub_date);
  FREE(rss->last_build_date);
  FREE(rss->generator);
  FREE(rss->docs);
  if (rss->image != NULL) delete_rss_image(rss->image);
  rss_delete_items(rss);
  rss_delete_categories(rss);

  FREE(rss);
}
