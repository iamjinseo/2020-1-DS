/*
 * postfix.c
 *
 *  2020 Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

 /* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum {
	lparen = 0,  /* ( */
	rparen = 9,  /* ) */
	times = 7,   /* * (곱셈) */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + */
	minus = 4,   /* - */
	operand = 1 /* 피연산자 */
} precedence;


char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과 저장 */

void postfixPush(char x)
{
	postfixStack[++postfixStackTop] = x;   //연산자 스택 push
}

char postfixPop()
{
	char x;
	if (postfixStackTop == -1)
		return '\0';
	else {
		x = postfixStack[postfixStackTop--];
	}
	return x;
}  /*연산자 스택 pop*/


void evalPush(int x)
{
	evalStack[++evalStackTop] = x;
}/*결과값 스택 push*/

int evalPop()
{
	if (evalStackTop == -1)
		return -1;
	else
		return evalStack[evalStackTop--];
}/*결과값 스택 pop*/


/**
 * infix expression을 입력받는다
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
	printf("Type the expression >>> ");
	scanf("%s", infixExp);
}

precedence getToken(char symbol)
{
	switch (symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	default: return operand;
	}
	/*symbol의 모양에 따라 우선순위 부여*/
}

precedence getPriority(char x)
{
	return getToken(x);  //우선순위 부여 함수, getToken()호출
}

/**
 * 문자 하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자 하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while (*exp != '\0')
	{
		precedence token = getPriority(*exp);  //현재 글자로부터 토큰 받기
		if (token == operand)
			charCat(exp); //토큰이 문자면 그대로 postfixEXP에 출력
		else if (token == lparen)
			postfixPush(*exp);//( 이면 postixEXP에 출력 
		else if (token == rparen) {
			/* 왼쪽 괄호가 나올 때까지 토큰 제거 및 출력 */
			while (postfixStack[postfixStackTop] != lparen) {
				charCat(&postfixStack[postfixStackTop]);
				postfixPop();
				postfixPop(); //최종결과에서 ( 삭제하기 위함

			}
			postfixPop(); /* 왼쪽 괄호 버림 */
		}

		else if (token > getToken(postfixStack[postfixStackTop]))
			postfixPush(*exp);  //최상위노드 값의 토큰이 입력토큰보다 작으면 입력토큰이 연산자스택에 push
		else if (token == getToken(postfixStack[postfixStackTop])) {
			charCat(exp);  //같은연산자가 있으면 pop & push 이므로 간단히 씀
		}
		exp++;
	}
	while (postfixStackTop != -1) {
		charCat(&postfixStack[postfixStackTop]);
		postfixPop();  //연산자 순서에 맞게 출력
	}

}
void debug()   //스택 상태 나타내기
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for (int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()  //스택 리셋 함수
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for (int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}//모든 스택을 초기값으로 되돌려놓음

void evaluation()  //후위표기식을 계산
{
	char *exp = postfixExp; //후위표기식이 들어있는 문자열 가리키기
	int len = strlen(postfixExp);  //후위표기식 길이 재기
	int x, y;   //evaluation()함수에 쓰일 피연산자

	for (int i = 0; i < len; i++) {  
		precedence token = getToken(*exp);  //한글자마다 토큰부여
		if (token == operand)
			evalPush(*exp-'0');  //피연산자를 정수로 만들기 위함
		else {
			/* 토큰이 연산자이면
			   evalStack (피연산자들의 모임) 에 있던 수를 꺼내 연산자 토큰에 맞게 연산   */
			x = evalPop();   
			y = evalPop();
			if (token == plus) evalPush(x + y);
			else if (token == minus) evalPush(x - y);
			else if (token == times) evalPush(x*y);
			else if (token == divide) evalPush(x / y);
		}
		exp++;
	}
	evalResult = evalPop();  //최종 연산 결과 도출
}


int main()
{
	printf("------[Software department]   [2019038032]   [Jinseo Lee]------\n");
	char command;

	do {/*입력 안내 메뉴창 출력*/
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);  //메뉴 입력

		switch (command) {
		case 'i': case 'I':
			getInfix();      //중위 표기식 연산식 입력받기
			break;
		case 'p': case 'P':
			toPostfix();    //후위 표기식으로 바꾸기
			break;
		case 'e': case 'E':
			evaluation();   //후위 표기식으로 바꾼 식을 계산하기
			break;
		case 'd': case 'D':
			debug();        //모든 상태 나타내기 (중위 식, 후위 식, 결과값 등)
			break;
		case 'r': case 'R':
			reset();        //모든 값 초기화
			break;
		case 'q': case 'Q':
			return 0;       //프로그램 종료
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 0;


}