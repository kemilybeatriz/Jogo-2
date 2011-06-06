#include "biblioteca.h"

void main()
{
    int matriz[LINHA][COLUNA];
    char opcao;
    char sair;
    int tempo, tempoTeste1, tempoTeste2;

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
        case '1': // Exibe instru��es sobre a pontua��o
            printf("Instrucoes");
            break;
        case '2': // Inicia o jogo
            system("cls");

            // inicializando vari�veis
            sair = 0;
            tempo = TEMPO_INICIAL;
            tempoTeste1 = time(NULL);
            tempoTeste2 = time(NULL);

            // la�o para o jogo; s� sai quando 'sair' receber 1
            do
            {
                // decrementa a vari�vel 'tempo' a cada segundo
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

                printf("%ds", tempo);

                system("cls");
            }
            while(sair==0);

            //sorteiaFrutas(matriz);
            //exibeCenario(matriz);
            fflush(stdin);
            getchar();
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

