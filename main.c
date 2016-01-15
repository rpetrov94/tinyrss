#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rss.h"
#include "rss-item.h"
#include "parser.h"

const char* test_rss_feed = "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
"<rss version=\"2.0\">"
  "<channel>"
    "<title>Titel des Feeds</title>"
    "<link>URL der Webpräsenz</link>"
    "<description>Kurze Beschreibung des Feeds</description>"
    "<language>Sprache des Feeds (z. B. \"de-de\")</language>"
    "<copyright>Autor des Feeds</copyright>"
    "<pubDate>Erstellungsdatum(\"Tue, 8 Jul 2008 2:43:19\")</pubDate>"
    "<image>"
      "<url>URL einer einzubindenden Grafik</url>"
      "<title>Bildtitel</title>"
      "<link>URL, mit der das Bild verknüpft ist</link>"
    "</image>"
    "<item>"
      "<title>Titel des Eintrags</title>"
      "<description>Kurze Zusammenfassung des Eintrags</description>"
      "<link>Link zum vollständigen Eintrag</link>"
      "<author>Autor des Artikels, E-Mail-Adresse</author>"
      "<guid>Eindeutige Identifikation des Eintrages</guid>"
      "<pubDate>Datum des Items</pubDate>"
    "</item>"
  "</channel>"
"</rss>";

int main(int argc, char* argv[])
{
  /*RSS* rss = create_rss();

  rss_set_title(rss, "my Title");
  rss_set_language(rss, "en-us");
  rss_set_copyright(rss, "GPL");

  RSSItem* item_1 = create_rss_item();
  rss_item_set_title(item_1, "fdaijifdjsi");
  rss_item_set_description(item_1, "fdaijifddasadsasdasdjsi");

  rss_add_rss_item(rss, item_1);

  RSSItem* item_2 = create_rss_item();
  rss_item_set_title(item_2, "fdaijifdjsi");
  rss_item_set_description(item_2, "fdaijifddasadsasdasdjsi");

  rss_add_rss_item(rss, item_2);

  RSSItem* item_3 = create_rss_item();
  rss_item_set_title(item_3, "fdaijifdjsi");
  rss_item_set_description(item_3, "fdaijifddasadsasdasdjsi");

  rss_add_rss_item(rss, item_3);

  printf("%lu\n", rss->num_items);

  delete_rss(rss);*/

  RSS* from_string = parse_string((char*) test_rss_feed);
  printf("%lu\n", from_string->num_items);

  delete_rss(from_string);

  return 0;
}