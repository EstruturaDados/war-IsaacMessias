// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <time.h>

// Definindo os tamanhos máximos pra não precisar ficar digitando 30 e 10 toda hora
#define TAM_MAX_NOME 30 
#define TAM_MAX_COR 10

// Nossa "ficha" do território. Guarda o que cada um tem.
struct Territorio {
    char nome[TAM_MAX_NOME];
    char cor[TAM_MAX_COR];
    int tropas;   
};

// --- PROTÓTIPOS DAS FUNÇÕES ---
void cadastrar(int indice, struct Territorio *t);
void atacar(struct Territorio *a, struct Territorio *d);
void exibir(int a, struct Territorio *t);
void liberarMemoria(struct Territorio *mapa, char *missao); // Atualizada para limpar a missão também
void LimparBufferEntradas();
int verifTerritorios(int terr);
int verifIndice(const struct Territorio *m, int idx_a, int idx_d, int terr);

// Novas funções exigidas pelo desafio:
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
int verificarMissao(char* missao, struct Territorio* mapa, int tamanho);

int main() {
    srand(time(NULL)); // Faz o rand() ser diferente toda vez
    int totalterritorios = 0;
    int maxTerritorios;

    // Vetor de strings com as missões (Requisito do desafio)
    char* listaMissoes[] = {
        "Dominar 3 territorios",
        "Eliminar tropas de uma cor",
        "Conquistar o mapa",
        "Acumular 10 tropas",
        "Mudar a cor de um vizinho"
    };

    printf("Quantos territorios vai ter no jogo? ");
    scanf("%d", &maxTerritorios);
    LimparBufferEntradas();

    // Criando o mapa dinamicamente
    struct Territorio *mapa = (struct Territorio *) calloc(maxTerritorios, sizeof(struct Territorio)); 

    // Alocando a missão dinamicamente (Requisito: usar malloc)
    char *missaoJogador = (char*) malloc(100 * sizeof(char));

    if (mapa == NULL || missaoJogador == NULL) {
        printf("Erro de memoria!\n");
        return 1;
    }

    // Sorteia e atribui a missão logo no início
    atribuirMissao(missaoJogador, listaMissoes, 5);
    printf("\n=== MISSAO RECEBIDA: %s ===\n", missaoJogador);

    int opcao;
    do {
        printf("\n--- MENU WAR ---\n");
        printf("1 - Cadastrar\n2 - Exibir Mapa\n3 - Batalha!\n0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        LimparBufferEntradas();

        switch (opcao) {
            case 1:
                if (totalterritorios < maxTerritorios) {
                    cadastrar(totalterritorios, mapa);                
                    totalterritorios++;
                } else printf("Mapa lotado!\n");
                break;

            case 2:
                exibir(totalterritorios, mapa); 
                printf("\nPressione ENTER para continuar...");
                getchar();
                break;
            
            case 3: {
                if (verifTerritorios(totalterritorios)) break;

                int atac, defen;
                exibir(totalterritorios, mapa);
                printf("\nIndice do atacante: ");
                scanf("%d", &atac);
                printf("Indice do defensor: ");
                scanf("%d", &defen);
                LimparBufferEntradas();

                if (!verifIndice(mapa, atac, defen, totalterritorios)) {
                    atacar(&mapa[atac - 1], &mapa[defen - 1]);
                    
                    // Verificação silenciosa de missão após o ataque
                    if (verificarMissao(missaoJogador, mapa, totalterritorios)) {
                        printf("\n************************************\n");
                        printf("VITORIA! Voce cumpriu sua missao:\n%s\n", missaoJogador);
                        printf("************************************\n");
                        opcao = 0; // Finaliza o jogo
                    }
                }
                break;
            }
        }
    } while (opcao != 0);

    liberarMemoria(mapa, missaoJogador); 
    return 0; 
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

// Atribui uma missão aleatória e copia para a memória alocada (Requisito)
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]); 
}

// Verifica se o objetivo foi alcançado (Lógica simples inicial)
int verificarMissao(char* missao, struct Territorio* mapa, int tamanho) {
    // Exemplo: se a missão for dominar 3 territórios, checa se a cor do jogador 1 se repete 3 vezes
    int cont = 0;
    for(int i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, mapa[0].cor) == 0) cont++;
    }
    if (cont >= 3) return 1; 
    return 0;
}

void cadastrar(int indice, struct Territorio *t) {
    printf("Nome do territorio: ");
    fgets(t[indice].nome, TAM_MAX_NOME, stdin);
    t[indice].nome[strcspn(t[indice].nome, "\n")] = '\0';
    
    printf("Cor: ");
    fgets(t[indice].cor, TAM_MAX_COR, stdin);
    t[indice].cor[strcspn(t[indice].cor, "\n")] = '\0';

    printf("Tropas: "); 
    scanf("%d", &t[indice].tropas); 
    LimparBufferEntradas();
}

void atacar(struct Territorio *a, struct Territorio *d) {
    int dadoAtac = (rand() % 6) + 1;
    int dadoDefen = (rand() % 6) + 1;

    printf("\n--- BATALHA: %s vs %s ---\n", a->nome, d->nome);
    printf("Dados - Atacante: %d | Defesa: %d\n", dadoAtac, dadoDefen);
    
    if (dadoAtac > dadoDefen) {
        d->tropas--;
        if (d->tropas <= 0) {
            printf("BOA! Territorio %s dominado!\n", d->nome);
            strcpy(d->cor, a->cor);
            d->tropas = a->tropas / 2;
            a->tropas -= d->tropas;
        } else {
            printf("O defensor perdeu uma tropa! Restam %d em %s.\n", d->tropas, d->nome);
        }
    } else {
        printf("A defesa segurou! O atacante perdeu uma tropa.\n");
        if (a->tropas > 0) a->tropas--;
    }
}

void exibir(int a, struct Territorio *t) {
    if (a == 0) {
        printf("Nada cadastrado ainda.\n");
    } else {
        for (int i = 0; i < a; i++) {
            printf("[%d] %s (%s) - Tropas: %d\n", i + 1, t[i].nome, t[i].cor, t[i].tropas);
        }
    }
} 

void liberarMemoria(struct Territorio *mapa, char *missao) {
    free(mapa);
    free(missao); // Libera a string da missão alocada com malloc
    printf("\nMemoria liberada com sucesso!\n");
}

void LimparBufferEntradas() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
}

int verifTerritorios(int terr) {
    if (terr < 2) {
        printf("\nPrecisa de pelo menos 2 territórios para lutar!\n");
        return 1;    
    }
    return 0;
}

int verifIndice(const struct Territorio *m, int idx_a, int idx_d, int terr) {
    if (idx_a < 1 || idx_a > terr || idx_d < 1 || idx_d > terr) {
        printf("\nIndice invalido!\n");
        return 1;
    }
    if (idx_a == idx_d) {
        printf("\nNao pode se atacar!\n");
        return 1;
    }
    if (strcmp(m[idx_a-1].cor, m[idx_d-1].cor) == 0) {
        printf("\nAtacar aliado nao pode!\n");
        return 1;
    }
    return 0;
}