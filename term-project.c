#include <stdio.h>
#include <stdlib.h>
#define  MAX_VERTEX 10

typedef struct Vertex {
	int num;                /* vertex number */
	struct Vertex* link;    /* link to a next adjacent vertext */
}Vertex;

typedef struct VertexHead {
	Vertex* head;           /* linked list of all adjacent vertices */
}VertexHead;

typedef struct Graph {
	VertexHead* vlist;      /* list of all vertices: vlist[MAX_VERTEX] */
}Graph;

int flag[MAX_VERTEX]; //v-flag

/* stack */
int stack[MAX_VERTEX];
int top = -1;
int pop() {
	if (top == -1) return -1; //공백스택일 시 종료
	return stack[top--];      //스택에서 pop
}
void push(int n) {
	stack[++top] = n;
}

/* queue */
int queue[MAX_VERTEX];
int front = -1;
int rear = -1;
int deQueue() {
	if (front == rear)                      //공백 큐일 때
		return -1;
	else {
		front = (front + 1) % MAX_VERTEX;   //큐의 front는 그 다음이 됨
		return queue[front];                //큐의 front부분 리턴
	}
}
void enQueue(int n) {
	if (((rear + 1) % MAX_VERTEX) == front) //큐에서 끝의 다음이 front일때
		return;
	else {
		rear = (rear + 1) % MAX_VERTEX;     //rear를 다음으로 이동시킴
		queue[rear] = n;                    //이동된 자리에 n삽입
	}
}
int isEmpty() {                             //공백 큐인지 검사
	if (front == rear)
		return 1;
	else return 0;
}



Graph* createGraph();                        /* empty graph creation */
void destroyGraph(Graph*);                   /* deallocating all allocated memory */
void insertVertex(int);                      /* vertex insertion */
void deleteVertex(Graph*, int);              /* vertex deletion */
void insertEdge(Graph*, int, int);           /* new edge creation between two vertices */
void deleteEdge(Graph*, int, int);           /* edge removal */
void depthFS(Graph*, int);                   /* depth firt search using stack */
void breadthFS(Graph*, int);                 /* breadth first search using queue */
void printGraph(Graph*);                     /* printing graph with vertices and edges */


/* 추가 함수 */
void flagToZero() { //flag 초기화
	for (int i = 0; i < MAX_VERTEX; i++)
		flag[i] = 0;
}

int isInRange(int n) {
	if (n >= MAX_VERTEX || n < 0) {
		printf("   >>>  re-enter the number of vertex.  <<< \n");
		return 0;   //범위 밖이면 0반환(실패)
	}
	else return 1;  //범위 안이면 1반환(성공)
}  //vertex number로 입력한 n이 적절한 범위 안에 있는지 검사하는 함수

Vertex* createVertex(int);  //vertex생성함수
void print_inserted_V();   //삽입된 vertex가 몇번인지 알려주는 함수
void search_and_delete(Graph*, int n, int m, Vertex*, Vertex*); //한 헤드(n)에서 m값의 노드를 찾아 삭제하는 함수
void search_and_insert(Graph*, int, Vertex*); //엣지를 추가하는 구현부 (n번 헤드에 vertex삽입)



