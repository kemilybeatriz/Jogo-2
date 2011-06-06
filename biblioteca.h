#include <stdio.h>
#include <string.h>
#include <time.h>
#include "janelas.h"

#define LINHA 8 //Tamanho das linhas
#define COLUNA 8 //Tamanho das colunas

// Limites
#define LIM_MIN_X 2
#define LIM_MIN_Y 2
#define LIM_MAX_X 32
#define LIM_MAX_Y 21

#define TEMPO_INICIAL 120 // Tempo inicial do jogo em segundos

//Caracteres das frutas
#define FRUTA_0 14
#define FRUTA_1 3
#define FRUTA_2 4
#define FRUTA_3 5
#define FRUTA_4 6

// caracteres da borda do cenario
#define BORDA_HORIZONTAL 205
#define BORDA_VERTICAL 186
#define BORDA_SUP_ESQUERDA 201
#define BORDA_INF_ESQUERDA 200
#define BORDA_SUP_DIREITA 187
#define BORDA_INF_DIREITA 188

void menu();
void bordasJogo();
void iniciaMatriz(int m[LINHA][COLUNA]);
void fazVarredura(int m[LINHA][COLUNA]);

void menu()
{
    printf("1 - Instrucoes sobre a pontuacao\n");
    printf("2 - Iniciar jogo\n");
    printf("3 - Sair\n");
}

void bordasJogo()
{
    int i, j;

    // Imprime a borda superior
    gotoxy(LIM_MIN_X, LIM_MIN_Y);
    printf("%c", BORDA_SUP_ESQUERDA);
    for(i=LIM_MIN_X+1; i<LIM_MAX_X; i++)
    {
        gotoxy(i, LIM_MIN_Y);
        printf("%c", BORDA_HORIZONTAL);
    }
    gotoxy(i, LIM_MIN_Y);
    printf("%c", BORDA_SUP_DIREITA);

    // Imprime as bordas laterais
    for(i=LIM_MIN_Y+1; i<LIM_MAX_Y; i++)
    {
        gotoxy(LIM_MIN_X, i);
        printf("%c", BORDA_VERTICAL);
        gotoxy(LIM_MAX_X, i);
        printf("%c", BORDA_VERTICAL);
    }

    // Imprime a borda inferior
    gotoxy(LIM_MIN_X, LIM_MAX_Y);
    printf("%c", BORDA_INF_ESQUERDA);
    for(i=LIM_MIN_X+1; i<LIM_MAX_X; i++)
    {
        gotoxy(i, LIM_MAX_Y);
        printf("%c", BORDA_HORIZONTAL);
    }
    gotoxy(i, LIM_MAX_Y);
    printf("%c", BORDA_INF_DIREITA);

    // Imprime índices
    for(i=LIM_MIN_X+6, j=65; j<65+LINHA; i=i+3, j++)
    {
        gotoxy(i, LIM_MIN_Y+1);
        printf("%c", j);
    }
    for(i=LIM_MIN_Y+3, j=1; j<1+COLUNA; i=i+2, j++)
    {
        gotoxy(LIM_MIN_X+2, i);
        printf("%d", j);
    }
}

void iniciaMatriz(int m[LINHA][COLUNA])
{
    int i, j;

    srand(time(NULL));
    for(i=0; i<LINHA; i++)
    {
        for(j=0; j<COLUNA; j++)
        {
            m[i][j]= rand()%5;
        }
    }
}

void fazVarredura(int m[LINHA][COLUNA])
{

}

