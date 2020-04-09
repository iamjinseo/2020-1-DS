#include <stdio.h>
#define MAX_SIZE 100

float sum(float list[], int n);   
float input[MAX_SIZE], answer;
int i;

void main(){
    printf("[ ----- [Software department]   [Jinseo Lee]   [2019038032] -----]\n");

    for (i=0; i <MAX_SIZE;i++)
        input[i]=i;                //배열 input의 각 인덱스에 순번에 맞는 값 대입
    
    printf("address of input = %p\n", input);   //배열 input의 주소 출력
    /* 배열 이름 == 배열의 0번 인덱스의 주소를 가리키는 포인터 == 배열 시작 주소 */
    
    answer = sum(input, MAX_SIZE); //input을 call by reference 하여 sum함수 호출 
    printf("The sum is : %f\n", answer);  //총합 출력
}
float sum(float list[], int n){
    printf("value of list = %p\n", list);     //list의 값(input 주소) 출력
    /* 매개변수 float list[]는 call by reference를 통해 input을 가리키고 있음 */
    printf("address of list %p\n\n", &list);  //list의 주소 출력

    int i;
    float tempsum =0;        //총합을 담을 실수형 변수를 선언하고 0으로 초기화
    for(i=0;i<n;i++)
        tempsum += list[i];  //list의 모든 인덱스가 가지고 있는 값(총합)을 tempsum에 대입
    return tempsum;          //tempsum 반환
}