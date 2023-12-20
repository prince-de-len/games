/*************************************
* Автор: Тимофеев Гордей Евгеньевич. ПИ-231
* Версия 1
* Название: Змейка
************************************/

#include <cstdlib>
#include <ncurses.h>

bool gameOver;
const int width = 20, height = 20;
int x,y, FruitX, FruitY, score;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

int TailX[100], TailY[100];
int nTail = 0;

void Setup() {

  initscr();
  clear();
  noecho();
  cbreak();
  curs_set(0);

  gameOver = false;
  dir = STOP;
  x = width / 2;
  y = height / 2;
  FruitX = (rand() % width) + 1;
  FruitY = (rand() % height) + 1;
  score = 0;

}

void Draw() {

  clear();

  for (int row = 0; row < width + 2; row++) {
    mvprintw(0, row, "+");
  }
  for (int row = 0; row < height + 2; row++) {
    for (int column = 0; column < width + 2; column++) {
      if (row == 0 | row == 21) {
        mvprintw(row, column, "#");
      }
      else if (column == 0 | column == 21) {
        mvprintw(row, column, "+");
      }
      else if (row == y && column == x) {
        mvprintw(row, column, "0");
      }
      else if (row == FruitY && column == FruitX) {
        mvprintw(row, column, "0");
      }
      else {
        for (int tailSegment = 0; tailSegment < nTail; tailSegment++) {
          if (TailX[tailSegment] == column && TailY[tailSegment] == row) {
            mvprintw(row, column, "o");
          }
        }
      }
    }
  }

  mvprintw(23, 0, "Score %d", score);

  refresh();


}

void Input() {

  keypad(stdscr, TRUE);
  halfdelay(1);

  int c = getch();

  switch(c) {
    case KEY_LEFT:
      dir = LEFT;
      break;
    case KEY_RIGHT:
      dir = RIGHT;
      break;
    case KEY_UP:
      dir = UP;
      break;
    case KEY_DOWN:
      dir = DOWN;
      break;
    case 113:
      gameOver = true;
      break;
  }

}

void Logic() {

  int prevX = TailX[0];
  int prevY = TailY[0];
  int prev2X, prev2Y;

  TailX[0] = x;
  TailY[0] = y;

  for (int segmentIndex = 1; segmentIndex < nTail; segmentIndex++) {
    prev2X = TailX[segmentIndex];
    prev2Y = TailY[segmentIndex];
    TailX[segmentIndex] = prevX;
    TailY[segmentIndex] = prevY;
    prevX = prev2X;
    prevY = prev2Y;
  }

  switch (dir) {
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
    default:
      break;
  }

  if (x > width || x < 1 || y > height || y < 1) {
    gameOver = true;
  }
  if (x == FruitX && y == FruitY) {
    score++;
    FruitX = (rand() % width)+1;
    FruitY = (rand() % height)+1;
    nTail++;
  }

  for (int tailSegment = 0; tailSegment < nTail; tailSegment++) {
    if (TailX[tailSegment] == x && TailY[tailSegment] == y) {
      gameOver = true;
    }
  }

}

int main() {

  Setup();

  while(!gameOver) {
    Draw();
    Input();
    Logic();
  }

  getch();
  endwin();

  return 0;
}
