import csv
import os
from collections import defaultdict

try:
    import matplotlib
    matplotlib.use("Agg")
    import matplotlib.pyplot as plt
except ImportError:
    raise SystemExit("Please `pip install matplotlib` first.")

CSV_PATH = os.path.join(os.path.dirname(__file__), "results_q1.csv")
OPS = ["search", "insert", "delete", "max", "min", "predecessor", "successor"]
STRUCTURES = ["unsorted_array", "sorted_array", "sll_unsorted", "sll_sorted",
              "dll_unsorted", "dll_sorted"]
LABELS = {
    "unsorted_array": "Unsorted array",
    "sorted_array": "Sorted array",
    "sll_unsorted": "Singly linked (unsorted)",
    "sll_sorted": "Singly linked (sorted)",
    "dll_unsorted": "Doubly linked (unsorted)",
    "dll_sorted": "Doubly linked (sorted)",
}

data = defaultdict(lambda: defaultdict(list))

with open(CSV_PATH) as f:
    for row in csv.DictReader(f):
        op, struct, n, t = row["operation"], row["structure"], int(row["n"]), float(row["avg_time_us"])
        data[op][struct].append((n, t))

os.makedirs("plots", exist_ok=True)

for op in OPS:
    plt.figure(figsize=(7, 5))
    for struct in STRUCTURES:
        pts = sorted(data[op].get(struct, []))
        if not pts:
            continue
        xs = [p[0] for p in pts]
        ys = [p[1] for p in pts]
        plt.plot(xs, ys, marker="o", label=LABELS[struct])
    plt.xscale("log")
    plt.yscale("log")
    plt.xlabel("n (number of elements)")
    plt.ylabel("avg time per operation (microseconds)")
    plt.title(f"Q1: {op.capitalize()} — order of growth")
    plt.legend(fontsize=8)
    plt.grid(True, which="both", alpha=0.3)
    plt.tight_layout()
    out = f"plots/q1_{op}.png"
    plt.savefig(out, dpi=140)
    plt.close()
    print(f"wrote {out}")

print("All plots written to ./plots/")
