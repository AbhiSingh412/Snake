#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>
#include<windows.h>
#include<process.h>
#include<time.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int length;
int len;
int life;
int bend_count;
char key;
void delay(long double);
void motion();
void refood();
int score();
void display_intro();
void GotoXY(int x,int y);
void bender();
void border();
void Down();
void Left();
void Up();
void Right();
void ExitGame();

struct coordinate
{
    int x;
    int y;
    int direction;
}head, food, body[30], bend[500];

int main()
{
    char key;
    display_intro();
    system("cls");
    length=2;
    head.x=35;
    head.y=20;
    head.direction=RIGHT;
    border();
    refood();
    life=3;
    bend[0]=head;
    motion();
    return 0;
}

void motion()
{
    int a,i;
    do
    {
        refood();
        fflush(stdin);
        len=0;
        for(i=0; i<30; i++)
        {
            body[i].x=0;
            body[i].y=0;
            if(i==length)
                break;
        }
        delay(length);
        border();
        if(head.direction==RIGHT)
            Right();
        else if(head.direction==LEFT)
            Left();
        else if(head.direction==DOWN)
            Down();
        else if(head.direction==UP)
            Up();
        ExitGame();
    }
    while(!kbhit());
    a=getch();
    if(a==27)
    {
        system("cls");
        exit(0);
    }
    key=getch();
    if((key==RIGHT && head.direction!=LEFT && head.direction!=RIGHT) || (key==LEFT && head.direction!=RIGHT && head.direction!=LEFT) || (key==UP && head.direction!=DOWN && head.direction!=UP) || (key==DOWN && head.direction!=UP && head.direction!=DOWN))
    {
        bend_count++;
        bend[bend_count]=head;
        head.direction=key;
        if(key==UP)
            head.y--;
        if(key==DOWN)
            head.y++;
        if(key==RIGHT)
            head.x++;
        if(key==LEFT)
            head.x--;
        motion();
    }
    else if(key==27)
    {
        system("cls");
        exit(0);
    }
    else
    {
        printf("\a");
        motion();
    }
}

void GotoXY(int x, int y)
{
    HANDLE out_device;
    COORD active_coord;
    fflush(stdout);
    active_coord.X = x;
    active_coord.Y = y;
    out_device = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(out_device,active_coord);
}

void display_intro()
{
    printf("Glad to see you in Abhishek's Snake game. Welcome.....\nPress any key to continue....");
    getch();
    system("cls");
    printf("\nGame instructions:\n");
    printf("Use arrow keys for moving the snake and have to eat the pills to be considered as the food for the snake. It will increase the score and if you hit your tail or wall, then one life will be lost and you have total of 3 lives. After 3 lives, game will be over.\n\nIt is requested to play the game in fullscreen for better performance.\n\n\n\n");
    printf("Press any key to play game...");
    if(getch()==27)
        exit(0);
}

void delay(long double k)
{
    score();
    long double i;
    for(i=0; i<=(10000000); i++);
}

void ExitGame()
{
    int i,chck=0;
    for(i=4; i<length; i++)
    {
        if(body[0].x==body[i].x && body[0].y==body[i].y)
        {
            chck++;
        }
        if(i==length||chck!=0)
            break;
    }
    if(head.x<=30 || head.x>=100 || head.y<=10 || head.y>=40 || chck!=0)
    {
        life--;
        if(life>=0)
        {
            head.x=35;
            head.y=20;
            bend_count=0;
            head.direction=RIGHT;
            motion();
        }
        else
        {
            system("cls");
            printf("You've lost all your lives\n\nBetter Luck Next Time!!!\n\n\n\n\n\n\nPress any key to quit the game\n");
            exit(0);
        }
    }
}

void refood()
{
    if(head.x==food.x && head.y==food.y)
    {
        length++;
        time_t a;
        a=time(0);
        srand(a);
        food.x=rand()%100;
        if(food.x<=30)
            food.x+=31;
        food.y=rand()%40;
        if(food.y<=10)
            food.y+=11;
    }
    else if(food.x==0)
    {
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)
            food.y+=11;
    }
}

void Up()
{
    int i;
    for(i=0; i<=(bend[bend_count].y-head.y) && len<length; i++)
    {
        GotoXY(head.x,head.y+i);
        {
            if(len==0)
                printf("^");
            else
                printf("*");
        }
        body[len].x=head.x;
        body[len].y=head.y+i;
        len++;
    }
    bender();
    if(!kbhit())
        head.y--;
}

void Down()
{
    int i;
    for(i=0; i<=(head.y-bend[bend_count].y) && len<length; i++)
    {
        GotoXY(head.x,head.y-i);
        {
            if(len==0)
                printf("v");
            else
                printf("*");
        }
        body[len].x=head.x;
        body[len].y=head.y-i;
        len++;
    }
    bender();
    if(!kbhit())
        head.y++;
}

void Left()
{
    int i;
    for(i=0; i<=(bend[bend_count].x-head.x) && len<length; i++)
    {
        GotoXY((head.x+i),head.y);
        {
            if(len==0)
                printf("<");
            else
                printf("*");
        }
        body[len].x=head.x+i;
        body[len].y=head.y;
        len++;
    }
    bender();
    if(!kbhit())
        head.x--;

}

void Right()
{
    for(int i=0; i<=(head.x-bend[bend_count].x) && len<length; i++)
    {
        body[len].x=head.x-i;
        body[len].y=head.y;
        GotoXY(body[len].x,body[len].y);
        {
            if(len==0)
                printf(">");
            else
                printf("*");
        }
        len++;
    }
    bender();
    if(!kbhit())
        head.x++;
}

void bender()
{
    int i,j,diff;
    for(i=bend_count; i>=0 && len<length; i--)
    {
        if(bend[i].x==bend[i-1].x)
        {
            diff=bend[i].y-bend[i-1].y;
            if(diff<0)
                for(j=1; j<=(-diff); j++)
                {
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y+j;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff; j++)
                {
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y-j;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
        }
        else if(bend[i].y==bend[i-1].y)
        {
            diff=bend[i].x-bend[i-1].x;
            if(diff<0)
                for(j=1; j<=(-diff)&&len<length; j++)
                {
                    body[len].x=bend[i].x+j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff&&len<length; j++)
                {
                    body[len].x=bend[i].x-j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
        }
    }
}

void border()
{
    system("cls");
    GotoXY(food.x,food.y);
    printf("o");
    for(int i=30; i<101; i++)
    {
        GotoXY(i,10);
        printf("-");
        GotoXY(i,40);
        printf("-");
    }
    for(int j=10; j<41; j++)
    {
        GotoXY(30,j);
        printf("|");
        GotoXY(100,j);
        printf("|");
    }
}

int score()
{
    int score;
    GotoXY(30,6);
    score=length-2;
    printf("Score: %d",score);
    // score=length-2;
    GotoXY(90,6);
    printf("Lives: %d",life);
    return score;
}
