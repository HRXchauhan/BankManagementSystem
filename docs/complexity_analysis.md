# Complexity Analysis

This document lists the time and space complexity of the major
operations in the Bank Management System.

| Operation                              | Data Structure | Time Complexity            | Space Complexity |
|-----------------------------------------|-----------------|------------------------------|-------------------|
| Insert Account                          | BST             | O(log n) avg, O(n) worst    | O(1) per node (O(h) recursion stack) |
| Search by Account Number                | BST             | O(log n) avg, O(n) worst    | O(h) recursion stack |
| Delete Account                          | BST             | O(log n) avg, O(n) worst    | O(h) recursion stack |
| In-order Display (sorted by Acc No)     | BST             | O(n)                         | O(h) recursion stack |
| Count Accounts (recursive)              | BST             | O(n)                         | O(h) recursion stack |
| Sum of Balances (recursive)             | BST             | O(n)                         | O(h) recursion stack |
| Search by Name                          | Array (linear)  | O(n)                         | O(n) for the array |
| Sort by Balance (Bubble Sort)           | Array           | O(n^2) worst/avg, O(n) best (already sorted, no swaps) | O(1) extra (in place) |
| Push / Pop Transaction                  | Stack (array)   | O(1)                          | O(1) |
| Enqueue / Dequeue Loan Request          | Queue (array, circular) | O(1)                  | O(1) |
| Save All Accounts to File               | BST + File      | O(n)                          | O(1) extra |
| Load All Accounts from File             | File + BST      | O(n log n) average (n inserts at O(log n) each) | O(n) total nodes |

**Notes**

- `n` = number of accounts currently in the bank.
- `h` = height of the BST (O(log n) for a balanced tree, O(n) for a
  completely skewed/unbalanced tree since this is a plain BST, not a
  self-balancing tree like an AVL or Red-Black tree).
- The Stack and Queue are implemented using fixed-size arrays, so all
  their operations are O(1) with O(1) auxiliary space.
- Bubble Sort was chosen for simplicity and because it is easy to
  explain and trace by hand during a viva. For a much larger number
  of accounts, a more efficient sort (e.g. Merge Sort, O(n log n))
  would be a natural optimization — see the Future Enhancements
  section of the project report.
