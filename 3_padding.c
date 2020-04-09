#include <stdio.h>

struct student { 
    char lastName[13];      //13 bytes
    int studentId;          //4 bytes
    short grade;            //2 bytes

    //총합 19 bytes
};

int main(){
    printf("[ ----- [Software department]   [Jinseo Lee]   [2019038032] -----]\n");
    struct student pst;

    printf("size of student = %ld\n", sizeof(struct student));   //24가 출력됨
    printf("size of int = %ld\n", sizeof(int));      //4가 출력됨
    printf("size of short = %ld\n", sizeof(short));  //2가 출력됨

    /* 이론상 student의 크기는 19인데 24가 출력된 이유
        : 문자열 lastName[13]에 공간을 주기 위해 (4*4)bytes만큼의 공간이 생성되고 3bytes는 padding됨*
          int형 변수 studentId에 4 bytes만큼에 공간이 생성됨
          short형 변수 grade에 공간을 주기 위해 4 bytes만큼의 공간이 생기고 2bytes는 padding됨*/

    /* 컴파일러마다 padding 처리가 다른데, gcc컴파일러는 padding 처리를 하고 있음이 나타남 */

    return 0;
}