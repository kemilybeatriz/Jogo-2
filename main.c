#include "biblioteca.h"

void main()
{
    int matriz[LINHA][COLUNA]; // matriz do jogo
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
            printf("Instrucoes");
            break;
        case '2': // Inicia o jogo
            system("cls");

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

            printf("Carregando...");

            //inicializando matriz do jogo
            iniciaMatriz(matriz);

            system("cls");

            bordasJogo();

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
                printf("Tempo: %ds  ", tempo);

                gotoxy(LIM_MAX_X+2, LIM_MIN_Y+3);
                printf("matriz[%d][%d]: %c", descobrePosI(y), descobrePosJ(x), matriz[descobrePosI(y)][descobrePosJ(x)]);

                gotoxy(LIM_MAX_X+2, LIM_MIN_Y+5);
                printf("%d", fazVarredura(matriz));

                for(i=0, mat_y=LIM_MIN_Y+3; i<LINHA; i++, mat_y=mat_y+2)
                {
                    for(j=0, mat_x=LIM_MIN_X+6; j<COLUNA; j++, mat_x=mat_x+3)
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
                        exibeElemento(matriz[i][j], mat_x, mat_y);
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
                            if( (x==elem_x-3 && y==elem_y) || (x==elem_x+3 && y==elem_y) || (x==elem_x && y==elem_y-2) || (x==elem_x && y==elem_y+2) )
                            {
                                trocaElementos(matriz, elem_x, elem_y, x, y);
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
            break;
        case '3': // Sai do jogo
            printf("Saindo...");
            break;
        default:
            printf("Opcao invalida!");
        }
        fflush(stdin);
        getchar();
    }
    while(opcao!='3');
}

