#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rss.h"
#include "rss-item.h"

int main(int argc, char* argv[])
{
  RSS* rss = create_rss();

  rss_set_title(rss, "my Title");
  rss_set_language(rss, "en-us");
  rss_set_copyright(rss, "GPL");

  delete_rss(rss);

  return 0;
}