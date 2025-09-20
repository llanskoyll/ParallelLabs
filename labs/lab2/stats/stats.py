import pandas as pd
import json
import matplotlib.pyplot as plt
import glob
import os
import re

os.makedirs("img", exist_ok=True)

files = glob.glob("stats.json")
all_data = []
for file in files:
    with open(file, "r") as f:
        data = json.load(f)
        all_data.extend(data["benchmarks"])

df = pd.DataFrame(all_data)

if "label" not in df.columns:
    df["label"] = df["name"]

def extract_size(label):
    match = re.search(r'_(\d+)$', label)
    if match:
        return int(match.group(1))
    return None

df["matrix_size"] = df["label"].apply(extract_size)
df["real_time_sec"] = df["real_time"] / 1_000_000_000

plt.figure(figsize=(12, 6))
for prefix in ["BASE_SOLVE_GAUSS", "PERF_SOLVE_GAUSS"]:
    group = df[df["label"].str.startswith(prefix)]
    group = group.sort_values("matrix_size")
    plt.plot(group["matrix_size"], group["real_time_sec"], marker='o', label=prefix)

plt.title("Сравнение Метода Гаусса: базовая vs параллельная")
plt.xlabel("Размер матрицы (n x n)")
plt.ylabel("Время (секунды)")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig("img/comparison_solve_gauss.png", dpi=200)
plt.close()
