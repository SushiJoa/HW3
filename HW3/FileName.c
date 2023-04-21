#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
// ===== ����ť �ڵ� ���� ======
typedef int element;
typedef struct { // ť Ÿ��
	element* data;
	int front, rear;
	int capacity;
	int count;
} QueueType;
// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// ���� ���� ���� �Լ�
void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
	q->count = 0;
	q->capacity = 2;
	q->data = (element*)malloc(q->capacity * sizeof(element));
}
// ���� ���� ���� �Լ�
int is_empty(QueueType* q)
{
	return q->count == 0;
}
// ��ȭ ���� ���� �Լ�
int is_full(QueueType* q)
{
	return q->count == q->capacity;
}
void resize(QueueType* q)
{
	int cap_prev = q->capacity;
	q->capacity *= 2;
	q->data = (element*)realloc(q->data, q->capacity * sizeof(element));
	for (int i = q->front + 1; i <= cap_prev; i++) {
		q->data[i + cap_prev] = q->data[i];
	}
	q->front = q->front + cap_prev;
}
// ����ť ��� �Լ�
void queue_print(QueueType* q)
{
	printf("QUEUE(front=%d, rear=%d, count=%d ) = ", q->front, q->rear, q->count);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (q->capacity);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}
// ���� �Լ�
void enqueue(QueueType* q, element item)
{
	if (is_full(q)) {
		resize(q);
	}
	q->rear = (q->rear + 1) % q->capacity;
	q->data[q->rear] = item;
	q->count++;
}
// ���� �Լ�
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % q->capacity;
	return q->data[q->front];
	q->count--;
}
int main(void) {
	QueueType queue;
	int element = 10;
	init_queue(&queue);
	int n = 50;

	for (int i = 0; i < n; i++) {
		enqueue(&queue, i);
		queue_print(&queue);
	}
	queue_print(&queue);

	for (int i = 0; i < n-1; i++) {
		int value = dequeue(&queue);
		queue_print(&queue);
	}

	return 0;
}