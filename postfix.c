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

/* stack ������ �켱����, lparen = 0 ���� ���� */
typedef enum{
	lparen = 0,  /* ( ���� ��ȣ */
	rparen = 9,  /* ) ������ ��ȣ*/
	times = 7,   /* * ���� */
	divide = 6,  /* / ������ */
	plus = 5,    /* + ���� */
	minus = 4,   /* - ���� */
	operand = 1 /* �ǿ����� */
} precedence; // enum Ÿ�� precedence ����

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression�� �����ϴ� �迭 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix�� ����� ���ڿ��� �����ϴ� �迭 */
char postfixStack[MAX_STACK_SIZE];	/* postfix�� ��ȯ�� ���� �ʿ��� ���� */
int evalStack[MAX_STACK_SIZE];		/* ����� ���� �ʿ��� ���� */

int postfixStackTop = -1;  /* postfixStack�� top */
int evalStackTop = -1;	   /* evalStack�� top */

int evalResult = 0;	   /* ��� ����� ���� */

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

	printf("[----- ������ 2020069031 -----]\n\n");

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
 * ���� x�� �Ű������� �޾� postStack�� ����
*/
void postfixPush(char x)
{
  postfixStack[++postfixStackTop] = x; // postfixStackTop�� 1 ������Ű�� �� ��ġ�� x ����
}

/**
 * postfixStack�� ��Ҹ� pop
*/
char postfixPop()
{
	char x;
	if(postfixStackTop == -1) // postfixTop�� -1���� Ȯ��(������ ����ִ� �� Ȯ��)
		return '\0'; // ��������� '\0' ��ȯ
	else {
		x = postfixStack[postfixStackTop--]; // ������� ������ postfixStackTop�� ����Ű�� ��ҷ� x�� �ʱ�ȭ�ϰ� postfixStackTop�� -1 ��ŭ �̵�
	}
	return x; // x ��ȯ
}

/**
 * ���� x�� �Ű������� �޾� evalStack�� ����
*/
void evalPush(int x)
{
	evalStack[++evalStackTop] = x; // // evalStackTop�� 1 ������Ű�� �� ��ġ�� x ����
}

/**
 * evalStack�� ��Ҹ� pop
*/
int evalPop()
{
	if(evalStackTop == -1) // evalStackTop�� -1���� Ȯ��(evalStack�� ����ִ� �� Ȯ��)
		return -1; // ��������� -1 ��ȯ
	else
		return evalStack[evalStackTop--]; // ������� ������ evalStackTop�� ����Ű�� ��Ҹ� ��ȯ�ϰ� evalStackTop�� -1 ��ŭ �̵�
}

/**
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
 */
void getInfix()
{
	printf("Type the expression >>> ");
	scanf("%s",infixExp);
}

/**
 * symbol���ڸ� �Ű������� �޾Ƽ� precedence�� ��ȯ
*/
precedence getToken(char symbol)
{
	switch(symbol) {
		case '(' : return lparen; // '('�̸� lparen ��ȯ
		case ')' : return rparen; // ')'�̸� rparen ��ȯ
		case '+' : return plus; // '+'�̸� plus ��ȯ
		case '-' : return minus; // '-'�̸� minus ��ȯ
		case '/' : return divide; // '/'�̸� devide ��ȯ
		case '*' : return times; // '*'�̸� times ��ȯ
		default : return operand; // ���� ���̽��� �ش����� ������ operand ��ȯ
	}
}

/**
 * ���� x�� �Ű������� �޾� x�� �켱���� ��ȯ
*/
precedence getPriority(char x)
{
	return getToken(x); // getToken�� ȣ���Ͽ� x�� �켱���� ��ȯ
}

/**
 * �����ϳ��� ���޹޾�, postfixExp�� �߰�
 */
