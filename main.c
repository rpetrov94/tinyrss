#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rss-item.h"

int main(int argc, char* argv[])
{
  RSSItem* item = create_rss_item();
  set_title(item, "dasuifhiufdusdui uidfs uidf s");

  delete_rss_item(item);

  return 0;
}