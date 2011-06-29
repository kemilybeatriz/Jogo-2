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
    struct COORDENADA mat; // usadas para posicionar cada item da matriz
    struct COORDENADA c; // usadas para posicionar o cursor do jogador
    char opcao; // usada para o menu
    char a; // usada na captura das teclas durante o jogo
    char sair; // usada para sair do laço do jogo
    int tempo, tempoTeste1, tempoTeste2; // usadas para controlar o tempo
    char cursorSelecao; // usada para selecionar os elementos
    char cursorTrava;
    struct COORDENADA elem; // posicao do elemento selecionado
    int varredura, pontos;
    int tamanho = 8; // tamanho da matriz
    struct COORDENADA lim_min; // limite mínimo
    struct COORDENADA lim_max; // limite máximo
    struct JOGADOR *top;
    struct JOGADOR player;

    // define o titulo da janela
    system("title Papagaio Sedento");

    top = malloc(NUM_JOGS * sizeof(struct JOGADOR));
    if(!top)
    {
        printf("Erro ao alocar memoria!");
        exit(1);
    }

    for(i=0; i<NUM_JOGS; i++)
    {
        strcpy( (top+i)->nome, "Jogador");
        (top+i)->pontos = (i+1) * (i+1) * 300;
    }

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
            calculaLimites(&lim_min, &lim_max, tamanho);
            c.x = lim_min.x+6;
            c.y = lim_min.y+3;
            sair = 0;
            tempo = TEMPO_INICIAL;
            tempoTeste1 = time(NULL);
            tempoTeste2 = time(NULL);
            cursorSelecao = 0;
            cursorTrava = 0;
            elem.x = lim_min.x;
            elem.y = lim_min.y;
            pontos = 0;

            textcolor(LIGHTGRAY);
            textbackground(BLACK);

            printf("Carregando...");

            //inicializando matriz do jogo
            iniciaMatriz(matriz, tamanho);

            system("cls");

            fflush(stdin);
            printf("Digite seu nome: ");
            gets(player.nome);

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

                gotoxy(lim_max.x+2, lim_min.y+1);
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

                gotoxy(lim_max.x+2, lim_min.y+4);
                puts(player.nome);

                gotoxy(lim_max.x+2, lim_min.y+6);
                if(tempo<20)
                {
                    textcolor(LIGHTRED);
                }
                printf("Tempo: %ds  ", tempo);
                textcolor(LIGHTGRAY);

                gotoxy(lim_max.x+2, lim_min.y+8);
                printf("Pontos: %d", pontos);

                for(i=0, mat.y=lim_min.y+3; i<tamanho; i++, mat.y=mat.y+2)
                {
                    for(j=0, mat.x=lim_min.x+6; j<tamanho; j++, mat.x=mat.x+3)
                    {
                        // imprime o cursor do jogador
                        if( (mat.x==c.x && mat.y==c.y) || (mat.x==elem.x && mat.y==elem.y) )
                        {
                            textbackground(DARKGRAY);
                        }
                        else
                        {
                            textbackground(BLACK);
                        }
                        // imprime o elemento da matriz
                        exibeElemento( *(matriz+(i*tamanho+j)), mat.x, mat.y);
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
                        if( c.y>=lim_min.y+5 && c.y<=lim_max.y-2 )
                        {
                            c.y = c.y-2;
                        }
                        break;
                    case 80: // seta para baixo
                        if( c.y>=lim_min.y+3 && c.y<=lim_max.y-4 )
                        {
                            c.y = c.y+2;
                        }
                        break;
                    case 77: // seta direita
                        if( c.x>=lim_min.x+6 && c.x<=lim_max.x-6 )
                        {
                            c.x = c.x+3;
                        }
                        break;
                    case 75: // seta esquerda
                        if( c.x>=lim_min.x+9 && c.x<=lim_max.x-3 )
                        {
                            c.x = c.x-3;
                        }
                        break;
                    case 32: // espaço
                        if(cursorSelecao==0)
                        {
                            cursorSelecao = 1;
                        }
                        else
                        {
                            if( testaTroca(elem.x, elem.y, c.x, c.y) )
                            {
                                trocaElementos(matriz, tamanho, elem.x, elem.y, c.x, c.y);
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
                            elem.x = lim_min.x;
                            elem.y = lim_min.y;
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
                        elem.x = c.x;
                        elem.y = c.y;
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
            player.pontos = pontos;
            free(matriz);
            break;
        case '3': // Ver ranking
            system("cls");
            sequenciaFrutas(1);
            textcolor(WHITE);
            printf(" PAPAGAIO SEDENTO");
            sequenciaFrutas(1);
            textcolor(LIGHTGRAY);
            printf("\n\nTOP %d\n\n", NUM_JOGS);
            verRank(top);
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
    free(top);
}

