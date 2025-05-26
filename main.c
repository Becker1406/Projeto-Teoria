// Para rodar o codigo em c deve ter gcc instalado
// compilação no terminal para rodar -> gcc mochila_gulosa.c -o mochila_gulosa -lm ./mochila_gulosa
// recomenda-se usar o terminal do linux ou windows com o WSL instalado

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    double valor;
    double peso;
    double valor_por_peso;
} Item;

void ordenar_itens(Item *itens, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (itens[j].valor_por_peso < itens[j + 1].valor_por_peso) {
                Item temp = itens[j];
                itens[j] = itens[j + 1];
                itens[j + 1] = temp;
            }
        }
    }
}

double mochila_fracionaria(Item *itens, int n, double capacidade) {
    ordenar_itens(itens, n);
    double valor_total = 0.0;
    double peso_atual = 0.0;

    for (int i = 0; i < n; i++) {
        if (peso_atual + itens[i].peso <= capacidade) {
            peso_atual += itens[i].peso;
            valor_total += itens[i].valor;
        } else {
            double restante = capacidade - peso_atual;
            valor_total += itens[i].valor_por_peso * restante;
            break;
        }
    }
    return valor_total;
}

void gerar_itens(Item *itens, int n) {
    for (int i = 0; i < n; i++) {
        itens[i].valor = rand() % 91 + 10; // [10, 100]
        itens[i].peso = rand() % 46 + 5;   // [5, 50]
        itens[i].valor_por_peso = itens[i].valor / itens[i].peso;
    }
}

int main() {
    srand(time(NULL));
    int tamanhos[] = {100, 1000, 5000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);
    int repeticoes = 20;
    double capacidade = 1000.0;

    for (int t = 0; t < num_tamanhos; t++) {
        int n = tamanhos[t];
        double soma_tempos = 0.0, soma_quad = 0.0;

        for (int r = 0; r < repeticoes; r++) {
            Item *itens = malloc(n * sizeof(Item));
            gerar_itens(itens, n);

            clock_t start = clock();
            mochila_fracionaria(itens, n, capacidade);
            clock_t end = clock();

            double tempo = (double)(end - start) / CLOCKS_PER_SEC;
            soma_tempos += tempo;
            soma_quad += tempo * tempo;

            free(itens);
        }

        double media = soma_tempos / repeticoes;
        double desvio = sqrt((soma_quad / repeticoes) - (media * media));
        printf("%d itens -> Tempo médio: %.6fs | Desvio-padrão: %.6fs\n", n, media, desvio);
    }

    return 0;
}