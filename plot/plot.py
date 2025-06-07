import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
##########################################################
# Este script fue creado con la ayuda de ChatGPT
##########################################################

# Cargar los datos
df = pd.read_csv("results.csv", names=["algoritmo", "distancia", "tiempo", "memoria", "file1", "file2"])

# Forzar tipos correctos
df["tiempo"] = pd.to_numeric(df["tiempo"], errors="coerce")
df["memoria"] = pd.to_numeric(df["memoria"], errors="coerce")
df["distancia"] = pd.to_numeric(df["distancia"], errors="coerce")

df["text1"] = df["file1"].apply(lambda x: x.split("/")[-1].replace(".txt", "").replace("test", "text"))
df["text2"] = df["file2"].apply(lambda x: x.split("/")[-1].replace(".txt", "").replace("test", "text"))

# Filtrar: fijar texto de entrada como text4
df_fixed_text = df[df["text1"] == "text4"].copy()

# Redondear memoria KB → MB
df_fixed_text["memoria_MB"] = (df_fixed_text["memoria"] / 1024).round()

# Orden para eje X
orden_textos = ["text1", "text2", "text3", "text4"]
df_fixed_text["text2"] = pd.Categorical(df_fixed_text["text2"], categories=orden_textos, ordered=True)

# Estilo
sns.set_theme(style="whitegrid")
palette = sns.color_palette("Set2")

# Gráfico de tiempo
plt.figure(figsize=(8, 5))
sns.lineplot(data=df_fixed_text, x="text2", y="tiempo", hue="algoritmo", marker="o", palette=palette)
plt.title("Comparación de tiempo (ms) - Texto inicial fijado a texto 4")
plt.ylabel("Tiempo (ms)")
plt.xlabel("Texto destino")
plt.legend(title="Algoritmo")
plt.tight_layout()
plt.show()

# Gráfico de memoria
plt.figure(figsize=(8, 5))
sns.lineplot(data=df_fixed_text, x="text2", y="memoria_MB", hue="algoritmo", marker="o", palette=palette)
plt.title("Comparación de memoria (MB) - Texto inicial fijado a texto 4")
plt.ylabel("Memoria (MB)")
plt.xlabel("Texto destino")
plt.legend(title="Algoritmo")
plt.tight_layout()
plt.show()
