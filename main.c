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

            //inicializando matriz do jogo
            iniciaMatriz(matriz);

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

                for(i=0, mat_x=LIM_MIN_X+6; i<LINHA; i++, mat_x=mat_x+3)
                {
                    for(j=0, mat_y=LIM_MIN_Y+3; j<COLUNA; j++, mat_y=mat_y+2)
                    {
                        gotoxy(mat_x, mat_y);
                        if(mat_x==x && mat_y==y)
                        {
                            textbackground(DARKGRAY);
                        }
                        else
                        {
                            textbackground(BLACK);
                        }
                        if(matriz[i][j] == 0)
                        {
                            textcolor(LIGHTGREEN);
                            printf("%c", FRUTA_0);
                        }
                        else if(matriz[i][j] == 1)
                        {
                            textcolor(LIGHTRED);
                            printf("%c", FRUTA_1);
                        }

                        else if(matriz[i][j] == 2)
                        {
                            textcolor(LIGHTCYAN);
                            printf("%c", FRUTA_2);
                        }
                        else if(matriz[i][j] == 3)
                        {
                            textcolor(LIGHTMAGENTA);
                            printf("%c", FRUTA_3);
                        }
                        else if(matriz[i][j] == 4)
                        {
                            textcolor(YELLOW);
                            printf("%c", FRUTA_4);
                        }
                        textcolor(LIGHTGRAY);
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
                    }
                }

                // imprime o cursor do jogador
                textbackground(DARKGRAY);
                gotoxy(x, y);
                printf("%c", 32);

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

