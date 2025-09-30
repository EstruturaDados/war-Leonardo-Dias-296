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

int rolarDado() {
    return (rand() % 6) + 1; // gera número de 1 a 6
}

int main() {
    struct Territorio mapa[QTD_TERRITORIOS];

    printf("\n Bem vindo ao War! \n");
    printf("##### Cadastre os seus Territorios #####\n\n");
    printf("Clique na tecla ENTER para iniciar!\n");
    getchar();

    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        printf("Territorio %d:\n", i + 1);

        printf("Digite o nome do territorio: ");
        fgets(mapa[i].nome, TAM_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Digite a cor deste territorio: ");
        fgets(mapa[i].corExercito, TAM_COR, stdin);
        mapa[i].corExercito[strcspn(mapa[i].corExercito, "\n")] = '\0';

        printf("Digite o numero de tropas que terao: ");
        scanf("%d", &mapa[i].tropas);
        limparBufferEntrada();

        printf("\n");
    }

    while (1) {
        printf("\n##### Mapa Atual #####\n");
        for (int i = 0; i < QTD_TERRITORIOS; i++) {
            printf("Territorio %d\n", i + 1);
            printf("Nome: %s\n", mapa[i].nome);
            printf("Cor: %s\n", mapa[i].corExercito);
            printf("Tropas: %d\n", mapa[i].tropas);
            printf("***************************************\n");
        }

        // ===== ATAQUE =====
        int atacante, defensor;
        printf("\nEscolha o numero do territorio ATACANTE (0 para sair): ");
        scanf("%d", &atacante);
        limparBufferEntrada();

        if (atacante == 0) {
            printf("\nSaindo do jogo...\n");
            break;
        }

        printf("Escolha o numero do territorio DEFENSOR: ");
        scanf("%d", &defensor);
        limparBufferEntrada();

        atacante--; // índice
        defensor--;

        if (atacante < 0 || atacante >= QTD_TERRITORIOS ||
            defensor < 0 || defensor >= QTD_TERRITORIOS ||
            atacante == defensor) {
            printf("Ataque invalido!\n");
            continue;
        }

        if (mapa[atacante].tropas < 2) {
            printf("O atacante precisa ter pelo menos 2 tropas para atacar!\n");
            continue;
        }

        printf("\n===== ATAQUE =====\n");
        printf("%s (%s, %d tropas) ataca %s (%s, %d tropas)\n",
               mapa[atacante].nome, mapa[atacante].corExercito, mapa[atacante].tropas,
               mapa[defensor].nome, mapa[defensor].corExercito, mapa[defensor].tropas);

        // cada lado rola 1 dado
        int dadoAtk = rolarDado();
        int dadoDef = rolarDado();

        printf("\nDado do atacante: %d\n", dadoAtk);
        printf("Dado do defensor: %d\n", dadoDef);

        if (dadoAtk > dadoDef) {
            printf("Vitória do atacante! O defensor perde 1 tropa.\n");
            mapa[defensor].tropas -= 1;
        } else if (dadoDef > dadoAtk) {
            printf("Vitória do defensor! O atacante perde 1 tropa.\n");
            mapa[atacante].tropas -= 1;
        } else {
            printf("Empate! O atacante perde 1 tropa.\n");
            mapa[atacante].tropas -= 1;
        }

        // verifica se defensor foi dominado
        if (mapa[defensor].tropas <= 0) {
            printf("\n*** TERRITORIO DOMINADO! ***\n");
            printf("%s conquistou %s!\n", mapa[atacante].nome, mapa[defensor].nome);

            mapa[defensor].tropas = 1; // move 1 tropa mínima
            mapa[atacante].tropas -= 1;
            strcpy(mapa[defensor].corExercito, mapa[atacante].corExercito);
        }

        // mostrar estado final da rodada
        printf("\n===== Estado Atual =====\n");
        printf("%s - Tropas: %d - Cor: %s\n", mapa[atacante].nome, mapa[atacante].tropas, mapa[atacante].corExercito);
        printf("%s - Tropas: %d - Cor: %s\n", mapa[defensor].nome, mapa[defensor].tropas, mapa[defensor].corExercito);

        // espera ação do jogador
        printf("\nPressione ENTER para próxima jogada ou digite 0 e ENTER para sair: ");
        char entrada[10];
        fgets(entrada, sizeof(entrada), stdin);
        if (entrada[0] == '0') {
            printf("\nSaindo do jogo...\n");
            break;
        }
    }

    return 0;
}
