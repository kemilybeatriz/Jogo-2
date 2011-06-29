#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "janelas.h"

#define TEMPO_INICIAL 120 // Tempo inicial do jogo em segundos

// constantes usadas na pontuação e no tempo
#define CONST_PONTOS 100
#define CONST_TEMPO 1

// caracteres das frutas
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

#define TAM_NOME 64
#define NUM_JOGS 10

struct COORDENADA
{
    int x;
    int y;
};

struct JOGADOR
{
    char nome[TAM_NOME];
    int pontos;
};

void menu();
void bordasJogo(int tam);
void iniciaMatriz(int *m, int tam);
int fazVarredura(int *m, int tam);
int descobrePosJ(int x, int tam);
int descobrePosI(int y, int tam);
void exibeElemento(int elemento, int x, int y);
void trocaElementos(int *m, int tam, int x1, int y1, int x2, int y2);
int testaTroca(int x1, int y1, int x2, int y2);
int sorteiaElemento();
void exibeInstrucoes();
void sequenciaFrutas(int a);
void calculaLimites(struct COORDENADA *lim_min, struct COORDENADA *lim_max, int tam);
void verRank(struct JOGADOR *top);

void menu()
{
    sequenciaFrutas(1);
    textcolor(WHITE);
    printf(" PAPAGAIO SEDENTO");
    sequenciaFrutas(1);
    textcolor(LIGHTGRAY);

    printf("\n\n1 - Instrucoes sobre a pontuacao\n");
    printf("2 - Iniciar jogo\n");
    printf("3 - Ver ranking\n");
    printf("4 - Determinar tamanho da matriz\n");
    printf("5 - Sair\n\n");
}

void bordasJogo(int tam)
{
    int i, j;
    struct COORDENADA lim_min;
    struct COORDENADA lim_max;

    calculaLimites(&lim_min, &lim_max, tam);

    // Imprime a borda superior
    gotoxy(lim_min.x, lim_min.y);
    printf("%c", BORDA_SUP_ESQUERDA);
    for(i=lim_min.x+1; i<lim_max.x; i++)
    {
        gotoxy(i, lim_min.y);
        printf("%c", BORDA_HORIZONTAL);
    }
    gotoxy(i, lim_min.y);
    printf("%c", BORDA_SUP_DIREITA);

    // Imprime as bordas laterais
    for(i=lim_min.y+1; i<lim_max.y; i++)
    {
        gotoxy(lim_min.x, i);
        printf("%c", BORDA_VERTICAL);
        gotoxy(lim_max.x, i);
        printf("%c", BORDA_VERTICAL);
    }

    // Imprime a borda inferior
    gotoxy(lim_min.x, lim_max.y);
    printf("%c", BORDA_INF_ESQUERDA);
    for(i=lim_min.x+1; i<lim_max.x; i++)
    {
        gotoxy(i, lim_max.y);
        printf("%c", BORDA_HORIZONTAL);
    }
    gotoxy(i, lim_max.y);
    printf("%c", BORDA_INF_DIREITA);

    // Imprime índices do jogo
    for(i=lim_min.x+6, j=65; j<65+tam; i=i+3, j++)
    {
        gotoxy(i, lim_min.y+1);
        printf("%c", j);
    }
    for(i=lim_min.y+3, j=1; j<1+tam; i=i+2, j++)
    {
        gotoxy(lim_min.x+2, i);
        printf("%d", j);
    }
}

void iniciaMatriz(int *m, int tam)
{
    int i;
    int a;

    for(i=0; i<(tam*tam); i++)
    {
        *(m+i) = sorteiaElemento();
        // aguarda 20ms para que não sorteie o mesmo elemento
        Sleep(20);
    }
    // garante que nao sobrara nenhuma combinacao
    do
    {
        a = fazVarredura(m, tam);
    }
    while(a);
}

