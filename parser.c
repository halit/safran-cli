// =====================================================================================
//
//       Filename:  parser.c
//
//    Description:  Parser functions
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

/* Initial function for item */
item* init_item(void){
    /* Alloc memory area for new item */
    item* n_item = calloc(sizeof(item), 1);

    /* Check the memory */
    check_mem(n_item);

    /* Make NULL all fields */
    n_item->title         = NULL;
    n_item->description   = NULL;
    n_item->pubDate       = NULL;
    n_item->link          = NULL;
    n_item->guid          = NULL;
    n_item->next          = NULL;
    n_item->readed        = 0;

    /* Return new item */
    return n_item;
}

/* Destroy and cleaner function for item */
void destroy_item(item* p_item){

    /* Dealloc memory area */
    free(p_item);
}

/* Parse the string for item tag */
char* parse_item(char* start, char* p_open_tag, char* p_close_tag){

    /* Calculate open and close tag size */
    size_t open_tag_size = strlen(p_open_tag);
    size_t close_tag_size = strlen(p_close_tag);
    
    /* Split text from open and close tag */
    char* label_open = strstr(start, p_open_tag);
    char* label_close = strstr(label_open, p_close_tag);
    
    /* Calculate new text size */
    size_t text_size = strlen(label_open) - strlen(label_close);

    /* Allocate memory area for new text */
    char* text = calloc(sizeof(char), text_size);
    
    /* Check the memory */
    check_mem(text);

    /* Copy splitted text to new allocated memory area */
    strncpy(text, label_open + open_tag_size, text_size - close_tag_size + 1);
    
    /* Return splitted text */
    return text;
}

/* Initial function for item list */
item_list* init_item_list(void){
    /* Alloc memory area for item list */
    item_list* n_item_list = calloc(sizeof(item_list), 1);

    /* Check the memory */
    check_mem(n_item_list);

    /* Make NULL head pointer */
    n_item_list->head = NULL;

    /* Make zero size */
    n_item_list->size = 0;

    /* Return new item list */
    return n_item_list;
}

/* String to item list function */
item_list* parse_string(char* p_text){

    /* Create empty item list and init */
    item_list* n_item_list = init_item_list();

    /* Create current iterator pointer */
    item* current = NULL;
    
    /* Temp string variables */
    char* sub_close_tag = p_text;
    char* sub_open_tag;
    
    /* Parsing */
    while(1){

        /* Parse open tag */
        sub_open_tag = strstr(sub_close_tag, ITEM_TAG_O);

        /* If there isn't open tag, parsing complete */
        if(!sub_open_tag) break;
        
        /* Parse close tag */
        sub_close_tag = strstr(sub_open_tag, ITEM_TAG_C);

        /* If there isn't close tag, parsing complete */
        if(!sub_close_tag) break;
        
        /* If current item is NULL, create and init */
        if(!current) current = init_item();
        
        /* Fill the item struct with parsed data */
        current->title          = parse_item(sub_open_tag, TITLE_TAG_O, TITLE_TAG_C);
        current->description    = parse_item(sub_open_tag, DESC_TAG_O, DESC_TAG_C);
        current->pubDate        = parse_item(sub_open_tag, PUB_TAG_O, PUB_TAG_C);
        current->link           = parse_item(sub_open_tag, LINK_TAG_O, LINK_TAG_C);
        current->guid           = parse_item(sub_open_tag, GUID_TAG_O, GUID_TAG_C);
        
        /* Control the feed number */
        if(n_item_list->size > FEED_NUMBER-1) break;

        /* Add current item to list */
        add_item(n_item_list, current);
        
        /* Now iterator is NULL */
        current = NULL;
    }
    
    /* Return the item list */
    return n_item_list;
}

/* Destroy and cleaner function for item list */
void destroy_item_list(item_list* p_item_list){
    /* Current item link is head item*/
    item* current = p_item_list->head;
    
    /* Traverse list and destroy items */
    while(current != NULL){
        /* Destroy current item */
        destroy_item(current);

        /* Advance iterator */
        current = current->next;
    }
    
    /* Dealloc memory area for item list */
    free(p_item_list);
}

/* Add item to item list */
void add_item(item_list* p_item_list, item* p_item){
    if(!p_item_list->head){

        /* If head of item list is empty init with p_item */
        p_item_list->head = p_item;
        
        /* Size increase */
        p_item_list->size++;
        
        /* Return */
        return;
    }else{

        /* If head of item list is not empty, now item become head of item list */
        p_item->next = p_item_list->head;
        p_item_list->head = p_item;

        /* Size increase */
        p_item_list->size++;
        
        /* Return */
        return;
    }
}

void clean(char* text_p){
    /* Pointer for main text */
    char* c;
    
    /* Replace the \n char with space */
    while((c = strchr(text_p, '\n')) != NULL) *c = ' ';

    /* Replace the \r char with new line */
    while((c = strchr(text_p, '\r')) != NULL) *c = '\n';
}
