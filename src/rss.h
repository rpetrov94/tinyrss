#ifndef RSS_H
#define RSS_H

#include "rss-item.h"
#include "rss-image.h"

#include <stdlib.h>

typedef struct
{
  char* title;
  char* link;
  char* description;
  char* language;
  char* copyright;
  char* managing_editor;
  char* web_master;
  char* pub_date;
  char* last_build_date;
  char* generator;
  char* docs;
  unsigned ttl;
  rss_image_t* image;
  char** categories;
  size_t num_categories;
  rss_item_t** items;
  size_t num_items;
} rss_t;

rss_t* create_rss();

void rss_set_title(rss_t*, const char*);
void rss_set_link(rss_t*, const char*);
void rss_set_description(rss_t*, const char*);
void rss_set_language(rss_t*, const char*);
void rss_set_copyright(rss_t*, const char*);
void rss_set_pub_date(rss_t*, const char*);
void rss_set_managing_editor(rss_t*, const char*);
void rss_set_web_master(rss_t*, const char*);
void rss_set_last_build_date(rss_t*, const char*);
void rss_set_generator(rss_t*, const char*);
void rss_set_docs(rss_t*, const char*);
void rss_set_ttl(rss_t*, const char*);
void rss_set_image(rss_t*, rss_image_t*);
void rss_add_category(rss_t*, char*);
void rss_add_rss_item(rss_t*, rss_item_t*);

void delete_rss(rss_t*);

#endif
