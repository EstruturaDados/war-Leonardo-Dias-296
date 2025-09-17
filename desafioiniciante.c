#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QTD_TERRITORIOS 5
#define TAM_NOME 50
#define TAM_COR 30

struct Territorio {
    char nome[TAM_NOME];
    char corExercito[TAM_COR];
    int tropas;
};

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    struct Territorio mapa[QTD_TERRITORIOS];

    printf("\n Bem vindo ao War! \n");
    printf("##### Cadastre os seus Territorios #####\n\n");
    printf("Clique na tecla ENTER para iniciar!\n");
    getchar();


    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        printf("Territorio %d:\n", i + 1);

        //printf("Voce so podera cadastrar %d territorios. \n", QTD_TERRITORIOS);
        printf("Digite o nome do territorio: ");
        fgets(mapa[i].nome, TAM_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // remove \n

        printf("Digite a cor deste territorio: ");
        fgets(mapa[i].corExercito, TAM_COR, stdin);
        mapa[i].corExercito[strcspn(mapa[i].corExercito, "\n")] = '\0';

        printf("Digite o numero de tropas que terao: ");
        scanf("%d", &mapa[i].tropas);
        limparBufferEntrada();

        printf("\n");
    }

    printf("\n##### Mapa Atual #####\n");
    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        printf("Territorio %d\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].corExercito);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("***************************************\n");
    }

    return 0;
}
