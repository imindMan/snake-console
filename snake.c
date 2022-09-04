#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

// initialize some structure and functions

struct Screen
{
	int width;
	int height;
	char *display;
};

struct Screen generate_screen(int width, int height);

void display(struct Screen *scr);

void draw_on_the_screen(struct Screen *scr, int x, int y, char content)
{

	if (scr->display[(y * (scr->width) + x)] == '\n')
	{
		scr->display[(y * (scr->width) + x) - 1] = content;
	}
	else
	{
		scr->display[(y * (scr->width) + x)] = content;
	}
}

struct Snake
{
	int start_x;
	int start_y;
	int blocks;
	char *direction;
};

void get_snake(struct Snake *snake, int start_x, int start_y, int blocks);
void draw_snake(struct Snake *snake, struct Screen *screen, int col_or_not)
{

	if (col_or_not == 0)
	{
		int x = snake->start_x;
		for (int i = 0; i < snake->blocks; i++)
		{
			draw_on_the_screen(screen, x, snake->start_y, 's');
			x += 1;
		};
	}
	else
	{
		int y = snake->start_y;
		for (int i = 0; i < snake->blocks; i++)
		{
			draw_on_the_screen(screen, snake->start_x, y, 's');
			y += 1;
		}
	}
}
int move_snake(struct Snake *snake, struct Screen *screen, char *direction);
void delete_snake(struct Snake *snake, struct Screen *screen, int col_or_not)
{

	if (col_or_not == 0)
	{
		int x = snake->start_x;
		for (int i = 0; i < snake->blocks; i++)
		{
			draw_on_the_screen(screen, x, snake->start_y, ' ');
			x += 1;
		};
	}
	else if (col_or_not == 1)
	{
		int y = snake->start_y;
		for (int i = 0; i < snake->blocks; i++)
		{
			draw_on_the_screen(screen, snake->start_x, y, ' ');
			y += 1;
		}
	}
}
// The entry part
int main(int argc, char *argv)
{
	system("cls");
	struct Screen scr;
	struct Snake snake;
	int default_side = 0;
	int x = 1;
	int y = 0;
	scr = generate_screen(100, 30);
	get_snake(&snake, x, y, 4);

	for (;;)
	{
		display(&scr);
		draw_snake(&snake, &scr, default_side);
		if (kbhit() == 1)
		{
			char c;
			c = getch();
			int a;
			// key 'w' pressed
			if (c == 119)
			{
				a = move_snake(&snake, &scr, "up");
			}
			// key 's' pressed
			else if (c == 115)
			{
				a = move_snake(&snake, &scr, "down");
			}
			// key 'a' pressed
			else if (c == 97)
			{
				a = move_snake(&snake, &scr, "left");
			}
			// key 'd' pressed
			else if (c == 100)
			{
				a = move_snake(&snake, &scr, "right");
			}
			default_side = a;
		}
	}
}

// Definition

struct Screen generate_screen(int width, int height)
{
	struct Screen sam_scr;
	char empty = ' ';

	sam_scr.width = width;
	sam_scr.height = height;

	sam_scr.display = (char *)(malloc(sizeof(char) * ((sam_scr.width * sam_scr.height) + sam_scr.height + 1000)));

	for (int i = 0; i < sam_scr.height; i++)
	{
		if (i == 0)
		{
			for (int j = 0; j < sam_scr.width + 1; j++)
			{

				if (j == sam_scr.width)
				{
					sam_scr.display[(i * sam_scr.width) + j] = '\n';
				}
				else
				{
					sam_scr.display[(i * sam_scr.width) + j] = empty;
				}
			}
		}
		else
		{
			sam_scr.display[(i * sam_scr.width) + 1] = empty;
			for (int j = 1; j < sam_scr.width + 1; j++)
			{
				if (j == sam_scr.width)
				{
					sam_scr.display[(i * sam_scr.width) + j] = '\n';
				}
				else
				{
					sam_scr.display[(i * sam_scr.width) + j] = empty;
				}
			}
		}
	}

	return sam_scr;
}

void display(struct Screen *scr)
{
	system("cls");
	printf("%s \n", scr->display);
}

void get_snake(struct Snake *snake, int start_x, int start_y, int blocks)
{
	snake->start_x = start_x;
	snake->start_y = start_y;
	snake->blocks = blocks;
	snake->direction = "right";
}

