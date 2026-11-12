# DAA Lab 03 — Divide and Conquer

Each question is a self-contained, ready-to-upload folder:

- `Q1_Binary_vs_Ternary_Search/`
- `Q2_Defective_Coin/`
- `Q3_MaxMin_Divide_Conquer/`
- `Q4_Strassen_Matrix_Mult/`
- `Q5_Special_Pattern_Matrix_Mult/`
- `Q6_Selection_Sort_Loop_Invariant/`

Each folder contains:
- the `.c` source (comments removed)
- a `.csv` file with measured performance data (comparisons/weighings/time vs input size `n`)
- a `.png` graph plotting that data
- a short `README.md` explaining what the graph shows

Compile any file with:
```bash
gcc -o out <filename>.c -lm
./out
```
(`-lm` is only needed for `2_defective_coin.c`, which uses `log2`.)
