#include "pch.h"
#include <iostream>
#include <time.h>
#include <conio.h>
#include <dos.h>
#include <stdio.h>

const int WIDTH = 20;
const int HEIGHT = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail = 0;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

bool gameOver;

void Setup() {
	gameOver = false;
	dir = STOP;
	x = WIDTH / 2 - 1;
	y = HEIGHT / 2 - 1;
	srand(time(NULL));
	fruitX = rand() % (WIDTH - 1);
	fruitY = rand() % (HEIGHT - 1);
	score = 0;
}

void Draw() {
	system("cls");  // Clear console

	for (int i = 0; i < WIDTH + 1; i++)	 //UP BORDER
		std::cout << "#";
	std::cout << "\n";


	for (int row = 0; row < HEIGHT - 1; row++)
	{
		for (int column = 0; column < WIDTH - 1; column++)
		{
			if (column == 0 || column == WIDTH - 1)
				std::cout << "#";
			if (row == y && column == x)
				std::cout << "0";
			else if (row == fruitY && column == fruitX)
				std::cout << "F";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == column && tailY[k] == row) {
						print = true;
						std::cout << "o";
					}
				}
				if (!print) {
					std::cout << " ";
				}


			}


		}

		std::cout << "\n";
	}


	for (int i = 0; i < WIDTH + 1; i++)	  //BOTTOM BORDER
		std::cout << "#";

	std::cout << "\n";
	std::cout << "SCORE: " << score << "\n";

}

void Input() {
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}

	//if (x > WIDTH - 2 || x < 0 || y > HEIGHT - 2 || y < 0) {
	//	gameOver = true;
	//}

	if (x >= WIDTH - 1)
		x = 0;
	else if (x < 0) {
		x = WIDTH - 2;
	}

	if (y >= HEIGHT)
		y = 0;
	else if (y < 0) {
		y = HEIGHT - 1;
	}



	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y) {
			gameOver = true;
		}
	}


	if (y == fruitY && x == fruitX) {
		score += 10;
		fruitX = rand() % WIDTH;
		fruitY = rand() % HEIGHT;
		nTail++;
	}
}

void sleep(double seconds) {
	clock_t stop = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < stop) {
	}
}

int main() {
	Setup();;
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		sleep(0.1);
	}
}
