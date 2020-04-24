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
}QueueType;  //큐를 구현하는 구조체

QueueType *createQueue();    //큐 만들기
int isEmpty(QueueType *cQ); //큐가 공백인지 검사하는 함수
int isFull(QueueType *cQ);  //큐가 만원인지 검사하는 함수
void enQueue(QueueType *cQ, element item);  //큐에 엘리멘트를 삽입하는 함수
void deQueue(QueueType *cQ, element* item); //큐의 앞 원소를 삭제하는 함수
void printQ(QueueType *cQ);    //큐 출력
void debugQ(QueueType *cQ);    //큐 상태 보여주기

element getElement();


int main(void)
{
	printf("------[Software department]   [2019038032]   [Jinseo Lee]------\n");
	QueueType *cQ = createQueue();  //큐 생성
	element data;

	char command;

	do {
		/*입력 안내 메세지 출력 */
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);  //메뉴 입력

		switch (command) {
		case 'i': case 'I':

			data = getElement();   //큐에 값 넣기
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);   //큐에 있는 값 빼기
			break;
		case 'p': case 'P':
			printQ(cQ);           //큐를 리스트 모양으로 출력
			break;
		case 'b': case 'B':
			debugQ(cQ);          //큐 상태 알아보기 *)front, rear 및 원소 정보 출력됨
			break;
		case 'q': case 'Q':
			free(cQ);  //동적할당 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}


QueueType *createQueue()   //큐 만들기 함수
{
	QueueType *cQ;         //큐 정보를 담을 구조체 포인터
	cQ = (QueueType *)malloc(sizeof(QueueType));  //공간을 동적으로 할당
	cQ->front = 0;
	cQ->rear = 0;          /*front와 rear를 0으로 설정*/
	return cQ;   //만들어진 큐를 반환
}

element getElement()      //원소 입력받기
{
	element item;         //문자형 원소
	printf("Input element = ");
	scanf(" %c", &item);
	return item;  /*입력 후 입력받은 값 리턴*/
}

int isEmpty(QueueType *cQ)  //큐가 공백인지 검사하는 함수
{
	if (cQ->rear == cQ->front) return 1; //rear와 front가 같다면 공백
	/* 초기상태 : 자료가 하나라도 들어왔다면 rear의 값은 하나 더해지기 때문
	   * 그 후에 원소를 하나 삭제하면 공백이 되고, front가 증가해 rear와 같아짐 */
	else return 0;  //아니면 0반환
}

int isFull(QueueType *cQ) //cQ가 full인지 검사하고, 만약 맞다면 1을 리턴하는 함수
{
	if (((cQ->rear) + 1) % MAX_QUEUE_SIZE == cQ->front) return 1;  //모듈로 연산자 이용, 큐가 포화인지 검사
	/* rear의 다음 위치가 front라면 큐는 포화상태 */
	else return 0;  //포화상태가 아니면 0 반환
}

void enQueue(QueueType *cQ, element item) //엘리멘트 삽입
{
	if (isFull(cQ)) {
		printf("Queue is full!\n");
		return; //큐가 만원이면 오류메세지 출력
	}
	else {
		cQ->rear = ((cQ->rear) + 1) % MAX_QUEUE_SIZE;  //rear위치를 한칸 뒤로
		cQ->queue[cQ->rear] = item; //큐에 원소 삽입
	}
}

void deQueue(QueueType *cQ, element *item)
{
	if (isEmpty(cQ)) {
		printf("Queue is empty!\n");
		return; //큐가 공백이면 오류메세지 출력
	}
	else {
		cQ->front = ((cQ->front) + 1) % MAX_QUEUE_SIZE; //front위치를 한칸 뒤로 배치
		*item = cQ->queue[cQ->front]; //큐 앞에있는 원소 삭제
	}
}


void printQ(QueueType *cQ){
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE;  //출력 시작할 곳
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE;    //출력 끝마침할 곳보다 +1해서 지정
			/* 끝까지 출력할 인덱스보다 1 커야함 */
	printf("Circular Queue : [");

	i = first;
	while (i != last) {  //
		printf("%3c", cQ->queue[i]);    //원소 출력
		i = (i + 1) % MAX_QUEUE_SIZE;   //다음 인덱스로 이동
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
			continue; /* front위치인 곳에는 front라고 출력하기 */
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);  //큐에서 해당 위치의 값 출력

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);  //front와 rear 위치 출력
}

