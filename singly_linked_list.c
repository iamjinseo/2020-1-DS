/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

 /* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;             /* 노드 */

typedef struct Head {
	struct Node* first;
}headNode;              /* 헤더 노드 */


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
  /* 노드 삽입 함수들 */

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
  /* 노드 제거 함수들 */

int invertList(headNode* h);
   /* 노드 뒤집기 */

void printList(headNode* h);  //노드 출력

int main()
{
	printf("----------[ Software department ]  [ 2 0 1 9 0 3 8 0 3 2 ] [ Jinseo Lee ]----------\n\n");
	char command;   //메뉴 입력 변수
	int key;
	headNode* headnode = NULL;


	printf("----------------------------------------------------------------\n");
	printf("                     Singly Linked List                         \n");
	printf("----------------------------------------------------------------\n");
	printf(" Initialize    = z           Print         = p \n");
	printf(" Insert Node   = i           Delete Node   = d \n");
	printf(" Insert Last   = n           Delete Last   = e\n");
	printf(" Insert First  = f           Delete First  = t\n");
	printf(" Invert List   = r           Quit          = q\n");
	printf("----------------------------------------------------------------\n");
    /* 메뉴 출력 */
	do {
		printf("Command = ");
		scanf(" %c", &command);  //메뉴 입력

		switch (command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);  //키 입력
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');
    /* 입력된 문자 메뉴에 맞게 함수 호출 */

	return 1;
}




headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while (p != NULL) {
		prev = p;       //이전 노드 지정
		p = p->link;    //p는 다음 노드를 가리킴
		free(prev);     //이전 노드 없앰
	}
	free(h);            //모든 노드를 없앤 후 헤드노드도 없앰
	return 0;
}



/**
 * list 처음에 key에 대한 노드 하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;  //key값을 가지는 노드 추가

	node->link = h->first; // 첫시도에는 NULL을 가리키게 됨 (h->first는 NULL이었으므로)
	h->first = node;       // 헤드 노드가 node를 가리키게 됨

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
	 * 오름차순 정렬 !!!
*/
int insertNode(headNode* h, int key) {
	listNode* p = h->first; //현재 노드
	listNode *prev = NULL;  //이전 노드
	listNode* newnode = (listNode*)malloc(sizeof(listNode));  //새 노드 생성
	newnode->key = key;      //새 노드에 인자로 받은 key값 넣기
	newnode->link = NULL;

	while (p != NULL) {
		if (key <= p->key) {
			if (prev == NULL) {     //key가 제일 작으면 맨 앞 노드에 삽입하는 조건문
				newnode->link = p;
				h->first = newnode;   
				return 0;
			}
			/* 노드 삽입하기 */
			newnode->link = p;       //새 노드의 다음은 현재 노드의 다음 노드
			prev->link = newnode;        //현재 노드의 다음은 새 노드
			return 0;
		}
		prev = p;            //이전 노드는 현재 노드로 이동
		p = p->link;        //현재 노드는 다음 노드로 이동
	}
	return 0;
}

/**
 * list에 key에 대한 노드 하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* p = h->first; //현재 노드
	listNode* newnode = (listNode*)malloc(sizeof(listNode));  //새 노드 생성
	newnode->key = key;

	while (p->link != NULL)
		p = p->link;        /*연결리스트 순회*/
	p->link = newnode;   //p가 마지막 노드일 때 다음 노드를 newnode로 연결
	newnode->link = NULL; //newnode가 마지막 노드
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* removing_node = h->first;  //첫번째 노드
	h->first = h->first->link; //첫번째 노드를 두번째 노드 위치로 바꾸기
	if (h->first == NULL)
		printf(" !!!!!!!!!! List is empty !!!!!!!!!! \n");  //첫번째 노드가 NULL이면 공백리스트임을 나타냄
	free(removing_node);  //첫번째 노드 삭제
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* prev = NULL;   //이전노드
	listNode* p = h->first;  //현재노드

	while (p != NULL) {
		if (key == p->key) {     //키가 현재 노드 키와 같음
			if (prev == NULL) {  
				printf("  Use deleteFirst function. command is t.\n");
				break; /*첫번째 노드를 삭제하고자 하면 커맨드 t를 제안하며 빠져나감*/
			}
			prev->link = p->link;
			free(p);
			return 0;  /*노드삭제*/
		}
		prev = p;            //이전 노드는 현재 노드로 이동
		p = p->link;        //현재 노드는 다음 노드로 이동
	}
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* p = h->first; //현재 노드
	listNode* prev = NULL;   //이전노드

	while (p->link != NULL) {
		prev = p;
		p = p->link;        
		/*연결리스트 순회*/
	}
	free(p);
	prev->link = NULL; //마지막 노드 삭제
	return 0;
}


/**
 * 리스트의 링크를 역순으로 재배치
 */
int invertList(headNode* h) {
	listNode *lead = h->first; //선두 노드
	listNode* middle = NULL; //중간노드
	listNode* prev;            //이전노드
	while (lead) {       //노드 순회하며 선두 노드가 NULL이 아닐 때까지
		prev = middle;   //이전노드는 middle위치를 가리킴
		middle = lead;   //중간노드는 선두노드 위치를 가리킴
		lead = lead->link;  //선두노드는 다음 노드로 이동
		middle->link = prev;  //중간노드의 다음노드는 prev
	}
	h->first = middle;  
    /* 결국 lead는 NULL이 되고 마지막 노드를 가리키는 것은 middle이다. middle부터 역순으로 노드를 가리키고 있으므로
       middle을 firsthead로 가리키면 리스트를 역순으로 만들 수 있다.
    */
	return 0;
}


void printList(headNode* h) { /*리스트 출력*/
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;  /*공백리스트 출력 안내*/
	}

	p = h->first;  //첫번째 노드

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i); /*노드를 순회하면서 순서값과 key값 출력*/
}
