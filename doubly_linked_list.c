/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */
#include<stdio.h>
#include<stdlib.h>        /* 필요한 헤더파일 추가 if necessary */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
		 singly-linked-list의 initialize와 차이점을 이해 할 것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
		- initialize와 왜 다른지 이해 할 것
		 - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode = NULL;

	printf("---- [ Software department ] [ 2 0 1 9 0 3 8 0 3 2 ] [ Jinseo Lee ] ----\n");

	do {
	printf("----------------------------------------------------------------\n");
	printf("                     Doubly Linked  List                        \n");
	printf("----------------------------------------------------------------\n");
	printf(" Initialize    = z           Print         = p \n");
	printf(" Insert Node   = i           Delete Node   = d \n");
	printf(" Insert Last   = n           Delete Last   = e\n");
	printf(" Insert First  = f           Delete First  = t\n");
	printf(" Invert List   = r           Quit          = q\n");
	printf("----------------------------------------------------------------\n");
		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initialize(&headnode);
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
			scanf("%d", &key);
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

	return 1;
}


int initialize(headNode** h) {
	if (*h != NULL)
		freeList(*h);

	(*h) = (headNode*)malloc(sizeof(listNode));          //헤드노드에 공간 부여
	(*h)->first = NULL; //첫번째 노드는 없음 (공백)

	return 1;
}

int freeList(headNode* h) {
	listNode* p = h->first;  //노드 p가 첫번째 노드를 가리키도록
	if (h->first == NULL) {
		free(h); 
		return 0;
	}

	while (p->rlink != NULL) {    //p가 순회를 끝마칠 때까지
		p = p->rlink;      //p는 다음 노드를 가리키도록 이동
		free(p->llink);    //p의 전 노드를 해제
	}
	free(p);  //p는 마지막 노드가 된다. 해제
	free(h);  //헤드노드도 해제
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* p = h->first; 
	listNode* newnode = (listNode*)malloc(sizeof(listNode));  //새 노드 생성
	newnode->key = key;    //새 노드는 key값을 가짐

	if (h->first == NULL) {  //공백리스트에 삽입
		h->first = newnode;
		newnode->llink = NULL;
		newnode->rlink = NULL;
	}
	while (p->rlink != NULL)
		p = p->rlink;			//연결리스트 순회
	p->rlink = newnode;
	newnode->llink = p;
	newnode->rlink = NULL;    //마지막에 삽입 과정

	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* p = h->first;

	if (h->first == NULL) {
		/* 공백리스트이면 경고문 출력 후 함수 종료 */
		printf(" !!! List is empty !!!\n");
		return 0;
	}

	if (p->rlink==NULL) {   //노드가 한개일 때 삭제
		h->first = NULL;
		free(p); return 0;
	}

	while (p->rlink != NULL)
		p=p->rlink;
	p->llink->rlink = NULL;
	/* 마지막 노드까지 간 후 마지막 이전 노드를 마지막 노드로 함 */
	free(p);  return 0;
}



