#include <type.h>
#include <timer.h>
#include <led.h>
#include <scheduler.h>

void task1_start() {
	while (1) {
		for (int i = 0; i < 2; i++) {
			ledOn();
			spinMilli(300);
			ledOff();
			spinMilli(200);
		}
		yield();
	}
}

void task2_start() {
	while (1) {
		for (int i = 0; i < 3; i++) {
			ledOn();
			spinMilli(100);
			ledOff();
			spinMilli(200);
		}
		yield();
	}
}

struct Task {
	uint32 r[13];
	uint32 sp;
	uint32 lr;
	uint32 pc;
	uint32 cpsr;
};

struct TaskQueueNode {
	struct Task task;
	struct TaskQueueNode* next;
};

struct TaskQueueNode queueNode1;
struct TaskQueueNode queueNode2;

struct TaskQueueNode* queue;
struct TaskQueueNode* queueEnd;

void initTask(struct Task* task, void* sp, void (*start)()) {
	for (int i = 0; i <= 12; i++) {
		task->r[i] = 0;
	}
	task->sp = (uint32) sp;
	task->lr = 0; // where to return?
	task->pc = (uint32) start;
	task->cpsr = 0x10 // USR mode
		| 0x40 // F bit
		| 0x80 // I bit
		| 0x100; // A bit
		// E bit is 0x200, not sure if set...
}

extern void* stack1;
extern void* stack2;

void initTaskQueue() {
	initTask(&(queueNode1.task), stack1, &task1_start);
	queueNode1.next = &queueNode2;
	initTask(&(queueNode2.task), stack2, &task2_start);
	queueNode2.next = NULL;
	queue = &queueNode1;
	queueEnd = &queueNode2;
}

void rotateTaskQueue() {
	queueEnd->next = queue;
	queueEnd = queue;
	queue = queue->next;
	queueEnd->next = NULL;
}

struct Task* getCurrentTask() {
	return &(queue->task);
}

void runTask(struct Task* task);

void startScheduler() {
	initTaskQueue();
	runTask(&(queue->task));
}

void runNextTask() {
	rotateTaskQueue();
	runTask(&(queue->task));
}
