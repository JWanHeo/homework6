/** 
 * postfix.c
 *
 * School of Computer Science, 
 * Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence; // enum 타입 precedence 정의

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixPush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	char command;

	printf("[----- 허제완 2020069031 -----]\n\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
			case 'i': case 'I':
				getInfix();
				break;
			case 'p': case 'P':
				toPostfix();
				break;
			case 'e': case 'E':
				evaluation();
				break;
			case 'd': case 'D':
				debug();
				break;
			case 'r': case 'R':
				reset();
				break;
			case 'q': case 'Q':
				break;
			default:
				printf("\n       >>>>>   Concentration!!   <<<<<     \n");
				break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

/**
 * 문자 x를 매개변수로 받아 postStack에 저장
*/
void postfixPush(char x)
{
  postfixStack[++postfixStackTop] = x; // postfixStackTop을 1 증가시키고 그 위치에 x 저장
}

/**
 * postfixStack의 요소를 pop
*/
char postfixPop()
{
	char x;
	if(postfixStackTop == -1) // postfixTop이 -1인지 확인(스택이 비어있는 지 확인)
		return '\0'; // 비어있으면 '\0' 반환
	else {
		x = postfixStack[postfixStackTop--]; // 비어있지 않으면 postfixStackTop이 가리키는 요소로 x를 초기화하고 postfixStackTop을 -1 만큼 이동
	}
	return x; // x 반환
}

/**
 * 문자 x를 매개변수로 받아 evalStack에 저장
*/
void evalPush(int x)
{
	evalStack[++evalStackTop] = x; // // evalStackTop을 1 증가시키고 그 위치에 x 저장
}

/**
 * evalStack의 요소를 pop
*/
int evalPop()
{
	if(evalStackTop == -1) // evalStackTop이 -1인지 확인(evalStack이 비어있는 지 확인)
		return -1; // 비어있으면 -1 반환
	else
		return evalStack[evalStackTop--]; // 비어있지 않으면 evalStackTop이 가리키는 요소를 반환하고 evalStackTop을 -1 만큼 이동
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
	printf("Type the expression >>> ");
	scanf("%s",infixExp);
}

/**
 * symbol문자를 매개변수로 받아서 precedence로 변환
*/
precedence getToken(char symbol)
{
	switch(symbol) {
		case '(' : return lparen; // '('이면 lparen 반환
		case ')' : return rparen; // ')'이면 rparen 반환
		case '+' : return plus; // '+'이면 plus 반환
		case '-' : return minus; // '-'이면 minus 반환
		case '/' : return divide; // '/'이면 devide 반환
		case '*' : return times; // '*'이면 times 반환
		default : return operand; // 위의 케이스에 해당하지 않으면 operand 반환
	}
}

