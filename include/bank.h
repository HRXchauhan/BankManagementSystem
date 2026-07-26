/* ============================================================
   bank.h
   Bank Management System - Header File
   DSA Concepts declared here: Structures, BST, Stack, Queue

   Data structures used in this project:
     - Binary Search Tree (BST)  -> primary account storage,
       keyed by Account Number (dynamic memory, recursion)
     - Stack                     -> last N transactions, used
       to Undo the most recent Deposit/Withdraw
     - Queue                     -> pending loan requests,
       processed strictly First-In-First-Out
     - Array + Sorting/Searching -> reports (top balances,
       search by name)
   ============================================================ */

#ifndef BANK_H
#define BANK_H

#define NAME_LEN     50
#define MAX_ACCOUNTS 100     /* used for temporary arrays (sort/search) */
#define MAX_TXN      20      /* transaction stack capacity              */
#define MAX_QUEUE    20      /* loan request queue capacity             */
#define DATA_FILE    "sample-data/bank_data.txt"

/* ---------------- Structures ---------------- */

/* One bank account */
typedef struct Account {
    int   accNo;
    char  name[NAME_LEN];
    float balance;
} Account;

/* Binary Search Tree node - keyed by accNo (dynamic memory: malloc/free) */
typedef struct BSTNode {
    Account data;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

/* One recorded transaction (for the Undo stack) */
typedef struct {
    int   accNo;
    char  type[10];     /* "DEPOSIT" or "WITHDRAW" */
    float amount;
} Transaction;

/* Array-based Stack of transactions */
typedef struct {
    Transaction items[MAX_TXN];
    int top;            /* -1 means empty */
} TransactionStack;

/* One pending loan request (for the Queue) */
typedef struct {
    int   accNo;
    char  name[NAME_LEN];
    float loanAmount;
} LoanRequest;

/* Array-based circular Queue of loan requests */
typedef struct {
    LoanRequest items[MAX_QUEUE];
    int front;
    int rear;
    int count;
} LoanQueue;

/* ---------------- bst.c ---------------- */
BSTNode* insertBST(BSTNode *root, Account acc);
BSTNode* searchBST(BSTNode *root, int accNo);
BSTNode* deleteBST(BSTNode *root, int accNo, int *found);
void     inorderDisplay(BSTNode *root);
void     inorderCollect(BSTNode *root, Account arr[], int *count);
int      countAccountsRecursive(BSTNode *root);
float    sumBalanceRecursive(BSTNode *root);
void     freeBST(BSTNode *root);

/* ---------------- sort_search.c ---------------- */
void bubbleSortByBalanceDesc(Account arr[], int n);
int  linearSearchByName(Account arr[], int n, const char *name);

/* ---------------- stack.c (Transaction Undo Stack) ---------------- */
void initStack(TransactionStack *s);
int  isStackFull(TransactionStack *s);
int  isStackEmpty(TransactionStack *s);
void pushTransaction(TransactionStack *s, Transaction t);
int  popTransaction(TransactionStack *s, Transaction *t);

/* ---------------- queue.c (Loan Request Queue) ---------------- */
void initQueue(LoanQueue *q);
int  isQueueFull(LoanQueue *q);
int  isQueueEmpty(LoanQueue *q);
void enqueueLoanRequest(LoanQueue *q, LoanRequest r);
int  dequeueLoanRequest(LoanQueue *q, LoanRequest *r);

/* ---------------- file_ops.c ---------------- */
void     saveAccountsToFile(BSTNode *root);
BSTNode* loadAccountsFromFile(BSTNode *root);

#endif /* BANK_H */
