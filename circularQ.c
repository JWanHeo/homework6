/**
 * circularQ.c
 *
 * School of Computer Science, 
 * Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element; // char�� element Ÿ�� ����
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType; // element Ÿ���� ����� 4�� �迭 queue�� int�� front�� rear�� ��������� ������ ����ü QueueType ����


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

	printf("[----- ������ 2020069031 -----]\n\n");

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

QueueType *createQueue() // ��ȯ���� QueueType �������� createQueue �Լ� ����
{
	QueueType *cQ; // QueueType ������ cQ ����
	cQ = (QueueType *)malloc(sizeof(QueueType)); // cQ�� QueueType�� ������(16byte)��ŭ�� �޸𸮸� ���� �Ҵ�
	cQ->front = 0; // cQ�� front ���� 0���� �ʱ�ȭ
	cQ->rear = 0; // cQ�� rear ���� 0���� �ʱ�ȭ
	return cQ; // cQ ��ȯ
}

int freeQueue(QueueType *cQ) // ��ȯ���� int�̰�, QueueType ������ cQ�� �Ű������� �޴� freeQueue�Լ� ����
{
    if(cQ == NULL) return 1; // cQ null pointer�̸� 1 ��ȯ�ϸ� �Լ� ����
    free(cQ); // cQ�� �Ҵ�� �޸� ����
    return 1; // 1 ��ȯ
}

element getElement() // ��ȯ���� element�̰�, �Ű������� ���� getElement�Լ� ����
{
	element item; // element Ÿ���� item ���� ����
	printf("Input element = "); 
	scanf(" %c", &item); // item �Է�
	return item; // item ��ȯ
}


/* complete the function */
int isEmpty(QueueType *cQ) // ��ȯ���� int�̰�, QueueType ������ cQ�� �Ű������� �޴� isEmpty�Լ� ����
{
	if(cQ->front == cQ->rear) return 0; // cQ�� front�� rear�� ���� �ε����� ����Ű�� 0 ��ȯ

  return 1; // �ƴϸ� 1 ��ȯ
}

/* complete the function */
int isFull(QueueType *cQ) // ��ȯ���� int�̰�, QueueType ������ cQ�� �Ű������� �޴� isFull�Լ� ����
{
	int nextRear;
	if(cQ->rear == MAX_QUEUE_SIZE - 1) {
		nextRear = 0;
	} else {
		nextRear = cQ->rear + 1;
	}
	if(nextRear == cQ->front) return 0; // cQ�� front�� rear�� ���� 1�̸� 0 ��ȯ

	return 1; // �ƴϸ� 1 ��ȯ
}


/* complete the function */
void enQueue(QueueType *cQ, element item) // ��ȯ���� void�̰�, QueueType ������ cQ�� element Ÿ�� item�� �Ű������� �޴� enQueue�Լ� ����
{
	if(isFull(cQ) == 0) { // ť�� �� á���� �˻�
		printf("ť�� �� á���ϴ�.");		
	} else {
		if(cQ->rear == MAX_QUEUE_SIZE - 1) { // �� ���� ���� ���, rear�� ���� MAX_QUEUE_SIZE-1(== 3)���� �˻�
			cQ->rear = 0; // MAX_QUEUE_SIZE�� ��� 0���� �ʱ�ȭ
		} else {
			cQ->rear++; // �ƴ� ��� rear + 1
		}
		cQ->queue[cQ->rear] = item; // rear�� item ����
	}
}

/* complete the function */
void deQueue(QueueType *cQ, element *item) // ��ȯ���� void�̰�, QueueType ������ cQ�� element ������ item�� �Ű������� �޴� deQueue�Լ� ����
{
	if(isEmpty(cQ) == 0) { // ť�� ����ִ� �� �˻�
		printf("ť�� ����ֽ��ϴ�.");
	} else {
		if(cQ->front == MAX_QUEUE_SIZE - 1) { // �ƴ� ��� cQ�� front���� MAX_QUEUE_SIZE�� ������ �� �˻�
			cQ->front = 0; // ������ ��� front�� 0���� �ʱ�ȭ
		} else {
			cQ->front++; // �ƴ� ��� front + 1
		}
		item = NULL; // item�� NULL pointer�� �ٲٱ�
	}
}


void printQ(QueueType *cQ) // ��ȯ���� void�̰�, QueueType ������ cQ�� �Ű������� �޴� printQ�Լ� ����
{
	int i, first, last; // int�� ���� i, first, last ���� ����

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; // first�� cQ�� front+1�� MAX_QUEUE_SIZE�� ���� �������� �ʱ�ȭ
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; // last�� cQ�� rear+1�� MAX_QUEUE_SIZE�� ���� �������� �ʱ�ȭ

	printf("Circular Queue : [");

	i = first; // i�� first�� �ʱ�ȭ
	while(i != last){ // i�� last�� �������� ���� �� ���� �˻�
		printf("%3c", cQ->queue[i]); // �������� ���� ��� cQ�� queue�� i��° ��� ���
		i = (i+1)%MAX_QUEUE_SIZE; // i�� (i+1)�� MAX_QUEUE_SIZE�� ���� �������� �ʱ�ȭ
	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ) // ��ȯ���� void�̰�, QueueType ������ cQ�� �Ű������� �޴� debugQ�Լ� ����
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++) // �ݺ����� i�� �ʱ갪�� 0�̰�, �ִ밡 MAX_QUEUE_SIZE-1�� �ݺ���
	{
		if(i == cQ->front) { // i�� ���� cQ�� front�� �������� Ȯ��
			printf("  [%d] = front\n", i); // ������ ��� "i�� �� = front" ���
			continue; // ���� �ݺ����� �Ѿ��
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); // i�� ���� cQ�� front�� �������� ���� ���, "[i�� ��] = cQ�� queue[i]�� ��" ���

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); // front�� rear�� �� ���
}


