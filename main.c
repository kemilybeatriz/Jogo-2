/*
UTFPR - UNIVERSIDADE TECNOLÓGICA FEDERAL DO PARANÁ
        CURSO DE ENGENHARIA ELETRÔNICA

Fundamentos de Programação I
Trabalho 3 - Papagaio Sedento
Professor: Ms Eng. Edson Tavares de Camargo

Alunos:
1168932 - Kemily Beatriz Rodrigues da Cruz Lopes
1054112 - Maurício Meneghini Fauth

*/

#include "biblioteca.h"

void main()
{
    int *matriz; // matriz do jogo
    int i, j; // usadas para percorrer a matriz
    int mat_x, mat_y; // usadas para posicionar cada item da matriz
    int x, y; // usadas para posicionar o cursor do jogador
    char opcao; // usada para o menu
    char a; // usada na captura das teclas durante o jogo
    char sair; // usada para sair do laço do jogo
    int tempo, tempoTeste1, tempoTeste2; // usadas para controlar o tempo
    char cursorSelecao; // usada para selecionar os elementos
    char cursorTrava;
    int elem_x, elem_y; // posicao do elemento selecionado
    int varredura, pontos;
    int tamanho = 8; // tamanho da matriz

    // define o titulo da janela
    system("title Papagaio Sedento");

    do
    {
        system("cls");
        //imprime o menu principal
        menu();
        scanf("%c", &opcao);
        switch(opcao)
        {
        case '1': // Exibe instruções sobre a pontuação
            system("cls");
            exibeInstrucoes();
            break;
        case '2': // Inicia o jogo
            system("cls");

            matriz = malloc(tamanho * tamanho * sizeof(int));
            if(!matriz)
            {
                printf("Erro ao alocar memoria!");
                exit(1);
            }

            // inicializando variáveis
            x = LIM_MIN_X+6;
            y = LIM_MIN_Y+3;
            sair = 0;
            tempo = TEMPO_INICIAL;
            tempoTeste1 = time(NULL);
            tempoTeste2 = time(NULL);
            cursorSelecao = 0;
            cursorTrava = 0;
            elem_x = LIM_MIN_X;
            elem_y = LIM_MIN_Y;
            pontos = 0;

            textcolor(LIGHTGRAY);
            textbackground(BLACK);

            printf("Carregando...");

            //inicializando matriz do jogo
            iniciaMatriz(matriz, tamanho);

            system("cls");

            bordasJogo(tamanho);

            // laço para o jogo; só sai quando 'sair' receber 1
            do
            {
                if(tempo==0)
                {
                    sair = 1;
                }
                // decrementa a variável 'tempo' a cada segundo
                if(tempoTeste1!=tempoTeste2)
                {
                    tempoTeste2 = tempoTeste1;
                    tempo--;
                }
                tempoTeste1 = time(NULL);

                gotoxy(LIM_MAX_X+2, LIM_MIN_Y+1);
                if(tempo%2)
                {
                    textcolor(LIGHTGREEN);
                }
                else
                {
                    textcolor(YELLOW);
                }
                printf("Papagaio Sedento");
                textcolor(LIGHTGRAY);

                gotoxy(LIM_MAX_X+2, LIM_MIN_Y+4);
                if(tempo<20)
                {
                    textcolor(LIGHTRED);
                }
                printf("Tempo: %ds  ", tempo);
                textcolor(LIGHTGRAY);

                gotoxy(LIM_MAX_X+2, LIM_MIN_Y+6);
                printf("Pontos: %d", pontos);

                for(i=0, mat_y=LIM_MIN_Y+3; i<tamanho; i++, mat_y=mat_y+2)
                {
                    for(j=0, mat_x=LIM_MIN_X+6; j<tamanho; j++, mat_x=mat_x+3)
                    {
                        // imprime o cursor do jogador
                        if( (mat_x==x && mat_y==y) || (mat_x==elem_x && mat_y==elem_y) )
                        {
                            textbackground(DARKGRAY);
                        }
                        else
                        {
                            textbackground(BLACK);
                        }
                        // imprime o elemento da matriz
                        exibeElemento( *(matriz+(i*tamanho+j)), mat_x, mat_y);
                    }
                }

                fflush(stdin);
                if (kbhit()) // se alguma tecla for pressionada
                {
                    fflush(stdin);
                    a = getch(); // pega mais uma...
                    switch (a)
                    {
                    case 72: // seta para cima
                        if( y>=LIM_MIN_Y+5 && y<=LIM_MAX_Y-2 )
                        {
                            y = y-2;
                        }
                        break;
                    case 80: // seta para baixo
                        if( y>=LIM_MIN_Y+3 && y<=LIM_MAX_Y-4 )
                        {
                            y = y+2;
                        }
                        break;
                    case 77: // seta direita
                        if( x>=LIM_MIN_X+6 && x<=LIM_MAX_X-6 )
                        {
                            x = x+3;
                        }
                        break;
                    case 75: // seta esquerda
                        if( x>=LIM_MIN_X+9 && x<=LIM_MAX_X-3 )
                        {
                            x = x-3;
                        }
                        break;
                    case 32: // espaço
                        if(cursorSelecao==0)
                        {
                            cursorSelecao = 1;
                        }
                        else
                        {
                            if( testaTroca(elem_x, elem_y, x, y) )
                            {
                                trocaElementos(matriz, tamanho, elem_x, elem_y, x, y);
                                do
                                {
                                    varredura = fazVarredura(matriz, tamanho);
                                    pontos = pontos + (varredura*CONST_PONTOS);
                                    tempo = tempo + (varredura*CONST_TEMPO);
                                }
                                while(varredura);
                            }

                            cursorSelecao = 0;
                            cursorTrava = 0;
                            elem_x = LIM_MIN_X;
                            elem_y = LIM_MIN_Y;
                        }
                        break;
                    case 27: // botão ESC para sair
                        sair = 1;
                        break;
                    }
                }

                if(cursorSelecao)
                {
                    if(cursorTrava==0)
                    {
                        elem_x = x;
                        elem_y = y;
                        cursorTrava = 1;
                    }
                }

                textcolor(LIGHTGRAY);
                textbackground(BLACK);
            }
            while(sair==0);
            system("cls");
            sequenciaFrutas(1);
            textcolor(WHITE);
            printf(" PAPAGAIO SEDENTO");
            sequenciaFrutas(1);
            textcolor(LIGHTRED);
            printf("\n\n\t\tGAME OVER\n\n");
            textcolor(LIGHTGRAY);
            printf("\t\t%d pontos!\n", pontos);
            free(matriz);
            break;
        case '3': // Ver ranking
            break;
        case '4': // Determinar tamanho da matriz
            do
            {
                printf("Informe o tamanho da matriz (5-10): ");
                scanf("%d", &tamanho);
            }
            while(tamanho < 5 || tamanho > 10);
            break;
        case '5': // Sai do jogo
            printf("Saindo...");
            break;
        default:
            printf("Opcao invalida!");
        }
        fflush(stdin);
        getchar();
    }
    while(opcao!='5');
}

