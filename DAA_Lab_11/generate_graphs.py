import os
import pandas as pd
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

base = os.path.dirname(os.path.abspath(__file__))

def load(q):
    return pd.read_csv(os.path.join(base, q, "results.csv"))

def save(q):
    plt.tight_layout()
    plt.savefig(os.path.join(base, q, "graph.png"), dpi=120)
    plt.close()

d = load("Q1")
plt.figure(figsize=(9, 5.5))
plt.plot(d["vertices"] + d["edges"], d["time_ms"], marker="o", linewidth=2)
plt.xlabel("V + E")
plt.ylabel("Time (ms)")
plt.title("Q1: 0-1 BFS on parity states - time grows linearly in V + E")
plt.grid(True, alpha=0.3)
save("Q1")

d = load("Q2")
plt.figure(figsize=(9, 5.5))
plt.plot(d["vertices"], d["multi_bfs_ms"], marker="o", linewidth=2, label="Multi-source BFS  O(V+E)")
plt.plot(d["vertices"], d["naive_ms"], marker="s", linewidth=2, label="K separate BFS  O(K(V+E))")
plt.xlabel("Vertices (E = 3V, K = 20, R = 10)")
plt.ylabel("Time (ms)")
plt.title("Q2: Multi-source BFS vs K separate BFS runs")
plt.legend()
plt.grid(True, alpha=0.3)
save("Q2")

d = load("Q3")
fig, ax = plt.subplots(1, 2, figsize=(12, 5))
ax[0].plot(d["words"], d["bidirectional_ms"], marker="o", linewidth=2, label="Bidirectional BFS")
ax[0].plot(d["words"], d["unidirectional_ms"], marker="s", linewidth=2, label="Unidirectional BFS")
ax[0].set_yscale("log")
ax[0].set_xlabel("Dictionary size N (L = 10)")
ax[0].set_ylabel("Avg time per query (ms, log scale)")
ax[0].set_title("Running time")
ax[0].legend()
ax[0].grid(True, alpha=0.3)
ax[1].plot(d["words"], d["bidirectional_visited"], marker="o", linewidth=2, label="Bidirectional BFS")
ax[1].plot(d["words"], d["unidirectional_visited"], marker="s", linewidth=2, label="Unidirectional BFS")
ax[1].set_yscale("log")
ax[1].set_xlabel("Dictionary size N (L = 10)")
ax[1].set_ylabel("Avg words visited (log scale)")
ax[1].set_title("Search space explored")
ax[1].legend()
ax[1].grid(True, alpha=0.3)
fig.suptitle("Q3: Bidirectional BFS on the word graph")
save("Q3")
print("graphs done")
