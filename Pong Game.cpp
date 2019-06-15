/*
Console C++ Pong Game
Started: 11/06/2018
Finished: 16/06/2018
by N0il
*/
#define KEY_UP 72
#define KEY_DOWN 80
#define _WIN32_WINNT 0x0500 //Says that you are running this program on Windows 2000 or higher
                            //is necessary for the GetConsoleWindow() function to work!
#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

char option, balldir;
int score1, score2, y1 = 11, y2 = 11, bally, ballx, prevx, prevy, dif = 4, difvalue;
int width = 66, height = 22, w_WIDTH, w_HEIGHT;
HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
bool GameOver, GameState = true;
string name1, name2 = "Machine";
enum Direction {UP, DOWN, UP2, DOWN2, LEFTDOWN, LEFTUP, RIGHTDOWN, RIGHTUP};
Direction ballRdir, ballLdir;

void RandomDir(){
    int random1 = rand() % 2 + 1;
    switch(random1){
        case 1:
            balldir = 'L';
        case 2:
            balldir = 'R';
    }
}
void RandomBallDir(){
     int random2 = rand() % 2 + 1;
     switch(random2){
         case 1:
             ballLdir = LEFTUP;
             ballRdir = RIGHTUP;
         case 2:
             ballLdir = LEFTDOWN;
             ballRdir = RIGHTDOWN;
     }
}
void GotoXY(int x, int y){
    COORD pos = {x, y};
    SetConsoleCursorPosition(Console, pos);
}
void Clear(){
    system("cls");
}
void Exit(){
    GameState = false;
    system("exit");
}
void Input(){
    if(kbhit()){
        switch(getch()){
            case 'w':
                if(y1 != height-1)
                    y1--;
                break;
            case 's':
                if(y1 != 2)
                    y1++;
                break;
            case KEY_UP:
                if(y2 != 2 && option == 'o')
                    y2--;
                break;
            case KEY_DOWN:
                if(y2 != height-1 && option == 'o')
                    y2++;
                break;
            case 'x':
                GotoXY(11,20);
                SetConsoleTextAttribute(Console, 6);
                cout <<"The game is stopped... press any key to continue\n";
                getch();
                break;
            case 'e':
                GameOver = true;
                break;
        }
    }
}
void Logic(){
    switch(balldir){
     case 'L':
         switch(ballLdir){
             case LEFTUP:
                 if(ballx == width / 2 && prevx < ballx){
                        bally = rand() % height;
                        ballx -= 1;
                 }
                 else{
                        bally -= 1;
                        ballx -= 1;
                 }
                 break;
             case LEFTDOWN:
                 if(ballx == width / 2 && prevx < ballx){
                        bally = rand() % height;
                        ballx -= 1;
                 }
                 else{
                        bally += 1;
                        ballx -= 1;
                 }
                 break;
        }
     break;
     case 'R':
         switch(ballRdir){
             case RIGHTUP:
                 if(ballx == width / 2 && prevx > ballx){
                        bally = rand() % height;
                        ballx += 1;
                 }
                 else{
                        bally -= 1;
                        ballx += 1;
                  }
                  break;
            case RIGHTDOWN:
                 if(ballx == width / 2 && prevx > ballx){
                        bally = rand() % height;
                        ballx += 1;
                 }
                 else{
                        bally += 1;
                        ballx += 1;
                 }
                 break;
    }
    break;
 }
    if(ballx == 3 && bally == y1){
        balldir = 'R';
        if(ballLdir == LEFTDOWN)
            ballRdir = RIGHTUP;
        else if(ballLdir == LEFTUP)
            ballRdir = RIGHTDOWN;
    }
    else if(ballx == 63 && bally == y2){
        balldir = 'L';
        if(ballRdir == RIGHTDOWN)
            ballLdir = LEFTUP;
        else if(ballRdir == RIGHTUP)
            ballLdir = LEFTDOWN;
    }
    else if(ballx == 63){
        if(bally != y2)
            score1++;
        balldir = 'L';
    }
    else if(ballx == 3){
        if(bally != y1)
            score2++;
        balldir = 'R';
    }
    else if(bally == height-1){
        if(balldir == 'L')
            ballLdir = LEFTUP;
        else if(balldir == 'R')
            ballRdir = RIGHTUP;
    }
    else if(bally == 2){
        if(balldir == 'L')
            ballLdir = LEFTDOWN;
        else if(balldir == 'R')
            ballRdir = RIGHTDOWN;
    }
}
void RemoveCursor(){
    CONSOLE_CURSOR_INFO  cursorInfo;
    GetConsoleCursorInfo(Console, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(Console, &cursorInfo);
}
void Init(){
    GameOver = false;
    score1 = 0;
    score2 = 0;
    ballx = width / 2;
    RandomDir();
    RandomBallDir();
    RemoveCursor();
    cout <<"Input the player one name: ";
    cin >> name1;
}
void Title(){
    Clear();
    SetConsoleTextAttribute(Console, 10);
    cout <<"-----------------------Console C++ Pong Game----------------------\n\n"
         <<"\t 8b dPPYba     adPPYba   8b dPPYba     adPPYb d8\n"
         <<"\t 88P      8a a8       8a 88P      8a a8      Y88\n"
         <<"\t 88       d8 8b       d8 88       88 8b       88\n"
         <<"\t 88b     a8   8a     a8  88       88  8a     d88\n"
         <<"\t 88 YbbdP       YbbdP    88       88    YbbdP Y8\n"
         <<"\t 88                                   aa      88\n"
         <<"\t 88                                     Y8bbdP  \n\n"
         <<"------------------------------------------------------------------\n";
    SetConsoleTextAttribute(Console, 6);
}
void StartMenu(){
    SetConsoleTitle("Pong Game");
    Title();
    cout <<"Menu\n"
         <<"For 1 players press 's'\n"
         <<"For 2 player press 'o'\n"
         <<"To change difficulty 'd'\n"
         <<"For instructions press 'i'\n"
         <<"To exit press 'e'\n"
         <<"Input: ";
    cin >> option;
}
void Difficulty(){
    Title();
    cout <<"Choose the difficulty from 1 to 3 in case of solo\n"
         <<"Easy - 1\nHard - 2\nExtreme - 3\n"
         <<"Input: ";
    cin >> difvalue;
    switch(difvalue){
        case 1:
            dif = 4;
            break;
        case 2:
            dif = 2;
            break;
        case 3:
            dif = 1;
            break;
        default:
            dif = 4;
            break;
    }
    cout <<"Press any key to go back to menu..";
    getch();
}
void Winner(){
    SetConsoleTextAttribute(Console, 10);
    cout << "WINNER\n";
    GotoXY((width/2)-8, 10);
    cout <<"Press any key to go back to menu..";
    getch();
    GameOver = true;
}
void Score(){
    GotoXY((width/4)-1, 3);
    SetConsoleTextAttribute(Console, 1);
    cout << name1 << ": " << score1;
    GotoXY(((width/4)*3)-2, 3);
    SetConsoleTextAttribute(Console, 4);
    cout << name2 << ": " << score2;
    if(score1 == 10){
        GotoXY((width/4)-1, 8);
        Winner();
    }else if(score2 == 10){
        GotoXY(((width/4)*3)-2, 8);
        Winner();
    }
}
void Instructions(){
    Title();
    cout <<"Player 1: \n"
         <<"Press 'w' to move up\n"
         <<"Press 's' to move down\n"
         <<"Player 2:\n"
         <<"Press 'arrow up' to move up\n"
         <<"Press 'arrow downs' to move down\n"
         <<"Press 'x' to stop\n"
         <<"Press 'e' to exit\n"
         <<"Press any key to return to menu\n";
         getch();
}
void Draw(){
    Clear();
    SetConsoleTextAttribute(Console, 8);
    for(int i = 0; i < width; i++){
        cout <<"#";
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            prevx = ballx;
            prevy = bally;
            if(j == (width/2)){
                SetConsoleTextAttribute(Console, 8);
                cout <<"|";
            }
            else if(j == 3 && i == y1){
                SetConsoleTextAttribute(Console, 1);
                cout <<(char)219;
            }
            else if(j == 63 && i == y2){
                SetConsoleTextAttribute(Console, 4);
                cout <<(char)219;
            }
            else if(ballx == j && bally == i){
                SetConsoleTextAttribute(Console, 7);
                cout <<(char)254;
            }
            else
                cout <<" ";
        }
        cout << endl;
    }
    SetConsoleTextAttribute(Console, 8);
    for(int i = 0; i < width; i++){
        cout <<"#";
    }
    Score();
}
void AI(){
    if(prevx == 61){
        if(ballRdir == RIGHTDOWN){
            y2 = prevy+2 + (rand() % dif);
        }
        else if(ballRdir == RIGHTUP){
            y2 = prevy-2 + (rand() % dif);
        }
    }
}
void Game(){
    if((ballx == 3 | ballx == 63) && bally != y1 && bally != y2){
        ballx = width / 2;
        RandomBallDir();
    }
    Draw();
    Logic();
    Input();
    Sleep(50);
}
int main(){
    while(GameState == true){
        StartMenu();
        switch(option){
            case 'o':
                Init();
                cout <<"Input player two name: ";
                cin >> name2;
                while(GameOver != true){
                    Game();
                }
                break;
            case 's':
                Init();
                while(GameOver != true){
                    AI();
                    Game();
                }
                break;
            case 'd':
                Difficulty();
                break;
            case 'i':
                Instructions();
                break;
            case 'e':
                Exit();
                break;
            default:
                cout <<"Try again (press 'y') or exit\n"
                     <<"Input: ";
                cin >> option;
                if(option != 'y')
                    Exit();
                break;
        }
    }

return 0;
}
