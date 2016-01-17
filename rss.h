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
  RSSItem** items;
  size_t num_items;
} RSS;

RSS* create_rss();

void rss_set_title(RSS*, const char*);
void rss_set_link(RSS*, const char*);
void rss_set_description(RSS*, const char*);
void rss_set_language(RSS*, const char*);
void rss_set_copyright(RSS*, const char*);
void rss_set_pub_date(RSS*, const char*);
void rss_set_managing_editor(RSS*, const char*);
void rss_set_web_master(RSS*, const char*);
void rss_set_last_build_date(RSS*, const char*);
void rss_set_generator(RSS*, const char*);
void rss_set_docs(RSS*, const char*);
void rss_set_ttl(RSS*, const char*);
void rss_set_image(RSS*, rss_image_t*);
void rss_add_category(RSS*, char*);
void rss_add_rss_item(RSS*, RSSItem*);

void delete_rss(RSS*);

void print_rss(RSS*);

#endif