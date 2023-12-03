#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ncurses/ncurses.h>

int maxY, maxX;
int x, y;
char arah = 'd';
int score = 0;
int tailLength = 1;
int tailX[100], tailY[100];
int fruitX, fruitY;
bool game = true;

void Console() {
    if (kbhit()) {
        switch (getch()) {
            case 'a': if(arah!='d')arah = 'a'; break;
            case 'w': if(arah!='s')arah = 'w'; break;
            case 's': if(arah!='w')arah = 's'; break;
            case 'd': if(arah!='a')arah = 'd'; break;
            case 'q': game = false; break;
        }
    }
}

void Draw() {
    clear();
    WINDOW *win = newwin(maxY, maxX, 0, 0);

    refresh();
    box(win, 50, 0);
    wrefresh(win);

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    
    attron(COLOR_PAIR(1));
   
    mvprintw(y, x, "O");
    mvprintw(fruitY, fruitX, "#");

    for (int i = 0; i < tailLength; i++) {
        mvprintw(tailY[i], tailX[i], "o");
    }

    refresh();
    Sleep(100);
  
}
    

void Algorithm() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    if (arah == 'w') {
        y--;
    }
    if (arah == 's') {
        y++;
    }
    if (arah == 'a') {
        x--;
    }
    if (arah == 'd') {
        x++;
    }

    if (x == fruitX && y == fruitY) {
        fruitX = rand() % maxX;
        fruitY = rand() % maxY;
        score++;
        tailLength++;
    }

    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            game = false;
        }
    }

    if (x <= 0 || x >= maxX || y <= 0 || y >= maxY) {
        game = false;
    }
}

int main() {
   
    initscr();
    noecho();  
    curs_set(0); 

    getmaxyx(stdscr, maxY, maxX);

    y = maxY / 2;
    x = maxX / 2;
    fruitX = rand() % maxX;
    fruitY = rand() % maxY;


    do {
    	
        Draw();
        Console();
        Algorithm();
    } while (game);
    clear();
    
    attron(COLOR_PAIR(2));
    
    mvprintw(maxY/2,(maxX/2)-19,"Yah cupu cuma dapet skor %d",score);
    refresh();
    getch();
    endwin();

    return 0;
}
