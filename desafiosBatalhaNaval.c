#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define MAR 0
#define NAVIO 3
#define OCUPADO 3
#define HABILIDADE 5
#define TAM_HABILIDADE 5

// Aplica matriz da habilidade ao tabuleiro com base na origem
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int origemLinha, int origemColuna) {
    int centro = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int linhaTab = origemLinha - centro + i;
                int colunaTab = origemColuna - centro + j;

                if (linhaTab >= 0 && linhaTab < TAM_TABULEIRO &&
                    colunaTab >= 0 && colunaTab < TAM_TABULEIRO) {
                    if (tabuleiro[linhaTab][colunaTab] == MAR) {
                        tabuleiro[linhaTab][colunaTab] = HABILIDADE;
                    }
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

    // Inicializa o tabuleiro com água (0)
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = MAR;
        }
    }

    // Coordenadas dos navios fixos
    int linhaNavioHorizontal = 2, colunaNavioHorizontal = 1;
    int linhaNavioVertical = 5, colunaNavioVertical = 7;

    // Posiciona navio horizontal
    if (colunaNavioHorizontal + TAM_NAVIO <= TAM_TABULEIRO) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linhaNavioHorizontal][colunaNavioHorizontal + i] = NAVIO;
        }
    }

    // Verifica sobreposição antes de posicionar o vertical
    int sobreposicao = 0;
    if (linhaNavioVertical + TAM_NAVIO <= TAM_TABULEIRO) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linhaNavioVertical + i][colunaNavioVertical] == NAVIO) {
                sobreposicao = 1;
                break;
            }
        }

        if (!sobreposicao) {
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaNavioVertical + i][colunaNavioVertical] = NAVIO;
            }
        } else {
            printf("Erro: Sobreposição de navios! Navio vertical não posicionado.\n");
        }
    }

    // Matrizes de habilidades (cone, cruz, octaedro)
    int cone[TAM_HABILIDADE][TAM_HABILIDADE] = {0};
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE] = {0};
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE] = {0};

    int centro = TAM_HABILIDADE / 2;

    // Matriz cone (expande para baixo)
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (j >= centro - i && j <= centro + i && i <= centro) {
                cone[i][j] = 1;
            }
        }
    }

    // Matriz cruz (linha e coluna centrais)
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == centro || j == centro) {
                cruz[i][j] = 1;
            }
        }
    }

    // Matriz octaedro (losango) — sem abs()
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int distI = (i - centro >= 0) ? (i - centro) : (centro - i);
            int distJ = (j - centro >= 0) ? (j - centro) : (centro - j);
            if (distI + distJ <= centro) {
                octaedro[i][j] = 1;
            }
        }
    }

    // Aplicação das habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, cone, 2, 2);       // Cone com origem em [2][2]
    aplicarHabilidade(tabuleiro, cruz, 5, 5);       // Cruz com origem em [5][5]
    aplicarHabilidade(tabuleiro, octaedro, 7, 2);   // Octaedro com origem em [7][2]

    // Exibe o tabuleiro
    printf("\nTabuleiro Batalha Naval com Habilidades:\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}