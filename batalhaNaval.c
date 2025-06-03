#include <stdio.h>

#define TAM 10
#define NAVIO 3
#define OCUPADO 3
#define AGUA 0

// Função para imprimir o tabuleiro com letras e números
void imprimirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("   ");
    for (char c = 'A'; c < 'A' + TAM; c++) {
        printf(" %c", c);
    }
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < TAM; j++) {
            printf(" %d", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar se as posições estão dentro dos limites
int dentroDosLimites(int linha, int coluna) {
    return linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM;
}

// Verifica se pode posicionar o navio (sem sobreposição)
int podePosicionar(int tabuleiro[TAM][TAM], int linha, int coluna, int dLinha, int dColuna) {
    for (int i = 0; i < NAVIO; i++) {
        int l = linha + i * dLinha;
        int c = coluna + i * dColuna;
        if (!dentroDosLimites(l, c) || tabuleiro[l][c] == OCUPADO)
            return 0; // Fora dos limites ou sobreposto
    }
    return 1;
}

// Posiciona o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, int dLinha, int dColuna) {
    for (int i = 0; i < NAVIO; i++) {
        int l = linha + i * dLinha;
        int c = coluna + i * dColuna;
        tabuleiro[l][c] = OCUPADO;
    }
}

int main() {
    int tabuleiro[TAM][TAM] = {0};

    // Definir as posições e direções dos 4 navios
    // Formato: linha inicial, coluna inicial, direção linha, direção coluna

    // Navio 1 - Horizontal (linha 2, col B até D)
    int l1 = 1, c1 = 1, dl1 = 0, dc1 = 1;

    // Navio 2 - Vertical (linha 5, col H até J)
    int l2 = 4, c2 = 7, dl2 = 1, dc2 = 0;

    // Navio 3 - Diagonal principal (\) - (linha 0, col 0 até 2)
    int l3 = 0, c3 = 0, dl3 = 1, dc3 = 1;

    // Navio 4 - Diagonal secundária (/) - (linha 2, col 7 até 5)
    int l4 = 2, c4 = 7, dl4 = 1, dc4 = -1;

    // Tenta posicionar todos os navios com verificação
    if (podePosicionar(tabuleiro, l1, c1, dl1, dc1))
        posicionarNavio(tabuleiro, l1, c1, dl1, dc1);
    else
        printf("Erro ao posicionar navio 1 (horizontal).\n");

    if (podePosicionar(tabuleiro, l2, c2, dl2, dc2))
        posicionarNavio(tabuleiro, l2, c2, dl2, dc2);
    else
        printf("Erro ao posicionar navio 2 (vertical).\n");

    if (podePosicionar(tabuleiro, l3, c3, dl3, dc3))
        posicionarNavio(tabuleiro, l3, c3, dl3, dc3);
    else
        printf("Erro ao posicionar navio 3 (diagonal \\).\n");

    if (podePosicionar(tabuleiro, l4, c4, dl4, dc4))
        posicionarNavio(tabuleiro, l4, c4, dl4, dc4);
    else
        printf("Erro ao posicionar navio 4 (diagonal /).\n");

    // Exibir o tabuleiro final
    imprimirTabuleiro(tabuleiro);

    return 0;
}
