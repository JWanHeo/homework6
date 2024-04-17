/**
 * circularQ.c
 *
 * School of Computer Science, 
 * Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element; // char형 element 타입 정의
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType; // element 타입의 사이즈가 4인 배열 queue와 int형 front와 rear를 멤버변수로 가지는 구조체 QueueType 정의


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
	QueueType *cQ = createQueue();
	element data;
	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue() // 반환형이 QueueType 포인터인 createQueue 함수 정의
{
	QueueType *cQ; // QueueType 포인터 cQ 선언
	cQ = (QueueType *)malloc(sizeof(QueueType)); // cQ에 QueueType의 사이즈(16byte)만큼의 메모리를 동적 할당
	cQ->front = 0; // cQ의 front 값을 0으로 초기화
	cQ->rear = 0; // cQ의 rear 값을 0으로 초기화
	return cQ; // cQ 반환
}

int freeQueue(QueueType *cQ) // 반환형이 int이고, QueueType 포인터 cQ를 매개변수로 받는 freeQueue함수 정의
{
    if(cQ == NULL) return 1; // cQ null pointer이면 1 반환하며 함수 종료
    free(cQ); // cQ에 할당된 메모리 해제
    return 1; // 1 반환
}

element getElement()
{
	element item; // element 타입의 item 변수 선언
	printf("Input element = "); 
	scanf(" %c", &item); // item 입력
	return item; // item 반환
}


/* complete the function */
int isEmpty(QueueType *cQ)
{

    return 0;
}

/* complete the function */
int isFull(QueueType *cQ)
{
   return 0;
}


/* complete the function */
void enQueue(QueueType *cQ, element item)
{
	return 0;
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)
{
    return 0;
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}


