"""
Generates the plots requested in Q3 and Q4 from the CSV files produced by
the C programs (bubble_results.csv, hanoi_results.csv).

Usage:
    python3 make_plots.py

Requires: matplotlib, pandas  (pip install matplotlib pandas)
"""
import csv
import matplotlib.pyplot as plt


def read_csv(path):
    with open(path, newline="") as f:
        return list(csv.DictReader(f))


def plot_bubble():
    rows = read_csv("bubble_results.csv")
    n = [int(r["n"]) for r in rows]
    early = [int(r["comparisons_early_exit"]) for r in rows]
    full = [int(r["comparisons_full_passes"]) for r in rows]

    plt.figure()
    plt.plot(n, early, marker="o", label="Early-exit bubble sort")
    plt.plot(n, full, marker="s", label="Always full-pass bubble sort")
    plt.xlabel("n (array size)")
    plt.ylabel("Number of comparisons")
    plt.title("Q3: Bubble sort comparisons vs n")
    plt.legend()
    plt.grid(True)
    plt.savefig("q3_bubble_plot.png", dpi=150, bbox_inches="tight")
    print("Saved q3_bubble_plot.png")


def plot_hanoi():
    rows = read_csv("hanoi_results.csv")
    n = [int(r["n"]) for r in rows]
    moves = [int(r["moves"]) for r in rows]

    plt.figure()
    plt.plot(n, moves, marker="o")
    plt.xlabel("n (number of discs)")
    plt.ylabel("Number of moves")
    plt.title("Q4: Towers of Hanoi moves vs n (linear scale)")
    plt.grid(True)
    plt.savefig("q4_hanoi_plot.png", dpi=150, bbox_inches="tight")
    print("Saved q4_hanoi_plot.png")

    plt.figure()
    plt.semilogy(n, moves, marker="o")
    plt.xlabel("n (number of discs)")
    plt.ylabel("Number of moves (log scale)")
    plt.title("Q4: Towers of Hanoi moves vs n (log scale -> straight line = exponential)")
    plt.grid(True, which="both")
    plt.savefig("q4_hanoi_plot_logscale.png", dpi=150, bbox_inches="tight")
    print("Saved q4_hanoi_plot_logscale.png")


def plot_coin():
    rows = read_csv("coin_results.csv")
    tosses = [int(r["tosses"]) for r in rows]
    fair = [float(r["fair_estimate"]) for r in rows]
    biased = [float(r["biased_estimate"]) for r in rows]

    plt.figure()
    plt.semilogx(tosses, fair, marker="o", label="Fair coin (p=0.5)")
    plt.semilogx(tosses, biased, marker="s", label="Biased coin (p=0.7)")
    plt.axhline(0.5, linestyle="--", color="gray", linewidth=1)
    plt.axhline(0.7, linestyle="--", color="gray", linewidth=1)
    plt.xlabel("Number of tosses (log scale)")
    plt.ylabel("Observed P(HEAD)")
    plt.title("Q2: Convergence of observed P(HEAD)")
    plt.legend()
    plt.grid(True)
    plt.savefig("q2_coin_plot.png", dpi=150, bbox_inches="tight")
    print("Saved q2_coin_plot.png")


def plot_uniqueness():
    rows = read_csv("uniqueness_results.csv")
    n = [int(r["n"]) for r in rows]
    brute = [int(r["brute_comparisons"]) for r in rows]
    sort_ = [int(r["sort_comparisons"]) for r in rows]

    plt.figure()
    plt.plot(n, brute, marker="o", label="Brute force O(n^2)")
    plt.plot(n, sort_, marker="s", label="Sort + scan O(n log n)")
    plt.xlabel("n")
    plt.ylabel("Number of comparisons")
    plt.title("Q6: Element uniqueness comparisons vs n")
    plt.legend()
    plt.grid(True)
    plt.savefig("q6_uniqueness_plot.png", dpi=150, bbox_inches="tight")
    print("Saved q6_uniqueness_plot.png")


if __name__ == "__main__":
    for name, fn in [("bubble", plot_bubble), ("hanoi", plot_hanoi),
                      ("coin", plot_coin), ("uniqueness", plot_uniqueness)]:
        try:
            fn()
        except FileNotFoundError as e:
            print(f"Skipping {name} plot: {e}. Run the matching C program first.")