int main() {
	Graph *graph = NULL;
	int n = 0;            //vertex number
	int m = 0;            //vertex number

	char command;
	printf("----------------------------------------------------------------\n");
	printf("                          Term-project                          \n");
	printf("----------------------------------------------------------------\n");
	printf(" createGraph      = z           \n");
	printf(" destroyGraph     = q           deleteEdge     = l\n");
	printf(" insertVertex     = i           depthFS        = t\n");
	printf(" deleteVertex     = d           breadthFS      = h\n");
	printf(" insertEdge       = e           printGraph     = p\n");
	printf("----------------------------------------------------------------\n");

	do {
		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			if (graph != NULL) destroyGraph(graph);  //그래프가 존재한다면 동적할당 해제
			graph = createGraph();                   //그래프 생성
			flagToZero();						 //flag초기화
			break;
		case 'q':case 'Q':
			destroyGraph(graph);
			break;
		case 'i': case 'I':
			printf("enter the Vertex number to be inserted : ");
			scanf("%d", &n);
			insertVertex(n);
			break;
		case 'd': case 'D':
			printf("enter the Vertex number to be deleted : ");
			scanf("%d", &n);
			deleteVertex(graph, n);
			break;
		case 'e':case 'E':
			printf("InsertEdge - enter the edge (ex. 1 10) : ");
			scanf("%d %d", &n, &m);
			insertEdge(graph, n, m);
			break;
		case 'l':case 'L':
			printf("DeleteEdge - endter the edge (ex. 1 10) : ");
			scanf("%d %d", &n, &m);
			deleteEdge(graph, n, m);
			break;
		case 't':case 'T':
			printf("depthFS - Select start-vertex : ");
			scanf("%d", &n);
			depthFS(graph, n);
			break;
		case 'h':case 'H':
			printf("breadthFS - Select start-vertex : ");
			scanf("%d", &n);
			breadthFS(graph, n);
			break;
		case 'p':case'P':
			print_inserted_V(flag);
			printGraph(graph); break;
		default:
			printf("re-enter the command.\n"); break;
		}

	} while (command != 'q' && command != 'Q');

	return 0;
}



//이 함수에서 그래프를 만들어 반환함
Graph* createGraph() {
	Graph* g = (Graph*)malloc(sizeof(Graph));  	                   //그래프 동적할당

	g->vlist = (VertexHead*)malloc(sizeof(VertexHead)*MAX_VERTEX); //리스트 동적할당

	for (int i = 0; i < MAX_VERTEX; i++)
		((g->vlist) + i)->head = NULL;     //그래프의 각 vertex를 전부 NULL로 초기화

	return g;
}

/* 그래프 동적할당 해제 */
void destroyGraph(Graph* g) {
	Vertex* vertex;
	Vertex* prev;    //vertex 제거용

	if (g != NULL) {
		if (g->vlist != NULL) {
			for (int i = 0; i < MAX_VERTEX; i++) {
				vertex = ((g->vlist) + i)->head; //헤드 지정
				while (vertex != NULL) {         //각 리스트 순회
					prev = vertex;
					vertex = vertex->link;
					free(prev);                  //다음 vertex로 이동하면서 이전 vertex free
				}
			}
			free(g->vlist);  //인접리스트 제거
		}
		free(g);             //그래프 제거
	}
}


/* 몇번 vertex가 삽입되어있나 확인해주는 함수 */
void print_inserted_V() {
	printf("Inserted : ");
	for (int i = 0; i < MAX_VERTEX; i++)
		if (flag[i] == 1)
			printf("[%d] ", i);
	printf("\n");
}

/* 그래프 출력 */
void printGraph(Graph* g) {
	Vertex* vertex;
	for (int i = 0; i < MAX_VERTEX; i++) {  //리스트 헤드 순회
		vertex = ((g->vlist) + i)->head;    //각 헤드로
		printf("[%d] -> ", i);
		while (vertex != NULL) {
			printf("%d ", vertex->num);
			vertex = vertex->link;          //노드들 출력
		}
		printf("\n");
	}
}

/* 정점 삽입 함수 */
void insertVertex(int n) {

	//n이 범위 밖의 수이면 경고문 출력 후 종료
	if (isInRange(n) == 0) return;

	//n번 vertex가 없다면 생성
	if (flag[n] == 0) flag[n] = 1;   //n번 vertex는 not null
	//이미 생성되어있다면 안내문 출력
	else printf("   >>>  [%d] vertex is already inserted.  <<<\n", n);

}

