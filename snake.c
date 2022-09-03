#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

// initialize some structure and functions

struct Screen {
	int width;
	int height;
	char *display;
};

struct Screen generate_screen(int width, int height);

void display(struct Screen *scr);

void draw_on_the_screen(struct Screen *scr, int x, int y, char content) {

	if (scr->display[(y * (scr->width) + x)] == '\n') {
		scr->display[(y * (scr->width) + x) - 1] = content; 
	} else {
		scr->display[(y * (scr->width) + x)] = content;
	}
	
}


struct Snake {
	int start_x;
	int start_y;
	int blocks;
	char *direction;
};

void get_Snake(struct Snake *snake, int start_x, int start_y, int blocks);
void draw_snake(struct Snake *snake, struct Screen *screen);
void move_snake(struct Snake *snake, struct Screen *screen, char *direction);
void delete_snake(struct Snake *snake, struct Screen *screen);

// The entry part
int main(int argc, char *argv) {
	system("cls");
	struct Screen scr;
	struct Snake snake;
	int x = 0;
	int y = 0;
	scr = generate_screen(100, 30);
	get_Snake(&snake, x, y, 1);

	for (;;){
		display(&scr);
		draw_snake(&snake, &scr);
		if (kbhit() == 1) {
			char c;
			c = getch();

			// key 'w' pressed
			if (c == 119) {
				move_snake(&snake, &scr, "up");	
			} 
			// key 's' pressed
			else if (c == 115) {
				move_snake(&snake, &scr, "down");
			} 
			// key 'a' pressed
			else if (c == 97) 
			{
				move_snake(&snake, &scr, "left");
			}
			// key 'd' pressed
			else if (c == 100) {
				move_snake(&snake, &scr, "right");
			}
					
		 }
	}
	
	}


// Definition

struct Screen generate_screen(int width, int height) {
	struct Screen sam_scr;
	char empty = ' ';

	sam_scr.width = width;
	sam_scr.height = height;
	
	sam_scr.display = (char *)(malloc(sizeof(char) * ((sam_scr.width * sam_scr.height) + sam_scr.height + 1000)));
	
	for (int i = 0; i < sam_scr.height; i++) {
		if (i == 0) {
			for (int j = 0; j < sam_scr.width + 1; j++) {
	
				if (j == sam_scr.width) {
					sam_scr.display[(i * sam_scr.width) + j] = '\n';
				}
				else {
					sam_scr.display[(i * sam_scr.width) + j] = empty;
		
				}
		
			}

		} else {
			sam_scr.display[(i * sam_scr.width) + 1] = empty;
			for (int j = 1; j < sam_scr.width + 1; j++) {
				if (j == sam_scr.width) {
					sam_scr.display[(i * sam_scr.width) + j] = '\n';
				}
				else {
					sam_scr.display[(i * sam_scr.width) + j] = empty;
		
				}
		
				}
	
			}
	}

	return sam_scr;

}

void display(struct Screen *scr) {
	system("cls");
	printf("%s \n", scr->display);
}


void get_Snake(struct Snake *snake, int start_x, int start_y, int blocks) {
	snake->start_x  = start_x;
	snake->start_y = start_y;
	snake->blocks = blocks;
	snake->direction = "right";
}
void draw_snake(struct Snake *snake, struct Screen *screen) {
	int x = snake->start_x;
	for (int i = 0; i < snake->blocks; i++) {
		draw_on_the_screen(screen, x, snake->start_y, 's');
		x += 1;
	};

}

void delete_snake(struct Snake *snake, struct Screen *screen) {
	int x = snake->start_x;
	for (int i = 0; i < snake->blocks; i++) {
		draw_on_the_screen(screen, x, snake->start_y, ' ');
		x += 1;
	};

}

void move_snake(struct Snake *snake, struct Screen *screen, char *direction) {
	if (strcmp(direction, "right") == 0) {
		if (strcmp(snake->direction, "right") == 0) {
			snake->direction = direction;
			delete_snake(snake, screen);
			snake->start_x++;

			draw_snake(snake, screen);
		
		}
		else if (strcmp(snake->direction, "left") == 0) {
			snake->direction = direction;
			delete_snake(snake, screen);
			snake->start_x++;
			draw_snake(snake, screen);
		} else if (strcmp(snake->direction, "down") == 0) {
			snake->direction = direction;
			if (snake->blocks == 1) {
				snake->direction = direction;
				delete_snake(snake, screen);
				snake->start_y++;
				draw_snake(snake, screen);
			}
		}
		else if (strcmp(snake->direction, "up") == 0) {
			snake->direction = direction;
			if (snake->blocks == 1) {
				snake->direction = direction;
				delete_snake(snake, screen);
				snake->start_y--;
				draw_snake(snake, screen);
			}
		}

	} else if (strcmp(direction, "left") == 0) {
		if (strcmp(direction, "left") == 0) {
			snake->direction = direction;
			delete_snake(snake, screen);
			snake->start_x--;
			draw_snake(snake, screen);
		}
		else if (strcmp(direction, "right") == 0) {
			snake->direction = direction;
			delete_snake(snake, screen);
			snake->start_x--;
			draw_snake(snake, screen);
		} else if (strcmp(snake->direction, "down") == 0) {
			snake->direction = direction;
			if (snake->blocks == 1) {
				snake->direction = direction;
				delete_snake(snake, screen);
				snake->start_y++;
				draw_snake(snake, screen);
			}
		}
		else if (strcmp(snake->direction, "up") == 0) {
			snake->direction = direction;
			if (snake->blocks == 1) {
				snake->direction = direction;
				delete_snake(snake, screen);
				snake->start_y--;
				draw_snake(snake, screen);
			}
		}


	} else if (strcmp(direction, "down") == 0) {
		if (strcmp(direction, "right") == 0) {
			if (snake->blocks == 1) {
				snake->direction = direction;
				delete_snake(snake, screen);
				snake->start_y++;
				draw_snake(snake, screen);
			}		

		}
		else if (strcmp(direction, "left")) {
			if (snake->blocks == 1) {
				snake->direction = direction;
				delete_snake(snake, screen);
				snake->start_y++;
				draw_snake(snake, screen);
			}
		}

	}
	else if (strcmp(direction, "up") == 0) {
		if (strcmp(direction, "right") == 0) {
			if (snake->blocks == 1) {
				snake->direction = direction;
				delete_snake(snake, screen);
				snake->start_y--;
				draw_snake(snake, screen);
			}		

		}
		else if (strcmp(direction, "left")) {
			if (snake->blocks == 1) {
				snake->direction = direction;
				delete_snake(snake, screen);
				snake->start_y--;
				draw_snake(snake, screen);
			}
		}

	}

}

