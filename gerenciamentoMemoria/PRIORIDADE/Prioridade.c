#include <stdio.h>
#include <stdlib.h>

// Estrutura de uma pagina na memoria
typedef struct {
    int numeroPagina; // Numero da pagina
    int prioridade; // Prioridade da pagina
} Pagina;

// Funcao para encontrar a pagina com menor prioridade
int encontrarMenorPrioridade(Pagina *paginas, int numPaginas) {
    int indiceMenorPrioridade = 0;
    int menorPrioridade = paginas[0].prioridade;

    for (int i = 1; i < numPaginas; i++) {
        if (paginas[i].prioridade < menorPrioridade) {
            indiceMenorPrioridade = i;
            menorPrioridade = paginas[i].prioridade;
        }
    }

    return indiceMenorPrioridade;
}

int main() {
    int numQuadros;
    printf("Digite a quantidade de quadros na memoria: ");
    scanf("%d", &numQuadros);

    int numReferencias;
    printf("Digite a quantidade de referencias: ");
    scanf("%d", &numReferencias);

    int *referencias = (int *)malloc(numReferencias * sizeof(int));
    int *prioridades = (int *)malloc(numReferencias * sizeof(int));
    printf("Digite as referencias e suas prioridades:\n");
    for (int i = 0; i < numReferencias; i++) {
        printf("Referencia %d: ", i + 1);
        scanf("%d", &referencias[i]);
        printf("Prioridade da referencia %d: ", i + 1);
        scanf("%d", &prioridades[i]);
    }

    Pagina *quadros = (Pagina *)malloc(numQuadros * sizeof(Pagina));
    for (int i = 0; i < numQuadros; i++) {
        quadros[i].numeroPagina = -1; // Inicializa com -1 para indicar que o quadro esta vazio
        quadros[i].prioridade = 0; // Inicializa com 0 a prioridade
    }

    int numFaltas = 0;

    for (int i = 0; i < numReferencias; i++) {
        int faltaPagina = 1; // Assumindo que havera uma falta de pagina

        // Verifica se a pagina ja esta na memoria
        for (int j = 0; j < numQuadros; j++) {
            if (quadros[j].numeroPagina == referencias[i]) {
                quadros[j].prioridade = prioridades[i]; // Atualiza a prioridade
                faltaPagina = 0; // Nao ha falta de pagina
                break;
            }
        }

        // Se houver falta de pagina
        if (faltaPagina) {
            int indiceMenorPrioridade = encontrarMenorPrioridade(quadros, numQuadros);
            quadros[indiceMenorPrioridade].numeroPagina = referencias[i];
            quadros[indiceMenorPrioridade].prioridade = prioridades[i];
            numFaltas++;
        }
    }

    printf("\nConteudo final dos quadros de memoria:\n");
    for (int i = 0; i < numQuadros; i++) {
        printf("Quadro %d: Pagina %d (Prioridade %d)\n", i + 1, quadros[i].numeroPagina, quadros[i].prioridade);
    }

    printf("\nQuantidade de faltas de pagina: %d\n", numFaltas);

    free(referencias);
    free(prioridades);
    free(quadros);

    return 0;
}