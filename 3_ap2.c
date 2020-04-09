// #include <stdio.h>
// #include <stdlib.h>

// void main(){
//     printf("[ ----- [Software department]   [Jinseo Lee]   [2019038032] -----]\n");
//     int list[5];
//     int *plist[5];

//     list[0]=10;
//     list[1]=11;

//     plist[0]=(int *)malloc(sizeof(int));

//     printf("list[0]\t= %d\n", list[0]);               //list의 0번 인덱스 값 출력
//     printf("address of list\t= %p\n", list);          //list의 주소를 출력
//     printf("address of list[0]\t = %p\n", &list[0]);  //list의 0번 인덱스의 주소를 출력, 0번인덱스 주소 == 배열이름 == 배열 시작 주소
//     printf("address of list + 0\t= %p\n", list+0);    //list(주소)에 0 bytes 더한 주소 출력, 위와 출력값 동일
//     printf("address of list + 1\t= %p\n", list+1);    //list(주소)에 4 bytes 더한 주소 출력
//     printf("address of list + 2\t= %p\n", list+2);    //list에 (4 * 2) bytes 더한 주소 값 출력
//     printf("address of list + 3\t= %p\n", list+3);    //list에 12 bytes 더한 주소 값 출력
//     printf("address of list + 4\t= %p\n", list+4);    //list에 16 bytes 더한 주소 값 출력
//     printf("address of list[4]\t= %p\n", &list[4]);   //list의 4번 인덱스의 주소 출력, 위와 출력 결과 같음
//     /* 배열이름 + n 은 배열의 n번 인덱스의 주소와 동일 */

//     free(plist[0]);  //동적할당 해제
// }