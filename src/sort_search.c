/* ============================================================
   sort_search.c
   Demonstrates a Sorting Algorithm and a Searching Algorithm
   working on a plain array of accounts (used for reports,
   separate from the BST which is the main storage).
   ============================================================ */

#include <stdio.h>
#include <string.h>
#include "bank.h"

/* ------------------------------------------------------------
   bubbleSortByBalanceDesc
   Sorts the array of accounts by balance, highest first.
   Time Complexity : O(n^2) worst/average case
   Space Complexity: O(1) extra space (sorts in place)
   ------------------------------------------------------------ */
void bubbleSortByBalanceDesc(Account arr[], int n) {
    int i, j;
    Account temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j].balance < arr[j + 1].balance) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

/* ------------------------------------------------------------
   linearSearchByName
   Searches the array for an account whose name matches
   (case-sensitive, exact match). Returns the index, or -1.
   Time Complexity: O(n)
   ------------------------------------------------------------ */
int linearSearchByName(Account arr[], int n, const char *name) {
    int i;
    for (i = 0; i < n; i++) {
        if (strcmp(arr[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}
