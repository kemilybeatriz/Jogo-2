#include <stdio.h>
#include <string.h>
#include <time.h>
#include "janelas.h"

#define LINHA 8 //Tamanho das linhas
#define COLUNA 8 //Tamanho das colunas

//Caracteres das frutas
#define FRUTA_0 14
#define FRUTA_1 3
#define FRUTA_2 4
#define FRUTA_3 5
#define FRUTA_4 6

//Letra inicial do índice horizontal
#define LETRA_INICIAL 65

#define BORDA_HORIZONTAL 205
#define BORDA_VERTICAL 186
#define BORDA_SUP_ESQUERDA 201
#define BORDA_INF_ESQUERDA 200
#define BORDA_INF_DIREITA 188
#define BORDA_SUP_DIREITA 187

void menu();
void sorteiaFrutas(int matriz[LINHA][COLUNA]);
void exibeCenario(int matriz[LINHA][COLUNA]);
void fazVarredura(int matriz[LINHA][COLUNA]);

void menu()
{
    printf("1 - Instrucoes sobre a pontuacao\n");
    printf("2 - Iniciar jogo\n");
    printf("3 - Sair\n");
}

void sorteiaFrutas(int matriz[LINHA][COLUNA])
{
    int i, j;

    srand(time(NULL));
    for(i=0; i<LINHA; i++)
    {
        for(j=0; j<COLUNA; j++)
        {
            matriz[i][j]= rand()%5;
        }
    }
}

void exibeCenario(int matriz[LINHA][COLUNA])
{
    int i, j;

    printf("%c", BORDA_SUP_ESQUERDA);
    for(i=0; i<=LINHA+14; i++) //Imprime a borda horizontal superior
    {
        printf("%c", BORDA_HORIZONTAL);
    }
    printf("%c", BORDA_SUP_DIREITA);

    printf("\n");
    printf("%c\t", BORDA_VERTICAL);

    for(i=LETRA_INICIAL; i<LETRA_INICIAL+LINHA; i++) //Imprime o índice horizontal de letras
    {
        printf("%c ", i);
    }

    printf("%c\n%c\t\t\t%c\n", BORDA_VERTICAL, BORDA_VERTICAL, BORDA_VERTICAL); //Imprime a borda vertical esquerda acima do índice numérico

    for(i=0; i<LINHA; i++)
    {
        printf("%c ", BORDA_VERTICAL); //Imprime a borda vertical esquerda ao lado do índice numérico
        printf("%d", i+1);            //Imprime o índice verdical numérico
        printf("\t");

        for(j=0; j<COLUNA; j++)    //Imprime os caracteres das frutas
        {
            if(matriz[i][j] == 0)
            {
                textcolor(LIGHTGREEN);
                printf("%c ", FRUTA_0);
            }
            else if(matriz[i][j] == 1)
            {
                textcolor(LIGHTRED);
                printf("%c ", FRUTA_1);
            }

            else if(matriz[i][j] == 2)
            {
                textcolor(LIGHTCYAN);
                printf("%c ", FRUTA_2);
            }
            else if(matriz[i][j] == 3)
            {
                textcolor(LIGHTMAGENTA);
                printf("%c ", FRUTA_3);
            }
            else if(matriz[i][j] == 4)
            {
                textcolor(YELLOW);
                printf("%c ", FRUTA_4);
            }
            textcolor(LIGHTGRAY);
        }
        printf("%c ", BORDA_VERTICAL); //Imprime a borda vertical direita do índice numérico
        printf("\n");
    }
    printf("%c", BORDA_INF_ESQUERDA); //imprime borda inferior esquerda
    for(i=0; i<=LINHA+14; i++)       //Imprime a borda horizontal inferior
    {
        printf("%c", BORDA_HORIZONTAL);
    }
    printf("%c", BORDA_INF_DIREITA); //Imprime a borda inferior direita

}

