#include <stdio.h>
#include <stdlib.h>

#define TAM 10
#define TAM_HAB 5

// Imprime o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("Tabuleiro de Batalha Naval:\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Aplica uma matriz de habilidade no tabuleiro, centrada em (linha, coluna)
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[TAM_HAB][TAM_HAB], int linha, int coluna) {
    int offset = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int x = linha + i - offset;
            int y = coluna + j - offset;
            if (x >= 0 && x < TAM && y >= 0 && y < TAM) {
                if (habilidade[i][j] == 1 && tabuleiro[x][y] == 0) {
                    tabuleiro[x][y] = 5;  // Marca área afetada pela habilidade
                }
            }
        }
    }
}

// Cria a matriz em formato de cone (pirâmide invertida)
void gerarCone(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            matriz[i][j] = 0;
        }
    }
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = TAM_HAB / 2 - i; j <= TAM_HAB / 2 + i; j++) {
            if (j >= 0 && j < TAM_HAB) {
                matriz[i][j] = 1;
            }
        }
    }
}

// Cria matriz em formato de cruz
void gerarCruz(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            matriz[i][j] = (i == TAM_HAB / 2 || j == TAM_HAB / 2) ? 1 : 0;
        }
    }
}

// Cria matriz em formato de octaedro (losango)
void gerarOctaedro(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int dist = abs(i - TAM_HAB / 2) + abs(j - TAM_HAB / 2);
            matriz[i][j] = (dist <= TAM_HAB / 2) ? 1 : 0;
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM] = {0};

    // Posiciona 4 navios (2 horizontais/verticais + 2 diagonais)
    // Horizontal
    tabuleiro[0][0] = tabuleiro[0][1] = tabuleiro[0][2] = 3;
    // Vertical
    tabuleiro[2][2] = tabuleiro[3][2] = tabuleiro[4][2] = 3;
    // Diagonal principal
    tabuleiro[5][5] = tabuleiro[6][6] = tabuleiro[7][7] = 3;
    // Diagonal inversa
    tabuleiro[6][3] = tabuleiro[7][2] = tabuleiro[8][1] = 3;

    // Matrizes de habilidades
    int cone[TAM_HAB][TAM_HAB], cruz[TAM_HAB][TAM_HAB], octaedro[TAM_HAB][TAM_HAB];

    gerarCone(cone);
    gerarCruz(cruz);
    gerarOctaedro(octaedro);

    // Aplicando habilidades no tabuleiro (origens fixas)
    aplicarHabilidade(tabuleiro, cone, 2, 7);
    aplicarHabilidade(tabuleiro, cruz, 5, 5);
    aplicarHabilidade(tabuleiro, octaedro, 8, 8);

    // Imprimir resultado final
    imprimirTabuleiro(tabuleiro);

    return 0;
}