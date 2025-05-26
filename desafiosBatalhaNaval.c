#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define MAR 0
#define NAVIO 3

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

    // Inicializa o tabuleiro com água (valor 0)
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = MAR;
        }
    }

    // Coordenadas iniciais dos navios (fixas)
    int linhaNavioHorizontal = 2;
    int colunaNavioHorizontal = 1;

    int linhaNavioVertical = 5;
    int colunaNavioVertical = 7;

    // Validação: Verifica se cabem no tabuleiro (sem ultrapassar limites)
    if (colunaNavioHorizontal + TAM_NAVIO <= TAM_TABULEIRO &&
        linhaNavioVertical + TAM_NAVIO <= TAM_TABULEIRO) {

        // Posiciona o navio horizontal
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linhaNavioHorizontal][colunaNavioHorizontal + i] = NAVIO;
        }

        // Verifica sobreposição com o navio horizontal antes de posicionar o vertical
        int sobreposicao = 0;
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linhaNavioVertical + i][colunaNavioVertical] == NAVIO) {
                sobreposicao = 1;
                break;
            }
        }

        if (!sobreposicao) {
            // Posiciona o navio vertical
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaNavioVertical + i][colunaNavioVertical] = NAVIO;
            }
        } else {
            printf("Erro: Navios se sobrepõem! O navio vertical não foi posicionado.\n");
        }
    } else {
        printf("Erro: Coordenadas inválidas. Navios não cabem no tabuleiro.\n");
    }

    // Exibe o tabuleiro
    printf("\n=== TABULEIRO ===\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}