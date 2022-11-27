#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
/*------------------> JOGO DA VELHA <------------------*/

/* Variaveis de uso global */
char matrizJogo[3][3]; // Gera a matriz do Jogo sendo 3x3.
int l, c; // l = Linha | c = Coluna. 
int quantidade_1 = 0; // variavel para o rank
int quantidade_2 = 0; // variavel para o rank

/* Preenche a matriz do Tabuleiro */
void inicializarMatriz() {
    for (l = 0; l < 3; l++) {
        for (c = 0; c < 3; c++)
            matrizJogo[l][c] = ' ';
    }
}

/* Imprime a matriz do Tabuleiro no formato do jogo da velha */
void imprimir() {
    printf("\n\n\t 0   1   2\n\n");
    for(l = 0; l < 3; l++) {
        for(c = 0; c < 3; c++) {
            if(c == 0)
                printf("\t");
            printf(" %c ", matrizJogo[l][c]);
            if(c < 2)
                printf("|");
            if(c == 2)
                printf("   %d", l);
        }
        printf("\n");
        if(l < 2)
            printf("\t-----------\n");
    }
}


/* Funções que Defininem condições de Vitoria */

/* Ganhou por linha  - Jogador 'c' na Linha 'l'  coluna fixa */
int ganhouPorLinha(int l, char c) {
    if (matrizJogo[l][0] == c && matrizJogo[l][1] == c && matrizJogo[l][2] == c)
        return 1;
    else
        return 0;
}

/* Marca vitoria linhas -  Jogador 'c' Nas Linhas */
int ganhouPorLinhas(char c) {
    int ganhou = 0;
    for (l = 0; l < 3; l++)
    {
        ganhou = ganhou + ganhouPorLinha(l, c);
    }
    return ganhou;
}

/* Ganhou por Coluna - Jogador 'j' Na Coluna 'c' Linha fixa */
int ganhouPorColuna(int c, char j) {
    if (matrizJogo[0][c] == j && matrizJogo[1][c] == j && matrizJogo[2][c] == j)
        return 1;
    else
        return 0;
}
/*
/* Marca vitoria coluna - Jogador 'j' Nas Colunas */
int ganhouPorColunas(char j) {
    int ganhou = 0;
    for (c = 0; c < 3; c++)
    {
        ganhou += ganhouPorColuna(c, j);
    }
    return ganhou;
}

/* Ganhou por diagonal - Jogador 'c' Na Diagonal Principal */
int ganhouPorDiagPrin(char c) {
    if (matrizJogo[0][0] == c && matrizJogo[1][1] == c && matrizJogo[2][2] == c)
        return 1;
    else
        return 0;
}

/* Ganhou por diagonal - Jogador 'c' Na Diagonal Secundaria **/
int ganhouPorDiagSec(char c) {
    if (matrizJogo[0][2] == c && matrizJogo[1][1] == c && matrizJogo[2][0] == c)
        return 1;
    else
        return 0;
}
/* Fim das Funções de condição de vitoria  */

/* Função para validar uma jogada l e c */
int cordenadaValida(int l, int c) {
    if (l >= 0 && l < 3 && c >= 0 && c < 3 && matrizJogo[l][c] == ' ')
        return 1;
    else
        return 0;
}

/* Função Para Pedir ao Jogador as Coordenadas para jogar*/
void lerCoordenadas(char j) {
    int linha, coluna;

    printf("\nJogador %c digite a linha: ", j);
    scanf("%d", &linha);
    printf("\nJogador %c digite a coluna: ", j);
    scanf("%d", &coluna);

    while (cordenadaValida(linha, coluna) == 0) {
        printf("\nCoordenadas invalidas!\n\nJogador %c digite outra linha e coluna: ", j);
        scanf("%d%d", &linha, &coluna);
    }
    matrizJogo[linha][coluna] = j;
}

/* Funcao Que Retorna Posicoes Vazias */
int quantVazias() {
    int quantidade = 0;

    for (l = 0; l < 3; l++) {
        for (c = 0; c < 3; c++)
            if (matrizJogo[l][c] == ' ')
                quantidade++;
    }
    return quantidade;
}

/* Funcao Para Iniciar Jogo da Velha */
void jogar() {
	
    int jogador = 1, vitoriaDeX = 0, vitoriaDe0 = 0;;
    char jogador1 = 'X', jogador2 = '0';


    do {
        imprimir();
        if (jogador == 1) {
            lerCoordenadas(jogador1);
            jogador++;
            vitoriaDeX += ganhouPorLinhas(jogador1);
            vitoriaDeX += ganhouPorColunas(jogador1);
            vitoriaDeX += ganhouPorDiagPrin(jogador1);
            vitoriaDeX += ganhouPorDiagSec(jogador1);
        } else {
            lerCoordenadas(jogador2);
            jogador = 1;
            vitoriaDe0 += ganhouPorLinhas(jogador2);
            vitoriaDe0 += ganhouPorColunas(jogador2);
            vitoriaDe0 += ganhouPorDiagPrin(jogador2);
            vitoriaDe0 += ganhouPorDiagSec(jogador2);
        }
        system("CLS");
    } while (vitoriaDeX == 0 && vitoriaDe0 == 0 && quantVazias() > 0);

    imprimir();

    if (vitoriaDe0 == 1) {
        printf("\nParabens Jogador 2. Voce venceu!!!\n");
        quantidade_2 += 1;
    } else if (vitoriaDeX == 1) {
        printf("\nParabens Jogador 1. Voce venceu!!!\n");
        quantidade_1 += 1;

    } else {
        printf("\nIsh Parece que Deu velha!!!\n");
    }
    
    printf("O Jogador 1 ganhou %d vezes\n", quantidade_1);
    printf("O jogador 2 ganhou %d vezes", quantidade_2);

}

/* Menu para selecionar no Switch */
int cabecalho() {
    int escolhido;

    printf("--- JOGO DA VELHA ---");
    printf("\n1- Jogar");
    printf("\n2- Creditos");
    printf("\n3- Rank");
    printf("\n4- Sair\n\n");
    scanf("%d", &escolhido);
    return escolhido;
}

/* Main */
int main() {
    
    setlocale(LC_ALL, "Portuguese");
    
	int menu;
    

    do {
        system("CLS");
        switch (cabecalho()) {
        case 1:
            do {
                system("CLS");
                inicializarMatriz();
                jogar(&quantidade_1, &quantidade_2);
                printf("\nDigite 1 para jogar novamente ou outro numero para sair: ");
                scanf("%d", &menu);
            } while (menu == 1);
            break;
        case 2:
            system("CLS");
            printf("--- CREDITOS ---\n\n");
            printf("Leon Denis Silvestre de Lucena\n");
            printf("Matheus de Moura Aguiar Quintanilha\n");
            printf("Bruna Siqueira Correia\n");
            break;
        case 3:
            system("CLS");
            printf("--- R A N k ---\n\n");
            printf("O jogador 1 ganhou %d\n", quantidade_1);
            printf("O jogador 2 ganhou %d\n\n", quantidade_2);
            break;
        case 4:
            exit(0);
            break;
        default:
        	printf("Opção invalida, digite um numero referente ao menu!");
        }
        printf("\nDigite 1 para retornar ao menu: ");
        scanf("%d", &menu);
    } while (menu == 1);

    return 0;
}
