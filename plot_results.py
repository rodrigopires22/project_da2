import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('results.csv')

plt.figure(figsize=(10,6))
for dataset in df['Dataset'].unique():
    subset = df[df['Dataset'] == dataset]
    plt.bar(subset['Algoritmo'] + f" ({dataset})", subset['Tempo(ms)'])
plt.ylabel('Tempo (ms)')
plt.title('Tempo de Execução por Algoritmo e Dataset')
plt.xticks(rotation=45, ha='right')
plt.tight_layout()
plt.savefig('tempo_execucao.png')
plt.show()

plt.figure(figsize=(10,6))
for dataset in df['Dataset'].unique():
    subset = df[df['Dataset'] == dataset]
    plt.bar(subset['Algoritmo'] + f" ({dataset})", subset['Lucro'])
plt.ylabel('Lucro')
plt.title('Lucro por Algoritmo e Dataset')
plt.xticks(rotation=45, ha='right')
plt.tight_layout()
plt.savefig('lucro_algoritmos.png')
plt.show()