int fazVarredura(int *m, int tam)
{
    int i, j;
    int a, b, c;
    int aux, cont;
    int pontos = 0;

    // faz a varredura horizontal
    for(i=0; i<tam; i++)
    {
        cont = 0;
        aux = *(m+(i*tam));
        a = 0;
        for(j=1; j<tam; j++)
        {
            if( aux == *(m+(i*tam+j)) )
            {
                cont++;
                // para quando a combinaçao estiver na ultima coluna
                if( (j+1==tam) && (cont>=2) )
                {
                    pontos = pontos + cont + 1;
                    if( i>0 )
                    {
                        // faz elementos descerem uma posição
                        for(b=j; b>=a; b--)
                        {
                            for(c=i; c>0; c--)
                            {
                                *(m+(c*tam+b)) = *(m+((c-1)*tam+b));
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
                                *(m+b) = sorteiaElemento();
                            }
                            while( *(m+b) == *(m+(tam+b)) );
                        }
                        else
                        {
                            do
                            {
                                *(m+b) = sorteiaElemento();
                            }
                            while( *(m+b) == *(m+(b+1)) || *(m+b) == *(m+(tam+b)) );
                        }
                    }
                }
            }
            else
            {
                // se houver alguma combinacao
                if(cont>=2)
                {
                    pontos = pontos + cont + 1;
                    if( i>0 )
                    {
                        // faz elementos descerem uma posição
                        for(b=j-1; b>=a; b--)
                        {
                            for(c=i; c>0; c--)
                            {
                                *(m+(c*tam+b)) = *(m+((c-1)*tam+b));
                            }
                        }
                    }
                    // sorteia elementos para a primeira linha
                    for(b=j-1; b>=a; b--)
                    {
                        // só sai do laço se não for repetido
                        do
                        {
                            *(m+b) = sorteiaElemento();
                        }
                        while( *(m+b) == *(m+(b+1)) || *(m+b) == *(m+(tam+b)) );
                    }
                }
                cont = 0;
                aux = *(m+(i*tam+j));
                a = j;
            }
        }
    }

    // faz a varredura vertical
    for(j=0; j<tam; j++)
    {
        cont = 0;
        aux = *(m+j);
        a = 0;
        for(i=1; i<tam; i++)
        {
            if( aux == *(m+(i*tam+j)) )
            {
                cont++;
                // para quando a combinaçao estiver na ultima linha
                if( (i+1==tam) && (cont>=2) )
                {
                    pontos = pontos + cont + 1;
                    if(a>0)
                    {
                        // faz elementos descerem uma posição
                        for(b=a-1; b>=0; b--)
                        {
                            *(m+((b+(cont+1))*tam+j)) = *(m+(b*tam+j));
                        }
                    }
                    // sorteia os elementos no topo
                    for(b=cont; b>=0; b--)
                    {
                        // só sai do laço se não forem repetidos
                        do
                        {
                            *(m+(b*tam+j)) = sorteiaElemento();
                        }
                        while( *(m+(b*tam+j)) == *(m+(b*tam+(j+1))) || *(m+(b*tam+j)) == *(m+((b+1)*tam+j)) );
                    }
                }
            }
            else
            {
                // se houver alguma combinacao
                if(cont>=2)
                {
                    pontos = pontos + cont + 1;
                    if(a>0)
                    {
                        // faz elementos descerem uma posição
                        for(b=a-1; b>=0; b--)
                        {
                            *(m+((b+(cont+1))*tam+j)) = *(m+(b*tam+j));
                        }
                    }
                    // sorteia os elementos no topo
                    for(b=cont; b>=0; b--)
                    {
                        // só sai do laço se não forem repetidos
                        do
                        {
                            *(m+(b*tam+j)) = sorteiaElemento();
                        }
                        while( *(m+(b*tam+j)) == *(m+(b*tam+(j+1))) || *(m+(b*tam+j)) == *(m+((b+1)*tam+j)) );
                    }
                }
                cont = 0;
                aux = *(m+(i*tam+j));
                a = i;
            }
        }
    }
    return pontos;
}



