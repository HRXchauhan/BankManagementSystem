/* ============================================================
   main.c
   Bank Management System
   Final Capstone Project - Data Structures & Algorithms in C

   Data Structures / Algorithms demonstrated:
     - Structures            : Account, BSTNode, Transaction, LoanRequest
     - Dynamic Memory Alloc. : malloc/free for every BST node
     - File Handling         : accounts saved to / loaded from a file
     - Searching Algorithm   : BST search (accNo) + Linear search (name)
     - Sorting Algorithm     : Bubble Sort (accounts by balance)
     - Tree (BST)            : primary account storage
     - Stack                 : undo last Deposit/Withdraw
     - Queue                 : pending loan requests (FIFO)
     - Recursion             : BST insert/search/delete/traversal,
                                account count, total balance
   ============================================================ */

#include <stdio.h>
#include <string.h>
#include "bank.h"

static void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { /* discard */ }
}

int main(void) {
    BSTNode *root = NULL;
    TransactionStack txnStack;
    LoanQueue loanQueue;
    int choice;

    initStack(&txnStack);
    initQueue(&loanQueue);

    root = loadAccountsFromFile(root);   /* restore previous session's data */

    printf("=====================================================\n");
    printf("             BANK MANAGEMENT SYSTEM\n");
    printf("=====================================================\n");

    do {
        printf("\n--------------------- MAIN MENU ---------------------\n");
        printf(" 1. Create Account\n");
        printf(" 2. Deposit\n");
        printf(" 3. Withdraw\n");
        printf(" 4. Search Account (by Account Number - BST)\n");
        printf(" 5. Search Account (by Name - Linear Search)\n");
        printf(" 6. Display All Accounts (sorted by Acc No)\n");
        printf(" 7. Top Balance Report (Bubble Sort)\n");
        printf(" 8. Delete Account\n");
        printf(" 9. Undo Last Transaction (Stack)\n");
        printf("10. Add Loan Request (Queue)\n");
        printf("11. Process Next Loan Request (Queue)\n");
        printf("12. Bank Summary (Recursion)\n");
        printf("13. Save & Exit\n");
        printf("-------------------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {

            case 1: {   /* Create Account */
                Account acc;
                printf("\n--- Create Account ---\n");
                printf("Enter Account Number : ");
                scanf("%d", &acc.accNo);
                clearInputBuffer();

                if (searchBST(root, acc.accNo) != NULL) {
                    printf("An account with this number already exists!\n");
                    break;
                }

                printf("Enter Account Holder Name : ");
                fgets(acc.name, NAME_LEN, stdin);
                acc.name[strcspn(acc.name, "\n")] = '\0';

                printf("Enter Initial Deposit : ");
                scanf("%f", &acc.balance);
                clearInputBuffer();

                if (acc.balance < 0) {
                    printf("Initial deposit cannot be negative.\n");
                    break;
                }

                root = insertBST(root, acc);
                printf("\nAccount created successfully!\n");
                break;
            }

            case 2: {   /* Deposit */
                int accNo;
                float amount;
                printf("\nEnter Account Number : ");
                scanf("%d", &accNo);

                BSTNode *node = searchBST(root, accNo);
                if (node == NULL) {
                    printf("Account not found.\n");
                    break;
                }

                printf("Enter Deposit Amount : ");
                scanf("%f", &amount);

                if (amount <= 0) {
                    printf("Amount must be positive.\n");
                    break;
                }

                node->data.balance += amount;

                Transaction t;
                t.accNo = accNo;
                strcpy(t.type, "DEPOSIT");
                t.amount = amount;
                pushTransaction(&txnStack, t);

                printf("Deposit successful. New Balance: %.2f\n", node->data.balance);
                break;
            }

            case 3: {   /* Withdraw */
                int accNo;
                float amount;
                printf("\nEnter Account Number : ");
                scanf("%d", &accNo);

                BSTNode *node = searchBST(root, accNo);
                if (node == NULL) {
                    printf("Account not found.\n");
                    break;
                }

                printf("Enter Withdrawal Amount : ");
                scanf("%f", &amount);

                if (amount <= 0 || amount > node->data.balance) {
                    printf("Invalid amount or insufficient balance.\n");
                    break;
                }

                node->data.balance -= amount;

                Transaction t;
                t.accNo = accNo;
                strcpy(t.type, "WITHDRAW");
                t.amount = amount;
                pushTransaction(&txnStack, t);

                printf("Withdrawal successful. New Balance: %.2f\n", node->data.balance);
                break;
            }

            case 4: {   /* Search by Account Number - BST */
                int accNo;
                printf("\nEnter Account Number to search: ");
                scanf("%d", &accNo);

                BSTNode *node = searchBST(root, accNo);
                if (node == NULL) {
                    printf("Account not found.\n");
                } else {
                    printf("\nAccount No : %d\n", node->data.accNo);
                    printf("Name       : %s\n", node->data.name);
                    printf("Balance    : %.2f\n", node->data.balance);
                }
                break;
            }

            case 5: {   /* Search by Name - Linear Search over an array */
                Account arr[MAX_ACCOUNTS];
                int cnt = 0;
                char name[NAME_LEN];

                inorderCollect(root, arr, &cnt);

                printf("\nEnter Name to search: ");
                fgets(name, NAME_LEN, stdin);
                name[strcspn(name, "\n")] = '\0';

                int idx = linearSearchByName(arr, cnt, name);
                if (idx == -1) {
                    printf("No account found with that name.\n");
                } else {
                    printf("\nAccount No : %d\n", arr[idx].accNo);
                    printf("Name       : %s\n", arr[idx].name);
                    printf("Balance    : %.2f\n", arr[idx].balance);
                }
                break;
            }

            case 6: {   /* Display All - inorder (sorted by Acc No) */
                printf("\n%-10s %-20s %-10s\n", "AccNo", "Name", "Balance");
                printf("----------------------------------------\n");
                if (root == NULL) {
                    printf("No accounts found.\n");
                } else {
                    inorderDisplay(root);
                }
                break;
            }

            case 7: {   /* Top Balance Report - Bubble Sort */
                Account arr[MAX_ACCOUNTS];
                int cnt = 0, i;

                inorderCollect(root, arr, &cnt);
                bubbleSortByBalanceDesc(arr, cnt);

                printf("\n--- Top Balance Report ---\n");
                printf("%-10s %-20s %-10s\n", "AccNo", "Name", "Balance");
                printf("----------------------------------------\n");
                for (i = 0; i < cnt; i++) {
                    printf("%-10d %-20s %-10.2f\n",
                           arr[i].accNo, arr[i].name, arr[i].balance);
                }
                break;
            }

            case 8: {   /* Delete Account */
                int accNo, found = 0;
                printf("\nEnter Account Number to delete: ");
                scanf("%d", &accNo);

                root = deleteBST(root, accNo, &found);
                if (found) {
                    printf("Account deleted successfully.\n");
                } else {
                    printf("Account not found.\n");
                }
                break;
            }

            case 9: {   /* Undo Last Transaction - Stack */
                Transaction t;
                if (!popTransaction(&txnStack, &t)) {
                    printf("\nNo transactions to undo.\n");
                    break;
                }

                BSTNode *node = searchBST(root, t.accNo);
                if (node == NULL) {
                    printf("Account for that transaction no longer exists.\n");
                    break;
                }

                if (strcmp(t.type, "DEPOSIT") == 0) {
                    node->data.balance -= t.amount;   /* reverse the deposit */
                    printf("\nUndone: Deposit of %.2f on Account %d.\n", t.amount, t.accNo);
                } else {
                    node->data.balance += t.amount;   /* reverse the withdrawal */
                    printf("\nUndone: Withdrawal of %.2f on Account %d.\n", t.amount, t.accNo);
                }
                printf("New Balance: %.2f\n", node->data.balance);
                break;
            }

            case 10: {  /* Add Loan Request - Queue */
                LoanRequest r;
                printf("\nEnter Account Number : ");
                scanf("%d", &r.accNo);
                clearInputBuffer();

                printf("Enter Applicant Name : ");
                fgets(r.name, NAME_LEN, stdin);
                r.name[strcspn(r.name, "\n")] = '\0';

                printf("Enter Loan Amount     : ");
                scanf("%f", &r.loanAmount);

                enqueueLoanRequest(&loanQueue, r);
                printf("\nLoan request submitted. Position in queue: %d\n", loanQueue.count);
                break;
            }

            case 11: {  /* Process Next Loan Request - Queue */
                LoanRequest r;
                if (!dequeueLoanRequest(&loanQueue, &r)) {
                    printf("\nNo pending loan requests.\n");
                    break;
                }
                printf("\nProcessing Loan Request:\n");
                printf("Account No : %d\n", r.accNo);
                printf("Name       : %s\n", r.name);
                printf("Amount     : %.2f\n", r.loanAmount);
                printf("Status     : Approved\n");
                break;
            }

            case 12: {  /* Bank Summary - Recursion */
                int total = countAccountsRecursive(root);
                float sum = sumBalanceRecursive(root);
                printf("\n--- Bank Summary ---\n");
                printf("Total Accounts        : %d\n", total);
                printf("Total Deposits (Sum)  : %.2f\n", sum);
                break;
            }

            case 13:
                saveAccountsToFile(root);
                printf("\nData saved. Thank you for using the Bank "
                       "Management System. Goodbye!\n");
                break;

            default:
                printf("\nInvalid choice. Please enter a number between 1 and 13.\n");
        }

    } while (choice != 13);

    freeBST(root);   /* release all dynamically allocated memory */
    return 0;
}
