#include "parser.h"

#include <stdio.h>
#include <string.h>
#include <libxml/tree.h>
#include <libxml/parser.h>

#define CLEAN(a) ((char*) (a))

void build_rss(RSS*, xmlNodePtr);

RSS* parse_string(char* string)
{
  xmlDocPtr doc;
  xmlNodePtr root_element;
  doc = xmlReadMemory(string, strlen(string), "noname.xml", NULL, 0);
  if (doc == NULL) {
    fprintf(stderr, "Failed to parse document\n");
    return NULL;
  }

  root_element = xmlDocGetRootElement(doc);
  xmlNodePtr child = root_element->children->children;

  RSS* rss = create_rss();
  build_rss(rss, child);

  xmlFreeDoc(doc);
  xmlCleanupParser();

  return rss;
}

void build_rss_item(RSSItem* item, xmlNodePtr node)
{
  if (strcmp((char*) node->name, "title") == 0) 
    rss_item_set_title(item, CLEAN(xmlNodeGetContent(node)));
  else if (strcmp((char*) node->name, "link") == 0) 
    rss_item_set_link(item, CLEAN(xmlNodeGetContent(node)));
  else if (strcmp((char*) node->name, "description") == 0) 
    rss_item_set_description(item, CLEAN(xmlNodeGetContent(node)));
  else if (strcmp((char*) node->name, "author") == 0) 
    rss_item_set_author(item, CLEAN(xmlNodeGetContent(node)));
  else if (strcmp((char*) node->name, "guid") == 0) 
    rss_item_set_guid(item, CLEAN(xmlNodeGetContent(node)));
  else if (strcmp((char*) node->name, "pub_date") == 0) 
    rss_item_set_pub_date(item, CLEAN(xmlNodeGetContent(node)));

  if (node->next == NULL) return;
  build_rss_item(item, node->next);
}

void build_rss(RSS* rss, xmlNodePtr node)
{
  if (strcmp((char*) node->name, "title") == 0) 
    rss_set_title(rss, CLEAN(xmlNodeGetContent(node)));
  else if (strcmp((char*) node->name, "link") == 0) 
    rss_set_link(rss, CLEAN(xmlNodeGetContent(node)));
  else if (strcmp((char*) node->name, "description") == 0) 
    rss_set_description(rss, CLEAN(xmlNodeGetContent(node)));
  else if (strcmp((char*) node->name, "language") == 0) 
    rss_set_language(rss, CLEAN(xmlNodeGetContent(node)));
  else if (strcmp((char*) node->name, "copyright") == 0) 
    rss_set_copyright(rss, CLEAN(xmlNodeGetContent(node)));
  else if (strcmp((char*) node->name, "pub_date") == 0) 
    rss_set_pub_date(rss, CLEAN(xmlNodeGetContent(node)));
  else if (strcmp((char*) node->name, "item") == 0)
  {
    RSSItem* item = create_rss_item();
    build_rss_item(item, node->children);
    rss_add_rss_item(rss, item);
  }

  if (node->next == NULL) return;
  build_rss(rss, node->next);
}