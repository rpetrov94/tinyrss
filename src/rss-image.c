#include "rss-image.h"
#include "helper.h"

#include <stdlib.h>

#define PP_RSS_IMAGE(a, b) (pretty_print_node(a, b, "\t"))
#define FREE(a) ({if (a != NULL) free(a);})

rss_image_t* create_rss_image()
{
  rss_image_t* image = malloc(sizeof(rss_image_t));
  image->url = NULL;
  image->title = NULL;
  image->link = NULL;
  image->width = DEFAULT_WIDTH;
  image->height = DEFAULT_HEIGHT;
  image->description = NULL;

  return image;
}

void
rss_image_set_url(rss_image_t* image, const char* url)
{
  set_string(&image->url, url);
}

void
rss_image_set_title(rss_image_t* image, const char* title)
{
  set_string(&image->title, title);
}

void
rss_image_set_link(rss_image_t* image, const char* link)
{
  set_string(&image->link, link);
}

void
rss_image_set_width(rss_image_t* image, const char* width)
{
  image->width = strtoul(width, NULL, 10);
}

void
rss_image_set_height(rss_image_t* image, const char* height)
{
  image->height = strtoul(height, NULL, 10);
}

void
rss_image_set_description(rss_image_t* image, const char* description)
{
  set_string(&image->description, description);
}

void
delete_rss_image(rss_image_t* image)
{
  FREE(image->url);
  FREE(image->title);
  FREE(image->link);
  FREE(image->description);
  FREE(image);
}

void
print_rss_image(rss_image_t* image)
{
  PP_RSS_IMAGE("url", image->url);
  PP_RSS_IMAGE("title", image->title);
  PP_RSS_IMAGE("link", image->link);
  PP_RSS_IMAGE("description", image->description);
}