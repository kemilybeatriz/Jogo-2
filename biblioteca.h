#include <stdio.h>
#include <stdlib.h>
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
int sorteiaElemento();

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

    // Imprime índices do jogo
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

    for(i=0; i<LINHA; i++)
    {
        for(j=0; j<COLUNA; j++)
        {
            m[i][j] = sorteiaElemento();
            // aguarda 20ms para que não sorteie o mesmo elemento
            Sleep(20);
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
                cont++;
                // para quando a combinaçao estiver na ultima coluna
                if( (j+1==COLUNA) && (cont>=2) )
                {
                    if( i>0 )
                    {
                        // faz elementos descerem uma posição
                        for(b=j; b>=a; b--)
                        {
                            for(c=i; c>0; c--)
                            {
                                m[c][b] = m[c-1][b];
                            }
                        }
                    }
                    // sorteia elementos para a primeira linha
                    for(b=j; b>=a; b--)
                    {
                        // só sai do laço se não for repetido
                        if(b==j) // caso seja a ultima coluna
                        {
                            do
                            {
                                m[0][b] = sorteiaElemento();
                            }
                            while( m[0][b]==m[1][b] );
                        }
                        else
                        {
                            do
                            {
                                m[0][b] = sorteiaElemento();
                            }
                            while( m[0][b]==m[0][b+1] || m[0][b]==m[1][b] );
                        }
                    }
                }
            }
            else
            {
                // se houver alguma combinacao
                if(cont>=2)
                {
                    if( i>0 )
                    {
                        // faz elementos descerem uma posição
                        for(b=j-1; b>=a; b--)
                        {
                            for(c=i; c>0; c--)
                            {
                                m[c][b] = m[c-1][b];
                            }
                        }
                    }
                    // sorteia elementos para a primeira linha
                    for(b=j-1; b>=a; b--)
                    {
                        // só sai do laço se não for repetido
                        do
                        {
                            m[0][b] = sorteiaElemento();
                        }
                        while( m[0][b]==m[0][b+1] || m[0][b]==m[1][b] );
                    }
                }
                cont = 0;
                aux = m[i][j];
                a = j;
            }
        }
    }
    // faz a varredura vertical
    for(j=0; j<COLUNA; j++)
    {
        cont = 0;
        aux = m[0][j];
        a = 0;
        for(i=1; i<LINHA; i++)
        {
            if( aux == m[i][j] )
            {
                cont++;
                cont2++;
            }
            else
            {
                // se houver alguma combinacao
                if(cont>=2)
                {
                    /*if( i>0 )
                    {
                        // faz elementos descerem uma posição
                        for(c=i-1; c>0; c--)
                        {
                            m[c][j] = m[c-1][j];
                        }
                    }
                    // sorteia o elemento da primeira linha
                    // só sai do laço se não for repetido
                    do
                    {
                        m[0][j] = sorteiaElemento();
                    }
                    while( m[0][j]==m[0][b+1] || m[0][b]==m[1][b] );*/
                    cont3++;
                }
                cont = 0;
                aux = m[i][j];
                a = i;
            }
        }
    }
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
    switch(elemento)
    {
    case FRUTA_0:
        textcolor(LIGHTGREEN);
        break;
    case FRUTA_1:
        textcolor(LIGHTRED);
        break;
    case FRUTA_2:
        textcolor(LIGHTCYAN);
        break;
    case FRUTA_3:
        textcolor(LIGHTMAGENTA);
        break;
    case FRUTA_4:
        textcolor(YELLOW);
        break;
    }
    gotoxy(x, y);
    printf("%c", elemento);
    textcolor(LIGHTGRAY);
}

void trocaElementos(int m[LINHA][COLUNA], int x1, int y1, int x2, int y2)
{
    int aux;

    x1 = descobrePosJ(x1);
    y1 = descobrePosI(y1);
    x2 = descobrePosJ(x2);
    y2 = descobrePosI(y2);

    aux = m[y1][x1];
    m[y1][x1] = m[y2][x2];
    m[y2][x2] = aux;
}

int sorteiaElemento()
{
    // a função GetTickCount() da biblioteca windows.h
    // possui uma resolução maior do que a time(NULL);

    //srand( time(NULL) );
    srand( GetTickCount() );

    switch( rand()%5 )
    {
    case 0:
        return FRUTA_0;
    case 1:
        return FRUTA_1;
    case 2:
        return FRUTA_2;
    case 3:
        return FRUTA_3;
    case 4:
        return FRUTA_4;
    }
}

