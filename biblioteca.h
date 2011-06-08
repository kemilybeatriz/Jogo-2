#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "janelas.h"

#define LINHA 8 // número de linhas
#define COLUNA 8 // número de colunas

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
int fazVarredura(int m[LINHA][COLUNA]);
int descobrePosJ(int x);
int descobrePosI(int y);
void exibeElemento(int elemento, int x, int y);
void trocaElementos(int m[LINHA][COLUNA], int x1, int y1, int x2, int y2);

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
    int i, j, x;

    srand(time(NULL));
    for(i=0; i<LINHA; i++)
    {
        for(j=0; j<COLUNA; j++)
        {
            x = rand()%5;
            if(x == 0)
            {
                m[i][j] = FRUTA_0;
            }
            else if(x == 1)
            {
                m[i][j] = FRUTA_1;
            }
            else if(x == 2)
            {
                m[i][j] = FRUTA_2;
            }
            else if(x == 3)
            {
                m[i][j] = FRUTA_3;
            }
            else if(x == 4)
            {
                m[i][j] = FRUTA_4;
            }
        }
    }
}

int fazVarredura(int m[LINHA][COLUNA])
{
    int i, j;
    int a, b, c;
    int aux, cont, cont2=0, cont3=0;

    // faz a varredura horizontal
    for(i=0; i<LINHA; i++)
    {
        cont = 0;
        aux = m[i][0];
        a = 0;
        for(j=1; j<COLUNA; j++)
        {
            if( aux == m[i][j] )
            {
                cont2++;
                cont++;
                if( (j+1==COLUNA) && (cont>=2) )
                {
                    cont3++;
                }
            }
            else
            {
                if(cont>=2)
                {
                    cont3++;
                    if( i>0 )
                    {
                        for(b=j-1; b>=a; b--)
                        {
                            for(c=i; c>0; c--)
                            {
                                m[c][b] = m[c-1][b];
                            }
                        }
                    }
                    for(b=j-1; b>=a; b--)
                    {
                        m[0][b] = 0;
                    }

                }
                cont = 0;
                aux = m[i][j];
                a = j;
            }
        }
    }
    // faz a varredura vertical
    /*for(j=0; j<COLUNA; j++)
    {
        cont = 0;
        aux = m[0][j];
        for(i=1; i<LINHA; i++)
        {
            if( aux == m[i][j] )
            {
                cont++;
                cont2++;
            }
            else
            {
                cont = 0;
                aux = m[i][j];
            }
        }
    }*/

    return cont3;
}

int descobrePosJ(int x)
{
    int i, j;
    for(i=0, j=LIM_MIN_X+6; i<LINHA; i++, j=j+3)
    {
        if(j==x)
        {
            return i;
        }
    }
    return 0;
}

int descobrePosI(int y)
{
    int i, j;
    for(i=0, j=LIM_MIN_Y+3; i<COLUNA; i++, j=j+2)
    {
        if(j==y)
        {
            return i;
        }
    }
    return 0;
}

void exibeElemento(int elemento, int x, int y)
{
    if(elemento == FRUTA_0)
    {
        textcolor(LIGHTGREEN);
    }
    else if(elemento == FRUTA_1)
    {
        textcolor(LIGHTRED);
    }
    else if(elemento == FRUTA_2)
    {
        textcolor(LIGHTCYAN);
    }
    else if(elemento == FRUTA_3)
    {
        textcolor(LIGHTMAGENTA);
    }
    else if(elemento == FRUTA_4)
    {
        textcolor(YELLOW);
    }
    gotoxy(x, y);
    printf("%c", elemento);
    textcolor(LIGHTGRAY);
}

void trocaElementos(int m[LINHA][COLUNA], int x1, int y1, int x2, int y2)
{
    int i, j, aux;

    x1 = descobrePosJ(x1);
    y1 = descobrePosI(y1);
    x2 = descobrePosJ(x2);
    y2 = descobrePosI(y2);

    aux = m[y1][x1];
    m[y1][x1] = m[y2][x2];
    m[y2][x2] = aux;
}

