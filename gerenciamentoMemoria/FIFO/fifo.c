#include <stdio.h>
#include <stdlib.h>

// Estrutura de uma página de memória
typedef struct {
    int numeroPagina;
} Pagina;

// Função para inicializar uma página de memória
Pagina inicializarPagina(int numeroPagina) {
    Pagina pagina;
    pagina.numeroPagina = numeroPagina;
    return pagina;
}

// Função para encontrar a página a ser substituída usando FIFO
int encontrarPaginaFIFO(int *proximaSubstituicao, int numPaginas) {
    int indice = *proximaSubstituicao;
    *proximaSubstituicao = (*proximaSubstituicao + 1) % numPaginas;
    return indice;
}

// Função principal para simular a substituição de página usando FIFO
void simularFIFO(int *referencias, int numReferencias, int numFrames) {
    Pagina *paginas = (Pagina *)malloc(numFrames * sizeof(Pagina));
    int faltasPagina = 0;
    int proximaSubstituicao = 0; // Indica qual página será substituída a seguir

    // Inicializar as páginas
    for (int i = 0; i < numFrames; i++) {
        paginas[i] = inicializarPagina(-1); // Inicialmente, todas as páginas estão vazias
    }

    // Simulação
    for (int i = 0; i < numReferencias; i++) {
        int paginaAtual = referencias[i];
        int paginaEncontrada = 0;

        // Verificar se a página já está na memória
        for (int j = 0; j < numFrames; j++) {
            if (paginas[j].numeroPagina == paginaAtual) {
                paginaEncontrada = 1;
                break;
            }
        }

        // Se a página não estiver na memória, substituir a página seguindo a ordem FIFO
        if (!paginaEncontrada) {
            int indicePaginaFIFO = encontrarPaginaFIFO(&proximaSubstituicao, numFrames);
            paginas[indicePaginaFIFO].numeroPagina = paginaAtual;
            faltasPagina++;
        }
    }

    // Imprimir resultados
    printf("FIFO:\n");
    printf("Paginas de memoria final: ");
    for (int i = 0; i < numFrames; i++) {
        printf("%d ", paginas[i].numeroPagina);
    }
    printf("\n");
    printf("Quantidade de faltas de pagina: %d\n", faltasPagina);

    free(paginas);
}

int main() {
    int numReferencias, numFrames;

    // Obter entrada do usuário
    printf("Digite o numero de referencias: ");
    scanf("%d", &numReferencias);
    int referencias[numReferencias];
    printf("Digite as referencias: ");
    for (int i = 0; i < numReferencias; i++) {
        scanf("%d", &referencias[i]);
    }
    printf("Digite o numero de paginas de memoria: ");
    scanf("%d", &numFrames);

    // Simular FIFO
    simularFIFO(referencias, numReferencias, numFrames);

    return 0;
}