/**
 * 문자 x를 매개변수로 받아 x의 우선순위 반환
*/
precedence getPriority(char x)
{
	return getToken(x); // getToken을 호출하여 x의 우선순위 반환
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0') // postfixExp가 '\0'인지 검사(비어있는 지 검사)
		strncpy(postfixExp, c, 1); // '\0'이면 postfixExp에 매개변수로 받은 문자 c를 저장
	else
		strncat(postfixExp, c, 1); // '\0'이 아니면 postfixExp 뒤에 c를 이어붙이기
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')	{
		/* 필요한 로직 완성 */
		if(getToken(*exp) == operand) { // exp가 가리키는 문자가 피연산자인지 확인
			charCat(exp); // 피연산자인 경우 postfixExp에 추가
		}
		else if(getToken(*exp) == lparen) { // exp가 가리키는 문자가 '('인지 확인
			postfixPush(*exp); // '('이면 postfixStack에 push
			
			exp++; // '(' 중복을 방지하기 위해 exp++ 수행		
			
			while(getToken(*exp) != rparen) { // exp가 가리키는 문자가 ')'일 때까지 반복
				if(getToken(*exp) == operand) { 
					charCat(exp);	// exp가 가리키는 문자가 피연산자이면 postfixExp에 추가
				} else { // 피연산자가 아닌 경우
					if(getPriority(*exp) <= getPriority(postfixStack[postfixStackTop])) { // exp가 가리키는 연산자가 postfixStackTop이 가리키는 연산자보다 우선순위가 낮거나 같은 경우
						x = postfixPop(); // postfixStackTop이 가리키는 연산자를 pop하여 x에 저장
						charCat(&x); // x를 postfixExp에 추가
						postfixPush(*exp); // exp가 가리키는 연산자를 postfixStack에 push
					} else {
						postfixPush(*exp); // exp가 가리키는 연산자가 postfixStackTop이 가리키는 연산자보다 우선순위가 높은 경우 postfixStack에 push
					}
				}
				exp++;
			}

			while(postfixStack[postfixStackTop] != '(')
			{
				x = postfixPop(); // postfixStackTop이 가리키는 연산자를 pop하여 x에 저장
				charCat(&x); // x를 postfixExp에 추가
			}

			x = postfixPop(); // '('를 postfixStack에서 pop
		}
		else { // exp가 가리키는 문자가 피연산자도 아니고, '('도 아닌 경우
			if(getPriority(*exp) <= getPriority(postfixStack[postfixStackTop])) { // exp가 가리키는 연산자가 postfixStackTop이 가리키는 연산자보다 우선순위가 낮거나 같은 경우
				x = postfixPop(); // postfixStackTop이 가리키는 연산자를 pop하여 x에 저장
				charCat(&x); // x를 postfixExp에 추가
				postfixPush(*exp); // exp가 가리키는 연산자를 postfixStack에 push
			} else {
				postfixPush(*exp);
			}
		}
		exp++;
	}

	/* 필요한 로직 완성 */
	while (postfixStackTop != -1)
	{
		x = postfixPop(); // postfixStackTop이 가리키는 연산자를 pop하여 x에 저장
		charCat(&x); // x를 postfixExp에 추가
	}

}

void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp); // infixExp에 들어있는 문자열 출력
	printf("postExp =  %s\n", postfixExp); // postfixExp에 들어있는 문자열 출력
	printf("eval result = %d\n", evalResult); // evaluation 연산 수행 결과 출력

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]); // postfixStack을 순회하며 각 요소를 출력

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0'; // infixExp의 첫번째 요소를 '\0'으로 초기화
	postfixExp[0] = '\0'; // postfixExp의 첫번째 요소를 '\0'으로 초기화

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0'; // postfixStack을 순회하며 각 요소를 '\0'으로 초기화
         
	postfixStackTop = -1; // postfixStackTop을 -1로 초기화
	evalStackTop = -1; // evalStackTop을 -1로 초기화
	evalResult = 0; // evalResult을 0으로 초기화
}

/**
 * postfix로 변환된 식을 연산
*/
void evaluation()
{
	/* postfixExp, evalStack을 이용한 계산 */
	char *exp = postfixExp;

	while (*exp != '\0') { // 문자열의 끝('\0')이 나올 떄까지 반복
		if (getToken(*exp) == operand) { // exp가 가리키는 요소가 operand인지 확인
			evalPush(*exp - '0'); // operand이면 char를 int로 변환하여 evalStack에 push
		}	else {
			int operand2 = evalPop(); // operand가 아니면 evalStack에서 요소를 하나 꺼내서 operand1에 저장
			int operand1 = evalPop(); // operand가 아니면 evalStack에서 요소를 하나 꺼내서 operand2에 저장
			switch (*exp) {
				case '+':
					evalPush(operand1 + operand2); // exp가 가리키는 요소가 +이면 두 operand를 더해서 evalStack에 push
					break;
				case '-':
					evalPush(operand1 - operand2); // exp가 가리키는 요소가 -이면 두 operand를 빼서 evalStack에 push
					break;
				case '*':
					evalPush(operand1 * operand2); // exp가 가리키는 요소가 *이면 두 operand를 곱해서 evalStack에 push
					break;
				case '/':
					if(operand2 == 0) {
						printf("0으로 나눌 수 없습니다.");
						exit(1);
					}
					evalPush(operand1 / operand2); // exp가 가리키는 요소가 /이면 두 operand를 나눠서 evalStack에 push
					break;
			}
		}
		exp++;
	}
	evalResult = evalPop(); // evalStack의 가장 마지막 요소를 pop하여 evalResult에 저장
}