/**
 * list의 처음에 key에 대한 노드 하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* newnode = (listNode*)malloc(sizeof(listNode));  //새 노드 생성
	newnode->key = key;    //새 노드는 key값을 가짐

	if (h->first == NULL) { //공백리스트이면
		//newnode를 첫번째 노드로 삽입하는 과정
		newnode->llink = NULL;  //newnode는 첫번째이므로 link=NULL
		h->first = newnode;  //newnode는 첫번째 노드가 됨
		newnode->rlink = NULL;
	}
	else {
		newnode->rlink = h->first;
		h->first->llink = newnode;  //원래 첫번째 노드와 newnode를 서로 연결
		h->first = newnode; 
		newnode->llink = NULL;    //newnode를 첫번째 노드로
	}

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* p = h->first;
	if (h->first == NULL) {
		printf(" !!! List is empty !!!\n");
		return 0;
	}

	if (p->rlink == NULL) { //노드가 한개이면
		h->first = NULL;
	}
	else {
		h->first = h->first->rlink;    //첫번째 노드는 2번째 노드를 가리킴
		h->first->llink = NULL; //두번째 노드의 llink는 NULL
	}

	free(p);  return 0;
}



	/**
	 * 리스트의 링크를 역순으로 재배치
	 */
	int invertList(headNode* h) {
		listNode* lead = h->first;     //선두 노드
		listNode* middle = h->first;   //링크 순서를 바꿀 노드
		listNode* prev=NULL;           //링크 순서를 바꿀 때 참고하는 노드

		if (h->first == NULL) {  //공백리스트일 때
			printf(" !!! List is empty !!!\n");
			return 0;
		}
		if (lead->rlink == NULL)       //노드가 한개일 떄
			return 0;

		while (lead != NULL) {
			lead = lead->rlink;    //lead는 2번째 노드
			
			middle->rlink = prev;  
			middle->llink = lead;
			/* lead를 뒤따라가면서 한 노드의 rlink와 llink 순서를 바꿈으로서 리스트를 역순 재배치 */

			prev = middle;
			middle = lead;
			/* prev는 middle을, middle은 lead를 따라감 */
		}
		h->first = prev;  
		/*   결국 middle과 lead는 NULL이 되었으므로 prev가 마지막 노드 지칭
		     prev를 헤드 노드로 하면 역순 재배치 완료           
		 */
		return 0;
	}



	/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
	int insertNode(headNode* h, int key) {
		listNode* p = h->first;  //p는 첫번째 노드를 가리킴
		listNode* newnode = (listNode*)malloc(sizeof(listNode));  //새 노드 생성
		newnode->key = key;  //새 노드에 key값추가

		listNode* lastnode = NULL;

		if (h->first == NULL) { /* 만약 첫번째 노드 삽입 시도라면 */
			h->first = newnode;      //첫번째 노드는 newnode
			newnode->llink = NULL;
			newnode->rlink = NULL;
			/*newnode의 llink와 rlink모두 NULL 처리함으로써 첫 삽입 시도 완료*/
			return 0;
		}
		else {
			while (p != NULL) {
				if (key <= p->key) {   //newnode가 p보다 작다면
					if (p == h->first) {        //그런데 p가 첫번째 노드라면
						/* 첫번째 부분에 newnode삽입하는 과정 */
						newnode->llink = NULL;  //newnode는 첫번째이므로 link=NULL
						newnode->rlink = p;     //newnode의 다음은 p
						h->first = newnode;  //newnode는 첫번째 노드가 됨
						p->llink = newnode;  //p는 밀려서 2번째 노드이므로 link로 newnode연결
					}
					else {
						newnode->rlink = p;
						newnode->llink = p->llink;
						p->llink->rlink = newnode;
						p->llink = newnode;   //newnode를 중간에 삽입하는 과정
					}
					return 0;
				}
				/* key값이 커 노드를 맨 뒤쪽에 삽입하는 과정 */
				if (h->first->rlink != NULL) {  //노드가 여러개일 때
					p = p->rlink; //p는 다음 노드로
					if (p != NULL)
						lastnode = p->llink;  //p가 NULL이 아닐때만 lastnode를 진행 노드의 뒤쪽 노드로 삼음
				}
				else {  //노드가 한개일 때
					h->first->rlink = newnode;  //newnode는 첫번째의 다음 노드
					newnode->llink = h->first;
					newnode->rlink = NULL;  /* 두번째 노드 삽입 과정 */
					return 0;
				}
			}

			lastnode = lastnode->rlink;  //lastnode는 최종적으로 마지막 노드가 됨
				/* while문을 빠져나오면 lastnode는 마지막에서 두번째에 있는 노드이기 때문에 다음으로 이동시켜야 함 */
			lastnode->rlink = newnode;
			newnode->llink = lastnode;
			newnode->rlink = NULL;
			/*newnode를 마지막 노드로 삽입하는 과정*/
		}
		return 0;
	}


	/**
	 * list에서 key에 대한 노드 삭제
	 */
	 //cannot find the node for key = n
	int deleteNode(headNode* h, int key) {
		listNode* p = h->first;  //p는 첫번째 노드를 가리킴
		if (h->first == NULL) {
			//공백리스트이면 경고문 출력 후 종료
			printf(" !!! List is empty !!!\n");
			return 0;
		}
		while (p != NULL) {
			if (key == p->key) {
				if (p == h->first) { //삭제할 노드가 첫번째라면
					if (p->rlink == NULL) { //그런데 노드가 한개이면
						h->first = NULL;
					}
					else {
						h->first = h->first->rlink;    //첫번째 노드는 2번째 노드를 가리킴
						h->first->llink = NULL; //두번째 노드의 llink는 NULL
					}
				}
				else if (p->rlink == NULL) {  //마지막 노드 제거라면
					p->llink->rlink = NULL;
				}
				else {
					p->llink->rlink = p->rlink;  //p 이전노드는 p의 다음노드를 가리킴
					p->rlink->llink = p->llink;  //삭제할 노드를 건너뛰고 연결
				}
				free(p); return 0;
			}
			p = p->rlink;
		}
		printf(" !!! Cannot find the node for key = %d !!!\n", key);
		return 1;
	}

