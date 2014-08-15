// =====================================================================================
//
//       Filename:  safran.c
//
//    Description:  Safran CLI main source code
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

int main(int argc, const char *argv[]){ 
    
    /* Fetch the feed content */
    memory_struct* n_content = fetch_content(FEED_URL);

    /* Set the localization for unicode characters */
    setlocale(LC_ALL, "");
    
    /* Clean the fetched content */
    clean(n_content->memory);

    /* Parse the fetched content to item list */
    item_list* result = parse_string(n_content->memory);

    /* Display the item list */
    display_item_list(result);
    
    /* Free memory area */
    destroy_memory_struct(n_content);
    destroy_item_list(result);

    /* Return the os */
    return 0;
}
