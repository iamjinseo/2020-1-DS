/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */
 // 30, 20,  (i -> 20,30) , 40, 10 , i ->10,20,30,40
 // p->30,20,10,40  
 // t->20,10,40,30

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

void printmenu() {
	printf("\n\n");
	printf("----------------------------------------------------------------\n");
	printf("                   Binary Search Tree #1                        \n");
	printf("----------------------------------------------------------------\n");
	printf(" Initialize BST       = z                                       \n");
	printf(" Insert Node          = n      Delete Node                  = d \n");
	printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
	printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
	printf(" Postorder Traversal  = t      Quit                         = q\n");
	printf("----------------------------------------------------------------\n");
}

/* you may add your own defined functions if necessary */

int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do {
		printmenu();
		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {  //트리 초기화 과정

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

void inorderTraversal(Node* ptr) {
	/* 중위 트리 순회 */

	if (ptr == NULL)
		return;   //없는 트리일 때 함수 빠져나감
	else { //중위 순회
		inorderTraversal(ptr->left); //재귀적으로 왼쪽 노드 탐색
		printf("[%d]", ptr->key);    //현재 노드 출력
		inorderTraversal(ptr->right);  //오른쪽 노드쪽으로 탐색
		/* 재귀적 탐색 */
	}
}
void preorderTraversal(Node* ptr) {
	/* 전위 트리 순회 */

	if (ptr == NULL)
		return;  //없는 트리일 때 함수 빠져나감
	else {  //ptr이 NULL이 아니면 
		printf("[%d]", ptr->key);        //먼저 현재 노드 값 출력
		preorderTraversal(ptr->left);    //왼쪽 노드쪽 탐색
		preorderTraversal(ptr->right);   //오른쪽 노드 탐색
		/* 재귀적 탐색 */
	}
}

void postorderTraversal(Node* ptr) {
	/* 후위 트리 순회 */
	if (ptr == NULL)
		return;  //없는 트리일 때 함수 빠져나감
	else {
		postorderTraversal(ptr->left);   //계속해서 왼쪽으로 노드 이동
		postorderTraversal(ptr->right);  //오른쪽 노드 탐색
		printf("[%d]", ptr->key);        //노드 값 출력
		/* 재귀적 탐색 */
	}
}

int insert(Node* head, int key) {
	/* 노드 삽입 함수 */
	if (head == NULL)	return 0;   //초기화안된 트리 배제

	Node *prevNode = NULL, *curNode = head->left;  //이전노드(부모노드)와 현재노드
		/* 이전노드는 NULL, 현재노드는 루트 */

	Node* newnode = (Node*)malloc(sizeof(Node));     //새 노드 생성
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->key = key;

	if (head->left == NULL) {     //트리가 초기상태일 때 (초기화만 됐을 때)
		head->left = newnode;
		return 0;
	}

	/* 노드 삽입 위치를 결정하는 과정 */
	while (curNode != NULL) {  //현재노드가 NULL이 될 때까지

		prevNode = curNode;  //부모노드는 현재노드의 위치로

		if (key == curNode->key)  //똑같은 키값을 가진 노드를 삽입하려할 때 함수 종료
			return 0;

		if (key < prevNode->key) //키 값이 현재 지금 prevNode위치 노드의 키값보다 작을 때
			curNode = prevNode->left; //현재 노드는 부모노드의 왼쪽
		else
			curNode = prevNode->right; //현재 노드는 부모노드의 오른쪽
	}

	/* prevNode는 삽입을 결정하고자 할 노드 위치에 있음 */
	if (prevNode) {  // NULL이 아니라면
		if (key < prevNode->key)
			prevNode->left = newnode;
		/* 키값이 prevNode의 키값보다 작으면 그 노드의 왼쪽에 삽입 */
		else
			prevNode->right = newnode; /* 아니라면 오른쪽에 삽입 */
	}
	return 0;  //함수 종료
}

int deleteLeafNode(Node* head, int key) { //리프노드 제거함수

	if (head->left == NULL || head == NULL) {   //초기화되지 않거나 루트노드가 없는 상태의 트리 처리
		printf(" !!! tree is empty !!!\n");
		return 0;
	}

	Node *p = head->left, *prevNode = NULL; //탐색용 변수

	while (p != NULL && p->key != key) {
		/* 키값 가지는 노드 탐색 */
		prevNode = p; //prevNode는 head(초기에)

		if (key < prevNode->key)
			p = p->left;
		else if (key > prevNode->key)
			p = p->right;
		//key가 부모 노드보다 작으면 왼쪽 노드로, 크면 오른쪽 노드로 이동
	}

	if (p == NULL) {
		printf("cannot find the key\n");
		return 0;
	}

	/* 리프 원소 삭제 */
	if (p->left == NULL && p->right == NULL) {  //p가 리프노드라면
		if (prevNode != NULL) {
			if (prevNode->left == p) {
				free(prevNode->left);
				prevNode->left = NULL;
				/* 부모노드의 왼쪽노드가 p이고 그걸 삭제함 */
			}
			else {
				free(prevNode->right);
				prevNode->right = NULL;
				/*부모노드의 오른쪽노드가 p이고 그걸 삭제*/
			}
		}
		else { //루트노드 삭제 과정
			head->left = NULL;
			p->left = NULL;
			p->right = NULL;
			free(p);
		}
	}
	else 
		printf("the node [%d] is not a leaf\n", key);

	return 0;

}

/* 재귀적으로 트리를 탐색하는 함수 */
Node* searchRecursive(Node* ptr, int key) {
	if (ptr == NULL)
		return NULL;  //없는 트리일 때 함수 빠져나감

	if (ptr->key == key) return ptr;  //key값과 현재 노드 ptr의 키값과 같으면 ptr(주소) 리턴
	if (key < ptr->key)  //키값이 현재노드 키값보다 작으면
		return searchRecursive(ptr->left, key);  //현재노드의 왼쪽노드를 인자로 해 탐색함수 재호출(재귀)
	else
		return searchRecursive(ptr->right, key); //크다면 오른쪽노드로 재호출
}

/* (재귀적이지 않은)반복적으로 노드를 탐색하는 함수 */
Node* searchIterative(Node* head, int key) {
	if (head->left == NULL || head == NULL) {   //초기화되지 않거나 루트노드가 없는 상태의 트리 처리
		printf(" !!! tree is empty !!!\n");
		return 0;
	}

	Node* ptr = head->left;  //ptr은 루트노드

	while (ptr != NULL) {	   	//현재노드가 NULL이 될 때까지
		if (ptr->key == key)
			return ptr;
		/* ptr의 key값과 입력받은 키값이 같으면 ptr(주소)반환 */
		else if (key < ptr->key)
			ptr = ptr->left;
		/* 입력받은 키값이 ptr키값보다 작으면 ptr왼쪽노드 탐색 */
		else
			ptr = ptr->right;
		/* 입력받은 키값이 ptr키값보다 크다면 ptr오른쪽노드 탐색 */
	}
	return 0; //함수 종료
}

/* 트리 공간 해제 함수 */
int freeBST(Node* head) {
	if (head == NULL)
		return 0;  //초기화 되지않은 트리는 공간이 없으므로 배제
	else if (head->right == head) {   //초기화만 된 트리일 때
		free(head);
		head = NULL;
		return 0;      //head 동적할당 해제하고 함수 종료
	}

	if (head != NULL) {  //head가 NULL이 될 때까지 탐색
	 /* 재귀적으로 탐색 및 동적할당 해제 */
		freeBST(head->left);    //왼쪽 아래 노드로 계속 이동
		/* return 0으로 빠져나오면 */
		freeBST(head->right);   //오른쪽 아래 노드로 이동
		/* return 0으로 빠져나오면 */
		head->left = NULL;
		head->right = NULL;
		free(head);
		head = NULL;
		/* 현재 있는 노드의 왼쪽 오른쪽 노드를 NULL로 하고 동적할당 해제 */
	}
	return 0;
}