/*
Console C++ Snake Game
by N0il
*/
#define _WIN32_WINNT 0x0500 //Says that you are running this program on Windows 2000 or higher
                            //is necessary for the GetConsoleWindow() function to work!
#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
const int WIDTH = 64, HEIGHT = 22;
const int W_width = 8.59375 * WIDTH, W_height = 18.18181 * HEIGHT; //Correspondent size in pixels for MoveWindow()
const int centerX = 413, centerY = 164; //X and Y for MoveWindow()
enum Direction {UP, DOWN, LEFT, RIGHT};
Direction dir;
bool GameState;
int x = WIDTH / 2, y = HEIGHT / 2, FruitX, FruitY;
char option, input;
int score, winner = 17, dif = 1, speed = 100;
int OverX = (WIDTH / 2)-6, OverY = (HEIGHT / 2)-3;
int tailX[30], tailY[30], nTail;

void GameMusic(){
    PlaySound(TEXT("TwoThirds.wav"), NULL, SND_ASYNC);  //background music
}
void FruitSpawn(){
    FruitX = rand() % WIDTH;
    FruitY = rand() % (HEIGHT-4);
}
void Init(){      //Meta-data to initialize the game
    GameState = true;
    score = 0;
    nTail = 0;
    input = 'x';
    x = WIDTH / 2, y = HEIGHT / 2;
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(hConsole, &cursorInfo);
      GameMusic();
      FruitSpawn();
}
void Title(){
    SetConsoleTextAttribute(hConsole, 10); //10 for green
    cout <<"---------------------Console C++ Snake Game---------------------\n"
         <<"                 _________         _________\n"
         <<"                /         \\       /         \\   ASCII Art by\n"
         <<"               /  /~~~~~\\  \\     /  /~~~~~\\  \\   Normand\n"
         <<"               |  |     |  |     |  |     |  |    Veilleux\n" //adapted
         <<"               |  |     |  |     |  |     |  |\n"
         <<"               |  |     |  |     |  |     |  |        /\n"
         <<"               |  |     |  |     |  |     |  |      //\n"
         <<"              (o  o)    \\  \\_____/  /     \\  \\_____/ /\n"
         <<"               \\__/      \\         /       \\         /\n"
         <<"                |         ~~~~~~~~~          ~~~~~~~~\n"
         <<"                ^\n"
         <<"----------------------------------------------------------------\n";

}
void OverSound(){
    Beep(300,250);
    Beep(230,250);
    Beep(200,1500);
}
void WinnerSound(){
    Beep(400,250);
    Beep(400,250);
    Beep(500,500);
    Beep(600,1000);
}
void GotoXY(int x, int y){
    COORD pos = {x, y};
    SetConsoleCursorPosition(hConsole, pos);
}
void GameOver(){
    SetConsoleTextAttribute(hConsole, 4); //4 for red
    system("cls");
    GotoXY(OverX, OverY);
    cout <<"Game Over!";
    OverSound();
}
void StartMenu(){
    system("cls");
    Title();
    SetConsoleTextAttribute(hConsole, 8); //8 for light-gray
    cout <<"Press 's' to start.\n"
         <<"Press 'd' to set the difficulty\n"
         <<"Press 'i' to show Instructions.\n"
         <<"Press 'e' to close the game.\n"
         <<"Current difficulty: " << dif << endl
         <<"Previous score: " << score << endl
         <<"Input: ";
     cin >> option;
}
void SetDifficulty(){
    system("cls");
    Title();
    SetConsoleTextAttribute(hConsole, 8);
    cout <<"Choose the difficulty (speed) of the game from level 1 to 3.\n"
         <<"Input: ";
    cin >> dif;
    if(dif == 1)
        speed = 100;
    else if(dif == 2)
        speed = 60;
    else if(dif == 3)
        speed = 30;
    else{
        cout <<"Value not supported!\n";
        Sleep(1000);
    }
}
void Instruction(){
    system("cls");
    Title();
    SetConsoleTextAttribute(hConsole, 8);
    cout <<"Press 'w' to move forward.\n"
         <<"Press 's' to move backwards.\n"
         <<"Press 'a' to move left.\n"
         <<"Press 'd' to move right.\n"
         <<"Press 'x' to stop the game.\n"
         <<"Press 'e' to end the game and go back to Start Menu.\n"
         <<"Enter any letter to exit instructions\n";
         getch();
}
void Score(){
    cout << "Score: " << score;
    if(score == winner){
        system("cls");
        SetConsoleTextAttribute(hConsole, 3); //3 for blue
        GotoXY(OverX, OverY);
        cout <<"CONGRATS YOU WON!!";
        WinnerSound();
        GameState = false;
    }
}
void Draw(){
    system("cls");
    for(int i = 0; i < WIDTH; i++) //top borders
        cout << "#";
    for(int j = 0; j < HEIGHT-4; j++){
       for(int i = 0; i < WIDTH; i++){
          if(i == 0)                    //right borders
             cout << "#";
          else if(i == x && j == y)
             cout << "O";
          else if(i == FruitX && j == FruitY)
             cout << "F";
          else if(i < WIDTH-1)
             cout << " ";
          else if(i == WIDTH-1)          //left borders
             cout << "#";
           for(int n = 0; n < nTail; n++){
                if(i == tailX[n]-1 && j == tailY[n]){
                   cout << "o";
                }
           }
      }
      cout << endl;
    }
    for(int i = 0; i < WIDTH; i++)  //downer borders
                    cout << "#";
}
void Input(){
    if(kbhit()){
        switch(input = getch()){
            case 'x':
                cout <<"\tGame is stopped...  Press any key to continue\n";
                getch();
                break;
            case 'w':
                Sleep(30);   //so that up speed is not higher than right or left
                dir = UP;
                break;
            case 's':
                Sleep(30);   //same as UP
                dir = DOWN;
                break;
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'e':
                GameState = false;
                break;
        }
    }
}
void Logic(){
    int prevX = tailX[0];  //it gives the coordinates of snake's head so that when snake head is printed
	int prevY = tailY[0];  //at other place the tail is printed right in the place where head was
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
    for(int i = 1; i < nTail; i++){
        prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;

    }
    switch(dir){
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
    }
    if (x == FruitX && y == FruitY) {
        FruitSpawn();
        Beep(600,60);
		score++;
		nTail++;
	}
	else if(x < 0 || y < 0 || x > WIDTH || y > HEIGHT-4)  //collision against borders
        GameState = false;
     for(int r = 0; r < nTail; r++){  //collision against it's own tail
         if(tailX[r] == x && tailY[r] == y)
            GameState = false;
     }
}
void remove_scrollbar()  //removes scrollbar
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hConsole, &info);
    COORD new_size =
    {
        info.srWindow.Right - info.srWindow.Left + 1,
        info.srWindow.Bottom - info.srWindow.Top + 1
    };
    SetConsoleScreenBufferSize(hConsole, new_size);
}
int main(){
    SetConsoleTitle("Snake Game");
    HWND console = GetConsoleWindow();
    MoveWindow(console, centerX, centerY, W_width, W_height, TRUE);  //MoveWindow(window_handle, x, y, width, height, redraw_window);
    remove_scrollbar();
START:
    StartMenu();
      if (option == 's'){
            Init();
            while(GameState == true){
                Draw();
                Score();
                Input();
                Logic();
                Sleep(speed);
            }
            if(score != winner){
                    GameOver();
            }
            goto START;
    }
    else if(option == 'd'){
        SetDifficulty();
          goto START;
    }
    else if(option == 'i'){
        Instruction();
          goto START;
    }
    else if(option == 'e')
        system("exit");
    else{
        cout << "Try again (t) or exit (e)\n"
             << "Input: ";
        cin >> option;
          if(option == 't')
            goto START;
          else
            system("exit");
    }
return 0;
}
