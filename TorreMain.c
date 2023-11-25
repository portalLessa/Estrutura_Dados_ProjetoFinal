#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Variáveis globais para controle do jogo --------------------
// Variável que controla o número de discos da torre
static int numeroDeDiscos;
static int vitoria = 0;

// Definindo as structs ----------
// Struct do tipo No, representa cada nó presente na pilha
typedef struct tNo {
    int valor;
    struct tNo *prox;
} tNo;

// Struct do tipo Pilha, representa as pilhas em si
typedef struct tPilha {
    tNo *topo;
} tPilha;

// Esqueleto das funcoes -----------
void colocarDiscos(tPilha *);
void inicializarPilha(tPilha *);
tPilha criarPilha();
void push(int, tPilha *);
void pop(tPilha *);
void moverNo(tPilha *, tPilha *);
bool verificarMaior(int, tPilha *);
void exibirPilha(tPilha *);
void exibirPilhas(tPilha *, tPilha *, tPilha *);

// Função para verificar se todos os discos estão corretamente empilhados na última torre
bool verificarVitoria(tPilha *pilhaC) {
    if (pilhaC->topo == NULL) {
        // A pilha C está vazia, a vitória só é possível se todos os discos foram movidos para lá
        return false;
    }

    int disco = numeroDeDiscos;
    tNo *ptr = pilhaC->topo;

    while (ptr != NULL && disco >= 1) {
        if (ptr->valor != disco) {
            return false; // Se o disco não estiver na ordem correta, não é uma vitória
        }

        disco--;
        ptr = ptr->prox;
    }

    return true; // Se todos os discos estão corretamente empilhados, é uma vitória
}

// Função main -----------
int main(int argc, char *argv[]) {
    tPilha pilhaA = criarPilha();
    tPilha pilhaB = criarPilha();
    tPilha pilhaC = criarPilha();

    int teste;
    // Pergunta o valor de discos ao usuário
    printf("Quantos discos você deseja: ");
    scanf("%d", &numeroDeDiscos);
    colocarDiscos(&pilhaA);

    // Imprimindo as pilhas
    do {
        printf("\n===============================\n");
        printf("-------TORRE DE HANOI--------\n");
        exibirPilhas(&pilhaA, &pilhaB, &pilhaC);
        scanf("%d", &teste);
        printf("\n===============================\n");

        // Verifica a condição de vitória
        if (verificarVitoria(&pilhaC)) {
            printf("Parabéns! Você venceu!\n");
            vitoria = 1;
        } else {
            // Aqui você pode chamar a função moverNo conforme necessário
            moverNo(&pilhaA, &pilhaB);
        }
    } while (vitoria != 1);

    return 0;
}


// Funcoes -----------
// Inicializando a pilha, fazendo o topo dela ficar vazio, ou seja, apontar para null
void inicializarPilha(tPilha *p) {
    p->topo = NULL;
}

// Coloca os discos na pilha inicial
void colocarDiscos(tPilha *p) {
    int v = numeroDeDiscos;
    for (int i = v; i > 0; i--) {
        push(i, p);
    }
}

// Funcao de criar pilha
tPilha criarPilha() {
    // Alocando a pilha
    tPilha *p = (tPilha *)malloc(sizeof(tPilha));
    // Verificando se o alocamento ocorreu corretamente
    if (p == NULL) {
        printf("\nErro de alocacao de pilha!");
        exit(0);
    } else {
        // Inicializando e retornando a pilha criada
        inicializarPilha(p);
        return *p;
    }
}

// Funcao de empilhamento - adicionar elementos ao topo da pilha
void push(int valor, tPilha *p) {
    // Criando um novo nó
    tNo *ptr = (tNo *)malloc(sizeof(tNo));
    // Verificando se realmente foi alocado nó
    if (ptr == NULL) {
        printf("\nErro ao criar no!");
        return;
    } else {
        // Caso o nó seja alocado, o nó recebe o valor a ser atribuído a ele
        ptr->valor = valor;
        // Seu ponteiro prox aponta para o topo atual da pilha
        ptr->prox = p->topo;
        // Topo da pilha começa a apontar para o novo elemento
        p->topo = ptr;
    }
}

