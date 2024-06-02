#include <stdio.h>
#include <stdlib.h>

// Estrutura de uma pagina na memoria
typedef struct {
    int numeroPagina; // Numero da pagina
    int referenciada; // Bit de referencia
} Pagina;

// Funcao para encontrar a pagina menos recentemente usada
int encontrarLRU(Pagina *paginas, int numPaginas) {
    int indiceLRU = 0;
    int referenciaLRU = paginas[0].referenciada;

    for (int i = 1; i < numPaginas; i++) {
        if (paginas[i].referenciada < referenciaLRU) {
            indiceLRU = i;
            referenciaLRU = paginas[i].referenciada;
        }
    }

    return indiceLRU;
}

int main() {
    int numQuadros;
    printf("Digite a quantidade de quadros na memoria: ");
    scanf("%d", &numQuadros);

    int numReferencias;
    printf("Digite a quantidade de referencias: ");
    scanf("%d", &numReferencias);

    int *referencias = (int *)malloc(numReferencias * sizeof(int));
    printf("Digite as referencias: ");
    for (int i = 0; i < numReferencias; i++) {
        scanf("%d", &referencias[i]);
    }

    Pagina *quadros = (Pagina *)malloc(numQuadros * sizeof(Pagina));
    for (int i = 0; i < numQuadros; i++) {
        quadros[i].numeroPagina = -1; // Inicializa com -1 para indicar que o quadro esta vazio
        quadros[i].referenciada = 0; // Inicializa com 0 o bit de referencia
    }

    int numFaltas = 0;

    for (int i = 0; i < numReferencias; i++) {
        int faltaPagina = 1; // Assumindo que havera uma falta de pagina

        // Verifica se a pagina ja esta na memoria
        for (int j = 0; j < numQuadros; j++) {
            if (quadros[j].numeroPagina == referencias[i]) {
                quadros[j].referenciada = 1; // Marca como referenciada
                faltaPagina = 0; // Nao ha falta de pagina
                break;
            }
        }

        // Se houver falta de pagina
        if (faltaPagina) {
            int indiceLRU = encontrarLRU(quadros, numQuadros);
            quadros[indiceLRU].numeroPagina = referencias[i];
            quadros[indiceLRU].referenciada = 1;
            numFaltas++;
        }
    }

    printf("\nConteudo final dos quadros de memoria:\n");
    for (int i = 0; i < numQuadros; i++) {
        printf("Quadro %d: Pagina %d\n", i+1, quadros[i].numeroPagina);
    }

    printf("\nQuantidade de faltas de pagina: %d\n", numFaltas);

    free(referencias);
    free(quadros);

    return 0;
}