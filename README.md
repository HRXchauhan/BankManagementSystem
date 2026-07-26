# Bank Management System

A console-based **Bank Management System** in C, built as the Final
Capstone Project for *Data Structures & Algorithms Using C*.

## Overview

The system manages bank accounts using a **Binary Search Tree (BST)**
keyed by account number, and layers several other core data
structures on top of it to solve real banking workflows:

- **BST** — primary account storage (insert, search, delete, sorted
  in-order display) — all implemented recursively.
- **Stack** — keeps a history of recent transactions so the most
  recent Deposit/Withdraw can be undone.
- **Queue** — holds pending loan requests and processes them
  strictly in the order they arrived (FIFO).
- **Sorting (Bubble Sort)** — generates a "Top Balance" report.
- **Searching (Linear Search)** — finds an account by customer name.
- **Recursion** — used throughout the BST (insert/search/delete/
  traversal) plus two dedicated demos: counting all accounts and
  summing all balances.
- **File Handling** — accounts are saved to and reloaded from
  `sample-data/bank_data.txt`, so data survives between runs.
- **Dynamic Memory Allocation** — every BST node is `malloc`'d on
  creation and `free`'d on deletion / program exit (no memory leaks).

## Team Members

- `<Add your name>`
- `<Add teammate name>`
- `<Add teammate name>`

**Guide:** `<Add guide/faculty name>`

## Minimum 8 DSA Concepts Implemented

1. Structures
2. Functions
3. Dynamic Memory Allocation
4. File Handling
5. Searching Algorithm (Linear Search + BST Search)
6. Sorting Algorithm (Bubble Sort)
7. Tree (Binary Search Tree) + Stack + Queue
8. Recursion

## Repository Structure

```
BankManagementSystem/
│── include/
│   └── bank.h
│── src/
│   ├── main.c
│   ├── bst.c
│   ├── sort_search.c
│   ├── stack.c
│   ├── queue.c
│   └── file_ops.c
│── docs/
│   └── complexity_analysis.md
│── report/
│   └── Bank_Management_System_Report.docx
│── presentation/
│   └── Bank_Management_System_Presentation.pptx
│── screenshots/
│   └── (5 program output screenshots)
│── sample-data/
│   └── bank_data.txt
│── README.md
│── LICENSE
│── Makefile
```

## How to Build & Run

Using the Makefile (recommended):

```bash
make
./bank_system
```

Or compile manually:

```bash
gcc -Wall -Iinclude -o bank_system src/main.c src/bst.c src/sort_search.c src/stack.c src/queue.c src/file_ops.c
./bank_system
```

Run from the project root (`BankManagementSystem/`) so the program
can find `sample-data/bank_data.txt`.

## Main Menu

```
 1. Create Account
 2. Deposit
 3. Withdraw
 4. Search Account (by Account Number - BST)
 5. Search Account (by Name - Linear Search)
 6. Display All Accounts (sorted by Acc No)
 7. Top Balance Report (Bubble Sort)
 8. Delete Account
 9. Undo Last Transaction (Stack)
10. Add Loan Request (Queue)
11. Process Next Loan Request (Queue)
12. Bank Summary (Recursion)
13. Save & Exit
```

## Sample Data

`sample-data/bank_data.txt` ships with 4 example accounts so the
program has something to load the first time it's run. Delete this
file if you'd like to start from a completely empty bank.

## Complexity Analysis

See [docs/complexity_analysis.md](docs/complexity_analysis.md) for
the time/space complexity of every major operation.

## License

This project is licensed under the MIT License — see [LICENSE](LICENSE).
