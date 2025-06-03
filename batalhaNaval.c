#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// Função para imprimir o tabuleiro com letras e números
void imprimirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Imprime cabeçalho com letras das colunas
    printf("   ");  // Espaço para alinhar com números das linhas
    for (char letra = 'A'; letra < 'A' + TAMANHO_TABULEIRO; letra++) {
        printf(" %c", letra);
    }
    printf("\n");

    // Imprime cada linha do tabuleiro com número da linha
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i + 1);  // Números da linha (1 a 10)
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" %d", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Coordenadas do navio horizontal (linha 3, coluna E)
    int linha_horizontal = 2;     // Linha 3
    int coluna_horizontal = 4;    // Coluna E

    // Coordenadas do navio vertical (linha 6, coluna B)
    int linha_vertical = 5;       // Linha 6
    int coluna_vertical = 1;      // Coluna B

    // Valida se cabem no tabuleiro
    if (coluna_horizontal + TAMANHO_NAVIO > TAMANHO_TABULEIRO ||
        linha_vertical + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        printf("Erro: Navios fora dos limites do tabuleiro.\n");
        return 1;
    }

    // Verifica sobreposição
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha_horizontal][coluna_horizontal + i] == NAVIO ||
            tabuleiro[linha_vertical + i][coluna_vertical] == NAVIO) {
            printf("Erro: Sobreposição de navios.\n");
            return 1;
        }
    }

    // Posiciona navio horizontal
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha_horizontal][coluna_horizontal + i] = NAVIO;
    }

    // Posiciona navio vertical
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha_vertical + i][coluna_vertical] = NAVIO;
    }

    // Exibe o tabuleiro
    imprimirTabuleiro(tabuleiro);

    return 0;
}
