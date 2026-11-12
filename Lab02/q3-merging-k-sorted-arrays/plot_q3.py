import csv
import math
import os
from collections import defaultdict

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

HERE = os.path.dirname(__file__)
os.makedirs(os.path.join(HERE, "plots"), exist_ok=True)

LABELS = {"sequential": "Method 1: sequential merge",
          "pairwise": "Method 2: pairwise (tournament) merge"}


def load(path):
    data = defaultdict(list)
    with open(path) as f:
        for row in csv.DictReader(f):
            data[row["method"]].append((int(row["n"]), int(row["k"]), float(row["time_ms"])))
    for k in data:
        data[k].sort()
    return data


data_k = load(os.path.join(HERE, "results_q3_vary_k.csv"))

plt.figure(figsize=(7, 5))
for method, pts in data_k.items():
    xs = [k for n, k, t in pts]
    ys = [t for n, k, t in pts]
    plt.plot(xs, ys, marker="o", label=LABELS[method])
plt.xscale("log")
plt.yscale("log")
plt.xlabel("k (number of arrays), n fixed = 500")
plt.ylabel("time (ms)")
plt.title("Q3: Merging k sorted arrays — runtime vs k")
plt.legend()
plt.grid(True, which="both", alpha=0.3)
plt.tight_layout()
plt.savefig(os.path.join(HERE, "plots/q3_vs_k.png"), dpi=140)
plt.close()

plt.figure(figsize=(7, 5))
pts = data_k["sequential"]
xs = [k for n, k, t in pts]
ys = [t / (k * k) for n, k, t in pts]
plt.plot(xs, ys, marker="o", label="sequential: t / k^2")
pts = data_k["pairwise"]
xs = [k for n, k, t in pts]
ys = [t / (k * math.log2(k)) for n, k, t in pts]
plt.plot(xs, ys, marker="o", label="pairwise: t / (k log2 k)")
plt.xscale("log")
plt.xlabel("k")
plt.ylabel("normalized time (ms)")
plt.title("Q3: normalized time confirms Θ(n k²) vs Θ(n k log k)")
plt.legend()
plt.grid(True, which="both", alpha=0.3)
plt.tight_layout()
plt.savefig(os.path.join(HERE, "plots/q3_normalized_vs_k.png"), dpi=140)
plt.close()

data_n = load(os.path.join(HERE, "results_q3_vary_n.csv"))

plt.figure(figsize=(7, 5))
for method, pts in data_n.items():
    xs = [n for n, k, t in pts]
    ys = [t for n, k, t in pts]
    plt.plot(xs, ys, marker="o", label=LABELS[method])
plt.xscale("log")
plt.yscale("log")
plt.xlabel("n (size of each array), k fixed = 16")
plt.ylabel("time (ms)")
plt.title("Q3: Merging k sorted arrays — runtime vs n")
plt.legend()
plt.grid(True, which="both", alpha=0.3)
plt.tight_layout()
plt.savefig(os.path.join(HERE, "plots/q3_vs_n.png"), dpi=140)
plt.close()

print("wrote plots/q3_vs_k.png, plots/q3_normalized_vs_k.png, plots/q3_vs_n.png")
