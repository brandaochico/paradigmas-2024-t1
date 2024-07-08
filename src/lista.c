/**
 * Insira seu código para solucionar o trabalho neste arquivo.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lista.h"

void Lista_new(Lista* lista, int data_size, void (*free_data)(void*)){
    lista->primeiro = NULL;
    lista->atual = NULL;
    lista->ultimo = NULL;
    lista->data = malloc(data_size);
    lista->tamanho = 0;
}

//Libera memória utilizada pela lista, e a reinicializa.
void Lista_delete(Lista* lista){
    Nodo *atual = lista->primeiro;
    while (atual != NULL) {
        Nodo *prox = atual->prox;
        free(atual->valor);
        free(atual);
        atual = prox;
    }
    free(lista->data);
    lista->primeiro = NULL;
    lista->atual = NULL;
    lista->ultimo = NULL;
    lista->tamanho = 0;
}

//Retorna 0 (zero) casa o lista possua elementos, e 1 se estiver vazia.
int Lista_isEmpty(Lista* lista){
    return lista->primeiro == NULL;
}

//Retorna o número de elementos armazenados na lista.
int Lista_size(Lista* lista){
    return lista->tamanho;
}

//Insere um novo valor no início da lista.
void Lista_pushFront(Lista* lista, void* valor){
    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    novo->valor = malloc(sizeof(lista->data));
    memcpy(novo->valor, valor, sizeof(lista->data));
    novo->prox = lista->primeiro;
    
    if (lista->primeiro == NULL) {
        lista->ultimo = novo;
    }
    
    lista->primeiro = novo;
    lista->tamanho++;
}

//Insere um novo valor no final da lista.
void Lista_pushBack(Lista* lista, void* valor){
    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    novo->valor = malloc(sizeof(lista->data));
    memcpy(novo->valor, valor, sizeof(lista->data));
    novo->prox = NULL;
    
    if (lista->primeiro == NULL) {
        lista->primeiro = novo;
    } else {
        lista->ultimo->prox = novo;
    }
    
    lista->ultimo = novo;
    lista->tamanho++;
}

//Procura na lista por um elemento associado com a chave.
int Lista_search(Lista* lista, void* chave, void* dest, int (*cmp)(void*,void*)){
    Nodo *aux = lista->primeiro;
    while (aux != NULL){
        if (cmp(chave, aux->valor) == 0){
            memcpy(dest, aux->valor, sizeof(lista->data));
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

//Ajusta o 'elemento atual' da lista para o primeiro elemento.
void Lista_first(Lista* lista){
    lista->atual = lista->primeiro;
}

//Ajusta o 'elemento atual' da lista para o último elemento.
void Lista_last(Lista* lista){
    lista->atual = lista->ultimo;
}

//Ajusta o 'elemento atual' da lista para próximo elemento.
int Lista_next(Lista* lista){
    if (lista->atual != NULL && lista->atual->prox != NULL){
        lista->atual = lista->atual->prox;
        return 1;
    }
    return 0;
}

//Retorna o valor do 'elemento atual' em 'dest'.
void Lista_current(Lista* lista, void* dest){
    if (lista->atual != NULL){
        memcpy(dest, lista->atual->valor, sizeof(lista->data));
    }
}

//Insere um novo elemento na lista após o 'elemento atual'.
void Lista_insertAfter(Lista* lista, void* dado){
    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    novo->valor = malloc(sizeof(lista->data));
    memcpy(novo->valor, dado, sizeof(lista->data));
    novo->prox = NULL;
    
    if (lista->atual == NULL) {
        lista->primeiro = novo;
        lista->ultimo = novo;
    } else {
        novo->prox = lista->atual->prox;
        lista->atual->prox = novo;
        if (lista->atual == lista->ultimo) {
            lista->ultimo = novo;
        }
    }
    
    lista->atual = novo;
    lista->tamanho++;
}

///////Extras

//Remove o 'elemento atual' da lista.
void Lista_removeCurrent(Lista* lista){
    if (lista->atual == NULL) {
        return;
    }

    Nodo *remover = lista->atual;
    if (remover == lista->primeiro) {
        lista->primeiro = remover->prox;
    } else {
        Nodo *anterior = lista->primeiro;
        while (anterior != NULL && anterior->prox != remover) {
            anterior = anterior->prox;
        }
        if (anterior != NULL) {
            anterior->prox = remover->prox;
        }
    }

    if (remover == lista->ultimo) {
        lista->ultimo = NULL;
    }

    lista->atual = remover->prox;
    free(remover->valor);
    free(remover);
    lista->tamanho--;
}

//Ajusta o 'elemento atual' da lista para elemento anterior.
int Lista_previous(Lista* lista){
    if (lista->atual == NULL) {
        return 0;
    }

    Nodo *anterior = lista->primeiro;
    while (anterior != NULL && anterior->prox != lista->atual) {
        anterior = anterior->prox;
    }

    if (anterior == NULL) {
        return 0;
    }

    lista->atual = anterior;
    return 1;
}

//Insere um novo elemento no lista antes do 'elemento atual'.
void Lista_insertBefore(Lista* lista, void* dado){
    if (lista->atual == NULL) {
        Lista_pushFront(lista, dado);
        return;
    }

    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    novo->valor = malloc(sizeof(lista->data));
    memcpy(novo->valor, dado, sizeof(lista->data));
    novo->prox = lista->atual;

    if (lista->atual == lista->primeiro) {
        lista->primeiro = novo;
    } else {
        Nodo *anterior = lista->primeiro;
        while (anterior != NULL && anterior->prox != lista->atual) {
            anterior = anterior->prox;
        }
        if (anterior != NULL) {
            anterior->prox = novo;
        }
    }

    lista->atual = novo;
    lista->tamanho++;
}
