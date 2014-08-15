#ifndef GUI_H
#define GUI_H

/* Include other dependencies */
#include "dep.h"

/* Include requirements for GUI */
#include <unistd.h>
#include <sys/ioctl.h>
#include <curses.h>

/* Define colors */
#define TITLE_COLOR 1
#define AUTHOR_COLOR 2
#define STORY_COLOR 3
#define MENU_COLOR 4
#define STANDARD_COLOR 5

/* Define a bar types */
#define TOP_BAR "#"

/* Type defination for winsize struct */
typedef struct winsize  winsize_t;
typedef struct winsize* winsize_r;

/* Function prototypes for GUI */
void print_char(winsize_r, char*);
void display_item(winsize_r, item*);
void display_item_list(item_list*);

#endif
