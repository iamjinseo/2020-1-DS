#include <stdio.h>

struct student1 {          //구조체 struct student1 선언
    char lastName;
    int studentId;
    char grade;
};

typedef struct {
    char lastName;
    int studentId;
    char grade;
} student2;         //typedef를 써서 구조체  student2 선언

int main(){
    printf("[ ----- [Software department]   [Jinseo Lee]   [2019038032] -----]\n");

    struct student1 st1 = {'A', 100, 'A'};           //변수 자료형은struct student으로, struct를 쓰지 않으면 컴파일 에러가 일어난다.
    /* typedef를 통해 선언하면 오류가 발생하지 않음 */
    printf("st1.lastName = %c\n", st1.lastName);     
    printf("st1.studentId = %d\n", st1.studentId);
    printf("st1.grade = %d\n", st1.grade);
    /* 구조체 변수 st1이 가진 멤버들의 값 출력 (A, 100, A) */

    student2 st2 = {'B', 200, 'B'};  //구조체 변수 st2선언 및 초기화
    /* typedef를 통해 구조체를 정의하였으므로 오류가 일어나지 않음  */
    printf("\nst2.lastName = %c\n", st2.lastName);
    printf("st2.studentId = %d\n", st2.studentId);
    printf("st2.grade = %c\n", st2.grade);
    /* 구조체 변수 st2가 가진 멤버들의 값 출력 (B, 200, B) */


    student2 st3;

    st3 = st2;    //구조체 변수 st2를 st3에 대입 

    printf("\nst3.lastName = %c\n", st3.lastName);
    printf("st3.studentId = %d\n", st3.studentId);
    printf("st3.grade = %c\n", st3.grade);
    /* 구조체 변수 st3이 가진 멤버들의 값 출력 (B, 200, B) */


    /* if(st3 == st2) printf("equal\n");
    else printf("not equal\n");  */   //구조체는 ==연산자로 비교될 수 없음

    return 0;
}