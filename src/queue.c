/* ============================================================
   queue.c
   Array-based circular Queue (FIFO) that holds pending loan
   requests - they must be processed strictly in the order
   they were received.
   ============================================================ */

#include <stdio.h>
#include "bank.h"

void initQueue(LoanQueue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

int isQueueFull(LoanQueue *q) {
    return q->count == MAX_QUEUE;
}

int isQueueEmpty(LoanQueue *q) {
    return q->count == 0;
}

/* ------------------------------------------------------------
   enqueueLoanRequest
   Adds a new loan request at the rear of the queue.
   Time Complexity: O(1)
   ------------------------------------------------------------ */
void enqueueLoanRequest(LoanQueue *q, LoanRequest r) {
    if (isQueueFull(q)) {
        printf("Loan request queue is full.\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE;
    q->items[q->rear] = r;
    q->count++;
}

/* ------------------------------------------------------------
   dequeueLoanRequest
   Removes and returns the request that has been waiting the
   longest (FIFO order). Returns 1 on success, 0 if empty.
   Time Complexity: O(1)
   ------------------------------------------------------------ */
int dequeueLoanRequest(LoanQueue *q, LoanRequest *r) {
    if (isQueueEmpty(q)) {
        return 0;
    }
    *r = q->items[q->front];
    q->front = (q->front + 1) % MAX_QUEUE;
    q->count--;
    return 1;
}
