import time
import random
import matplotlib.pyplot as plt # para instalar use: pip install matplotlib

# Estrutura de um item da mochila
class Item:""
    def __init__(self, valor, peso):
        self.valor = valor
        self.peso = peso
        self.valor_por_peso = valor / peso

def mochila_fracionaria(capacidade, itens):
    itens.sort(key=lambda x: x.valor_por_peso, reverse=True)
    
    valor_total = 0.0
    peso_atual = 0.0
    
    for item in itens:
        if peso_atual + item.peso <= capacidade:
            peso_atual += item.peso
            valor_total += item.valor
        else:
            restante = capacidade - peso_atual
            valor_total += item.valor_por_peso * restante
            break
    
    return valor_total

def gerar_itens(n):
    return [Item(random.randint(10, 100), random.randint(5, 50)) for _ in range(n)]

def testar_algoritmo(num_itens, capacidade, repeticoes=20):
    tempos = []
    for _ in range(repeticoes):
        itens = gerar_itens(num_itens)
        start = time.time()
        mochila_fracionaria(capacidade, itens)
        end = time.time()
        tempos.append(end - start)

    media = sum(tempos) / len(tempos)
    desvio = (sum((t - media) ** 2 for t in tempos) / len(tempos)) ** 0.5
    return media, desvio

# Executa testes e armazena resultados
tamanhos = [100, 1000, 5000, 10000]
capacidade = 1000
tempos_medios = []
desvios = []

for tamanho in tamanhos:
    print(f"Testando para {tamanho} itens...")
    media, desvio = testar_algoritmo(tamanho, capacidade)
    tempos_medios.append(media)
    desvios.append(desvio)
    print(f" -> Tempo médio: {media:.6f}s | Desvio padrão: {desvio:.6f}s")

# Geração dos gráficos
plt.figure(figsize=(10, 6))
plt.bar([str(t) for t in tamanhos], tempos_medios, yerr=desvios, capsize=5)
plt.title("Tempo Médio de Execução vs. Tamanho de Entrada")
plt.xlabel("Número de Itens")
plt.ylabel("Tempo Médio (s)")
plt.grid(True, axis='y', linestyle='--', alpha=0.7)
plt.tight_layout()
plt.savefig("tempo_execucao_mochila.png")
plt.show()

plt.figure(figsize=(10, 6))
plt.errorbar(tamanhos, tempos_medios, yerr=desvios, fmt='-o', capsize=5)
plt.title("Tempo Médio com Desvio Padrão")
plt.xlabel("Número de Itens")
plt.ylabel("Tempo Médio (s)")
plt.grid(True)
plt.tight_layout()
plt.savefig("tempo_execucao_linha.png")
plt.show()