/* 정점 제거 함수 */
void deleteVertex(Graph* g, int n) {

	/* n이 범위 밖의 수이면 경고문 출력 후 종료 */
	if (isInRange(n) == 0) return;

	Vertex* vertex = ((g->vlist) + n)->head;
	Vertex* prev;

	/* n번 vertex를 제거 */
	if (flag[n] != 0 && vertex != NULL) {
		flag[n] = 0;
		/* n번 모든 인접 노드 삭제 */
		while (vertex != NULL) {       //각 리스트 순회
			prev = vertex;
			vertex = vertex->link;
			free(prev);                //다음 vertex로 이동하면서 이전 vertex free
		}
		((g->vlist) + n)->head = NULL; //최종적으로 n번 head는 null
	}
	/* 존재하지 않는다면 안내문 출력 */
	else if (flag[n] != 0 && vertex == NULL) flag[n] = 0;
	else printf("   >>>  [%d] vertex is already NULL  <<<\n", n);

	/* n번 노드와 연결된 모든 연결점 삭제 */
	/* 3과 6이 연결되어있다면 6번 head의 리스트 중 n값을 가지는 노드 삭제 */
	Vertex* Head;
	Vertex* prev2;
	for (int i = 0; i < MAX_VERTEX; i++) {
		if (i == n) continue;  //n번 vertex 건너뛰기
		Head = ((g->vlist) + i)->head;
		prev2 = Head;          //반복문 초기를 위해 prev 지정
		search_and_delete(g, i, n, Head, prev2); //i번 헤드에서 n값 가지는 노드 찾아 삭제
	}
}

void insertEdge(Graph* g, int n, int m) {
	if (isInRange(n) == 0 || isInRange(m) == 0) return;     //범위 검사

	/* n, m vertex가 삽입되지 않았다면 경고문 출력 후 함수 종료 */
	if (flag[n] == 0 || flag[m] == 0) {
		printf("   >>>  [%d] or [%d] vertex is not inserted.  <<<\n", n, m);
		return;
	}
	Vertex* vertex1 = createVertex(n);
	Vertex* vertex2 = createVertex(m); //번호 값을 가지는 vertex 생성
	search_and_insert(g, n, vertex2); //n번 헤드에 vertex2와의 엣지 추가
	search_and_insert(g, m, vertex1); //n번 헤드에 vertex1과의 엣지 추가
}

void search_and_insert(Graph* g, int n, Vertex* vertex) {
	Vertex* Head;           //각 head의 리스트를 순회할 포인터
	Vertex* prev;           //마지막 노드

	if (((g->vlist) + n)->head == NULL) {
		((g->vlist) + n)->head = vertex;     //n번 Vertex에 어떠한 인접노드도 없을 경우 
	}
	else {
		Head = ((g->vlist) + n)->head;
		while (Head != NULL) {
			if (Head->num == vertex->num) {  //이미 삽입된 엣지일 때 경고문 출력 후 종료
				printf("   >>>  Already inserted ! <<< \n");
				return;
			}
			prev = Head;
			Head = Head->link;  //리스트 순회
		}
		prev->link = vertex;    //edge 생성
	}
}

/* 한개의 vertex를 생성하는 함수 */
Vertex* createVertex(int v) {
	Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));
	vertex->num = v;
	vertex->link = NULL;
	return vertex;
}

/* 엣지 없애기 */
void deleteEdge(Graph* g, int n, int m) {
	if (isInRange(n) == 0 || isInRange(m) == 0) return;  //범위검사
	/* n, m vertex가 삽입되지 않았다면 경고문 출력 후 함수 종료 */
	if (flag[n] == 0 || flag[m] == 0) {
		printf("   >>> [%d] or [%d] vertex is not inserted.  <<<\n", n, m);
		return;
	}
	/* n 또는 m 헤드에 엣지가 없다면 경고문 출력 후 종료 */
	if (((g->vlist) + n)->head == NULL || ((g->vlist) + m)->head == NULL) {
		printf("   >>>  fail to delete edge ( NO EDGE )  <<<\n");
	}

	Vertex* Head = ((g->vlist) + n)->head;
	Vertex* prev = Head;

	search_and_delete(g, n, m, Head, prev);  //n이 헤드인 리스트에서, m이 vertex number인 노드 찾아 삭제
	Head = ((g->vlist) + m)->head;   //헤드 재지정
	prev = Head;                     //prev재지정
	search_and_delete(g, m, n, Head, prev);  //m이 헤드인 리스트에서, n이 vertex number인 노드 찾아 삭제
}

