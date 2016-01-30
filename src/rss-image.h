#ifndef RSS_IMAGE_H
#define RSS_IMAGE_H

#define DEFAULT_WIDTH   88
#define DEFAULT_HEIGHT  31

#define MAX_WIDTH   144
#define MAX_HEIGHT  400

#include <stdint.h>

typedef struct {
  char* url;
  char* title;
  char* link;
  uint16_t width;
  uint16_t height;
  char* description;
} rss_image_t;

rss_image_t* create_rss_image();

void rss_image_set_url(rss_image_t*, const char*);
void rss_image_set_title(rss_image_t*, const char*);
void rss_image_set_link(rss_image_t*, const char*);
void rss_image_set_width(rss_image_t*, const char*);
void rss_image_set_height(rss_image_t*, const char*);
void rss_image_set_description(rss_image_t*, const char*);

void delete_rss_image(rss_image_t*);

#endif
