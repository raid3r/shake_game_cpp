#include <iostream>
#include <deque>
#include <conio.h>
#include "work_with_console.h"

using namespace std;

enum ShakePartType {
	Tail, Body, Head
};

enum Direction {
	Left, Right, Up, Down
};

struct SnakePart {
	short x;
	short y;
	ShakePartType type;
};

void initSnake(deque<SnakePart>& snake) {
	snake.clear();
	snake.push_back({ 10,10,Head });
	snake.push_back({ 9,10,Body });
	snake.push_back({ 8,10,Tail });
}

void printSnake(const deque<SnakePart>& snake) {
	for (auto part : snake) {
		SetCursorPosition(part.x * 2, part.y);
		SetColor(White, Green);

		if (part.type == Head)
			cout << "HH";

		if (part.type == Body)
			cout << "BB";

		if (part.type == Tail)
			cout << "TT";
	}
}
void clearSnake(const deque<SnakePart>& snake) {
	for (auto part : snake) {
		SetCursorPosition(part.x * 2, part.y);
		SetColor(Black, Black);
		cout << "  ";
	}
}

SnakePart getNext(SnakePart& head, Direction direction) {
	switch (direction)
	{
	case Left:
		return { (short)(head.x + 1), head.y, Head };
	case Right:
		return { (short)(head.x - 1), head.y, Head };
	case Up:
		return { (short)(head.x), (short)(head.y - 1), Head };
	case Down:
		return { (short)(head.x), (short)(head.y + 1), Head };
	default:
		break;
	}
}

void moveSnake(deque<SnakePart>& snake, Direction direction, bool grow = false) {
	// [H] [B] [T]
	// тип голови замінити на тіло
	auto prevHead = snake.begin();
	prevHead->type = Body;

	// додати нову голову
	// TODO - coordinates 
	SnakePart newHead = getNext(*prevHead, direction);
	snake.push_front(newHead);

	if (!grow) {
		// видалити хвіст
		snake.pop_back();
		// останньому елементу замінити тип на хвіст
		snake.back().type = Tail;
	}
}


void drawFrame(int posX, int posY, int width, int height, ConsoleColor color) {
	for (size_t x = posX; x < posX + width; x++)
	{
		for (size_t y = posY; y < posY + height; y++) {
			SetCursorPosition(x, y);
			if (x == posX || x == posX + width - 1 || y == posY || y == posY + height - 1) {
				SetColor(White, color);
				cout << " ";
			}
			else {
				SetColor(White, Black);
				cout << " ";
			}
		}
	}
	SetColor(White, Black);
}



int main()
{
	drawFrame(0, 0, 44, 22, DarkGray);

	deque<SnakePart> snake;
	initSnake(snake);
	printSnake(snake);
	_getch();

	while (true)
	{
		clearSnake(snake);
		moveSnake(snake, Up);
		printSnake(snake);
		_getch();
	}


	/*
	Гра змійка

	Поле
	20 х 20
	2 елементи рухаеється вправо
	керування клавішами
	Змійка постійно рухаеться через заданий проміжок часу у напрямку останнього руху
	якщо врізається в стіну або в себе - гра закінчується

	Яблуко (їжа) з'являється у випадковому місці на полі
	за з'їдання їжі нараховується 10 очок та змія росте на 1 клітинку



	*/



}
