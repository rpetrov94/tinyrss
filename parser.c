#include "parser.h"

#include "helper.h"

#include <stdio.h>
#include <string.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#define CLEAN(a) ((char*) (a))

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

typedef void (*SETTER_FUNC) (void*, const char*);
void cleanup_after_set(SETTER_FUNC fn, void* item, char* string)
{
  (*fn)(item, string);
  xmlFree(string);
}

void build_rss_item(RSSItem* item, xmlNodePtr node)
{
  SETTER_FUNC setter_func = NULL;
  if (strcmp((char*) node->name, "title") == 0)
    setter_func = (SETTER_FUNC) rss_item_set_title;
  else if (strcmp((char*) node->name, "link") == 0) 
    setter_func = (SETTER_FUNC) rss_item_set_link;
  else if (strcmp((char*) node->name, "description") == 0) 
    setter_func = (SETTER_FUNC) rss_item_set_description;
  else if (strcmp((char*) node->name, "author") == 0) 
    setter_func = (SETTER_FUNC) rss_item_set_author;
  else if (strcmp((char*) node->name, "guid") == 0) 
    setter_func = (SETTER_FUNC) rss_item_set_guid;
  else if (strcmp((char*) node->name, "pubDate") == 0) 
    setter_func = (SETTER_FUNC) rss_item_set_pub_date;

  if (setter_func != NULL)
    cleanup_after_set(setter_func, item, CLEAN(xmlNodeGetContent(node)));

  if (node->next == NULL) return;
  build_rss_item(item, node->next);
}

void build_rss(RSS* rss, xmlNodePtr node)
{
  SETTER_FUNC setter_func = NULL;
  if (strcmp((char*) node->name, "title") == 0) 
    setter_func = (SETTER_FUNC) rss_set_title;
  else if (strcmp((char*) node->name, "link") == 0) 
    setter_func = (SETTER_FUNC) rss_set_link;
  else if (strcmp((char*) node->name, "description") == 0) 
    setter_func = (SETTER_FUNC) rss_set_description;
  else if (strcmp((char*) node->name, "language") == 0) 
    setter_func = (SETTER_FUNC) rss_set_language;
  else if (strcmp((char*) node->name, "copyright") == 0) 
    setter_func = (SETTER_FUNC) rss_set_copyright;
  else if (strcmp((char*) node->name, "pubDate") == 0) 
    setter_func = (SETTER_FUNC) rss_set_pub_date;
  else if (strcmp((char*) node->name, "item") == 0)
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