/*
 * hw5-sorting.c
 *
 *  Created on: May 22, 2019
 *
 *  Homework 5: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>   
/* 난수 생성을 위함 */
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main(){
	char command;
	int *array = NULL;    
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a) { //array를 실매개변수로
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);   
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	}
	else
		temp = *a;   //temp가 a를 가리킴

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;  //a(array)의 각 원소에 랜덤값 지정

	return 0;
}
int freeArray(int *a) {  // array free함수
	if(a != NULL)
		free(a);      //a 동적해제
	return 0;
}

void printArray(int *a) {  //array출력 함수
	if (a == NULL) {  
		printf("nothing to print.\n");
		return;
	}//array가 공백이라면 경고문 출력 후 종료
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);  //인덱스 출력
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);  //원소 출력
	printf("\n");
}


int selectionSort(int *a) {
	int min;        //최소값
	int minindex;   //최소값 인덱스
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++) {  //인덱스 탐색
		minindex = i;  //처음에 minindex는 0으로 지정
		min = a[i];    //최초의 최소값은 0번째 인덱스 원소
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) {
			if (min > a[j]) {  //다른 인덱스 원소값이 더 작으면
				min = a[j];    //최소값변경
				minindex = j;  //최소값 인덱스 변경
			}
		}
		a[minindex] = a[i];    
		a[i] = min;
		/* 값 바꾸기 */
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a) {  //삽입정렬 함수
	int i, j, t;  //t is key

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++){ //배열순회
		t = a[i];  //key는 i번째 인덱스 원소값
		j = i;     //j는 계속 다음 인덱스로
		while (a[j-1] > t && j > 0){ //j는 양수이고 이전인덱스 원소값이 키값보다 크다면
			a[j] = a[j-1];  //원소를 오른쪽으로 이동
			j--; //j값을 다시 줄임
		}
		a[j] = t;  //j번째 원소가 key가 된다
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a) {  //버블정렬
	int i, j, t;  //t is key

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //printing array

	for(i = 0; i < MAX_ARRAY_SIZE; i++){
		for (j = 1; j < MAX_ARRAY_SIZE; j++){ //j는 i다음원소
			if (a[j-1] > a[j]){      //인접한 두개의 원소를 비교
				t = a[j-1];       
				a[j-1] = a[j];
				a[j] = t;
			}//이전원소가 작으면 서로 키값 바꾸기
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0; //함수 종료
}

int shellSort(int *a){  //셸 정렬
	int i, j, k, h, v; //h는 간격 

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2){ //h를 반씩 줄이면서 1이될때까지반복
		for (i = 0; i < h; i++){  //i가 간격까지
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h){ //j는 간격 너머의 원소
				v = a[j]; //v는 array의 j번째인덱스값 
				k = j;  //k는 j인덱스값 
				while (k > h-1 && a[k-h] > v){  
					a[k] = a[k-h];
					k -= h;  //인덱스 간격 이전으로 변경
					/* 간격 끝에 있는 인덱스, 원소값을 비교하여 앞의 값을 뒤로 변경  */
				}
				a[k] = v;  
				//값을 변경하게 됨
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n){ //퀵 정렬 n is size of array
	int v, t; //v : pivot, t : for swaping
	int i, j; //탐색용인덱스

	if (n > 1){
		v = a[n-1];  //가장 오른쪽 원소
		i = -1;  //초기 인덱스(가장왼쪽)
		j = n - 1; //초기인덱스(가장오른쪽)

		while(1) {
			while(a[++i] < v);  //가장 왼쪽에서 오른쪽으로 가면서 v보다 큰 수가 나올 때까지
			while(a[--j] > v);  //가장 오른쪽에서 왼쪽으로 가면서 v보다 작은 수가 나올 때까지

			if (i >= j) break;  //인덱스가 엇갈리면 종료
			t = a[i];
			a[i] = a[j];
			a[j] = t;
			//i, j인덱스에 있는 원소를 바꾸기
		}
		t = a[i]; //t는 원래 오른쪽에 있던 원소
		a[i] = a[n-1]; //a[n-1]은 pivot
		a[n-1] = t;
		//pivot과 오른쪽에 있던 원소 바꿈

		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
		//pivot의 위치가 바뀌었으므로 pivot앞부분과 뒷부분을 정렬
    }
	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht){
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} 
    else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1; //해시테이블 전체를 -1로 초기화

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++){ //배열순회
		key = a[i]; //현재 인덱스의 원소값은 key
		hashcode = hashCode(key);  //key값의 hashcode 산출
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1) //해당 hashcode부분에 정보가 없다면
			hashtable[hashcode] = key; //빈 곳에 key삽입
		
         else {

			index = hashcode;

			while(hashtable[index] != -1){ //해시테이블 탐색 수행
				index = (++index) % MAX_HASH_TABLE_SIZE; //인덱스 이동
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key; //빈곳에 정보 삽입
		}
	}
	return 0;
}

int search(int *ht, int key){   //key 탐색
	int index = hashCode(key);  //key의 인덱스값을 반환하여 index에 삽입

	if(ht[index] == key)  
		return index;	//index의 정보가 key와 같다면 해당 인덱스 리턴

	while(ht[++index] != key)   //인덱스 탐색하면서 key값을 찾기 까지
		index = index % MAX_HASH_TABLE_SIZE;  //인덱스 이동
	return index; //인덱스값 반환
}


