#include <stdio.h>	//ǥ����������
#include <stdlib.h>	//malloc, free ��
#include <Windows.h>//windows console api ���
#include <time.h>	//���� �õ�� time �Լ� ���
#include <conio.h>	//gotoxy���� ����� api ���

#define FIELD_WIDTH 50	//�ʵ尡�α���
#define FIELD_HEIGHT 25	//�ʵ弼�α���
#define LEFT 75			//Ű���� �� ȭ��ǥ�� char��
#define RIGHT 77		//Ű���� ��
#define UP 72			//Ű���� ��
#define DOWN 80			//������ �Ʒ�
#define ITEM_MAX 2		//ȭ�鿡 ǥ�õǴ� �����۰���
#define ITEM_GOLD 101	//��� ������ �ε�������
#define ITEM_EXP 102	//����ġ ������ �ε�������
#define LEFT_MARGIN 30	//ȭ����ʸ���(����)
#define TOP_MARGIN 3	//ȭ�� ��ܸ���(����)
#define DELAYTIME 200	//Sleep�Լ��� �� x/1000 ��

//�����̸� ������ ���߿��Ḯ��Ʈ ����ü
#pragma pack(push,1)
typedef struct _WORM
{
	int x;	//x��ǥ
	int y;	//y��ǥ
	char direction;	//�������
	struct _WORM* next;	//��������ּ�
	struct _WORM* before;//��������ּ�
}WORM, * pWORM;

//�������� ������ ���Ͽ��Ḯ��Ʈ ����ü
typedef struct _ITEM
{
	int x;
	int y;
	int itemType;
	int itemNo;
	struct _ITEM* next;
}ITEM, * pITEM;
#pragma pack(pop)

//Ŀ���� ���� ��ǥ�� �̵�
void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x + LEFT_MARGIN;//���μ��� ������ ���߱� ���ؼ� ������ ��ǥ�� 2��
	Pos.Y = y + TOP_MARGIN;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//���ӿ������
void PrintField()
{
	for (int i = 1; i < FIELD_WIDTH; i++)
	{
		gotoxy(i, 0);
		printf("��");
		gotoxy(i, FIELD_HEIGHT);
		printf("��");
	}

	for (int i = 1; i < FIELD_HEIGHT; i++)
	{
		gotoxy(0, i);
		printf("��");
		gotoxy(FIELD_WIDTH, i);
		printf("��");
	}
	gotoxy(0, 0);
	printf("��");
	gotoxy(0, FIELD_HEIGHT);
	printf("��");
	gotoxy(FIELD_WIDTH, 0);
	printf("��");
	gotoxy(FIELD_WIDTH, FIELD_HEIGHT);
	printf("��");
}

//�����̸� �ø��� �Լ�(���߿��Ḯ��Ʈ�� �����ʿ� ��� �߰�)
void AddWorm(pWORM wormTailNode)
{
	pWORM newNode = malloc(sizeof(WORM));
	pWORM temp = wormTailNode->next;

	//�� ����� �ּڰ� �̾��ֱ�;
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

//���Ḯ��Ʈ�� �޾Ƽ� ������ ���
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

//�������� ���
void PrintScore(int score)
{
	gotoxy(FIELD_WIDTH + 3, 3);
	printf("���� : %d��", score);
	gotoxy(FIELD_WIDTH + 3, 5);
	printf("�����Ϸ��� Q�� ��������");
	gotoxy(FIELD_WIDTH + 3, 7);
	printf("������ ȭ��ǥŰ��");
}

//���� ������ �ڸ� �����
void ClearWorm(int x, int y)
{
	gotoxy(x, y);
	printf(" ");
}

//�� �����̱� 
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


//�� ����Ʈ�� �Ҵ�� �޸𸮸� ������ ����
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

//item �߻���Ű��
void CreateItem(pITEM itemNode, int* itemNo) {

	pITEM newItem = malloc(sizeof(ITEM));

	newItem->next = itemNode->next;
	newItem->itemNo = (*itemNo)++;
	itemNod