void charCat(char* c)
{
	if (postfixExp == '\0') // postfixExp�� '\0'���� �˻�(����ִ� �� �˻�)
		strncpy(postfixExp, c, 1); // '\0'�̸� postfixExp�� �Ű������� ���� ���� c�� ����
	else
		strncat(postfixExp, c, 1); // '\0'�� �ƴϸ� postfixExp �ڿ� c�� �̾���̱�
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix()
{
	/* infixExp�� ���� �ϳ����� �б����� ������ */
	char *exp = infixExp;
	char x; /* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */

	/* exp�� �������Ѱ��鼭, ���ڸ� �а� postfix�� ���� */
	while(*exp != '\0')	{
		/* �ʿ��� ���� �ϼ� */
		if(getToken(*exp) == operand) { // exp�� ����Ű�� ���ڰ� �ǿ��������� Ȯ��
			charCat(exp); // �ǿ������� ��� postfixExp�� �߰�
		}
		else if(getToken(*exp) == lparen) { // exp�� ����Ű�� ���ڰ� '('���� Ȯ��
			postfixPush(*exp); // '('�̸� postfixStack�� push
			
			exp++; // '(' �ߺ��� �����ϱ� ���� exp++ ����		
			
			while(getToken(*exp) != rparen) { // exp�� ����Ű�� ���ڰ� ')'�� ������ �ݺ�
				if(getToken(*exp) == operand) { 
					charCat(exp);	// exp�� ����Ű�� ���ڰ� �ǿ������̸� postfixExp�� �߰�
				} else { // �ǿ����ڰ� �ƴ� ���
					if(getPriority(*exp) <= getPriority(postfixStack[postfixStackTop])) { // exp�� ����Ű�� �����ڰ� postfixStackTop�� ����Ű�� �����ں��� �켱������ ���ų� ���� ���
						x = postfixPop(); // postfixStackTop�� ����Ű�� �����ڸ� pop�Ͽ� x�� ����
						charCat(&x); // x�� postfixExp�� �߰�
						postfixPush(*exp); // exp�� ����Ű�� �����ڸ� postfixStack�� push
					} else {
						postfixPush(*exp); // exp�� ����Ű�� �����ڰ� postfixStackTop�� ����Ű�� �����ں��� �켱������ ���� ��� postfixStack�� push
					}
				}
				exp++;
			}

			while(postfixStack[postfixStackTop] != '(')
			{
				x = postfixPop(); // postfixStackTop�� ����Ű�� �����ڸ� pop�Ͽ� x�� ����
				charCat(&x); // x�� postfixExp�� �߰�
			}

			x = postfixPop(); // '('�� postfixStack���� pop
		}
		else { // exp�� ����Ű�� ���ڰ� �ǿ����ڵ� �ƴϰ�, '('�� �ƴ� ���
			if(getPriority(*exp) <= getPriority(postfixStack[postfixStackTop])) { // exp�� ����Ű�� �����ڰ� postfixStackTop�� ����Ű�� �����ں��� �켱������ ���ų� ���� ���
				x = postfixPop(); // postfixStackTop�� ����Ű�� �����ڸ� pop�Ͽ� x�� ����
				charCat(&x); // x�� postfixExp�� �߰�
				postfixPush(*exp); // exp�� ����Ű�� �����ڸ� postfixStack�� push
			} else {
				postfixPush(*exp);
			}
		}
		exp++;
	}

	/* �ʿ��� ���� �ϼ� */
	while (postfixStackTop != -1)
	{
		x = postfixPop(); // postfixStackTop�� ����Ű�� �����ڸ� pop�Ͽ� x�� ����
		charCat(&x); // x�� postfixExp�� �߰�
	}

}

void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp); // infixExp�� ����ִ� ���ڿ� ���
	printf("postExp =  %s\n", postfixExp); // postfixExp�� ����ִ� ���ڿ� ���
	printf("eval result = %d\n", evalResult); // evaluation ���� ���� ��� ���

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]); // postfixStack�� ��ȸ�ϸ� �� ��Ҹ� ���

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0'; // infixExp�� ù��° ��Ҹ� '\0'���� �ʱ�ȭ
	postfixExp[0] = '\0'; // postfixExp�� ù��° ��Ҹ� '\0'���� �ʱ�ȭ

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0'; // postfixStack�� ��ȸ�ϸ� �� ��Ҹ� '\0'���� �ʱ�ȭ
         
	postfixStackTop = -1; // postfixStackTop�� -1�� �ʱ�ȭ
	evalStackTop = -1; // evalStackTop�� -1�� �ʱ�ȭ
	evalResult = 0; // evalResult�� 0���� �ʱ�ȭ
}

/**
 * postfix�� ��ȯ�� ���� ����
*/
void evaluation()
{
	/* postfixExp, evalStack�� �̿��� ��� */
	char *exp = postfixExp;

	while (*exp != '\0') { // ���ڿ��� ��('\0')�� ���� ������ �ݺ�
		if (getToken(*exp) == operand) { // exp�� ����Ű�� ��Ұ� operand���� Ȯ��
			evalPush(*exp - '0'); // operand�̸� char�� int�� ��ȯ�Ͽ� evalStack�� push
		}	else {
			int operand2 = evalPop(); // operand�� �ƴϸ� evalStack���� ��Ҹ� �ϳ� ������ operand1�� ����
			int operand1 = evalPop(); // operand�� �ƴϸ� evalStack���� ��Ҹ� �ϳ� ������ operand2�� ����
			switch (*exp) {
				case '+':
					evalPush(operand1 + operand2); // exp�� ����Ű�� ��Ұ� +�̸� �� operand�� ���ؼ� evalStack�� push
					break;
				case '-':
					evalPush(operand1 - operand2); // exp�� ����Ű�� ��Ұ� -�̸� �� operand�� ���� evalStack�� push
					break;
				case '*':
					evalPush(operand1 * operand2); // exp�� ����Ű�� ��Ұ� *�̸� �� operand�� ���ؼ� evalStack�� push
					break;
				case '/':
					if(operand2 == 0) {
						printf("0���� ���� �� �����ϴ�.");
						exit(1);
					}
					evalPush(operand1 / operand2); // exp�� ����Ű�� ��Ұ� /�̸� �� operand�� ������ evalStack�� push
					break;
			}
		}
		exp++;
	}
	evalResult = evalPop(); // evalStack�� ���� ������ ��Ҹ� pop�Ͽ� evalResult�� ����
}

