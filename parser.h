#ifndef PARSER_H
#define PARSER_H

/* Include other dependencies */
#include "dep.h"

/* Define label names */
#define ITEM_TAG_N  "item"
#define TITLE_TAG_N "title"
#define DESC_TAG_N  "description" 
#define PUB_TAG_N   "pubDate"
#define LINK_TAG_N  "link"
#define GUID_TAG_N  "guid"

/* Define macro for open and close wrapping */
#define TAG_WRAPPER_O(label) "<" label ">"
#define TAG_WRAPPER_C(label) "</" label ">"

/* 'item' label open and close tags */
#define ITEM_TAG_O TAG_WRAPPER_O(ITEM_TAG_N)
#define ITEM_TAG_C TAG_WRAPPER_C(ITEM_TAG_N)

/* 'title' label open and close tags */
#define TITLE_TAG_O TAG_WRAPPER_O(TITLE_TAG_N)
#define TITLE_TAG_C TAG_WRAPPER_C(TITLE_TAG_N)

/* 'description' label open and close tags */
#define DESC_TAG_O TAG_WRAPPER_O(DESC_TAG_N)
#define DESC_TAG_C TAG_WRAPPER_C(DESC_TAG_N)

/* 'pubDate' label open and close tags */
#define PUB_TAG_O TAG_WRAPPER_O(PUB_TAG_N)
#define PUB_TAG_C TAG_WRAPPER_C(PUB_TAG_N)

/* 'link' label open and close tags */
#define LINK_TAG_O TAG_WRAPPER_O(LINK_TAG_N)
#define LINK_TAG_C TAG_WRAPPER_C(LINK_TAG_N)

/* 'guid' label open and close tags */
#define GUID_TAG_O TAG_WRAPPER_O(GUID_TAG_N)
#define GUID_TAG_C TAG_WRAPPER_C(GUID_TAG_N)

/* Define a linked list item structure for parsed data */
typedef struct _item{
    char* title;
    char* description;
    char* pubDate;
    char* link;
    char* guid;    
    struct _item* next;
    unsigned char readed:1;    
}item;

/* Define a linked list structure for items */
typedef struct _item_list{
    item* head;
    size_t size;
}item_list;

/* Item init, parse and destroy functions */
item* init_item(void);
char* parse_item(char*, char*, char*);
void destroy_item(item*);

/* Item list init, parse, add, destroy and clean functions */
item_list* init_item_list(void);
item_list* parse_string(char*);
void destroy_item_list(item_list*);
void add_item(item_list*, item*);
void clean(char*);

#endif
