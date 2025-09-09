import pandas as pd
import json
import matplotlib.pyplot as plt
import glob
import os
import re

# Создаем папку для графиков, если её нет
os.makedirs("img", exist_ok=True)

# Загружаем все JSON файлы
files = glob.glob("stats*.json")
all_data = []
for file in files:
    with open(file, "r") as f:
        data = json.load(f)
        all_data.extend(data["benchmarks"])

df = pd.DataFrame(all_data)

def extract_size(label):
    match = re.search(r'_(\d+)$', label)
    if match:
        return int(match.group(1))
    return None

df["matrix_size"] = df["label"].apply(extract_size)

labels_to_compare = ["BASE_MATRIX", "THREAD_MATRIX"]

plt.figure(figsize=(12, 6))

for base_label in labels_to_compare:
    group = df[df["label"].str.startswith(base_label)]
    plt.plot(group["matrix_size"], group["real_time"], marker='o', label=base_label, alpha=1)

plt.title("Сравнение real_time по размеру матрицы")
plt.xlabel("Размер матрицы (n x n)")
plt.ylabel("Время (нс)")
plt.legend()
plt.grid(True)
plt.tight_layout()

plt.savefig("img/comparison_real_time.png", dpi=200)
plt.close()
