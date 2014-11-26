// =====================================================================================
//
//       Filename:  gui.c
//
//    Description:  GUI for safran feed reader
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

#include "gui.h"

/* Character print function */
void print_char(winsize_r win_p, char* char_p){

	/* Define a index variable */
	unsigned int i_v = 0;

	/* Loop for print the char */
	while(i_v < win_p->ws_col){

		/* Print a single char */
		printw(char_p);

		/* Increase index value */
		i_v++;
	}
}

/* Display function for single item */
void display_item(winsize_r win_p, item* item_p){
    
	/* Declare a most used variable */
	size_t date_size = strlen(item_p->pubDate);

	/* Clean the window */
	clear();

	/* Print single item info if it is not NULL */
	if(item_p){
		
		attron(COLOR_PAIR(MENU_COLOR));
		/* Print the top bar */
		print_char(win_p, TOP_BAR);
		
		/* Print item title if item is not NULL */
		if(item_p->title){
		
			/* On the Title color */
			attron(COLOR_PAIR(TITLE_COLOR));
			
			/* If title is large for line, cut it */
			if(strlen(item_p->title) < win_p->ws_col - date_size - 5){
				printw("%s", item_p->title);
			}else{
				printw("%.*s...", win_p->ws_col - date_size - 8, item_p->title);
			}

			/* End the title */
			printw(" %s\n", TOP_BAR);
			
			/* Off the Title color */
			attroff(COLOR_PAIR(TITLE_COLOR));

			/* Print the pubDate on right corner */
			if(item_p->pubDate){
			
				/* On the Menu color */
				attron(COLOR_PAIR(MENU_COLOR));
				
				/* Print bar on the right corner */
				mvprintw(1, win_p->ws_col - date_size - 2, TOP_BAR);
				
				/* Print pubDate on the right corner */
				mvprintw(1, win_p->ws_col - date_size, "%s", item_p->pubDate);
			}
		}

		/* Print the top bar */
		print_char(win_p, TOP_BAR);
		
		/* Off the Menu color */
		attroff(COLOR_PAIR(MENU_COLOR));

		/* Print item description if item is not NULL */
		if(item_p->description){
		
			/* Print the item description */
			printw("\n%s\n\n", item_p->description);
		}
        
		/* On the menu color */
		attron(COLOR_PAIR(MENU_COLOR));
		
		/* Print the top bar */
		print_char(win_p, TOP_BAR);
		
		/* Print the item link */
		if(item_p->link){
		
			/* Print the item link */
			printw("%s\n", item_p->link);
		}

		/* Print the top bar */
		print_char(win_p, TOP_BAR);
		
		/* Off the menu color */
		attroff(COLOR_PAIR(MENU_COLOR));
	}
	
	/* Refresh the screen */
	refresh();
	
	/* Sleep */
	getch();
}

void display_item_list(item_list* item_list_p){
	
	/* Init variables */
	int option = 1;
	int index  = 0;
	item* current;
	
	/* Init the screen and start coloring */
	initscr();
	start_color();
	
	/* Terminal window size type */
	winsize_t window;
	
	/* Get the window size */
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
	
	/* Init the color pairs */
	init_pair(TITLE_COLOR, COLOR_YELLOW, COLOR_BLACK);
	init_pair(AUTHOR_COLOR, COLOR_GREEN, COLOR_BLACK);
	init_pair(STANDARD_COLOR, COLOR_WHITE, COLOR_BLACK);
	init_pair(MENU_COLOR, COLOR_CYAN, COLOR_BLACK);	

	/* Infinite loop */
	while(1) {
	
		/* On the Menu color */
		attron(COLOR_PAIR(MENU_COLOR));
		
		/* Clear the screen */
		clear();
		
		/* Print the top bar */
		print_char(&window, TOP_BAR);
		
		/* Print the program name */
		printw("%s %s ", PROGRAM_NAME, TOP_BAR);
		
		/* Print the version */
		mvprintw(1, window.ws_col - strlen(VERSION) - 2, TOP_BAR);
		mvprintw(1, window.ws_col - strlen(VERSION), "%s", VERSION);
		
		/* Print the top bar */
		print_char(&window, TOP_BAR);
        
		/* If item list */
		if(item_list_p){
		
			/* Now index variable is 0 */
			index = 0;
		
			/* Iterate linked list */
			for(current = item_list_p->head;current != NULL;current = current->next){
			
				/* If current item is readed, change color */
				if(current->readed){
					attron(COLOR_PAIR(STANDARD_COLOR));
				}else{
					attron(COLOR_PAIR(MENU_COLOR));
				}
			
				/* If title is large for line, cut it */
				if(strlen(current->title) < window.ws_col - 6){
					printw("%3d : %s\n", item_list_p->size - index, current->title);
				}else{
					printw("%3d : %.*s...\n", item_list_p->size - index, window.ws_col - 10, current->title);
				}
			
				/* On the standart color */
				attron(COLOR_PAIR(STANDARD_COLOR));
				
				/* Increase index */
				index++;
			}
		}
	        
		/* Off the menu color and on the standart color */
		attroff(COLOR_PAIR(MENU_COLOR));
		attron(COLOR_PAIR(STANDARD_COLOR));
		
		/* Move window */
		move(window.ws_row - 2, 0);
		
		/* Print the top bar */
		print_char(&window, TOP_BAR);
		
		/* Prompt question */
		printw(PROMPT_ASK);
		
		/* Refresh the window */
		refresh();
		
		/* Get the option from user */
		scanw("%d", &option);
		
		/* If option is invalid, ask the new option */
		while(option < 0 || option > item_list_p->size) {
			mvprintw(window.ws_row - 1, 0, PROMPT_ASK_ERROR);
			scanw("%d", &option);
		}
		
		/* If option is 0, break the loop */
		if (option == 0)
			break;
		
		/* Iterate linked list */
		unsigned int i = 0;
		for(current = item_list_p->head;i < item_list_p->size - option;current = current->next, i++);
		
		/* Display the current item */
		display_item(&window, current);
		
		/* Set the readed */
		current->readed = 1;
	}

    /* Clear window */
	clear();

    /* Refresh window */
	refresh();

    /* Close the window */
	endwin();
}
