/* ============================================================
   file_ops.c
   File Handling - persists all accounts to a text file so
   data survives between program runs.
   ============================================================ */

#include <stdio.h>
#include "bank.h"

/* ------------------------------------------------------------
   writeNodeToFile (recursive helper, static/internal to file)
   Visits the BST in-order and writes one line per account.
   ------------------------------------------------------------ */
static void writeNodeToFile(BSTNode *root, FILE *fp) {
    if (root == NULL) {
        return;
    }
    writeNodeToFile(root->left, fp);
    fprintf(fp, "%d,%s,%.2f\n",
            root->data.accNo, root->data.name, root->data.balance);
    writeNodeToFile(root->right, fp);
}

/* ------------------------------------------------------------
   saveAccountsToFile
   Writes every account (in sorted order) to DATA_FILE.
   ------------------------------------------------------------ */
void saveAccountsToFile(BSTNode *root) {
    FILE *fp = fopen(DATA_FILE, "w");
    if (fp == NULL) {
        printf("\nError: Could not save data to file.\n");
        return;
    }
    writeNodeToFile(root, fp);
    fclose(fp);
}

/* ------------------------------------------------------------
   loadAccountsFromFile
   Reads DATA_FILE (if it exists) and inserts every account
   back into a fresh BST. Returns the resulting tree root.
   ------------------------------------------------------------ */
BSTNode* loadAccountsFromFile(BSTNode *root) {
    FILE *fp = fopen(DATA_FILE, "r");
    Account acc;

    if (fp == NULL) {
        return root;   /* no saved data yet - start with an empty bank */
    }

    while (fscanf(fp, "%d,%49[^,],%f\n",
                   &acc.accNo, acc.name, &acc.balance) == 3) {
        root = insertBST(root, acc);
    }

    fclose(fp);
    return root;
}
