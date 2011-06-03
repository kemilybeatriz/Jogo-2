#include "biblioteca.h"

void main()
{
    int matriz[LINHA][COLUNA];
    int opcao;

    do
    {
        system("cls");
        menu();
        scanf("%d", &opcao);
        switch(opcao)
        {
        case 1:
            printf("Instrucoes");
            break;
        case 2:
            system("cls");
            sorteiaFrutas(matriz);
            exibeCenario(matriz);
            fflush(stdin);
            getchar();
            break;
        case 3:
            printf("Saindo...");
            break;
        default:
            printf("Opcao invalida!");
        }
        fflush(stdin);
        getchar();
    }
    while(opcao!=3);
}

