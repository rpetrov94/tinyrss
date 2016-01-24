#include "fetcher.h"

#include <curl/curl.h>

#include <string.h>
#include <stdlib.h>

fetch_data_t*
create_fetch_data()
{
  fetch_data_t* fetch_data = malloc(sizeof(fetch_data_t));
  fetch_data->data = malloc(sizeof(char));
  return fetch_data;
}

void fetch_content(fetch_data_t* fetch_data, const char* uri);

fetch_data_t*
fetch_document(const char* uri)
{
  fetch_data_t* fetch_data = create_fetch_data();
  fetch_content(fetch_data, uri);

  return fetch_data;
}

static size_t
fetch_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  fetch_data_t* mem = (fetch_data_t*)userp;
 
  mem->data = realloc(mem->data, mem->size + realsize + 1);
  if(mem->data == NULL) {
    fprintf(stderr, "not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  memcpy(&(mem->data[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->data[mem->size] = 0;
 
  return realsize;
}

void
fetch_content(fetch_data_t* fetch_data, const char* uri)
{
  CURL* curl;

  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, uri);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fetch_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)fetch_data);
  curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);
  curl_global_cleanup();
}

void
delete_fetch_data(fetch_data_t* fetch_data)
{
  free(fetch_data->data);
  free(fetch_data);
}