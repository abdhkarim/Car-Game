#include <iostream>
#include<conio.h>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyX[3];
int enemyY[3];
int enemyFlag[3];
char car[4][4] = { ' ','+','+',' ',
                   '+','+','+','+',
                   ' ','+','+',' ',
                   '+','+','+','+' };

int carPos = WIN_WIDTH / 2;
int score = 0;

void gotoxy(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console,CursorPosition);
}

void setcursor(bool visible, DWORD size)
{
    if(size == 0)
    {
        size = 20;
    }

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console,&lpCursor);
}

void drawBorder()
{
    for(int i=0; i<SCREEN_HEIGHT; i++)
    {
        for(int j=0; j<17; j++)
        {
            gotoxy(0+j,i); cout<<("+");
            gotoxy(WIN_WIDTH-j,i); cout<<("+");
        }
        for(int i=0; i<SCREEN_HEIGHT; i++)
        {
            gotoxy(WIN_WIDTH+1,i); cout<<"+";
        }
    }
}

void genEnemy(int ind)
{
    enemyX[ind] = 17 + rand()%(33);
}

void drawEnemy(int ind)
{
    if(enemyFlag[ind] == true)
    {
        gotoxy(enemyX[ind],enemyY[ind]);   cout<<"****";
        gotoxy(enemyX[ind],enemyY[ind]+1); cout<<" ** ";
        gotoxy(enemyX[ind],enemyY[ind]+2); cout<<"****";
        gotoxy(enemyX[ind],enemyY[ind]+3); cout<<" ** ";
    }
}

void eraseEnemy(int ind)
{
    if(enemyFlag[ind] == true)
    {
        gotoxy(enemyX[ind],enemyY[ind]);   cout<<"    ";
        gotoxy(enemyX[ind],enemyY[ind]+1); cout<<"    ";
        gotoxy(enemyX[ind],enemyY[ind]+2); cout<<"    ";
        gotoxy(enemyX[ind],enemyY[ind]+3); cout<<"    ";
    }
}
void resetEnemy(int ind)
{
    eraseEnemy(ind);
    enemyY[ind] = 1;
    genEnemy(ind);
}

void drawCar()
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            gotoxy(j+carPos,i+22); cout<<car[i][j];
        }
    }
}

void eraseCar()
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            gotoxy(j+carPos,i+22); cout<<" ";
        }
    }
}

int collision()
{
    if(enemyY[0]+4 >= 23)
    {
        if(enemyX[0]+4-1 >= carPos && enemyX[0] <= carPos+4-1)
        {
            return 1;
        }
    }
    return 0;
}

void gameover()
{
    system("cls");
    cout<<endl;
    cout<<"\t\t\t=============================="<<endl;
    cout<<"\t\t\t========= GAME OVER =========="<<endl;
    cout<<"\t\t\t=============================="<<endl<<endl;   
    cout<<"\t\t\tAppuie sur n'importe quel bouton pour revenir au menu principal..."<<endl;
    getch();
}

void updateScore()
{
    gotoxy(WIN_WIDTH+7,5); cout<<"Score: "<<score<<endl;
}

void instructions()
{
    system("cls");
    cout<<"Instructions";
    cout<<"\n----------------";
    cout<<"\n Chef, vesqui les voitures qui roulent a contre sens";
    cout<<"\n Appuie sur 'A' pour bouger a gauche";
    cout<<"\n Appuie sur 'D' pour bouger a droite";
    cout<<"\n----------------";
    cout<<"\n Touche n'importe quel touche pour retourner au menu principal";
    getch();

}

void play()
{
    carPos = -1 + WIN_WIDTH/2;
    score = 0;
    enemyFlag[0] = 1;
    enemyFlag[1] = 0;
    enemyY[0] = enemyY[1] = 1;

    system("cls");
    drawBorder();
    updateScore();
    genEnemy(0);
    genEnemy(1);

    gotoxy(WIN_WIDTH+7,2); cout<<"VESQUI LA TCHOP";
    gotoxy(WIN_WIDTH+6,4); cout<<"----------";
    gotoxy(WIN_WIDTH+6,6); cout<<"----------";
    gotoxy(WIN_WIDTH+7,8); cout<<"Controles";
    gotoxy(WIN_WIDTH+7,9); cout<<"----------";
    gotoxy(WIN_WIDTH+2,10); cout<<"A - Gauche";
    gotoxy(WIN_WIDTH+2,11); cout<<"D - Droite";

    gotoxy(18,5); cout<<"Touche n'importe quel touche pour debuter la partie";
    getch();
    gotoxy(18,5); cout<<"                      ";

    while(1)
    {
        if(kbhit())
        {
            char ch = getch();
            if(ch == 'a' || ch == 'A')
            {
                if(carPos > 18)
                {
                    carPos -= 4;
                    eraseCar();
                    drawCar();
                }
            }
            if(ch == 'd' || ch == 'D')
            {
                if(carPos < 50)
                {
                    carPos += 4;
                    eraseCar();
                    drawCar();
                }
            }
            if(ch == 27)
            {
                break;
            }
        }
    drawCar();
    drawEnemy(0);
    drawEnemy(1);
    if(collision() == 1)
    {
        gameover();
        return;
    }
    Sleep(50);
    eraseCar();
    eraseEnemy(0);
    eraseEnemy(1);

        if(enemyY[0] == 10)
        {
            if(enemyFlag[1] == 0)
                enemyFlag[1] = 1;
        }

        if(enemyFlag[0] == 1)
        {
            enemyY[0] += 1;
        }

        if(enemyFlag[1] == 1)
        {
            enemyY[1] += 1;
        }

        if(enemyY[0] > SCREEN_HEIGHT-4)
        {
            resetEnemy(0);
            score++;
            updateScore();
        }

        if(enemyY[1] > SCREEN_HEIGHT-4)
        {
            resetEnemy(1);
            score++;
            updateScore();
        }
    }

}

int main()
{
    setcursor(0,0);
    srand((unsigned)time(NULL));

    do{
        system("cls");
        gotoxy(10,5);  cout<<"=======================";
        gotoxy(10,6);  cout<<"|   VESQUI LA TCHOP     |";
        gotoxy(10,7);  cout<<"=======================";
        gotoxy(10,9);  cout<<"1. Jouer au jeu";
        gotoxy(10,10); cout<<"2. Instructions";
        gotoxy(10,11); cout<<"3. Quitter";
        gotoxy(10,13); cout<<"Choisir une option: ";
        char op = getche();

        if(op == '1')
        {
            play();
        }
        else if(op == '2')
        {
            instructions();
        }
        else if(op == '3')
        {
            exit(0);
        }
    }while(1);

    return 0;
}
