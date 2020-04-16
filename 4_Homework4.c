#include <stdio.h>     //입출력함수 사용을 위함
#include <time.h>      //컴파일 할 때마다 다른 난수를 생성하기 위함
#include <stdlib.h>    //동적할당 및 난수생성함수 사용 위함

int** create_matrix(int row, int col);  //행렬 생성 함수
int free_matrix(int **matrix, int row, int col);  //동적할당 받은 행렬의 공간을 해제하는 함수
void print_matrix(int** matrix, int row, int col);  //행렬을 출력하는 함수
int fill_data(int** matrix, int row, int col); //행렬에 난수값을 넣는 함수
int transpose_matrix(int **matrix, int **matrix_t, int row, int col); //행렬의 전치행렬을 만드는 함수
int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum, int row, int col);  //행렬끼리 더하는 함수
int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col);  //행렬끼리 빼는 함수
int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt, int row, int col); //행렬곱을 구현하는 함수


int main() {
	int row, col;  //행과 열 변수 선언
	printf("------------[Software department] [Jinseo Lee] [2019038032]------------\n");
	srand((unsigned int)(time(NULL)));      //seed값 사용

	printf("enter the size of row and col : "); //입력 안내 메세지
	scanf("%d %d", &row, &col);             //행, 열 크기 입력

	int** A = create_matrix(row, col);  //행렬 A 생성
	fill_data(A, row, col);  //행렬의 성분값에 난수를 생성하는 함수 호출
	int** B = create_matrix(row, col);  //행렬 B생성
	fill_data(B, row, col);  //행렬의 성분값에 난수를 생성하는 함수 호출
	//두 행렬을 크기에 맞게 생성 후 난수 값 집어넣기
	printf("\n\t\tmatrix A\n"); print_matrix(A, row, col);
	printf("\n\t\tmatrix B\n"); print_matrix(B, row, col);
	/*A,B행렬 출력*/

	int** addAB = create_matrix(row, col); //A+B를 구현하기 위해 행렬의 합 값을 넣을 행렬 만들기
	addition_matrix(A, B, addAB, row, col);  //A+B구현 함수 호출
	printf("\n\t\tmatrix A+B\n"); print_matrix(addAB, row, col);           //A+B행렬 출력

	int** subAB = create_matrix(row, col); //A-B를 구현하기 위해 행렬의 차 값을 넣을 행렬 만듬
	subtraction_matrix(A, B, subAB, row, col); //A-B구현 함수 호출
	printf("\n\t\tmatrix A-B\n");print_matrix(subAB, row, col);             //A-B행렬 출력
	
	/*    전치행렬 T에 공간을 할당하는 과정   */
	/*    A가  nxm 행렬이라면 T는 mxn 행렬    */
	int **T = (int**)malloc(sizeof(int*)*col); //전치행렬 T에 열 사이즈만큼의 공간 할당, 다시 1차원 배열을 가리켜야 하므로 sizeof(int*)
	if (T == NULL) {
		printf("Dynamic allocation failed.\n");
		return -1; //동적할당에 실패하면 오류 메세지를 출력하고 비정상종료값 리턴
	}
	for (int i = 0; i < col; i++)
		*(T + i) = (int*)malloc(sizeof(int)*row);  //각 행에 row사이즈 만큼의 1차원 배열 할당
	transpose_matrix(A, T, row, col); //A의 전치행렬 구하기
	printf("\n\t\tmatrix T\n");print_matrix(T, col, row);  //전치행렬 출력



	/*    행렬곱을 통해 만들어진 AxB행렬에 공간을 할당하는 과정   */
	/*    A가 nxm 행렬이고 T가 mxn행렬이면 AxB는 nxn 행렬이다.    */
	int** mulAB = (int**)malloc(sizeof(int*)*row); //행 사이즈만큼의 공간 할당
	if (mulAB == NULL) {
		printf("Dynamic allocation failed.\n");
		return -1; //동적할당에 실패하면 오류 메세지를 출력하고 비정상종료값 리턴
	}
	for (int i = 0; i < row; i++)
		*(mulAB + i) = (int*)malloc(sizeof(int)*row);  //각 행에 row사이즈 만큼의 1차원 배열 할당
	multiply_matrix(A, T, mulAB, row, col);  //AxT 구하기
	printf("\n\t\tmatrix AxB A\n"); print_matrix(mulAB, row, row);   //AxT함수 출력하기. 열 크기도 row값임


	free_matrix(A, row, col);
	free_matrix(B, row, col);
	free_matrix(addAB, row, col);
	free_matrix(subAB, row, col);
	free_matrix(T, col, row);   //행과 열의 크기가 뒤바뀐 전치행렬이므로 매개변수를 바꿔 줘야 함
	free_matrix(mulAB, row, row); //rowxrow 크기의 행렬이므로
	/*행렬(이중포인터) A와 B, addAB, subAB, T, mulAB에 할당되었던 공간 해제*/
	return 0;
}






