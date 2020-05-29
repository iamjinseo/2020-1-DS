/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop(); 
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */
void printMenu();

//void printStack();


int main()
{
	printf("-----------------[Software department] [2019038032] [Jinseo Lee]-----------------");
	char command;
	int key;
	Node* head = NULL;

	do {
        printMenu();
		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		/*case 'p': case 'P':
			printStack();
			break;
		*/
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if (ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

void iterativeInorder(Node* node)
{
	for (;;) {
		for (; node; node = node->left) { //node가 NULL이 될 때까지
			push(node);  //왼쪽 아래 노드로 이동하면서 계속 스택에 node값 삽입
		}
		node = pop();    //왼쪽 아래 끝까지 왔으면 스택에서 pop
		
		if (node == NULL) break; //공백스택일시 반복문 탈출

		printf("[%d] ", node->key);  //pop한 원소의 키값 출력
		node = node->right;          //pop했던 곳 바로 위(node)에서 오른쪽 아래로 이동
	}
}

void levelOrder(Node* ptr)
{
	if (ptr == NULL) return;     //공백트리이면 함수 종료
	enQueue(ptr);  //큐에 ptr(루트노드)삽입

	for (;;) {
		ptr = deQueue();    // delete Q, 첫번째엔 ptr==루트노드
		if (ptr) {           
			printf("[%d] ", ptr->key);
			if (ptr->left)  //왼쪽 자식노드가 있으면
				enQueue(ptr->left);  //그 노드 삽입
			if (ptr->right) //오른쪽 자식노드가 있으면
				enQueue(ptr->right); //삽입
		}
		else break;  //공백트리일 시 반복 종료
	}
}

int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;
	/* 새 노드 생성 과정 */

	if (head->left == NULL) {  //루트노드가 없으면(공백트리이면)
		head->left = newNode;  //newnode는 루트
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while (ptr != NULL) {

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	
	if (head->left == NULL) {   //루트노드가 없는 상태의 트리 처리
		printf(" !!! tree is empty !!!\n");
		return 0;
	}

	Node *p = head->left, *p_prev = NULL; //초기 탐색용 변수
			/* 추후에 p는 key값 가지는 노드, p_prev는 p의 부모노드 */
	Node *Smallest=NULL, *Smallest_prev=NULL; //자식이 두개일 때를 위한 변수(탐색용)

	while (p != NULL && p->key != key) {
		/* 키값 가지는 노드 탐색 */
		p_prev = p; //p_prev는 head(초기에)

		if (key < p_prev->key)
			p = p->left;
		else if (key > p_prev->key)
			p = p->right;
		//key가 부모 노드보다 작으면 왼쪽 노드로, 크면 오른쪽 노드로 이동
	}

	if (p == NULL) {
		printf("cannot find the key\n");
		return 0;
	}

	/* 리프 원소 삭제 */
	if (p->left == NULL && p->right == NULL) {  //p가 리프노드라면
		if (p_prev != NULL) {
			if (p_prev->left == p) {
				free(p_prev->left);
				p_prev->left = NULL;
				/* 부모노드의 왼쪽노드가 p이고 그걸 삭제함 */
			}
			else {
				free(p_prev->right);
				p_prev->right = NULL;
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
	/* 두 개의 자식을 가진 노드의 삭제  */
	else if (p->left != NULL && p->right != NULL) {  
		/* p의 오른쪽 서브트리에서 가장 작은 값 찾기 */
		Smallest = p->right; 
		Smallest_prev = p;;
		while(Smallest->left!=NULL){  //Smallest의 left가 NULL이 될 때까지 (제일 작은 값 가지는 노드로 이동)
			Smallest_prev = Smallest;    //Smallest_prev는 Smallest의 부모노드
			Smallest = Smallest->left;   //Smallest는 왼쪽 아래로 계속 가기
		} 
		p->key = Smallest->key;       //가장 작은 원소로 대체

		if (Smallest_prev->right == Smallest) //Smallest가 이전노드의 오른쪽에 있는 노드라면
			Smallest_prev->right = Smallest->right;  //이전노드의 오른쪽은 Smallest의 오른쪽  
		else  //왼쪽에 있는 노드라면
			Smallest_prev->left = Smallest->right;   //이전노드의 왼쪽은 Smallest의 오른쪽
	}
	/* 한개의 자식을 가진 노드의 삭제 */
	else { 
		if (p_prev->left == p) {       //p가 왼쪽자식이라면
			if (p->left) {             //p가 왼쪽 자식만을 가진다면
				p_prev->left = p->left;
				free(p);
				p->left = NULL;
			}
			else {                     //p가 오른쪽 자식만 가지면
				p_prev->left = p->right;
				free(p);
				p->right = NULL;
			}
		}
		else {                         //p가 오른쪽 자식
			if (p->left) {             //p가 왼쪽 자식만을 가진다면
				p_prev->right = p->left;
				free(p);
				p->left = NULL;
			}
			else {                     //p가 오른쪽 자식만 가지면
				p_prev->right = p->right;
				free(p);
				p->right = NULL;
			}

		}
	}
		
	return 0;
}


void freeNode(Node* ptr) {
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{
	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}

Node* pop() //stack에서 pop
{
	if (top == -1) return NULL;  //top==-1 은 공백 스택이므로 종료
	return stack[top--];  //스택에서 pop
}

void push(Node* aNode) //stack에 push
{
	if (top >= MAX_STACK_SIZE - 1) {
		printf(" !!! Stack is full !!!\n");
		return;
		//top이 최대크기를 넘어서면 경고문 출력 후 종료
	}
	else stack[++top] = aNode;  //스택에 push
}

Node* deQueue()
{
	if (front == rear)  //공백 큐일 때
		return NULL;
	else {
		front = (front + 1) % MAX_QUEUE_SIZE; //큐의 front는 그 다음이 됨
		return queue[front];  //큐의 front부분 리턴
	}
}

void enQueue(Node* aNode)
{
	if (((rear + 1) % MAX_QUEUE_SIZE) == front) //큐에서 끝의 다음이 front일때
		return;
	else {
		rear = (rear + 1) % MAX_QUEUE_SIZE;  //rear를 다음으로 이동시킴
		queue[rear] = aNode;  //이동된 자리에 aNode삽입
	}
}

void printMenu() {
	printf("\n\n");
	printf("----------------------------------------------------------------\n");
	printf("                   Binary Search Tree #2                        \n");
	printf("----------------------------------------------------------------\n");
	printf(" Initialize BST       = z                                       \n");
	printf(" Insert Node          = i      Delete Node                  = d \n");
	printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
	printf(" Level Order (Queue)  = l      Quit                         = q \n");
	printf("----------------------------------------------------------------\n");
}


