/* ============================================================
   bst.c
   Binary Search Tree operations - accounts are stored keyed
   by Account Number. Demonstrates:
     - Dynamic Memory Allocation (malloc / free)
     - Recursion (every operation below is recursive)
     - Trees (BST insert / search / delete / traversal)
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bank.h"

/* ------------------------------------------------------------
   insertBST (recursive)
   Inserts a new account into the BST based on account number.
   Time Complexity: O(log n) average, O(n) worst case
   ------------------------------------------------------------ */
BSTNode* insertBST(BSTNode *root, Account acc) {
    if (root == NULL) {
        BSTNode *node = (BSTNode *) malloc(sizeof(BSTNode));  /* dynamic memory */
        node->data = acc;
        node->left = NULL;
        node->right = NULL;
        return node;
    }

    if (acc.accNo < root->data.accNo) {
        root->left = insertBST(root->left, acc);
    } else if (acc.accNo > root->data.accNo) {
        root->right = insertBST(root->right, acc);
    }
    /* if equal, ignore (duplicate account numbers are rejected
       by the caller before insertBST is used) */

    return root;
}

/* ------------------------------------------------------------
   searchBST (recursive)
   Searches for an account by account number.
   Time Complexity: O(log n) average, O(n) worst case
   ------------------------------------------------------------ */
BSTNode* searchBST(BSTNode *root, int accNo) {
    if (root == NULL || root->data.accNo == accNo) {
        return root;
    }

    if (accNo < root->data.accNo) {
        return searchBST(root->left, accNo);
    }
    return searchBST(root->right, accNo);
}

/* ------------------------------------------------------------
   findMin
   Helper: returns the node with the smallest accNo in a subtree
   (used by deleteBST when a node has two children).
   ------------------------------------------------------------ */
static BSTNode* findMin(BSTNode *root) {
    while (root != NULL && root->left != NULL) {
        root = root->left;
    }
    return root;
}

/* ------------------------------------------------------------
   deleteBST (recursive)
   Deletes an account by account number and frees its memory.
   *found is set to 1 if the account was located and removed.
   ------------------------------------------------------------ */
BSTNode* deleteBST(BSTNode *root, int accNo, int *found) {
    if (root == NULL) {
        return NULL;
    }

    if (accNo < root->data.accNo) {
        root->left = deleteBST(root->left, accNo, found);
    } else if (accNo > root->data.accNo) {
        root->right = deleteBST(root->right, accNo, found);
    } else {
        /* node found */
        *found = 1;

        if (root->left == NULL) {
            BSTNode *temp = root->right;
            free(root);
            return temp;
        }
        if (root->right == NULL) {
            BSTNode *temp = root->left;
            free(root);
            return temp;
        }

        /* two children: replace with the in-order successor */
        BSTNode *successor = findMin(root->right);
        root->data = successor->data;
        root->right = deleteBST(root->right, successor->data.accNo, found);
    }

    return root;
}

/* ------------------------------------------------------------
   inorderDisplay (recursive)
   Prints every account in ascending order of account number.
   ------------------------------------------------------------ */
void inorderDisplay(BSTNode *root) {
    if (root == NULL) {
        return;
    }
    inorderDisplay(root->left);
    printf("%-10d %-20s %-10.2f\n",
           root->data.accNo, root->data.name, root->data.balance);
    inorderDisplay(root->right);
}

/* ------------------------------------------------------------
   inorderCollect (recursive)
   Copies every account into a plain array (sorted by accNo),
   used whenever the program needs to sort/search over an array
   instead of the tree (e.g. sorting by balance).
   ------------------------------------------------------------ */
void inorderCollect(BSTNode *root, Account arr[], int *count) {
    if (root == NULL) {
        return;
    }
    inorderCollect(root->left, arr, count);
    if (*count < MAX_ACCOUNTS) {
        arr[*count] = root->data;
        (*count)++;
    }
    inorderCollect(root->right, arr, count);
}

/* ------------------------------------------------------------
   countAccountsRecursive (recursion demo)
   Recursively counts how many accounts exist in the tree.
   ------------------------------------------------------------ */
int countAccountsRecursive(BSTNode *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countAccountsRecursive(root->left)
             + countAccountsRecursive(root->right);
}

/* ------------------------------------------------------------
   sumBalanceRecursive (recursion demo)
   Recursively adds up the balance of every account - used to
   report the bank's total deposits.
   ------------------------------------------------------------ */
float sumBalanceRecursive(BSTNode *root) {
    if (root == NULL) {
        return 0.0f;
    }
    return root->data.balance
           + sumBalanceRecursive(root->left)
           + sumBalanceRecursive(root->right);
}

/* ------------------------------------------------------------
   freeBST (recursive)
   Frees every node before the program exits (proper dynamic
   memory management - avoids memory leaks).
   ------------------------------------------------------------ */
void freeBST(BSTNode *root) {
    if (root == NULL) {
        return;
    }
    freeBST(root->left);
    freeBST(root->right);
    free(root);
}
