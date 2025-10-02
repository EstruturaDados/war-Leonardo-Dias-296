#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QTD_TERRITORIOS 5
#define TAM_COR 30
#define NUM_MISSOES 5

typedef struct {

    char continente[20];
    char cor[TAM_COR];
    int dono;     // 0 = neutro, 1 = jogador
    int tropas;   // quantidade de tropas
} Territorio;

typedef struct {
    char descricao[100];
    int concluida;
} Missao;

Territorio territorios[QTD_TERRITORIOS];

Missao missoes[NUM_MISSOES] = {
    {"Conquiste 2 territorios do Mapa", 0},
    {"Conquiste o territorio 4", 0},
    {"Ataque o territorio 1 e 3", 0},
    {"Derrote pelo menos 2 tropas em cada territorio", 0},
    {"Conquistar 4 territorios quaisquer", 0}
};

int numAleatorio(int max) {
    return rand() % max;
}

void cadastrarTerritorios() {
    printf("\n=== Cadastro dos Territorios ===\n");
    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        printf("\nTerritorio %d:\n", i + 1);


        printf("Continente: ");
        scanf(" %[^\n]", territorios[i].continente);

        printf("Cor: ");
        scanf(" %[^\n]", territorios[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        territorios[i].dono = 0; // comeca neutro
    }
}

void mostrarMapa() {
    printf("\n=== MAPA DE TERRITORIOS ===\n");
    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        printf("%d - %s (%s) - Cor: %s - Tropas: %d - Dono: %s\n",
               i, territorios[i].continente,
               territorios[i].cor, territorios[i].tropas,
               territorios[i].dono ? "Jogador" : "Neutro");
    }
    printf("===========================\n\n");
}

int contarTerritoriosConquistadosPorContinente(const char *continente) {
    int total = 0;
    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        if (territorios[i].dono == 1 && strcmp(territorios[i].continente, continente) == 0) {
            total++;
        }
    }
    return total;
}

int contarTerritoriosConquistados() {
    int total = 0;
    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        if (territorios[i].dono == 1) {
            total++;
        }
    }
    return total;
}

int verificarMissao(int indice) {
    if (indice == 0) {
        return contarTerritoriosConquistadosPorContinente("America do Sul") >= 2;
    } else if (indice == 1) {
        return contarTerritoriosConquistadosPorContinente("Europa") >= 2;
    } else if (indice == 2) {
        return contarTerritoriosConquistados() >= 3;
    } else if (indice == 3) {
        return contarTerritoriosConquistadosPorContinente("America do Sul") >= 1 &&
               contarTerritoriosConquistadosPorContinente("America do Norte") >= 1 &&
               contarTerritoriosConquistadosPorContinente("Europa") >= 1;
    } else if (indice == 4) {
        return contarTerritoriosConquistados() >= 4;
    }
    return 0;
}

void mostrarRankingFinal() {
    int total = contarTerritoriosConquistados();
    printf("\n===== RANKING FINAL =====\n");
    printf("Voce conquistou %d territorios!\n", total);

    if (total == 0) {
        printf("Nenhuma conquista... precisa treinar mais!\n");
    } else if (total < 3) {
        printf("Conquistas modestas, mas ja e um comeco!\n");
    } else if (total < QTD_TERRITORIOS) {
        printf("Bom trabalho! Voce foi um comandante respeitavel!\n");
    } else {
        printf("Incrivel! Voce dominou todos os territorios!\n");
    }

    printf("\n--- Territorios conquistados ---\n");
    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        if (territorios[i].dono == 1) {
            printf("- %s (%s) com %d tropas\n",
                   territorios[i].continente, territorios[i].tropas);
        }
    }
    printf("==========================\n\n");
}

void jogarComMissao() {
    int indiceMissao = numAleatorio(NUM_MISSOES);
    printf("\nSua missao: %s\n", missoes[indiceMissao].descricao);

    char continuar;

    do {
        int atq, def;
        printf("\nDigite o territorio ATACANTE (0-%d): ", QTD_TERRITORIOS - 1);
        scanf("%d", &atq);
        printf("Digite o territorio DEFENSOR (0-%d): ", QTD_TERRITORIOS - 1);
        scanf("%d", &def);

        int dadoAtq = numAleatorio(6) + 1;
        int dadoDef = numAleatorio(6) + 1;

        printf("Resultado do dado: Atacante %d x %d Defensor\n", dadoAtq, dadoDef);

        if (dadoAtq > dadoDef) {
            printf("Vitoria! Voce conquistou %s!\n", territorios[def].continente);
            territorios[def].dono = 1;
            territorios[def].tropas = (territorios[atq].tropas > 1 ? territorios[atq].tropas - 1 : 1);
        } else if (dadoAtq == dadoDef) {
            printf("Empate! Nada muda.\n");
        } else {
            printf("Derrota! Voce perdeu tropas!\n");
            if (territorios[atq].tropas > 0) territorios[atq].tropas--;
        }

        if (verificarMissao(indiceMissao)) {
            printf("\n=== MISSAO CONCLUIDA! ===\n");
            mostrarRankingFinal();
            break;
        }

        printf("\nDeseja continuar atacando? (s/n): ");
        scanf(" %c", &continuar);

    } while (continuar == 's');

    char jogarNovamente;
    printf("\nDeseja jogar novamente (s) ou sair (n)? ");
    scanf(" %c", &jogarNovamente);

    if (jogarNovamente == 's') {
        for (int i = 0; i < QTD_TERRITORIOS; i++) {
            territorios[i].dono = 0;
        }
        cadastrarTerritorios();
        jogarComMissao();
    } else {
        mostrarRankingFinal();
        printf("\nObrigado por jogar!\n");
        exit(0);
    }
}

void jogarSemMissao() {
    char continuar;
    do {
        int atq, def;
        printf("\nDigite o territorio ATACANTE (0-%d): ", QTD_TERRITORIOS - 1);
        scanf("%d", &atq);
        printf("Digite o territorio DEFENSOR (0-%d): ", QTD_TERRITORIOS - 1);
        scanf("%d", &def);

        int dadoAtq = numAleatorio(6) + 1;
        int dadoDef = numAleatorio(6) + 1;

        printf("Resultado do dado: Atacante %d x %d Defensor\n", dadoAtq, dadoDef);

        if (dadoAtq > dadoDef) {
            printf("Vitoria! Voce conquistou %s!\n", territorios[def].continente);
            territorios[def].dono = 1;
            territorios[def].tropas = (territorios[atq].tropas > 1 ? territorios[atq].tropas - 1 : 1);
        } else if (dadoAtq == dadoDef) {
            printf("Empate! Nada muda.\n");
        } else {
            printf("Derrota! Voce perdeu tropas!\n");
            if (territorios[atq].tropas > 0) territorios[atq].tropas--;
        }

        printf("\nDeseja continuar atacando? (s/n): ");
        scanf(" %c", &continuar);

    } while (continuar == 's');

    mostrarRankingFinal();
}

int main() {
    int opcao;
    srand(1234);

    // Tela inicial
    printf("\nBem-vindo ao WAR!\n");
    printf("Clique ENTER para iniciar...\n");
    getchar(); // espera ENTER

    cadastrarTerritorios();

    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1 - Ver mapa\n");
        printf("2 - Jogar com missao\n");
        printf("3 - Jogar sem missao\n");
        printf("4 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                mostrarMapa();
                break;
            case 2:
                jogarComMissao();
                break;
            case 3:
                jogarSemMissao();
                break;
            case 4:
                printf("\nSaindo do jogo...\n");
                mostrarRankingFinal();
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while (opcao != 4);

    return 0;
}
