#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

#define FIELD_HEIGHT 9
#define FIELD_WIDTH 16
#define PLAYER1_X 2
#define PLAYER2_X 13

typedef struct 
{
	int position_x;
	int position_y;
	int type;
}shot;

shot shots[30] = {{}};
char field[FIELD_HEIGHT][FIELD_WIDTH];
char displayBuffer[FIELD_HEIGHT][FIELD_WIDTH];
 
int i, j;
int player1_y = 3;
int player2_y = 3;
int life_1 = 10;
int life_2 = 10;
int checkFlag = 0;

void end(int winner) 
{
	printf("GAME is OVER!!\n");
	printf("player %d WIN!!\n", winner);
	printf("press 'O' KEY!!");
	while (_getch()!='o') 
	{
		
	};
	for (i = 0; i < 30; i++)
	{
		shots[i].position_x = 0;
		shots[i].position_y = 0;
		shots[i].type = 0;
	}
	life_1 = 10;
	life_2 = 10;
}

void moveShot() 
{
	for (i = 0; i < 30; i++) 
	{
		if (shots[i].type == 1)
		{
			if (shots[i].position_x+2 >= FIELD_WIDTH)
				shots[i].type = 0;
			else shots[i].position_x += 2;
		}
		if (shots[i].type == 2)
		{
			if (shots[i].position_x <= 1)
				shots[i].type = 0;
			else shots[i].position_x -= 2;
		}
	}
}

void checkHit() 
{
	if (!checkFlag)
	{
		for (i = 0; i < 30; i++)
		{
			if ((shots[i].position_x == PLAYER1_X) && (shots[i].position_y == player1_y))
			{
				displayBuffer[player1_y][PLAYER1_X] = 5;
				life_1--;
				checkFlag = 1;
				if (life_1 < 0)
					end(2);
			}
			if ((shots[i].position_x == PLAYER2_X) && (shots[i].position_y == player2_y))
			{
				displayBuffer[player2_y][PLAYER2_X] = 5;
				life_2--;
				checkFlag = 1;
				if (life_2 < 0)
					end(1);
			}
		}
	}
}	

void display()
{
	memcpy(displayBuffer, field, sizeof(field));
	displayBuffer[player1_y][PLAYER1_X] = 2;
	displayBuffer[player2_y][PLAYER2_X] = 2;
	for (i = 0; i < 30; i++)
	{	
		if (shots[i].type == 1)
			displayBuffer[shots[i].position_y][shots[i].position_x] = 3;
		if (shots[i].type == 2)
			displayBuffer[shots[i].position_y][shots[i].position_x] = 4;
	}
	checkHit();

	system("cls");
	printf("player1 Life:%d  player2 Life:%d\n",life_1,life_2);
	for (i = 0; i < FIELD_HEIGHT; i++) 
	{
		for (j = 0; j < FIELD_WIDTH; j++) 
		{
			switch (displayBuffer[i][j])
			{
			case 0:
				printf("@");
				break;
			case 1:
				printf("¡");
				break;
			case 2:
				printf("›");
				break;
			case 3:
				printf("¨");
				break;
			case 4:
				printf("©");
				break;
			case 5:
				printf("~");
				break;
			}

		}
		printf("\n");

	}
}

int main() 
{
	int shotCount= 0;
	memset(field, 0, sizeof(field));
	for (i = 0; i < FIELD_HEIGHT; i++) 
	{
		field[i][0] = 1;
		field[i][FIELD_WIDTH - 1] = 1;
	}
	for (i = 0; i < FIELD_WIDTH; i++)
	{
		field[0][i] = 1;
		field[FIELD_HEIGHT - 1][i] = 1;
	}

	time_t t = time(NULL);
	display();
	while (1) 
	{
		if (_kbhit()) 
		{
			switch (_getch()) 
			{
				case 'w':
					if(player1_y > 1)
					player1_y -= 1;
					break;
				case 's':
					if(player1_y < FIELD_HEIGHT-2)
					player1_y += 1;
					break;
				case 0x20:
					shots[shotCount].position_x = PLAYER1_X+1;
					shots[shotCount].position_y = player1_y;
					shots[shotCount].type = 1;
					shotCount++;
					break;

				case '8':
					if (player2_y > 1)
					player2_y -= 1;
					break;
				case '5':
					if (player2_y < FIELD_HEIGHT - 2)
					player2_y += 1;
					break;
				case '4':
					shots[shotCount].position_x = PLAYER2_X - 1;
					shots[shotCount].position_y = player2_y;
					shots[shotCount].type = 2;
					shotCount++;
					break;
			}
			display();
		}
		if (shotCount >= 30)shotCount = 0;
		if (t != time(NULL)) 
		{
			t = time(NULL);
			moveShot();
			display();
			checkFlag = 0;
		}
	}

	_getch();
	return 0;
}