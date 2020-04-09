#include <stdio.h>
#include <stdlib.h>

void main(){
    printf("[ ----- [Software department]   [Jinseo Lee]   [2019038032] -----]\n");

    int **x;   //이중 포인터

    /* 32bit 시스템에서 실습을 진행하고 있습니다. */
    printf("sizeof(x) = %lu\n", sizeof(x));   //주소를 갖고있는 이중 포인터 이므로, 사이즈는 4bytes
    printf("sizeof(*x) = %lu\n", sizeof(*x)); //x가 참조하는 *x도 주소를 저장하는 포인터이기에 사이즈는 4bytes
    printf("sizeof(**X) = %lu\n", sizeof(**x)); //이중 포인터가 두번 참조하는 것은 포인터가 아니므로 int형의 크기 출력(4 bytes)

}