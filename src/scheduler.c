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
	void (*start)();
};

struct TaskQueueNode {
	struct Task task;
	struct TaskQueueNode* next;
};

struct TaskQueueNode queueNode1;
struct TaskQueueNode queueNode2;

struct TaskQueueNode* queue;
struct TaskQueueNode* queueEnd;

void initTaskQueue() {
	queueNode1.task.start = &task1_start;
	queueNode1.next = &queueNode2;
	queueNode2.task.start = &task2_start;
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

void runCurrentTask() {
	struct Task* currentTask = getCurrentTask();
	(currentTask->start)();
}

void startScheduler() {
	initTaskQueue();
	runCurrentTask();
}

void runNextTask() {
	rotateTaskQueue();
	runCurrentTask();
}
