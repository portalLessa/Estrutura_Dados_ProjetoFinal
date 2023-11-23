#include <stdio.h>
#include <stdlib.h>

// definindo as structs ----------
// struct do tipo No, representa cada no presente na pilha
typedef struct tNo{
	int valor;
	struct tNo *prox; 
}tNo;

// struct do tipo Pilha, representa as plihas em si
typedef struct tPilha {
	tNo *topo;
} tPilha;


// Esqueleto das funcoes -----------
void inicializandoPilha(tPilha*);
tPilha criarPilha();
void push(int,tPilha*);
void pop(tPilha*);
void exibirPilha(tPilha*);

// Funcao main -----------
int main(int argc, char *argv[]) {
	tPilha pilhaA = criarPilha();
	tPilha pilhaB = criarPilha();
	
	// passando o endereço da variável como parametro
	push(1,&pilhaA);
	push(2,&pilhaA);
	push(3,&pilhaA);	
	push(5,&pilhaB);
	push(1,&pilhaB);
	// impeimindo as pilhas
	exibirPilha(&pilhaA);
	printf("\n\nPilha B\n");
	exibirPilha(&pilhaB);
	printf("\n");
	// desempilhando elementos para teste
	pop(&pilhaA);
	printf("\nPilha A apos o POP\n");
	exibirPilha(&pilhaA);
	return 0;
}

// Funcoes -----------
//  inicializando a pilha, fazendo o topo dela fica vazio, ou seja, apontar para null
void inicializarPilha(tPilha *p) {
	p->topo = NULL;
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

// funcao que imprime todos os valores presentes na pilha
void exibirPilha(tPilha *p) {
	tNo *ptr = p->topo;
	
	if (ptr == NULL) {
		printf("\nA pilha esta vazia!");
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