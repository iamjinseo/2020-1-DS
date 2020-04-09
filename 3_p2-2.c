#include <stdio.h>

 void print1(int *ptr, int rows); 

 int main(){
    printf("[ ----- [Software department]   [Jinseo Lee]   [2019038032] -----]\n");

    int one[]={0,1,2,3,4};

    printf("one       = %p\n", one);        //배열 one의 값 출력
    /* 배열의 이름 == 배열의 시작주소 */
    printf("&one      = %p\n", &one);       //배열 시작 주소 출력   
    printf("&one[0]   = %p\n", &one[0]);    //배열의 0번 인덱스 주소 출력
    /* 결과는 모두 one의 시작주소로, 동일하다 */
    printf("\n");

    print1(&one[0], 5);    //배열의 0번 인덱스 주소를 print1함수에 넘겨줌

    return 0;
 }
 void print1(int *ptr, int rows){    //포인터 변수 ptr이 배열 one의 시작주소를 가리킴
    int i;
    printf("Address \t Contents\n");
    for(i=0;i<rows;i++)
        printf("%p \t %5d\n", ptr+i, *(ptr+i)); //ptr의 값(one 주소)을 i(i*4 bytes)씩 늘린 주소값과 그 주소가 가지고 있는 값 출력
      /* one의 0번 인덱스부터 4번 인덱스 까지의 주소와 각 인덱스마다 가지고 있는 값이 출력됨 */
    printf("\n");
 }