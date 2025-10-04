import pandas as pd
import json
import matplotlib.pyplot as plt
import glob
import os
import re
import numpy as np

os.makedirs("img", exist_ok=True)

files = glob.glob("stats.json")
all_data = []
for file in files:
    with open(file, "r") as f:
        data = json.load(f)
        all_data.extend(data["benchmarks"])

df = pd.DataFrame(all_data)

def extract_precision(name):
    match = re.search(r'1e-(\d+)', name)
    if match:
        return int(match.group(1))
    return None

def extract_step(precision):
    if precision:
        return 10 ** -precision
    return None

def extract_type(name):
    if 'Parallel' in name:
        return 'PARALLEL'
    else:
        return 'SEQUENTIAL'

df["precision"] = df["name"].apply(extract_precision)
df["step"] = df["precision"].apply(extract_step)
df["type"] = df["name"].apply(extract_type)
df["real_time_sec"] = df["real_time"] / 1_000_000_000
df["cpu_time_sec"] = df["cpu_time"] / 1_000_000_000

df = df.sort_values("step", ascending=False)

fig, ax1 = plt.subplots(1, 1, figsize=(12, 6))

for bench_type in ['SEQUENTIAL', 'PARALLEL']:
    group = df[df["type"] == bench_type]
    group = group.sort_values("step", ascending=False)
    label = "Последовательная" if bench_type == 'SEQUENTIAL' else "Параллельная"
    ax1.plot(group["step"], group["real_time_sec"], marker='o', linewidth=2, markersize=8, label=label)

ax1.set_xscale('log')
ax1.set_yscale('log')
ax1.set_title("Сравнение времени выполнения", fontsize=14, fontweight='bold')
ax1.set_xlabel("Шаг интегрирования", fontsize=12)
ax1.set_ylabel("Время (секунды)", fontsize=12)
ax1.legend(fontsize=11)
ax1.grid(True, which="both", ls="-", alpha=0.2)
ax1.invert_xaxis()

plt.tight_layout()
plt.savefig("img/integration_comparison_combined.png", dpi=200, bbox_inches='tight')
plt.close()