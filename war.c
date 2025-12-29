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

#define TAM_MAX_NOME 30 // Definindo constantes para os territorios e tamanho maximo da string da cor e nome
#define NUM_TERRITORIOS 5
#define TAM_MAX_COR 10

//definindo a struct do territorio
struct Territorio{
    char nome[TAM_MAX_NOME];
    char cor[TAM_MAX_COR];
    int tropas;   
};

//função para limpar o buffer de entrada
void LimparBufferEntredas(){
    int c;
    while ((c = getchar())!= '\n' && c != EOF ); 
};

int main(){
    struct Territorio cadastro[NUM_TERRITORIOS];
    int totalterritorios;
    int opcao;

    do{
        printf("----Bem vindo---\n");
        printf("======================\n");
        printf("---Menu de opções---\n");
        printf("======================\n");
        printf("1 - Para cadastrar um territorio\n");
        printf("2 - Para exibir os territorios cadastrador\n");
        printf("0 - Para sair\n");
        printf("======================\n");
        scanf("----> %d", &opcao);
        LimparBufferEntredas();

        switch (opcao)
        {
        case 1:
            if (totalterritorios < NUM_TERRITORIOS){
                printf("Digite o nome do territorio: ");
                fgets(cadastro[totalterritorios].nome, TAM_MAX_NOME, stdin);

                printf("Digite a cor do seu territorio: ");
                fgets(cadastro[totalterritorios].cor, TAM_MAX_COR, stdin);//aqui os valores do tipo char



                cadastro[totalterritorios].nome[strcspn(cadastro[totalterritorios].nome, "\n")] = '\0';// Finalidade: Remover o caractere de nova linha (\n) inserido por fgets.
                cadastro[totalterritorios].cor[strcspn(cadastro[totalterritorios].cor, "\n")] = '\0';// Garante que não haja salto de linha no meio da string         
            
                printf("Digite o numero de tropas: "); // separadaamente, a do tipo interio
                scanf("%d", &cadastro[totalterritorios].tropas);
                LimparBufferEntredas(); // usando a função de limpar buffer apos o scanf, preventivo
                
                totalterritorios ++;

            }else{
                printf("Maximo de territorios atingido\n");
                printf("\n Pressione enter para continuar..."); //Pausa para o usuario ler
                getchar();

            }

        break;

        case 2:
            if (totalterritorios == 0){ // confere se tem um territorio cadastrado
                printf("Nenhum territorio encontrado...\n ");
                printf("Pressione enter para continuar...");
                getchar();
   
            }else{
                for (int i = 0; i < totalterritorios; i++ ){ //Loop que corre todos os territorios
                    printf("======================\n");
                    printf("Territorio %d: \n", i + 1);
                    printf("Nome: %s \n", cadastro[i].nome);
                    printf("Cor: %s \n", cadastro [i].cor);
                    printf("Tropas: %d \n", cadastro[i].tropas);
                };

            };

            printf("Pressione enter para continuar..."); //pausa para o usuario ler 
            getchar();
            break;
            
    
        default: // defalt para valores invalidos
            printf("Valor digitado invalido...");
            printf("Pressione enter para continuar...");
            getchar();
            break;    
        };
    }while (opcao != 0);
    return 0;
};

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.


// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
