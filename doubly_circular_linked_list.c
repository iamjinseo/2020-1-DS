/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */


#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode = NULL;

	do {
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h) {
	listNode* p = h->rlink;  //p는 첫번째 노드
	listNode* prev = NULL;   //리스트를 순회하면서 p를 뒤쫒아올 노드

	if (h->rlink == h) {
		/* 리스트에 헤드노드만 남았으면 */
		free(h);
		return 1;  //헤드노드를 동적할당 해제하고 함수 종료
	}

	while (p != NULL && p != h) { //리스트 순회
		prev = p;       //prev는 현재 노드
		p = p->rlink;   //p는 다음 노드로
		free(prev);     //p의 이전 노드 해제
	}
	free(h);   //남아있던 헤드노드 해제
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}
}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	listNode* newnode = (listNode*)malloc(sizeof(listNode));  //새 노드 생성
	newnode->llink = NULL;
	newnode->rlink = NULL;   //아무것도 연결하지 않았으므로 두쪽 링크 NULL
	newnode->key = key;   //새 노드는 key값을 가진다

	if (h == NULL) {
		printf(" !!! List is not initialized !!!\n");
		return 0;  /* 초기화안된 리스트이면 경고문 출력 후 함수종료 */
	}

	if (h->rlink == h) {        //공백리스트에 노드 삽입하는 과정
		h->llink = newnode;
		h->rlink = newnode;
		newnode->llink = h;
		newnode->rlink = h;
		/* 이중 원형 연결리스트의 공백리스트에 노드를 하나 넣는것이므로
		   각 노드가 상대 노드를 가리키도록 함 */
		return 0;
	}
	else {   //공백리스트가 아닌 리스트에 노드 삽입
		h->llink->rlink = newnode;  //h->llink는 가장 끝번노드, 끝번노드의 rlink에 삽입
		newnode->llink = h->llink;  //newnode의 llink는 끝번노드였던 것 (뒤에서 두번째)
		h->llink = newnode;   //newnode가 가장 끝번 노드가 됨
		newnode->rlink = h;   //newnode의 다음(rlink)은 h( *원형연결리스트)
	}
	return 0;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	if (h == NULL) {
		printf(" !!! List is not initialized !!!\n");
		return 0;  /* 초기화안된 리스트이면 경고문 출력 후 함수종료 */
	}

	listNode* lastnode = h->llink;  //h의 llink는 끝번노드

	if (h->rlink == h) {   // 공백 이중 연결 원형리스트이면
		printf(" !!! List is empty !!!\n");
		return 0;  //경고문 출력 후 함수 종료
	}

    lastnode->llink->rlink = h;  //끝번노드의 이전노드의 다음은 h
	h->llink = lastnode->llink;  //끝번노드를 lastnode의 llink로 재지정
	free(lastnode);  //남겨진 lastnode해제
	/* 리스트에 노드가 하나일 때도(h 제외)가능 */
	return 0;
}

/**
 * list의 처음에 key에 대한 노드 하나를 추가
 */
int insertFirst(listNode* h, int key) {
	listNode* newnode = (listNode*)malloc(sizeof(listNode));  //새 노드 생성
	newnode->rlink = NULL;
	newnode->llink = NULL;  //새 노드는 아무것도 가리키고있지 않음
	newnode->key = key;     //새 노드는 key값을 가짐

	if (h == NULL) {   /* 초기화안된 리스트이면 경고문 출력 후 함수종료 */
		printf(" !!! List is not initialized !!!\n");
		return 0;
	}
	else if (h->rlink == h) {  //공백리스트이면
		h->rlink = newnode;
		h->llink = newnode;  /* newnode가 리스트의 새로운 노드가 되는 과정 */
		newnode->llink = h;
		newnode->rlink = h;
		return 0;
	}

	newnode->rlink = h->rlink;  //newnode의 다음 노드는 현재 첫번째 노드
	h->rlink->llink = newnode;  //현재 첫번째 노드의 앞(llink)노드를 newnode로 함
	newnode->llink = h;         //newnode가 맨 앞 노드가 됨. llink는 h
	h->rlink = newnode;     //맨 앞 노드로써 h의 다음(rlink)는 newnode

	return 0;
}


int deleteFirst(listNode* h) {
	if (h == NULL) {   /* 초기화안된 리스트이면 경고문 출력 후 함수종료 */
		printf(" !!! List is not initialized !!!\n");
		return 0;
	}

	listNode* firstnode = h->rlink;  //firstnode는 첫번째 노드

	if (h->rlink == h) {
		printf(" !!! List is empty !!!\n");
		return 0;
	}  //공백리스트이면 경고문 출력 후 함수종료

	firstnode->rlink->llink = h;   //첫 노드의 다음 노드(2번노드)의 llink로 h를 지칭
		/* 첫 번째 노드 배제 과정 */
	h->rlink = firstnode->rlink;   //첫 노드로써 2번노드 지칭
	free(firstnode);  //배제됐던 첫 노드 해제

	return 0;

}


