// =====================================================================================
//
//       Filename:  fetcher.c
//
//    Description:  Fetcher functions of safran
//
//        Version:  0.1.0
//        Created:  08/15/2014
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  Halit Alptekin (), info@halitalptekin.com
//        License:  MIT
//
// =====================================================================================
#include "dep.h"

/* Write memory callback function */
size_t write_memory(void* contents_p, size_t size_p, size_t nmemb_p, void* userp_p){
    
    /* Calculate realsize */
    size_t realsize = size_p * nmemb_p;

    /* Cast void pointer to memory_struct */
    memory_struct* n_mem = (memory_struct*)userp_p;
    
    /* Reallocate memory area */
    n_mem->memory = realloc(n_mem->memory, n_mem->size + realsize + 1);
    
    /* Check the memory */
    check_mem(n_mem);

    /* Copy the content to reallocated area */
    memcpy(&(n_mem->memory[n_mem->size]), contents_p, realsize);

    /* Increase size variable with realsize */
    n_mem->size += realsize;

    /* Null value */
    n_mem->memory[n_mem->size] = 0;
    
    /* Return realsize */
    return realsize;
}

/* Init new memory struct */
memory_struct* init_memory_struct(){
    
    /* Alloc memoery area */
    memory_struct* n_memory = calloc(sizeof(memory_struct), 1);

    /* Check memory */
    check_mem(n_memory);

    /* Initial values */
    n_memory->size = 0;
    n_memory->memory = NULL;
    
    /* Return new memory struct */
    return n_memory;
}

/* Free memory area */
void destroy_memory_struct(memory_struct* memory_struct_p){

    /* Firstly free memory sub area */
    free(memory_struct_p->memory);

    /* Then free memory struct */
    free(memory_struct_p);
}

/* Fetch content from internet */
memory_struct* fetch_content(char* link){

    /* Curl handle and response variable */
    CURL* curl_handle;
    CURLcode res;
    
    /* Init new memory struct */
    memory_struct* chunk = init_memory_struct();
    
    /* Start the memory area with 1 */
    chunk->memory = calloc(1, 1);

    /* Size is 0 now */
    chunk->size = 0;   
    
    /* Curl global init */
    curl_global_init(CURL_GLOBAL_ALL);
 
    /* Init the curl session */ 
    curl_handle = curl_easy_init();
 
    /* Specify URL to get */ 
    curl_easy_setopt(curl_handle, CURLOPT_URL, link);

    /* Follow the white rabbit */
    curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
 
    /* Send all data to this function  */ 
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_memory);
 
    /* Se pass our 'chunk' struct to the callback function */ 
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)chunk);
 
    /* Safran user-agent */ 
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "safran-c-cli");
 
    /* Fetch the content */ 
    res = curl_easy_perform(curl_handle);
 
    /* Check for errors */ 
    if(res != CURLE_OK) {
        /* Log the this error */
        log_err("curl_easy_perform() failed");
    }else{
        /* Clean the handlers */
        curl_easy_cleanup(curl_handle);
        curl_global_cleanup();
    }
    
    /* Return the chunk */
    return chunk;
}