int move_snake(struct Snake *snake, struct Screen *screen, char *direction)
{
	if (strcmp(direction, "right") == 0)
	{
		if (strcmp(snake->direction, "right") == 0)
		{
			snake->direction = direction;
			delete_snake(snake, screen, 0);
			snake->start_x++;

			draw_snake(snake, screen, 0);
		}
		else if (strcmp(snake->direction, "left") == 0)
		{
			snake->direction = direction;
			delete_snake(snake, screen, 0);
			snake->start_x++;
			draw_snake(snake, screen, 0);
		}
		else if (strcmp(snake->direction, "down") == 0)
		{
			snake->direction = direction;
			if (snake->blocks == 1)
			{
				snake->direction = direction;
				delete_snake(snake, screen, 0);
				snake->start_x++;
				draw_snake(snake, screen, 0);
			}
			else
			{
				snake->direction = direction;
				delete_snake(snake, screen, 1);
				snake->start_y += snake->blocks - 1;
				draw_snake(snake, screen, 0);
			}
		}
		else if (strcmp(snake->direction, "up") == 0)
		{
			snake->direction = direction;
			if (snake->blocks == 1)
			{
				snake->direction = direction;
				delete_snake(snake, screen, 0);
				snake->start_x++;
				draw_snake(snake, screen, 0);
			}
			else
			{
				snake->direction = direction;
				delete_snake(snake, screen, 1);
				snake->start_y += snake->blocks - 1;
				draw_snake(snake, screen, 0);
			}
		}
	}
	else if (strcmp(direction, "left") == 0)
	{
		if (strcmp(snake->direction, "left") == 0)
		{
			snake->direction = direction;
			delete_snake(snake, screen, 0);
			snake->start_x--;
			draw_snake(snake, screen, 0);
		}
		else if (strcmp(snake->direction, "right") == 0)
		{
			snake->direction = direction;
			delete_snake(snake, screen, 0);
			snake->start_x--;
			draw_snake(snake, screen, 0);
		}
		else if (strcmp(snake->direction, "down") == 0)
		{
			snake->direction = direction;
			if (snake->blocks == 1)
			{
				snake->direction = direction;
				delete_snake(snake, screen, 0);
				snake->start_x--;
				draw_snake(snake, screen, 0);
			}
			else
			{
				snake->direction = direction;
				delete_snake(snake, screen, 1);
				snake->start_y += snake->blocks - 1;
				draw_snake(snake, screen, 0);
			}
		}
		else if (strcmp(snake->direction, "up") == 0)
		{
			snake->direction = direction;
			if (snake->blocks == 1)
			{
				snake->direction = direction;
				delete_snake(snake, screen, 0);
				snake->start_x--;
				draw_snake(snake, screen, 0);
			}
			else
			{
				snake->direction = direction;
				delete_snake(snake, screen, 1);
				snake->start_y += snake->blocks - 1;
				draw_snake(snake, screen, 0);
			}
		}
	}
	else if (strcmp(direction, "down") == 0)
	{
		if (strcmp(snake->direction, "right") == 0)
		{
			if (snake->blocks == 1)
			{
				snake->direction = direction;
				delete_snake(snake, screen, 0);
				if (snake->start_y == 0)
				{
					snake->start_y += 2;
				}
				else
				{
					snake->start_y++;
				}
				snake->start_x += snake->blocks - 1;
				draw_snake(snake, screen, 0);
			}
			else
			{
				snake->direction = direction;
				delete_snake(snake, screen, 0);
				if (snake->start_y == 0)
				{
					snake->start_y += 2;
				}
				else
				{
					snake->start_y++;
				}
				snake->start_x += snake->blocks - 1;
				draw_snake(snake, screen, 1);
			}
			return 1;
		}
		else if (strcmp(snake->direction, "left") == 0)
		{
			if (snake->blocks == 1)
			{
				snake->direction = direction;
				delete_snake(snake, screen, 0);
				if (snake->start_y == 0)
				{
					snake->start_y += 2;
				}
				else
				{
					snake->start_y++;
				}
				draw_snake(snake, screen, 0);
			}
			else
			{

				snake->direction = direction;
				delete_snake(snake, screen, 0);
				if (snake->start_y == 0)
				{
					snake->start_y += 2;
				}
				else
				{
					snake->start_y++;
				}
				draw_snake(snake, screen, 1);
			}
			return 1;
		}
		else if (strcmp(snake->direction, "down") == 0)
		{
			snake->direction = direction;
			delete_snake(snake, screen, 1);
			if (snake->start_y == 0)
			{
				snake->start_y += 2;
			}
			else
			{
				snake->start_y++;
			}
			draw_snake(snake, screen, 1);
			return 1;
		}
		else if (strcmp(snake->direction, "up") == 0)
		{
			snake->direction = direction;
			delete_snake(snake, screen, 1);
			if (snake->start_y == 0)
			{
				snake->start_y += 2;
			}
			else
			{
				snake->start_y++;
			}
			draw_snake(snake, screen, 1);
			return 1;
		}
	}
	else if (strcmp(direction, "up") == 0)
	{
		if (strcmp(snake->direction, "right") == 0)
		{
			if (snake->blocks == 1)
			{
				snake->direction = direction;
				delete_snake(snake, screen, 0);
				if (snake->start_y == 0)
				{
					snake->start_y -= 2;
				}
				else
				{
					snake->start_y--;
				}
				snake->start_x += snake->blocks - 1;
				draw_snake(snake, screen, 0);
			}
			else
			{
				snake->direction = direction;
				delete_snake(snake, screen, 0);
				if (snake->start_y == 0)
				{
					snake->start_y -= 2;
				}
				else
				{
					snake->start_y--;
				}
				snake->start_x += snake->blocks - 1;
				draw_snake(snake, screen, 1);
			}
			return 1;
		}
		else if (strcmp(snake->direction, "left") == 0)
		{
			if (snake->blocks == 1)
			{
				snake->direction = direction;
				delete_snake(snake, screen, 0);
				if (snake->start_y == 0)
				{
					snake->start_y -= 2;
				}
				else
				{
					snake->start_y--;
				}
				draw_snake(snake, screen, 0);
			}
			else
			{

				snake->direction = direction;
				delete_snake(snake, screen, 0);
				if (snake->start_y == 0)
				{
					snake->start_y -= 2;
				}
				else
				{
					snake->start_y--;
				}
				draw_snake(snake, screen, 1);
			}
			return 1;
		}
		else if (strcmp(snake->direction, "down") == 0)
		{
			snake->direction = direction;
			delete_snake(snake, screen, 1);
			if (snake->start_y == 0)
			{
				snake->start_y -= 2;
			}
			else
			{
				snake->start_y--;
			}
			draw_snake(snake, screen, 1);
			return 1;
		}
		else if (strcmp(snake->direction, "up") == 0)
		{
			snake->direction = direction;
			delete_snake(snake, screen, 1);
			if (snake->start_y == 0)
			{
				snake->start_y -= 2;
			}
			else
			{
				snake->start_y--;
			}
			draw_snake(snake, screen, 1);
			return 1;
		}
	}
	return 0;
}
