#ifndef FETCHER_H
#define FETCHER_H

/* Include other dependencies */
#include "dep.h"

/* Include curl lib */
#include <curl/curl.h>

/* Define a memory chunk structure */
typedef struct{
    char *memory;
    size_t size;
}memory_struct;

/* Memory struct init, destroy and content fetcher functions */
size_t write_memory(void*, size_t, size_t, void*);
memory_struct* fetch_content(char*);
memory_struct* init_memory_struct();
void destroy_memory_struct(memory_struct*);

#endif
