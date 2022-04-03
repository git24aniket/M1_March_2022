#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <windows.h>

int brd[10] = {2,2,2,2,2,2,2,2,2,2};
int trn = 1,flag = 0;
int plyr,comp;

void menu();
void go(int n);
void strt_gm();
void chk_drw();
void draw_brd();
void plyr_first();
void put_X_O(char ch,int ps);
COORD coord= {0,0};
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void main()
{
    system("cls");
    menu();
    getch();

}

void menu()
{
    int choose;
    system("cls");
    printf("\n--------TIC TAC TOE--------");
    printf("\n1 : Play with X");
    printf("\n2 : Play with O");
    printf("\n3 : Exit");
    printf("\nEnter your choice:>");
    scanf("%d",&choose);
    trn = 1;
    switch (choose)
    {
    case 1:
        plyr = 1;
        comp = 0;
        plyr_first();
        break;
    case 2:
        plyr = 0;
        comp = 1;
        strt_gm();
        break;
    case 3:
        exit(1);
    default:
        menu();
    }
}

int make2()
{
    if(brd[5] == 2)
        return 5;
    if(brd[2] == 2)
        return 2;
    if(brd[4] == 2)
        return 4;
    if(brd[6] == 2)
        return 6;
    if(brd[8] == 2)
        return 8;
    return 0;
}

int make4()
{
    if(brd[1] == 2)
        return 1;
    if(brd[3] == 2)
        return 3;
    if(brd[7] == 2)
        return 7;
    if(brd[9] == 2)
        return 9;
    return 0;
}

int psswin(int p)
{
    int i;
    int chk_val,ps;

    if(p == 1)
        chk_val = 18;
    else
        chk_val = 50;

    i = 1;
    while(i<=9)
    {
        if(brd[i] * brd[i+1] * brd[i+2] == chk_val)
        {
            if(brd[i] == 2)
                return i;
            if(brd[i+1] == 2)
                return i+1;
            if(brd[i+2] == 2)
                return i+2;
        }
        i+=3;
    }

    i = 1;
    while(i<=3)
    {
        if(brd[i] * brd[i+3] * brd[i+6] == chk_val)
        {
            if(brd[i] == 2)
                return i;
            if(brd[i+3] == 2)
                return i+3;
            if(brd[i+6] == 2)
                return i+6;
        }
        i++;
    }

    if(brd[1] * brd[5] * brd[9] == chk_val)
    {
        if(brd[1] == 2)
            return 1;
        if(brd[5] == 2)
            return 5;
        if(brd[9] == 2)
            return 9;
    }

    if(brd[3] * brd[5] * brd[7] == chk_val)
    {
        if(brd[3] == 2)
            return 3;
        if(brd[5] == 2)
            return 5;
        if(brd[7] == 2)
            return 7;
    }
    return 0;
}

void go(int n)
{
    if(trn % 2)
        brd[n] = 3;
    else
        brd[n] = 5;
    trn++;
}

void plyr_first()
{
    int ps;

    chk_drw();
    draw_brd();
    gotoxy(30,18);
    printf("Your Trn :> ");
    scanf("%d",&ps);

    if(brd[ps] != 2)
        plyr_first();

    if(ps == psswin(plyr))
    {
        go(ps);
        draw_brd();
        gotoxy(30,20);
        printf("you Won");
        getch();
        exit(0);
    }

    go(ps);
    draw_brd();
    strt_gm();
}

void strt_gm()
{
    if(psswin(comp))
    {
        go(psswin(comp));
        flag = 1;
    }
    else if(psswin(plyr))
        go(psswin(plyr));
    else if(make2())
        go(make2());
    else
        go(make4());
    draw_brd();

    if(flag)
    {
        gotoxy(30,20);
        printf("opponent won");
        getch();
    }
    else
        plyr_first();
}

void chk_drw()
{
    if(trn > 9)
    {
        gotoxy(30,20);
        printf("Draw");
        getch();
        exit(0);
    }
}

void draw_brd()
{
    int j;

    for(j=9; j<17; j++)
    {
        gotoxy(35,j);
        printf("|       |");
    }
    gotoxy(28,11);
    printf("-----------------------");
    gotoxy(28,14);
    printf("-----------------------");

    for(j=1; j<10; j++)
    {
        if(brd[j] == 3)
            put_X_O('X',j);
        else if(brd[j] == 5)
            put_X_O('O',j);
    }
}

void put_X_O(char ch,int ps)
{
    int m;
    int x = 31, y = 10;

    m = ps;

    if(m > 3)
    {
        while(m > 3)
        {
            y += 3;
            m -= 3;
        }
    }
    if(ps % 3 == 0)
        x += 16;
    else
    {
        ps %= 3;
        ps--;
        while(ps)
        {
            x+=8;
            ps--;
        }
    }
    gotoxy(x,y);
    printf("%c",ch);
}

