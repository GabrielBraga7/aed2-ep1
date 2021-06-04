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

typedef struct NOF{
    NOF* ant;
    int v;
}NOF;

//estrutura de PILHA auxiliar, usada para a busca em largura
typedef struct PILHA{
    NOF* fim;
}PILHA;



void addPilha(PILHA* f, int v){ //adiciona um novo NO no fim da PILHA
    
    NOF* novoFim = (NOF*) malloc(sizeof(NOF));
    
    novoFim->v = v;

    novoFim->ant = f->fim;
    
    f->fim = novoFim;
}

void removeFinal(PILHA* f){
    if(!f->fim)
        return;

    NOF* fim = f->fim;
    f->fim = fim->ant;
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



void percorreProfundidade(VERTICE* g, int i, int destino, int vertices, bool flag[], int maxVer, NO** caminhos, PILHA* caminhoAtual){
    
    ++vertices;

    addPilha(caminhoAtual, i);

    flag[i] = true;

    if(i == destino){

        NOF* atual = caminhoAtual->fim;

        while (atual)
        {
            adicionaNoInicio(caminhos, atual->v);

            atual = atual->ant;
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
	
    PILHA* f = (PILHA*) malloc(sizeof(PILHA)); //cria estrutura auxiliar de PILHA para busca em profundidade

    f->fim = NULL;

    flag[x] = true;//marca como visitado

    percorreProfundidade(g, x, y, 0, flag, d, &caminhos, f);

    return caminhos;
    
	// seu codigo AQUI
}




void inicializaGrafo(VERTICE** g, int N){
    *g = (VERTICE*) malloc(sizeof(VERTICE)*N);

    for(int i = 0; i < N; i++){
        ((*g)[i]).inicio = NULL;
    }
}
bool adicionaVertice (VERTICE** v, int remetente, int valor) {
    if(!v)
        return false;
    NO* inicio = (*v)[remetente].inicio;
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->prox = inicio;
    novo->v = valor;
    ((*v)[remetente]).inicio = novo;
    return true;
}
void imprimeGrafo(VERTICE* inicio, int T){
    VERTICE* p = inicio;
    for(int i = 0; i < T; i++){
        printf("%d:",i);
        NO* a = p[i].inicio;
        while(a){
            printf("%d ", a->v);
            a = a->prox;
        }
        printf("\n");
    }
}

void GRAPHrandER(VERTICE** grafo, int V, int A) { 
   double prob = (double) A / (V*(V-1));
   inicializaGrafo(grafo, V);
   for (int v = 1; v < V; ++v)
      for (int w = 1; w < V; ++w)
         if (v != w)
            if (rand( ) < prob*(RAND_MAX+1.0))
               adicionaVertice( grafo, v, w);
}

void teste1(){
    VERTICE* grafo;
    int tamanho = 6;
    inicializaGrafo(&grafo, tamanho);
    adicionaVertice(&grafo, 1, 2);
    //adicionaVertice(&grafo, 2, 1);
    adicionaVertice(&grafo, 1, 3);
    //adicionaVertice(&grafo, 3, 1);
    adicionaVertice(&grafo, 3, 2);
    //adicionaVertice(&grafo, 2, 3);
    adicionaVertice(&grafo, 3, 5);
    //adicionaVertice(&grafo, 5, 3);
    adicionaVertice(&grafo, 4, 2);
    //adicionaVertice(&grafo, 2, 4);
    adicionaVertice(&grafo, 4, 3);
    //adicionaVertice(&grafo, 3, 4);
    adicionaVertice(&grafo, 5, 4);
    //adicionaVertice(&grafo, 4, 5);
    //adicionaVertice(&grafo, 2, 6);
    //adicionaVertice(&grafo, 6, 7);
    //adicionaVertice(&grafo, 7, 0);
	imprimeGrafo(grafo, tamanho);
	NO* resp = caminhos_max_d(grafo, tamanho, 1, 2, 3);
    NO* atual = resp;
    printf("\n\n");
    while(atual){
        printf("%d,",atual->v);
        NO* temp = atual;
        atual = atual->prox;
        free(temp);
    }
}

void teste2(){
    VERTICE* grafo;
    int tamanho = 6;
    inicializaGrafo(&grafo, tamanho);
    adicionaVertice(&grafo, 1, 2);
    adicionaVertice(&grafo, 1, 3);
    adicionaVertice(&grafo, 1, 4);
    adicionaVertice(&grafo, 1, 5);

    adicionaVertice(&grafo, 2, 1);
    adicionaVertice(&grafo, 2, 3);
    adicionaVertice(&grafo, 2, 4);
    adicionaVertice(&grafo, 2, 5);

    adicionaVertice(&grafo, 3, 1);
    adicionaVertice(&grafo, 3, 2);
    adicionaVertice(&grafo, 3, 5);

    adicionaVertice(&grafo, 4, 1);
    adicionaVertice(&grafo, 4, 2);
    adicionaVertice(&grafo, 4, 5);

    adicionaVertice(&grafo, 5, 2);
    adicionaVertice(&grafo, 5, 3);
    adicionaVertice(&grafo, 5, 4);

	imprimeGrafo(grafo, tamanho);
	NO* resp = caminhos_max_d(grafo, tamanho, 1, 2, 3);
    NO* atual = resp;
    printf("\n\n");
    while(atual){
        printf("%d,",atual->v);
        NO* temp = atual;
        atual = atual->prox;
        free(temp);
    }

}
void teste3(){
    VERTICE* grafo;
    int tamanho = 8;
    GRAPHrandER(&grafo, tamanho, 20);
    imprimeGrafo(grafo, tamanho);
	NO* resp = caminhos_max_d(grafo, tamanho, 5, 6, 4);
    NO* atual = resp;
    printf("\n\n");
    while(atual){
        printf("%d,",atual->v);
        NO* temp = atual;
        atual = atual->prox;
        free(temp);
    }

}
//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
// mas nao entregue o codido de main() nem inclua nada
// abaixo deste ponto
//---------------------------------------------------------
int main()
{
	if (nroUSP()==0) printf("\n\nNro USP nao informado!!!\n\n");
    teste1();
    printf("\n");
    teste2();
    printf("\n");
    teste3();

	// crie um grafo de teste aqui
	// chame a funcao caminhos_max_d implementada
	// verifique se a lista retornada está correta
    return 0;
}


