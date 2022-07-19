#include <stdio.h>	//표준입출력헤더
#include <stdlib.h>	//malloc, free 등
#include <Windows.h>//windows console api 헤더
#include <time.h>	//랜덤 시드용 time 함수 헤더
#include <conio.h>	//gotoxy에서 사용할 api 헤더

#define FIELD_WIDTH 50	//필드가로길이
#define FIELD_HEIGHT 25	//필드세로길이
#define LEFT 75			//키보드 좌 화살표의 char값
#define RIGHT 77		//키보드 우
#define UP 72			//키보드 위
#define DOWN 80			//지보드 아래
#define ITEM_MAX 2		//화면에 표시되는 아이템개수
#define ITEM_GOLD 101	//골드 아이템 인디케이터
#define ITEM_EXP 102	//경험치 아이템 인디케이터
#define LEFT_MARGIN 30	//화면왼쪽마진(공백)
#define TOP_MARGIN 3	//화면 상단마진(공백)
#define DELAYTIME 200	//Sleep함수에 들어갈 x/1000 초

//지렁이를 구현할 이중연결리스트 구조체
#pragma pack(push,1)
typedef struct _WORM
{
	int x;	//x좌표
	int y;	//y좌표
	char direction;	//진행방향
	struct _WORM* next;	//다음노드주소
	struct _WORM* before;//이전노드주소
}WORM, * pWORM;

//아이템을 구현할 단일연결리스트 구조체
typedef struct _ITEM
{
	int x;
	int y;
	int itemType;
	int itemNo;
	struct _ITEM* next;
}ITEM, * pITEM;
#pragma pack(pop)

//커서를 일정 좌표로 이동
void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x + LEFT_MARGIN;//가로세로 비율을 맞추기 위해서 가로의 좌표는 2배
	Pos.Y = y + TOP_MARGIN;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//게임영역출력
void PrintField()
{
	for (int i = 1; i < FIELD_WIDTH; i++)
	{
		gotoxy(i, 0);
		printf("─");
		gotoxy(i, FIELD_HEIGHT);
		printf("─");
	}

	for (int i = 1; i < FIELD_HEIGHT; i++)
	{
		gotoxy(0, i);
		printf("│");
		gotoxy(FIELD_WIDTH, i);
		printf("│");
	}
	gotoxy(0, 0);
	printf("┌");
	gotoxy(0, FIELD_HEIGHT);
	printf("└");
	gotoxy(FIELD_WIDTH, 0);
	printf("┐");
	gotoxy(FIELD_WIDTH, FIELD_HEIGHT);
	printf("┘");
}

//지렁이를 늘리는 함수(이중연결리스트의 테일쪽에 노드 추가)
void AddWorm(pWORM wormTailNode)
{
	pWORM newNode = malloc(sizeof(WORM));
	pWORM temp = wormTailNode->next;

	//새 노드의 주솟값 이어주기;
	newNode->before = wormTailNode;
	newNode->next = wormTailNode->next;
	wormTailNode->next = newNode;
	newNode->next->before = newNode;
	newNode->direction = temp->direction;
	newNode->x = temp->x;
	newNode->y = temp->y;
	switch (temp->direction)
	{
	case LEFT:
		newNode->x = newNode->x + 1;
		break;
	case RIGHT:
		newNode->x = newNode->x - 1;
		break;
	case UP:
		newNode->y = newNode->y + 1;
		break;
	case DOWN:
		newNode->y = newNode->y - 1;
		break;
	default:
		break;
	}


}

//연결리스트를 받아서 지렁이 출력
void PrintWorm(pWORM wormTailNode, pWORM wormHeadNode)
{
	pWORM curr = wormTailNode->next;
	while (curr != wormHeadNode)
	{
		gotoxy(curr->x, curr->y);
		printf("O");
		curr = curr->next;
	}
}

//게임점수 출력
void PrintScore(int score)
{
	gotoxy(FIELD_WIDTH + 3, 3);
	printf("점수 : %d점", score);
	gotoxy(FIELD_WIDTH + 3, 5);
	printf("종료하려면 Q를 누르세요");
	gotoxy(FIELD_WIDTH + 3, 7);
	printf("조작은 화살표키로");
}

//웜이 지나간 자리 지우기
void ClearWorm(int x, int y)
{
	gotoxy(x, y);
	printf(" ");
}

//웜 움직이기 
void MoveWorm(pWORM wormTailNode, pWORM wormHeadNode)
{
	pWORM curr;

	curr = wormTailNode->next;
	while (curr != NULL && curr != wormHeadNode->before)
	{
		curr->x = curr->next->x;
		curr->y = curr->next->y;
		curr = curr->next;
	}
	curr = wormHeadNode->before;
	if (curr->direction == LEFT)
	{
		curr->x--;
	}
	else if (curr->direction == RIGHT)
	{
		curr->x++;
	}
	else if (curr->direction == UP)
	{
		curr->y--;
	}
	else if (curr->direction == DOWN)
	{
		curr->y++;
	}
}


//웜 리스트에 할당된 메모리를 순차로 해제
void FreeWormList(pWORM wormTailNode)
{
	pWORM curr;
	pWORM temp;
	curr = wormTailNode;
	while (curr != NULL)
	{
		temp = curr->next;
		free(curr);
		curr = temp;
	}
}

//item 발생시키기
void CreateItem(pITEM itemNode, int* itemNo) {

	pITEM newItem = malloc(sizeof(ITEM));

	newItem->next = itemNode->next;
	newItem->itemNo = (*itemNo)++;
	itemNod