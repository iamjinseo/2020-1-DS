/*
 * circularQ.c
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;  //ť�� �����ϴ� ����ü

QueueType *createQueue();    //ť �����
int isEmpty(QueueType *cQ); //ť�� �������� �˻��ϴ� �Լ�
int isFull(QueueType *cQ);  //ť�� �������� �˻��ϴ� �Լ�
void enQueue(QueueType *cQ, element item);  //ť�� ������Ʈ�� �����ϴ� �Լ�
void deQueue(QueueType *cQ, element* item); //ť�� �� ���Ҹ� �����ϴ� �Լ�
void printQ(QueueType *cQ);    //ť ���
void debugQ(QueueType *cQ);    //ť ���� �����ֱ�

element getElement();


int main(void)
{
	printf("------[Software department]   [2019038032]   [Jinseo Lee]------\n");
	QueueType *cQ = createQueue();  //ť ����
	element data;

	char command;

	do {
		/*�Է� �ȳ� �޼��� ��� */
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);  //�޴� �Է�

		switch (command) {
		case 'i': case 'I':

			data = getElement();   //ť�� �� �ֱ�
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);   //ť�� �ִ� �� ����
			break;
		case 'p': case 'P':
			printQ(cQ);           //ť�� ����Ʈ ������� ���
			break;
		case 'b': case 'B':
			debugQ(cQ);          //ť ���� �˾ƺ��� *)front, rear �� ���� ���� ��µ�
			break;
		case 'q': case 'Q':
			free(cQ);  //�����Ҵ� ����
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}


QueueType *createQueue()   //ť ����� �Լ�
{
	QueueType *cQ;         //ť ������ ���� ����ü ������
	cQ = (QueueType *)malloc(sizeof(QueueType));  //������ �������� �Ҵ�
	cQ->front = 0;
	cQ->rear = 0;          /*front�� rear�� 0���� ����*/
	return cQ;   //������� ť�� ��ȯ
}

element getElement()      //���� �Է¹ޱ�
{
	element item;         //������ ����
	printf("Input element = ");
	scanf(" %c", &item);
	return item;  /*�Է� �� �Է¹��� �� ����*/
}

int isEmpty(QueueType *cQ)  //ť�� �������� �˻��ϴ� �Լ�
{
	if (cQ->rear == cQ->front) return 1; //rear�� front�� ���ٸ� ����
	/* �ʱ���� : �ڷᰡ �ϳ��� ���Դٸ� rear�� ���� �ϳ� �������� ����
	   * �� �Ŀ� ���Ҹ� �ϳ� �����ϸ� ������ �ǰ�, front�� ������ rear�� ������ */
	else return 0;  //�ƴϸ� 0��ȯ
}

int isFull(QueueType *cQ) //cQ�� full���� �˻��ϰ�, ���� �´ٸ� 1�� �����ϴ� �Լ�
{
	if (((cQ->rear) + 1) % MAX_QUEUE_SIZE == cQ->front) return 1;  //���� ������ �̿�, ť�� ��ȭ���� �˻�
	/* rear�� ���� ��ġ�� front��� ť�� ��ȭ���� */
	else return 0;  //��ȭ���°� �ƴϸ� 0 ��ȯ
}

void enQueue(QueueType *cQ, element item) //������Ʈ ����
{
	if (isFull(cQ)) {
		printf("Queue is full!\n");
		return; //ť�� �����̸� �����޼��� ���
	}
	else {
		cQ->rear = ((cQ->rear) + 1) % MAX_QUEUE_SIZE;  //rear��ġ�� ��ĭ �ڷ�
		cQ->queue[cQ->rear] = item; //ť�� ���� ����
	}
}

void deQueue(QueueType *cQ, element *item)
{
	if (isEmpty(cQ)) {
		printf("Queue is empty!\n");
		return; //ť�� �����̸� �����޼��� ���
	}
	else {
		cQ->front = ((cQ->front) + 1) % MAX_QUEUE_SIZE; //front��ġ�� ��ĭ �ڷ� ��ġ
		*item = cQ->queue[cQ->front]; //ť �տ��ִ� ���� ����
	}
}


void printQ(QueueType *cQ){
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE;  //��� ������ ��
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE;    //��� ����ħ�� ������ +1�ؼ� ����
			/* ������ ����� �ε������� 1 Ŀ���� */
	printf("Circular Queue : [");

	i = first;
	while (i != last) {  //
		printf("%3c", cQ->queue[i]);    //���� ���
		i = (i + 1) % MAX_QUEUE_SIZE;   //���� �ε����� �̵�
	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if (i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue; /* front��ġ�� ������ front��� ����ϱ� */
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);  //ť���� �ش� ��ġ�� �� ���

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);  //front�� rear ��ġ ���
}

