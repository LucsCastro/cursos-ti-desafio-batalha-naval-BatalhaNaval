#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

int main() {
    
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0}; // 0 representa água, 3 representa navio

// Definindo coordenadas iniciais do navio
    int linhaV = 2, colunaV = 2; // Coordenada inicial do navio vertical 
    int linhaH = 5, colunaH = 5; // Coordenada inicial do navio horizontal

// Validação de limites e sobreposição
    int erro = 0;

// Validar o navio vertical
    if (linhaV + TAM_NAVIO > TAM_TABULEIRO)
    {
        printf("Erro 🚫: Navio vertical fora dos limites do tabuleiro.\n");
        erro = 1;
    }

// Validar o navio horizontal
    if (colunaH + TAM_NAVIO > TAM_TABULEIRO)
    {
        printf("Erro 🚫: Navio horizontal fora dos limites do tabuleiro.\n");
        erro = 1;
    }

// Verificar sobreposição
   if (erro == 0)
   {
    // Posicionando o navio vertical
    for (int i = 0; i < TAM_NAVIO; i++)
    {
        tabuleiro[linhaV + i][colunaV] = 3;
    }

    // Posicionando o navio horizontal
    for (int i = 0; i < TAM_NAVIO; i++)
    {
        if (tabuleiro[linhaH][colunaH + i] == 3)
        {
            erro = 2; // Sobreposição detectada
            break;
        }
        tabuleiro[linhaH][colunaH + i] = 3;
    }
 }

// Exibição do Tabuleiro
   if (erro == 1)
   {
    printf("Erro 🚫: Navio fora dos limites do tabuleiro!\n");
   }else if (erro == 2)
   {
    printf("Erro 🚫: Sobreposição de navios detectada!\n");
   }else
   {
    printf("| Batalha Naval 🚢 - Tabuleiro |\n");
    printf("\n");
// Imprimir o Cabeçalho do Tabuleiro
    printf("   "); // Espaço para o alinhamento do cabeçalho

    for (char c = 'A'; c < 'A' + TAM_TABULEIRO; c++)
    {
        printf("%c ", c);
    }
    printf("\n");
//imprimir as Linhas com os Números e o Conteúdo do Tabuleiro   
     for (int i = 0; i < TAM_TABULEIRO; i++)
     {
       printf("%2d ", i + 1); // O %2d serve para alinhar números de 1 e 2 dígitos (ex: o 10)

       for (int j = 0; j < TAM_TABULEIRO; j++)
       {
        printf("%d ", tabuleiro[i][j]);
       }
      printf("\n"); 
     }
     
   }
   
   
   
return 0;
}
