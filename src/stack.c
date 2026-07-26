/* ============================================================
   stack.c
   Array-based Stack (LIFO) that records recent transactions
   (Deposit / Withdraw) so the last operation can be undone.
   ============================================================ */

#include <stdio.h>
#include "bank.h"

/* ------------------------------------------------------------
   initStack
   Prepares an empty stack.
   ------------------------------------------------------------ */
void initStack(TransactionStack *s) {
    s->top = -1;
}

int isStackFull(TransactionStack *s) {
    return s->top == MAX_TXN - 1;
}

int isStackEmpty(TransactionStack *s) {
    return s->top == -1;
}

/* ------------------------------------------------------------
   pushTransaction
   Records a new transaction. If the stack is full, the oldest
   record is simply not kept (only recent history matters here).
   Time Complexity: O(1)
   ------------------------------------------------------------ */
void pushTransaction(TransactionStack *s, Transaction t) {
    if (isStackFull(s)) {
        printf("(Transaction history full - oldest record will not be kept)\n");
        return;
    }
    s->top++;
    s->items[s->top] = t;
}

/* ------------------------------------------------------------
   popTransaction
   Removes and returns the most recent transaction.
   Returns 1 on success, 0 if the stack was empty.
   Time Complexity: O(1)
   ------------------------------------------------------------ */
int popTransaction(TransactionStack *s, Transaction *t) {
    if (isStackEmpty(s)) {
        return 0;
    }
    *t = s->items[s->top];
    s->top--;
    return 1;
}