// Funcao de desempilhar - retirar o elemento do topo da pilha
void pop(tPilha *p) {
    // Referenciando o topo da pilha
    tNo *ptr = p->topo;
    // Verificando se o topo da pilha está vazio
    if (ptr == NULL) {
        printf("\nO topo da pilha está vazio!");
        return;
    } else {
        // O topo da pilha começa a apontar para o prox da referencia, ou seja, aponta para o elemento abaixo do topo
        p->topo = ptr->prox;
        ptr->prox = NULL;
        // Liberando o alocamento da referencia
        free(ptr);
    }
}

// Funcao para mover um nó de uma pilha para outra
void moverNo(tPilha *pilhaOrigem, tPilha *pilhaDestino) {
    // Verifica se a pilha de origem não está vazia
    if (pilhaOrigem->topo == NULL) {
        printf("\nPilha de origem vazia. Nada a mover.\n");
        return;
    }

    int topo1 = pilhaOrigem->topo->valor;
    int topo2 = (pilhaDestino->topo != NULL) ? pilhaDestino->topo->valor : numeroDeDiscos + 1;

    // Verifica se o valor é maior que o topo da pilha de destino
    if (topo1 > topo2) {
        printf("\nO valor é maior que o valor no topo da pilha de destino. Movimento não permitido.\n");
        return;
    }

    // Remove o nó da pilha de origem
    pop(pilhaOrigem);

    // Adiciona o nó à pilha de destino
    push(topo1, pilhaDestino);

    printf("\nValor %d movido com sucesso da pilha de origem para a pilha de destino.\n", topo1);
}

// Funcao para verificar se o valor do nó é maior que o valor no topo da pilha
bool verificarMaior(int valor, tPilha *pilhaDestino) {
    if (pilhaDestino->topo == NULL) {
        // A pilha de destino está vazia, qualquer valor pode ser movido
        return true;
    }

    // Verifica se o valor do nó é maior que o valor no topo da pilha
    return valor < pilhaDestino->topo->valor;
}

// Funcao que imprime todos os valores presentes na pilha
void exibirPilha(tPilha *p) {
    tNo *ptr = p->topo;
    int v = numeroDeDiscos;

    if (ptr == NULL) {
        for (int i = v; i > 0; i--) {
            printf("0");
            printf("\n");
        }
        return;
    } else {
        // Percorrendo toda a pilha e printando o valor de cada nó
        while (ptr != NULL) {
            printf("%d", ptr->valor);
            ptr = ptr->prox;
            printf("\n");
        }
    }
}

void exibirPilhas(tPilha *p1, tPilha *p2, tPilha *p3) {
    printf("\nTorre 1\n");
    exibirPilha(p1);
    printf("\n\nTorre 2\n");
    exibirPilha(p2);
    printf("\n\nTorre 3\n");
    exibirPilha(p3);
}
void moverNo(tPilha *pilhaOrigem, tPilha *pilhaDestino) {
    // Verifica se a pilha de origem não está vazia
    if (pilhaOrigem->topo == NULL) {
        printf("\nPilha de origem vazia. Nada a mover.\n");
        return;
    }

    int topo1 = pilhaOrigem->topo->valor;
    int topo2 = (pilhaDestino->topo != NULL) ? pilhaDestino->topo->valor : numeroDeDiscos + 1;

    // Verifica se o valor é maior que o topo da pilha de destino
    if (topo1 > topo2) {
        printf("\nO valor é maior que o valor no topo da pilha de destino. Movimento não permitido.\n");
        return;
    }

    // Remove o nó da pilha de origem
    pop(pilhaOrigem);

    // Adiciona o nó à pilha de destino
    push(topo1, pilhaDestino);

    // Imprime informação sobre o movimento
    printf("\nMovendo disco %d da Torre %d para a Torre %d\n", topo1, pilhaOrigem == &pilhaA ? 1 : (pilhaOrigem == &pilhaB ? 2 : 3),
           pilhaDestino == &pilhaA ? 1 : (pilhaDestino == &pilhaB ? 2 : 3));
}