int** create_matrix(int row, int col) {  //행렬 생성 함수
	if (row <= 0 || col <= 0) {
		printf("size error!\n");
		return (int**)(-1); //행과 열의 사이즈가 0이하면 오류메세지 출력 후 비정상종료 값 리턴
	}
	int **matrix = (int**)malloc(sizeof(int*)*row); //이중포인터 matrix에 row 사이즈만큼의 공간 할당, 다시 1차원 배열을 가리켜야 하므로 sizeof(int*)
	if (matrix == NULL) {
		printf("Dynamic allocation failed.\n");
		return (int**)(-1); //동적할당에 실패하면 오류 메세지를 출력하고 비정상종료값 리턴
	}
	for (int i = 0; i < row; i++)
		*(matrix + i) = (int*)malloc(sizeof(int)*col);  //각 행에 col사이즈 만큼의 1차원 배열 할당
	return matrix;   //행렬 반환
}

int free_matrix(int** matrix, int row, int col) {  //동적할당 해제 함수
	for (int i = 0; i < row; i++)
		free(matrix[i]);  //일차원 배열을 연결하기위한 포인터들 해제
	free(matrix);   //이중 포인터 matrix해제

}

int fill_data(int** matrix, int row, int col) {  //행렬 성분값에 난수 생성하는 함수
	int i, k;   //반복문 사용 위함
	for (i = 0; i < row; i++)
		for (k = 0; k < col; k++)
			*(*(matrix + i) + k) = rand() % 20; //행렬의 각 성분값에 0부터 19까지의 랜덤값 집어넣기
	if (matrix == NULL) {
		printf("Failed to generate random values.\n");
		return (-1); //랜덤값 생성 실패 시 오류 메세지를 출력하고 비정상종료값 리턴
	}
}

void print_matrix(int **matrix, int row, int col) {   //행렬 출력 함수
	printf("\n\t ROWS : %d\t COLS : %d\n", row, col); //행과 열의 크기 출력
	for (int i = 0; i < row; i++) {
		printf("\t    ");   //줄간격 맞춤
		for (int k = 0; k < col; k++)
			printf("%4d", *(*(matrix + i) + k));
		/*행렬 성분값 출력하는 for문*/
		printf("\n");   //줄바꿈
	}
}

int addition_matrix(int** matrix_a, int** matrix_b, int** matrix_sum, int row, int col) {
	for (int i = 0; i < row; i++)
		for (int k = 0; k < col; k++)
			*(*(matrix_sum + i) + k) = *(*(matrix_a + i) + k) + *(*(matrix_b + i) + k);
	//matrix_a의 i행 k열 값 + matrix_b의 i행 k열 값
	if (matrix_sum == NULL) {
		printf("Failed to sum A and B.\n");
		return (-1); //A+B 실패 시 오류 메세지를 출력하고 비정상종료값(-1) 리턴
	}
}/*행렬의 합을 구현하는 함수, matrix_sum에 두 행렬의 행과 열에 대응하는 성분값의 합을 집어넣음*/

int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col) {
	for (int i = 0; i < row; i++)
		for (int k = 0; k < col; k++)
			*(*(matrix_sub + i) + k) = *(*(matrix_a + i) + k) - *(*(matrix_b + i) + k);
	//matrix_a의 i행 k열 값 - matrix_b의 i행 k열 값
	if (matrix_sub == NULL) {
		printf("Failed to subtraction A and B.\n");
		return (-1); //A-B 실패 시 오류 메세지를 출력하고 비정상종료값(-1) 리턴
	}
}/*행렬의 차를 구하는 함수, matrix_sub에 두 행렬의 행과 열에 대응하는 성분값의 차를 대입*/

int transpose_matrix(int **matrix, int **matrix_t, int row, int col) {
	for (int i = 0; i < row; i++)
		for (int k = 0; k < col; k++)
			matrix_t[k][i] = matrix[i][k];
	/*matrix의 i행 k열 성분을 matrix_t(전치행렬)의 k행 i열로 만듬*/
}
 int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt, int row, int col){  //행렬곱 구현 함수
	 for (int i = 0; i < row; i++) {  //matrix_axt의 행을 따라
		 for (int k = 0; k < row; k++) {  //matrix_axt의 열을 따라 (열은 row크기)
			 int sum = 0;
			 for (int j = 0; j < col; j++)  //matrix_t의 열을 따라
				 sum += matrix_a[i][j] * matrix_t[j][k];    
			 matrix_axt[i][k] = sum;  
		 }/* 행렬곱 알고리즘은 행렬곱 구하는 식을 보고 만들었습니다
			 ===> sigma k=1 to n A(ik)*B(kj)                        */
	 }
	 if (matrix_axt == NULL) {
		 printf("Failed to multiply A and B.\n");
		 return (-1); //AxB 실패 시 오류 메세지를 출력하고 비정상종료값(-1) 리턴
	 }
 }