void search_and_delete(Graph*g, int n, int m, Vertex* Head, Vertex* prev) {
	//n은 head의 위치, m은 vertex number
	while (Head != NULL) {      //리스트순회
		if (Head->num == m) {   //m값의 노든를 찾았다면
			if (Head == ((g->vlist) + n)->head)  //맨처음 노드의 엣지 삭제 시
				((g->vlist) + n)->head = Head->link;
			else
				prev->link = Head->link;
			free(Head); //n번 노드 삭제
			break;
		}
		/* 리스트순회 */
		prev = Head;
		Head = Head->link;
	}
}

/* 깊이 우선 탐색 */
void depthFS(Graph *g, int n) {           //n은 탐색 노드 번호 및 인덱스
	if (isInRange(n) == 0)
		return;        //범위 검사
	if (flag[n] == 0) {
		printf("   >>>  vertex isn't inserted.  <<<\n");
		return;        //vertex가 삽입되었는지 검사
	}
	if (((g->vlist) + n)->head == NULL) {
		printf("   >>>  [%d] doesn't have a edge.  <<<\n", n);
		return;  //edge가 존재하는지 검사
	}

	printf("depthFS ===> ");

	int visited[MAX_VERTEX] = { 0 };      //인덱스 번호의 노드를 방문했는지 검사하는 배열
	visited[n] = 1;   //n번은 방문
	Vertex* vertex;
	push(n);          //stack에 n 삽입
	printf("%d ", n);

	while (top != -1) {
		vertex = ((g->vlist) + n)->head;     //n번 head
		while (vertex != NULL) {             //인접노드 탐색
			if (visited[vertex->num] == 0) { //방문한 적 없는 노드일 시
				push(vertex->num);
				printf("%d ", vertex->num);  //stack에 삽입 후 출력

				visited[vertex->num] = 1;    //방문 체크
				//printf("%d ", vertex->num);

				n = vertex->num;
				vertex = ((g->vlist) + n)->head;  //해당 인접노드가 다시 헤드가 됨
				break;  //반복문 탈출
				//printf("\n%d is next head", n);
			}
			else {
				vertex = vertex->link;           //방문한 노드이면 다음 노드로
			}
		}
		//반복문 탈출 후를 고려한 부분
		if (vertex == NULL) {          //인접노드가 없다면
			n = pop();                 //스택에 있던 해당 값 pop
			//printf("\n%d pop", n);
			n = stack[top];            //n값 다시 정의(stack의 top값이 다음 헤드가 되어야 함)
		}
	}
	printf("\n");
}
void breadthFS(Graph* g, int n) {
	if (isInRange(n) == 0)
		return;        //범위 검사
	if (flag[n] == 0) {
		printf("   >>>  vertex isn't inserted.  <<<\n");
		return;        //vertex가 삽입되었는지 검사
	}
	if (((g->vlist) + n)->head == NULL) {
		printf("   >>> [%d] doesn't have a edge.  <<<\n", n);
		return;  //edge가 존재하는지 검사
	}

	printf("breadthFS ===> ");
	int visited[MAX_VERTEX] = { 0 };  //방문 검사 배열
	visited[n] = 1;      //n번은 방문
	enQueue(n);          //q에 삽입
	Vertex* vertex;

	while (1) {         
		n = deQueue();  //큐의 front에서 값 빼오기
		if (n == -1)
			break;  //공백큐일 시 종료
		else {
			printf("%d ", n);   //큐에서 빼온 값 출력
			vertex = ((g->vlist) + n)->head;   //빼온 값이 탐색할 노드의 헤드
			while (vertex != NULL) {           //리스트 순회
				if (visited[vertex->num] == 0) {   //방문하지 않은 노드일 시
					enQueue(vertex->num);          //큐에 삽입
					visited[vertex->num] = 1;      //방문 처리
				}
				vertex = vertex->link;             //방문한 노드일 시 다음 노드로
			}
		}
	}
	printf("\n");
}