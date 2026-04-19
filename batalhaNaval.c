#include <stdio.h>
#include <stdlib.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5
// Definição das cores para facilitar a leitura
#define COR_AGUA    "\033[0;36m" // Ciano para a água
#define COR_NAVIO   "\033[0;33m" // Amarelo para os navios
#define COR_HABILIDADE "\033[0;35m" // Magenta para habilidades
#define COR_RESET   "\033[0m"    // Volta ao normal


int main() {
    
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0}; // 0 representa água, 3 representa navio
// DEFINIÇÃO DAS MATRIZES DE HABILIDADE
    int cone[TAM_HABILIDADE][TAM_HABILIDADE] = {0};
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE] = {0};
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE] = {0};

// Definindo coordenadas iniciais do navio
    int linhaV = 1, colunaV = 8; // Coordenada inicial do navio vertical 
    int linhaH = 5, colunaH = 1; // Coordenada inicial do navio horizontal
    int linhaD1 = 0, colunaD1 = 0; // Diagonal 1 (Principal: \ )
    int linhaD2 = 7, colunaD2 = 5; // Diagonal 2 (Secundária: / ) 
// Pontos de origem das habilidades (centro da matriz 5x5)
    int origemConeL = 2, origemConeC = 5;
    int origemCruzL = 8, origemCruzC = 1;
    int origemOctaL = 6, origemOctaC = 6;

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

// Validar o navio diagonal
    if (linhaD1 + TAM_NAVIO > TAM_TABULEIRO || colunaD1 + TAM_NAVIO > TAM_TABULEIRO)
    {
        printf("Erro 🚫: Navio diagonal fora dos limites do tabuleiro.\n");
        erro = 1;
    }

//Validar o navio diagonal secundária
    if (linhaD2 + TAM_NAVIO > TAM_TABULEIRO || colunaD2 - TAM_NAVIO < -1)
    {
        printf("Erro 🚫: Navio diagonal secundária fora dos limites do tabuleiro.\n");
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
 
    // Posicionando o navio diagonal principal
    for (int i = 0; i < TAM_NAVIO; i++)
    {
        if (tabuleiro[linhaD1 + i][colunaD1 + i] == NAVIO)
        {
            erro = 2; // Sobreposição detectada
            break;
        }
        
        tabuleiro[linhaD1 + i][colunaD1 + i] = NAVIO;
    }
    
    // Posicionando o navio diagonal secundária
    for (int i = 0; i < TAM_NAVIO; i++)
    {
        if (tabuleiro[linhaD2 + i][colunaD2 - i] == NAVIO)
        {
            erro = 2; // Sobreposição detectada
            break;
        }
        
        tabuleiro[linhaD2 + i][colunaD2 - i] = NAVIO;
    }
    
   }
// Logica para posicionar as habilidades (exemplo: cone, cruz e octaedro)
   for (int i = 0; i < TAM_HABILIDADE; i++) {
      for (int j = 0; j < TAM_HABILIDADE; j++) {
         //Logica do Cone (triângolo invertido)
         if (i == 0 && j == 2) cone[i][j] = 1;
         if (i == 1 && j >= 1 && j <= 3) cone[i][j] = 1;
         if (i == 2) cone[i][j] = 1;

         //Logica da Cruz
         if (i == 2 || j == 2) cruz[i][j] = 1;

         //Logica do Octaedro (losango)
         //Usamos a distância de Manhattan: |x1-x2| + |y1-y2|
         if (abs(i - 2) + abs(j - 2) <= 2) octaedro[i][j] = 1;
      }
   }
   
//INTEGRAÇÃO NO TABULEIRO 
// Aplicando as habilidades (Sobreposição)
   for (int i = 0; i < TAM_HABILIDADE; i++) {
      for (int j = 0; j < TAM_HABILIDADE; j++) {
         // Cálculo do deslocamento: centro da matriz 5x5 é (2,2)
         int dL = i - 2; 
         int dC = j - 2;
         // Sobrepor Cone
         int bL = origemConeL + dL;
         int bC = origemConeC + dC;
         if (bL >= 0 && bL < TAM_TABULEIRO && bC >= 0 && bC < TAM_TABULEIRO && cone[i][j] == 1) {
            tabuleiro[bL][bC] = HABILIDADE; // Marca a habilidade no tabuleiro
         }
         // Sobrepor Cruz
         bL = origemCruzL + dL;
         bC = origemCruzC + dC;
         if (bL >= 0 && bL < TAM_TABULEIRO && bC >= 0 && bC < TAM_TABULEIRO && cruz[i][j] == 1) {
            tabuleiro[bL][bC] = HABILIDADE; // Marca a habilidade no tabuleiro
         }
         // Sobrepor Octaedro
         bL = origemOctaL + dL;
         bC = origemOctaC + dC;
         if (bL >= 0 && bL < TAM_TABULEIRO && bC >= 0 && bC < TAM_TABULEIRO && octaedro[i][j] == 1) {
            tabuleiro[bL][bC] = HABILIDADE; // Marca a habilidade no tabuleiro
         }
         
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
     for (int i = 0; i < TAM_TABULEIRO; i++) {
      printf("%2d ", i); // Imprime o número da linha com alinhamento

      for (int j = 0; j < TAM_TABULEIRO; j++) {
        if (tabuleiro[i][j] == AGUA) {
           printf(COR_AGUA "%d " COR_RESET, tabuleiro[i][j]); // Imprime o 0 em Ciano
        }
        else if (tabuleiro[i][j] == NAVIO) {
           printf(COR_NAVIO "%d " COR_RESET, tabuleiro[i][j]); // Imprime o 3 em Amarelo
        }
        else if (tabuleiro[i][j] == HABILIDADE) {
            printf(COR_HABILIDADE "%d " COR_RESET, tabuleiro[i][j]); // Imprime a habilidade em Roxo
        }
        
      }
      printf("\n"); 
     }
     
   }

return 0;
}

