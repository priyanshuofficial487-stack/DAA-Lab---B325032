# Q1 — Dictionary Operations: Asymptotic Analysis

We analyze the worst-case running time of the seven dictionary operations
(`Search`, `Insert`, `Delete`, `Max`, `Min`, `Predecessor`, `Successor`) for
six underlying implementations. `n` is the number of elements currently
stored.

**Assumptions used (standard CLRS-style):**
- For arrays, `Delete(D, x)` is given the *index* of `x`; for unsorted array,
  we delete in O(1) by overwriting with the last element and shrinking the
  array (order doesn't matter). For a sorted array, deleting must preserve
  order, so remaining elements are shifted → O(n).
- For linked lists, `Delete(D, x)` is given a pointer to the node `x` itself.
  In a **singly** linked list you cannot access the previous node in O(1)
  (no `prev` pointer), so unlinking requires an O(n) scan from the head to
  find the predecessor. In a **doubly** linked list the predecessor is
  available directly, so delete is O(1).
- `Insert` always adds at whichever position is O(1) for unsorted
  structures (head of list / end of array), and at the correct sorted
  position for sorted structures.

## Complexity Table

| Structure                     | Search | Insert | Delete | Max  | Min  | Predecessor | Successor |
|--------------------------------|:------:|:------:|:------:|:----:|:----:|:-----------:|:---------:|
| Unsorted array                | O(n)   | O(1)   | O(1)*  | O(n) | O(n) | O(n)        | O(n)      |
| Sorted array                  | O(log n) | O(n) | O(n)   | O(1) | O(1) | O(1)        | O(1)      |
| Singly linked, unsorted list  | O(n)   | O(1)   | O(n)   | O(n) | O(n) | O(n)        | O(n)      |
| Singly linked, sorted list    | O(n)   | O(n)   | O(n)   | O(n) | O(1) | O(n)        | O(1)      |
| Doubly linked, unsorted list  | O(n)   | O(1)   | O(1)   | O(n) | O(n) | O(n)        | O(n)      |
| Doubly linked, sorted list    | O(n)   | O(n)   | O(1)   | O(1) | O(1) | O(1)        | O(1)      |

`*` Delete on an unsorted array is O(1) only because the pointer/index of
the element is given directly and order does not need to be preserved
(swap-with-last trick). If instead we required an O(n) search to *find*
the element first (i.e. `Delete(D, k)` by key rather than by pointer),
Search dominates and it becomes O(n) regardless.

### Notes on individual entries
- **Sorted array**: `Search` uses binary search → O(log n). `Max`/`Min` are
  simply the last/first element → O(1). `Predecessor`/`Successor` of an
  element at index `i` are just `arr[i-1]`/`arr[i+1]` → O(1). `Insert`/
  `Delete` must shift elements to keep the array sorted → O(n).
- **Singly linked sorted list**: `Min` is the head (O(1)), `Successor` is
  `x->next` (O(1)), but `Max` and `Predecessor` require traversing from the
  head since there is no `prev` pointer and no tail-adjacent access → O(n).
- **Doubly linked sorted list**: maintaining both a `head` and `tail`
  pointer makes `Min`/`Max` O(1), and `prev`/`next` pointers make
  `Predecessor`/`Successor` O(1). Insert still needs an O(n) scan to find
  the correct sorted position (no auxiliary index).

The accompanying `dictionary_ops.c` empirically measures the average time
of each operation as `n` grows, and `plot_q1.py` plots the resulting order
of growth to visually confirm the table above.
