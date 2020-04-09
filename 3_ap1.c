// #include <stdio.h>
// #include <stdlib.h>

// void main(){
//     printf("[ ----- [Software department]   [Jinseo Lee]   [2019038032] -----]\n");
//     int list[5];
//     int *plist[5]={NULL};    //int형 포인터를 담고있는 배열을 NULL로 초기화

//     plist[0]=(int *)malloc(sizeof(int));   //int의 크기만큼 heap영역에 공간을 할당하고 plist[0]에 넘김

//     list[0]=1;
//     list[1]=100;

//     *plist[0]=200;

//     printf("value of list[0] = %d\n", list[0]);    //list의 0번째 인덱스에 있는 값(1) 출력       
//     printf("address of list[0]          = %p\n", &list[0]);  //list의 0번째 인덱스의 주소를  출력
//     printf("value of list               = %p\n", list);      //list의 값을 주소로 출력, 위와 결과 같음
//     printf("address of list (&list)     = %p\n", &list);   //list의 주소를 출력, 위와 결과 같음
//     /* 0번째 인덱스 주소 == 배열 이름 == 배열 주소 */

//     printf("----------------------------------------------------------\n\n");
//     printf("value of list[1]            = %d\n", list[1]);   //list의 1번째 인덱스의 값(100) 출력
//     printf("address of list[1]          = %p\n", &list[1]);  //list의 1번째 인덱스의 주소를 출력
//     printf("value of *(list+1)          = %d\n", *(list+1)); //list(주소)에 1(4 bytes)을 더한 주소에 있는 값 출력, 결과는 1번째 인덱스의 값과 동일
//     printf("address of list+1           = %p\n", list+1);    //list에 1을 더한 주소값을 출력, list의 1번째 인덱스의 주소와 같음

//     printf("----------------------------------------------------------\n\n");
//     printf("value of *plist[0] = %d\n", *plist[0]);  //plist의 0번째 인덱스가 가리키는 값 출력, 결과는 200
//     printf("&plist[0]          = %p\n", &plist[0]);  //0번째 인덱스의 주소 출력
//     printf("&plist             = %p\n", &plist);     //plist의 주소 출력, 위와 결과 동일
//     printf("plist              = %p\n", plist);      //plist의 값을 주소로 출력, 위와 결과 동일  
//     printf("plist[0]           = %p\n", plist[0]);   //plist의 0번 인덱스가 가지고 있는 주소값 출력
//     printf("plist[1]           = %p\n", plist[1]);   
//     printf("plist[2]           = %p\n", plist[2]);
//     printf("plist[3]           = %p\n", plist[3]);
//     printf("plist[4]           = %p\n", plist[4]);
//     /*plist[1]부터 plist[4]까지의 출력 값은 모두 00000000
//       plist[0]에만 malloc을 통해 메모리 공간을 할당 해주었기 때문*/

//     free(plist[0]);   //동적할당 해제
// }