int descobrePosJ(int x, int tam)
{
    int i, j;
    struct COORDENADA lim_min;

    calculaLimites(&lim_min, NULL, tam);

    for(i=0, j=lim_min.x+6; i<tam; i++, j=j+3)
    {
        if(j==x)
        {
            return i;
        }
    }
    return 0;
}

int descobrePosI(int y, int tam)
{
    int i, j;
    struct COORDENADA lim_min;

    calculaLimites(&lim_min, NULL, tam);

    for(i=0, j=lim_min.y+3; i<tam; i++, j=j+2)
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

void trocaElementos(int *m, int tam, int x1, int y1, int x2, int y2)
{
    int aux;

    x1 = descobrePosJ(x1, tam);
    y1 = descobrePosI(y1, tam);
    x2 = descobrePosJ(x2, tam);
    y2 = descobrePosI(y2, tam);

    aux = *(m+(y1*tam+x1));
    *(m+(y1*tam+x1)) = *(m+(y2*tam+x2));
    *(m+(y2*tam+x2)) = aux;
}

int testaTroca(int x1, int y1, int x2, int y2)
{
    if(
        // só permite trocar com o elemento vizinho
        (x2==x1-3 && y2==y1) ||
        (x2==x1+3 && y2==y1) ||
        (x2==x1 && y2==y1-2) ||
        (x2==x1 && y2==y1+2)
    )
    {
        return 1;
    }
    else
    {
        return 0;
    }
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

void exibeInstrucoes()
{
    sequenciaFrutas(2);
    textcolor(WHITE);
    printf(" INSTRUCOES");
    sequenciaFrutas(2);

    textcolor(LIGHTGRAY);
    printf("\n\nO objetivo do jogo e fazer combinacoes de 3 ou mais frutas\n");
    printf("iguais, tanto em linha quanto em coluna usando as setas do\n");
    printf("teclado para mover o cursor e a tecla espaco para trocar as\n");
    printf("frutas de lugar. A fruta somente pode ser movida para uma\n");
    printf("posicao a sua esquerda ou a sua direita ou uma posicao para\n");
    printf("cima ou para baixo. O tempo inicia-se em %d segundos e vai\n", TEMPO_INICIAL);
    printf("decrementando ate chegar em zero. A medida que as combinacoes sao\n");
    printf("feitas, o tempo e incrementado em %d segundos para cada fruta\n", CONST_TEMPO);
    printf("combinada. Para sair do jogo e voltar ao menu principal,\n");
    printf("pressione ESC.\n\n");

    printf("Pontuacao:\n");
    printf("Quanto maior a quantidade de frutas em cada combinacao, maior\n");
    printf("a pontuacao do jogador.\n");
    printf("A pontuacao de cada combinacao e definida pelo produto entre\n");
    printf("a quantidade de frutas combinadas e %d.\n\n", CONST_PONTOS);

    printf("Divirta-se!\n");
}

void sequenciaFrutas(int a)
{
    //mostra a sequencia de frutas
    int i=0;
    do
    {
        textcolor(LIGHTGREEN);
        printf(" %c ", FRUTA_0);
        textcolor(LIGHTRED);
        printf("%c ", FRUTA_1);
        textcolor(LIGHTCYAN);
        printf("%c ", FRUTA_2);
        textcolor(LIGHTMAGENTA);
        printf("%c ", FRUTA_3);
        textcolor(YELLOW);
        printf("%c", FRUTA_4);
        i++;
    }
    while(i<a);
    textcolor(LIGHTGRAY);
}

void calculaLimites(struct COORDENADA *lim_min, struct COORDENADA *lim_max, int tam)
{
    lim_min->x = 2;
    lim_min->y = 2;
    if(lim_max)
    {
        lim_max->x = lim_min->x+6+3*tam;
        lim_max->y = lim_min->y+3+2*tam;
    }
}

void verRank(struct JOGADOR *top)
{
    int i;
    for(i=0; i<NUM_JOGS; i++)
    {
        printf("%2d - %d - ", i+1, (top+i)->pontos);
        puts( (top+i)->nome );
    }
}
