import csv
import math
import os
from collections import defaultdict

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

CSV_PATH = os.path.join(os.path.dirname(__file__), "results_q2.csv")
data = defaultdict(list)
with open(CSV_PATH) as f:
    for row in csv.DictReader(f):
        data[row["algorithm"]].append((int(row["n"]), float(row["time_ms"])))

for k in data:
    data[k].sort()

os.makedirs("plots", exist_ok=True)

plt.figure(figsize=(7, 5))
labels = {"merge_sort_2way": "Merge sort (2-way, halves)",
          "merge_sort_3way": "Modified merge sort (3-way, thirds)"}
for algo, pts in data.items():
    xs = [p[0] for p in pts]
    ys = [p[1] for p in pts]
    plt.plot(xs, ys, marker="o", label=labels.get(algo, algo))
plt.xscale("log")
plt.yscale("log")
plt.xlabel("n (array size)")
plt.ylabel("time (ms)")
plt.title("Q2: Merge sort vs. 3-way merge sort — runtime")
plt.legend()
plt.grid(True, which="both", alpha=0.3)
plt.tight_layout()
plt.savefig("plots/q2_runtime.png", dpi=140)
plt.close()

plt.figure(figsize=(7, 5))
for algo, pts in data.items():
    xs = [n for n, t in pts]
    ys = [t / (n * math.log2(n)) for n, t in pts]
    plt.plot(xs, ys, marker="o", label=labels.get(algo, algo))
plt.xscale("log")
plt.xlabel("n (array size)")
plt.ylabel("time / (n * log2(n))   [ms]")
plt.title("Q2: t / (n log n) — flat line confirms Theta(n log n)")
plt.legend()
plt.grid(True, which="both", alpha=0.3)
plt.tight_layout()
plt.savefig("plots/q2_normalized.png", dpi=140)
plt.close()

print("wrote plots/q2_runtime.png and plots/q2_normalized.png")
