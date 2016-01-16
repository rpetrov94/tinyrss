#include "parser.h"

#include "helper.h"

#include <stdio.h>
#include <string.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#define CLEAN(a) ((char*) (a))
typedef void (*SETTER_FUNC) (void*, const char*);

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
  {END, NULL}
};

const Mapping rss_item_mapping[] = {
  {"title", (SETTER_FUNC)rss_item_set_title},
  {"description", (SETTER_FUNC)rss_item_set_description},
  {"link", (SETTER_FUNC)rss_item_set_link},
  {"author", (SETTER_FUNC)rss_item_set_author},
  {"guid", (SETTER_FUNC)rss_item_set_guid},
  {"pubDate", (SETTER_FUNC)rss_item_set_pub_date},
  {END, NULL}
};

void build_rss(RSS*, xmlNodePtr);

RSS* parse_string(char* string)
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

  RSS* rss = create_rss();
  build_rss(rss, root_element->children);

  xmlFreeDoc(doc);
  xmlXPathFreeObject(xpathObj);
  xmlXPathFreeContext(xpathCtx); 
  xmlCleanupParser();

  return rss;
}

void cleanup_after_set(SETTER_FUNC fn, void* item, char* string)
{
  (*fn)(item, string);
  xmlFree(string);
}

SETTER_FUNC map_fn(char*, const Mapping*);

void build_rss_item(RSSItem* item, xmlNodePtr node)
{
  SETTER_FUNC setter_func = NULL;
  char* node_name = (char*) node->name;
  setter_func = map_fn(node_name, rss_item_mapping);

  if (setter_func != NULL)
    cleanup_after_set(setter_func, item, CLEAN(xmlNodeGetContent(node)));

  if (node->next == NULL) return;
  build_rss_item(item, node->next);
}

void build_rss(RSS* rss, xmlNodePtr node)
{
  SETTER_FUNC setter_func = NULL;
  char* node_name = (char*) node->name;
  setter_func = map_fn(node_name, rss_mapping);

  if (strcmp((char*) node->name, "item") == 0)
  {
    RSSItem* item = create_rss_item();
    build_rss_item(item, node->children);
    rss_add_rss_item(rss, item);
  }

  if (setter_func != NULL)
    cleanup_after_set(setter_func, rss, CLEAN(xmlNodeGetContent(node)));

  if (node->next == NULL) return;
  build_rss(rss, node->next);
}

SETTER_FUNC map_fn(char* field, const Mapping* mapping)
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