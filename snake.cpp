#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#define up VK_UP
#define left VK_LEFT
#define right VK_RIGHT
#define down VK_DOWN


/*51x51*/
//GetAsyncKeyState(down)
void gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	_COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hConsole, pos);
}

void dell(int x, int y)
{
	gotoxy(x, y);
	printf(" ");
}

struct snake
{
	int x;
	int y;
	int dir;
	snake *sig;
	snake *prev;
};
snake * nueva(int x, int y, int dir)
{
	snake *p = new snake;
	p->x = x;
	p->y = y;
	p->dir = dir;
	p->sig = NULL;
	p->prev = NULL;
	return p;
}
void insertar(snake **p)
{
	snake *a = *p;
	if (*p)
	{
		while (a->sig)
			a = a->sig;
		int x=a->x, y=a->y;
		switch (a->dir)
		{
			case 1:x = a->x-1; break;
			case 2:y = a->y - 1; break;
			case 3:x = a->x + 1; break;
			case 4:y = a->y + 1; break;
		}
		a->sig = nueva(x, y, a->dir);
		a->sig->prev = a;
	}
}
void cambia(snake *p)
{
	switch (p->dir)
	{
		case 1:	p->x+=1; break;
		case 2:	p->y+=1; break;
		case 3:	p->x-=1; break;
		case 4:	p->y-=1; break;
	}

}
void mostrar(snake *p)
{
	while (p->sig)
		p = p->sig;
	dell(p->x, p->y);	
	while (p)
	{
			
		cambia(p);
		if(p->prev)p->dir = p->prev->dir;
		gotoxy(p->x, p->y);
		printf("*");
		p = p->prev;
	}
}
void comida(int *x, int *y)
{
	*x = rand() % 50 +1;
	*y= rand() % 50 +1;
	gotoxy(*x, *y);
	printf("*");
}

int busca(snake *p,int x,int y)
{
	if (p)
		return p->x == x&&p->y == y ? 1 : busca(p->sig, x, y);
	return 0;
}
int muerte(snake *p)
{
	if(p->x>50||p->x<1||p->y<1||p->y>50||busca(p->sig,p->x,p->y))
		return 1;
	return 0;
}
void main()
{
	srand(time(NULL));
	snake * j = nueva(10,5,1);
	for (int i = 0; i < 4; i++)
		insertar(&j);
	int x, y;
	comida(&x, &y);
	while (!muerte(j))
	{		
		Sleep(100);
		mostrar(j);		
		if (GetAsyncKeyState(right)&&j->dir!=3)
			j->dir = 1;
		if (GetAsyncKeyState(down)&&j->dir != 4)
			j->dir = 2;
		if (GetAsyncKeyState(left) && j->dir != 1)
			j->dir = 3;
		if (GetAsyncKeyState(up) && j->dir != 2)
			j->dir = 4;
		if (j->x == x&&j->y == y)
		{
			comida(&x, &y);
			insertar(&j);
		}
	}
	system("cls");
	printf("\n\n\t\tGAME OVER");
	getchar();
}