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
void deQueue(QueueType *cQ, element *item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
	QueueType *cQ = createQueue();
	element data;
	char command;

	printf("[----- 허제완 2020069031 -----]\n\n");

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

element getElement() // 반환형이 element이고, 매개변수가 없는 getElement함수 정의
{
	element item; // element 타입의 item 변수 선언
	printf("Input element = "); 
	scanf(" %c", &item); // item 입력
	return item; // item 반환
}


/* complete the function */
int isEmpty(QueueType *cQ) // 반환형이 int이고, QueueType 포인터 cQ를 매개변수로 받는 isEmpty함수 정의
{
	if(cQ->front == cQ->rear) return 0; // cQ의 front와 rear가 같은 인덱스를 가리키면 0 반환

  return 1; // 아니면 1 반환
}

/* complete the function */
int isFull(QueueType *cQ) // 반환형이 int이고, QueueType 포인터 cQ를 매개변수로 받는 isFull함수 정의
{
	int nextRear;
	if(cQ->rear == MAX_QUEUE_SIZE - 1) {
		nextRear = 0;
	} else {
		nextRear = cQ->rear + 1;
	}
	if(nextRear == cQ->front) return 0; // cQ의 front와 rear의 차가 1이면 0 반환

	return 1; // 아니면 1 반환
}


/* complete the function */
void enQueue(QueueType *cQ, element item) // 반환형이 void이고, QueueType 포인터 cQ와 element 타입 item을 매개변수로 받는 enQueue함수 정의
{
	if(isFull(cQ) == 0) { // 큐가 꽉 찼는지 검사
		printf("큐가 꽉 찼습니다.");		
	} else {
		if(cQ->rear == MAX_QUEUE_SIZE - 1) { // 꽉 차지 않은 경우, rear의 값이 MAX_QUEUE_SIZE-1(== 3)인지 검사
			cQ->rear = 0; // MAX_QUEUE_SIZE인 경우 0으로 초기화
		} else {
			cQ->rear++; // 아닌 경우 rear + 1
		}
		cQ->queue[cQ->rear] = item; // rear에 item 저장
	}
}

/* complete the function */
void deQueue(QueueType *cQ, element *item) // 반환형이 void이고, QueueType 포인터 cQ와 element 포인터 item을 매개변수로 받는 deQueue함수 정의
{
	if(isEmpty(cQ) == 0) { // 큐가 비어있는 지 검사
		printf("큐가 비어있습니다.");
	} else {
		if(cQ->front == MAX_QUEUE_SIZE - 1) { // 아닌 경우 cQ의 front값이 MAX_QUEUE_SIZE와 동일한 지 검사
			cQ->front = 0; // 동일한 경우 front를 0으로 초기화
		} else {
			cQ->front++; // 아닌 경우 front + 1
		}
		item = NULL; // item을 NULL pointer로 바꾸기
	}
}


void printQ(QueueType *cQ) // 반환형이 void이고, QueueType 포인터 cQ를 매개변수로 받는 printQ함수 정의
{
	int i, first, last; // int형 변수 i, first, last 변수 선언

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; // first를 cQ의 front+1을 MAX_QUEUE_SIZE로 나눈 나머지로 초기화
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; // last를 cQ의 rear+1을 MAX_QUEUE_SIZE로 나눈 나머지로 초기화

	printf("Circular Queue : [");

	i = first; // i를 first로 초기화
	while(i != last){ // i와 last가 동일하지 않은 지 조건 검사
		printf("%3c", cQ->queue[i]); // 동일하지 않은 경우 cQ의 queue의 i번째 요소 출력
		i = (i+1)%MAX_QUEUE_SIZE; // i를 (i+1)를 MAX_QUEUE_SIZE로 나눈 나머지로 초기화
	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ) // 반환형이 void이고, QueueType 포인터 cQ를 매개변수로 받는 debugQ함수 정의
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++) // 반복변수 i의 초깃값이 0이고, 최대가 MAX_QUEUE_SIZE-1인 반복문
	{
		if(i == cQ->front) { // i의 값이 cQ의 front와 동일한지 확인
			printf("  [%d] = front\n", i); // 동일한 경우 "i의 값 = front" 출력
			continue; // 다음 반복으로 넘어가기
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); // i의 값이 cQ의 front와 동일하지 않은 경우, "[i의 값] = cQ의 queue[i]의 값" 출력

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); // front와 rear의 값 출력
}