int invertList(listNode* h) {
	if (h == NULL) {   /* 초기화안된 리스트이면 경고문 출력 후 함수종료 */
		printf(" !!! List is not initialized !!!\n");
		return 0;
	}
	listNode *lead = h->rlink;    //선두노드
	listNode *middle = h;  //중간노드(현재노드, 링크 순서를 바꿀 노드)
	listNode *prev = h;    //링크 순서를 바꿀 때 참고하는 노드

	if (h->rlink == h) {
		printf(" !!! List is empty !!!\n");
		return 0;
	}  //공백리스트이면 경고문 출력 후 함수종료
	else if (h->rlink->rlink == h)   //노드가 한개일 때
		return 0;

	h->llink = h->rlink;  //h의 llink는 rlink (뒤집기)
		/* h의 링크 바꾸기 */
	while (lead != NULL && lead != h) {  //리스트 순회
		/* h를 제외한 다른 노드들 순서 바꾸는 과정 */
		prev = middle;           //prev는 middle을 따라감
        middle = lead;           //middle은 lead를 따라감
        lead = lead->rlink;      //lead는 다음 노드로 이동
        middle->rlink = prev;    
        middle->llink = lead;
		/* middle(현재노드의) 링크 순서를 바꿈 */
	}
     h->rlink = middle;  //최종적으로 middle은 끝번 노드에 있고 h의 rlink는 middle이 됨 
	 	/* h의 링크 바꾸기 */

	return 0;
}



int insertNode(listNode* h, int key) {
	if (h == NULL) {   /* 초기화안된 리스트이면 경고문 출력 후 함수종료 */
		printf(" !!! List is not initialized !!!\n");
		return 0;
	}

    listNode* p = h->rlink;  //현재 노드
	listNode* newnode = (listNode*)malloc(sizeof(listNode));  //새 노드 생성
	newnode->llink = NULL;
	newnode->rlink = NULL;  //새 노드는 아무것도 가리키지 않는다
	newnode->key = key;     //새 노드는 key값을 가진다

	if (h->rlink == h){ //공백리스트이면
		h->rlink = newnode;
		h->llink = newnode;  /* newnode가 리스트의 새로운 노드가 되는 과정 */
		newnode->llink = h;
		newnode->rlink = h;
		return 0;
	}

	while (p != NULL && p != h) {   //리스트 순회
		if (key <= p->key) {   //newnode의 key값이 현재 노드 키값보다 작으면
			if (p == h->rlink) {  //현재 노드가 첫번째 노드라면
				newnode->rlink = h->rlink;  
	            h->rlink->llink = newnode; 
	            newnode->llink = h;       
	            h->rlink = newnode;     
                    /* newnode를 첫번째에 삽입하는 과정 */
			}
			else {
				newnode->rlink = p;
				newnode->llink = p->llink;
				p->llink->rlink = newnode;
                p->llink=newnode; 
                /* 새 노드를 중간에 삽입하는 과정 */
			}
			return 0;
		}
		p = p->rlink;  //p는 다음 노드로
	}
    /* newnode의 키값이 리스트에서 가장 큰 상황 */
	h->llink->rlink = newnode;  
	newnode->llink = h->llink; 
	h->llink = newnode;  
	newnode->rlink = h;   
    /* newnode를 리스트의 맨 끝번 노드가 되도록 함 */

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	if (h == NULL) {   /* 초기화안된 리스트이면 경고문 출력 후 함수종료 */
		printf(" !!! List is not initialized !!!\n");
		return 0;
	}

    listNode* p = h->rlink;  //현재노드

    if (h->rlink == h) {
		printf(" !!! List is empty !!!\n");
		return 0;
	}  //공백리스트이면 경고문 출력 후 함수종료


	while (p != NULL && p != h) {  //리스트 순회
		if (p->key == key) {       //현재노드의 key값이 인자로 전달받은 key값과 같다면
			if (p == h->rlink) {   //p가 첫번째 노드라면
	            deleteFirst(h); //첫번째 노드 삭제 함수 호출
			}
			else if (p->rlink == h) {   //p가 끝번노드이면
				deleteLast(h);          //마지막 노드 삭제 함수 호출
			}
			else {  //현재노드가 중간에 있는 노드라면
                /* 현재노드 동적할당 해제 과정 */
				p->llink->rlink = p->rlink; 
				p->rlink->llink = p->llink;
				free(p);
			}
			return 0;
		}
		p = p->rlink;  //현재 노드는 다음 노드
	}

	printf("cannot find the node for key = %d\n", key); //순회가 끝나고도 리턴되지 않으면 키값이 없다는 오류 메세지
	return 0;
}

