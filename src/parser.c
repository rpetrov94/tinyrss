#include "parser.h"

#include "helper.h"

#include <stdio.h>
#include <string.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

typedef void (*SETTER_FUNC) (void*, const char*);
typedef void (*BUILD_FUNC) (void*, xmlNodePtr);

typedef struct {
  char field[20];
  SETTER_FUNC fn;
} Mapping;

#define END "tinyrss_end"
const Mapping rss_mapping[] = {
  {"title", (SETTER_FUNC)rss_set_title},
  {"description", (SETTER_FUNC)rss_set_description},
  {"link", (SETTER_FUNC)rss_set_link},
  {"language", (SETTER_FUNC)rss_set_language},
  {"copyright", (SETTER_FUNC)rss_set_copyright},
  {"pubDate", (SETTER_FUNC)rss_set_pub_date},
  {"managingEditor", (SETTER_FUNC)rss_set_managing_editor},
  {"webMaster", (SETTER_FUNC)rss_set_web_master},
  {"pubDate", (SETTER_FUNC)rss_set_pub_date},
  {"lastBuildDate", (SETTER_FUNC)rss_set_last_build_date},
  {"generator", (SETTER_FUNC)rss_set_generator},
  {"category", (SETTER_FUNC)rss_add_category},
  {"docs", (SETTER_FUNC)rss_set_docs},
  {"ttl", (SETTER_FUNC)rss_set_ttl},
  {END, NULL}
};

const Mapping rss_image_mapping[] = {
  {"url", (SETTER_FUNC)rss_image_set_url},
  {"title", (SETTER_FUNC)rss_image_set_title},
  {"link", (SETTER_FUNC)rss_image_set_link},
  {"width", (SETTER_FUNC)rss_image_set_width},
  {"height", (SETTER_FUNC)rss_image_set_height},
  {"description", (SETTER_FUNC)rss_image_set_description},
  {END, NULL}
};

const Mapping rss_item_mapping[] = {
  {"title", (SETTER_FUNC)rss_item_set_title},
  {"description", (SETTER_FUNC)rss_item_set_description},
  {"link", (SETTER_FUNC)rss_item_set_link},
  {"author", (SETTER_FUNC)rss_item_set_author},
  {"guid", (SETTER_FUNC)rss_item_set_guid},
  {"pubDate", (SETTER_FUNC)rss_item_set_pub_date},
  {"category", (SETTER_FUNC)rss_item_add_category},
  {END, NULL}
};

void build(void*, xmlNodePtr, const Mapping*, BUILD_FUNC);
void build_rss(rss_t*, xmlNodePtr);

rss_t*
parse_string(char* string)
{
  xmlDocPtr doc;
  xmlNodePtr root_element;
  xmlXPathObjectPtr xpathObj;
  xmlXPathContextPtr xpathCtx;
  string = trim(string);
  doc = xmlReadMemory(string, strlen(string), "noname.xml", NULL, 0);
  if (doc == NULL) {
    fprintf(stderr, "Failed to parse document\n");
    return NULL;
  }

  xpathCtx = xmlXPathNewContext(doc);
  xpathObj = xmlXPathEvalExpression(BAD_CAST "//channel", xpathCtx);

  root_element = (xpathObj->nodesetval)->nodeTab[0];

  rss_t* rss = create_rss();
  build(rss, root_element->children, rss_mapping, (BUILD_FUNC)build_rss);

  xmlFreeDoc(doc);
  xmlXPathFreeObject(xpathObj);
  xmlXPathFreeContext(xpathCtx); 
  xmlCleanupParser();

  return rss;
}

void
cleanup_after_set(SETTER_FUNC fn, void* item, xmlChar* string)
{
  (*fn)(item, (char*) string);
  xmlFree(string);
}

SETTER_FUNC map_fn(char*, const Mapping*);

void 
build(void* item, xmlNodePtr node, const Mapping* mapping, BUILD_FUNC build_fn)
{
  SETTER_FUNC setter_func = NULL;
  char* node_name = (char*) node->name;
  setter_func = map_fn(node_name, mapping);

  if (build_fn)
    build_fn(item, node);

  if (setter_func != NULL)
    cleanup_after_set(setter_func, item, xmlNodeGetContent(node));

  if (node->next == NULL) return;
  build(item, node->next, mapping, build_fn);
}

void
build_rss(rss_t* rss, xmlNodePtr node)
{
  if (strcmp((char*) node->name, "item") == 0)
  {
    rss_item_t* item = create_rss_item();
    build(item, node->children, rss_item_mapping, NULL);
    rss_add_rss_item(rss, item);
  }
  else if (strcmp((char*) node->name, "image") == 0)
  {
    rss_image_t* image = create_rss_image();
    build(image, node->children, rss_image_mapping, NULL);
    rss_set_image(rss, image);
  }
}

SETTER_FUNC
map_fn(char* field, const Mapping* mapping)
{
  const Mapping* p_mapping = mapping;
  while (strcmp((*p_mapping).field, END) != 0) {
    if (strcmp(field, (*p_mapping).field) == 0) {
      return (*p_mapping).fn;
    }
    p_mapping++;
  }

  return NULL;
}