//--------------------------------------------------------------
// NOME : Gabriel Braga Lagrotaria de Oliveira 
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <string.h>


// ######### ESCREVA O NROUSP AQUI
int nroUSP() {
    return 11796600;
}

//-------------------------------------------

// nos das listas de adjacencias
typedef struct adj {
	int v;
	struct adj* prox;
} NO;

// vertices
typedef struct {
	NO* inicio;
} VERTICE;



void addPilha(VERTICE* f, int v){ //adiciona um novo NO no fim da PILHA
    
    NO* novoFim = (NO*) malloc(sizeof(NO));
    
    novoFim->v = v;

    novoFim->prox = f->inicio;
    
    f->inicio = novoFim;
}

void removeFinal(VERTICE* f){
    if(!f->inicio)
        return;

    NO* fim = f->inicio;
    f->inicio = fim->prox;
    free(fim);

}

bool adicionaNoInicio(NO** v, int valor){ //adiciona um NO no inicio da lista ligada de NO's
    if(!v)
        return false;
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->v = valor;
    novo->prox = (*v);
    (*v) = novo;
    return true;
}



void percorreProfundidade(VERTICE* g, int i, int destino, int vertices, bool flag[], int maxVer, NO** caminhos, VERTICE* caminhoAtual){
    
    ++vertices;

    addPilha(caminhoAtual, i);

    flag[i] = true;

    if(i == destino){

        NO* atual = caminhoAtual->inicio;

        while (atual)
        {
            adicionaNoInicio(caminhos, atual->v);

            atual = atual->prox;
        }
        flag[i] = false;
        removeFinal(caminhoAtual);
        return;
        
    }


    if(vertices > maxVer){
        removeFinal(caminhoAtual);
        flag[i] = false;
        return;
    }
    

    NO* adj = g[i].inicio;
    
    while(adj){

        if(!flag[adj->v])
            percorreProfundidade(g, adj->v, destino, vertices, flag, maxVer, caminhos, caminhoAtual);
        
        adj = adj->prox;
    }
    flag[i] = false;
    removeFinal(caminhoAtual);
}


// funcao principal
NO* caminhos_max_d(VERTICE* g, int n, int x, int y, int d);

//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------
NO* caminhos_max_d(VERTICE* g, int n, int x, int y, int d)
{
    NO* caminhos = NULL;

	bool flag[n]; //vetor de flags, usado para marcar se um vertice ja foi visitado ou nao 
    //OBS.: PROFESSOR DISSE QUE PODERIA SER USADO, JÁ QUE NÃO HÁ UM CAMPO FLAG NO TYPEDEF DO VERTICE

    for(int i = 0; i < n; i++){ //inicialização do vetor de flags
        flag[i] = false;
    }
	
    VERTICE* f = (VERTICE*) malloc(sizeof(VERTICE)); //cria estrutura auxiliar que funciona como uma pilha para busca em profundidade

    f->inicio = NULL;

    flag[x] = true;//marca como visitado

    percorreProfundidade(g, x, y, 0, flag, d, &caminhos, f);

    return caminhos;
    
	// seu codigo AQUI
}



