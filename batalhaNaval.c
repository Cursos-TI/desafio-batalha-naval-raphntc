#include <stdio.h>

#define TAM 10
#define NAVIO 3
#define OCUPADO 3
#define AGUA 0
#define HABILIDADE 5
#define TAM_HAB 5

// Função para imprimir o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("   ");
    for (char c = 'A'; c < 'A' + TAM; c++) {
        printf(" %c", c);
    }
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == AGUA) printf(" ~");
            else if (tabuleiro[i][j] == OCUPADO) printf(" X");
            else if (tabuleiro[i][j] == HABILIDADE) printf(" *");
        }
        printf("\n");
    }
}

// Função para verificar se coordenada está dentro dos limites
int dentroDosLimites(int linha, int coluna) {
    return linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM;
}

// Verifica e posiciona navio (direção dLinha, dColuna)
int posicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, int dLinha, int dColuna) {
    for (int i = 0; i < NAVIO; i++) {
        int l = linha + i * dLinha;
        int c = coluna + i * dColuna;
        if (!dentroDosLimites(l, c) || tabuleiro[l][c] != AGUA)
            return 0; // Fora dos limites ou já ocupado
    }
    for (int i = 0; i < NAVIO; i++) {
        tabuleiro[linha + i * dLinha][coluna + i * dColuna] = OCUPADO;
    }
    return 1;
}

// Cria matriz de habilidade: Cone (expande para baixo)
void criarCone(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i >= j && i >= TAM_HAB - 1 - j)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Cria matriz de habilidade: Cruz (linha + coluna centrais)
void criarCruz(int matriz[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == centro || j == centro)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Cria matriz de habilidade: Octaedro (losango)
void criarOctaedro(int matriz[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Aplica matriz de habilidade ao tabuleiro no ponto (linhaOrigem, colOrigem)
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[TAM_HAB][TAM_HAB], int linhaOrigem, int colOrigem) {
    int offset = TAM_HAB / 2;

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (habilidade[i][j] == 1) {
                int l = linhaOrigem - offset + i;
                int c = colOrigem - offset + j;
                if (dentroDosLimites(l, c) && tabuleiro[l][c] == AGUA)
                    tabuleiro[l][c] = HABILIDADE;
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM] = {0};

    // Posiciona navios
    posicionarNavio(tabuleiro, 1, 1, 0, 1); // Horizontal
    posicionarNavio(tabuleiro, 4, 7, 1, 0); // Vertical
    posicionarNavio(tabuleiro, 0, 0, 1, 1); // Diagonal \
    posicionarNavio(tabuleiro, 2, 7, 1, -1); // Diagonal /

    // Matrizes de habilidade
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Aplicar habilidades em posições específicas
    aplicarHabilidade(tabuleiro, cone, 6, 2);       // Cone com origem em (6, C)
    aplicarHabilidade(tabuleiro, cruz, 5, 5);       // Cruz com origem em (5, F)
    aplicarHabilidade(tabuleiro, octaedro, 7, 7);   // Octaedro com origem em (7, H)

    // Exibe o tabuleiro
    imprimirTabuleiro(tabuleiro);

    return 0;
}
