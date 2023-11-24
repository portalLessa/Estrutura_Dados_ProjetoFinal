#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

//Variáveis globais para controle do jogo --------------------
//variável que controla o número de discos da torre
static int numeroDeDiscos;
static int vitoria = 0;

// definindo as structs ----------
// struct do tipo No, representa cada no presente na pilh
typedef struct tNo{
	int valor;
	struct tNo *prox; 
}tNo;

// struct do tipo Pilha, representa as plihas em si
typedef struct tPilha {
	tNo *topo;
} tPilha;


// Esqueleto das funcoes -----------
void colocarDiscos(tPilha*);
void inicializandoPilha(tPilha*);
tPilha criarPilha();
void push(int,tPilha*);
void pop(tPilha*);
void moverNo(int, tPilha*, tPilha*);
bool verificarMaior(int, tPilha*);
void exibirPilha(tPilha*);
void exibirPilhas(tPilha*,tPilha*,tPilha*);

// Funcao main -----------
int main(int argc, char *argv[]) {
	tPilha pilhaA = criarPilha();
	tPilha pilhaB = criarPilha();
	tPilha pilhaC = criarPilha();

	int teste;
	//Pergunta o valor de discos ao usuário
	printf("Quantos discos você deseja: ");
	scanf("%d", &numeroDeDiscos);
	colocarDiscos(&pilhaA);
	/*
	// passando o endereço da variável como parametro
    // Inicializando pilha A com os valores iniciais
	push(5,&pilhaA);
	push(4,&pilhaA);
	push(3,&pilhaA);	
	push(2,&pilhaA);
	push(1,&pilhaA);

	// Movimentos teste na Torre (pode tirar depois isso 👇🏼)
    moverNo(1, &pilhaA, &pilhaB);
    moverNo(2, &pilhaA, &pilhaC);
	*/
	// imprimindo as pilhas
	do{
    printf("\n===============================\n");
    printf("-------TORRE DE HANOI--------\n");
	exibirPilhas(&pilhaA,&pilhaB,&pilhaC);
	scanf("%d",&teste);
	printf("\n===============================\n");
	}while(vitoria != 1);

	return 0;
}

// Funcoes -----------
//  inicializando a pilha, fazendo o topo dela fica vazio, ou seja, apontar para null
void inicializarPilha(tPilha *p) {
	p->topo = NULL;
}

// coloca os discos na pilha inicial
void colocarDiscos(tPilha *p) {
	int v = numeroDeDiscos;
	for(int i=v;i>0;i--) {
		push(i,p);
	}
}

// funcao de criar pilha
tPilha criarPilha() {
	// alocando a pilha
	tPilha *p = (tPilha*) malloc(sizeof(tPilha));
	// verificando se o alocamento ocorreu corretamente
	if (p == NULL) {
		printf("\nErro de alocacao de pilha!");
		exit(0);
	} else {
		// inicializando e retornando a pilha criada
		inicializarPilha(p);
		return *p;
	}
}

// funcao de empilhamento - adicionar elementos ao topo da pilha
void push(int valor, tPilha *p) {
	// Criando um novo nó
	tNo *ptr = (tNo*) malloc(sizeof (tNo));
	// verificando se realmente foi alocado nó
	if (ptr == NULL) {
		printf("\nErro ao criar no!");
		return;
	} else {
		// caso o no seja alocado , o nó recebe o valor a ser atribuido a ele
		ptr->valor = valor;
		//seu ponteiro prox aponta para topo atual da pilha
		ptr->prox = p->topo;
		//topo da pilha começa a apontar para o novo elemento
		p->topo = ptr;
		
	}
}

// funcao de desempilhar - retirar o elemento do topo da pilha
void pop(tPilha *p) {
	// referenciando o topo da pilha
	tNo* ptr = p->topo;
	// verficando se o topo da pilha esta vazio
	if (ptr == NULL) {
		printf("\nO topo da pilha esta vazio!");
		return;
	} else {
		// o topo da pilha começa a apontar para o prox da referencia, ou seja, aponta para o elemento abaixo do topo
		p->topo = ptr->prox;
		ptr->prox = NULL;
		// liberando o alocamento da refencia 
		free(ptr);
	}
}

// Função para mover um nó de uma pilha para outra
void moverNo(int valor, tPilha *pilhaOrigem, tPilha *pilhaDestino) {
    // Verifica se a pilha de origem não está vazia
    if (pilhaOrigem->topo == NULL) {
        printf("\nPilha de origem vazia. Nada a mover.\n");
        return;
    }

    // Verifica se o valor desejado está no topo da pilha de origem
    if (pilhaOrigem->topo->valor != valor) {
        printf("\nO valor %d não está no topo da pilha de origem. Nada a mover.\n", valor);
        return;
    }

 	// Verifica se o valor é maior que o topo da pilha de destino
    if (!verificarMaior(valor, pilhaDestino)) {
        printf("\nO valor %d é maior que o valor no topo da pilha de destino. Movimento não permitido.\n", valor);
        
        return;
    }

    // Remove o nó da pilha de origem
    pop(pilhaOrigem);

    // Adiciona o nó à pilha de destino
    push(valor, pilhaDestino);

    printf("\nValor %d movido com sucesso da pilha de origem para a pilha de destino.\n", valor);
}

// Função para verificar se o valor do nó é maior que o valor no topo da pilha
bool verificarMaior(int valor, tPilha *pilhaDestino) {
    if (pilhaDestino->topo == NULL) {
        // A pilha de destino está vazia, qualquer valor pode ser movido
        return true;
    }

    // Verifica se o valor do nó é maior que o valor no topo da pilha
    return valor < pilhaDestino->topo->valor;
}

// funcao que imprime todos os valores presentes na pilha
void exibirPilha(tPilha *p) {
	tNo *ptr = p->topo;
	int v = numeroDeDiscos;
	
	if (ptr == NULL) {
		for(int i=v;i>0;i--) {
			printf("0");
			printf("\n");
		}
		return;
	} else {
		// percorrendo toda a pilha e printando o valor de cada no
		while(ptr != NULL) {
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