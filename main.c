#include "biblioteca.h"

void main()
{
    int matriz[LINHA][COLUNA]; // matriz do jogo
    int i, j; // usadas para percorrer a matriz
    int x, y; // usadas para posicionar cada item da matriz
    char opcao; // usada para o menu
    char sair;
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
                // decrementa a variável 'tempo' a cada segundo
                if(tempoTeste1!=tempoTeste2)
                {
                    tempoTeste2 = tempoTeste1;
                    tempo--;
                }
                tempoTeste1 = time(NULL);

                if(tempo==0)
                {
                    sair = 1;
                }

                gotoxy(LIM_MAX_X+2, LIM_MIN_Y+1);
                printf("Tempo: %ds  ", tempo);

                for(i=0, x=LIM_MIN_X+6; i<LINHA; i++, x=x+3)
                {
                    for(j=0, y=LIM_MIN_Y+3; j<COLUNA; j++, y=y+2)
                    {
                        gotoxy(x, y);
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

                //iniciaMatriz(matriz);
                //exibeCenario(matriz);
                //bordasJogo();

                //system("cls");
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

