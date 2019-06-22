#include <stdio.h>
#include <stdlib.h>

typedef int TipoChave;  //Tipo das var.
typedef char TipoNome;
typedef struct No *Apontador;

typedef struct Registro{    //dados
    TipoChave Chave, Trash;
    TipoNome Nome[50];
}Registro;

typedef struct No{      //tree
    Registro Reg;
    Apontador pEsq, pDir;
}No;

void Insert(Registro Reg, Apontador *pTree){        
    if(*pTree == NULL){
        *pTree = (Apontador) malloc(sizeof(No));
        (*pTree)->Reg = Reg;
        (*pTree)->pEsq = NULL; (*pTree)->pDir = NULL;   //1º elemento
        return;
    }
    if(Reg.Chave < (*pTree)->Reg.Chave){        //recursao no lado esq da tree
        Insert(Reg, &(*pTree)->pEsq);
        return;
    }
    if(Reg.Chave > (*pTree)->Reg.Chave){        //recursao no lado dir da tree 
        Insert(Reg, &(*pTree)->pDir);
    }else{
        printf("Erro: Já existe uma pessoa com essa idade na arvore!\n");   
    }
}
void Print(Apontador pTree){        
    if(pTree != NULL){
        printf("\n%s -", pTree->Reg.Nome); 
        printf(" %d anos.", pTree->Reg.Chave);  
    }
    if(pTree->pEsq != NULL){       //imprime ate achar a folha do lad esq
        Print(pTree->pEsq);
    }
    if(pTree->pDir != NULL){        //imprime ate achar a folha no lad dir
        Print(pTree->pDir);
    }
}
void Seach(Registro *Reg, Apontador pTree){  
    if(pTree == NULL){
        printf("ERRO: nao tem registro na arvore\n");
        return;
    }
    if(Reg->Trash < pTree->Reg.Chave){      //prucura trash menor que a chave no lado esq com recursao
        Seach(Reg, pTree->pEsq);
        return;
    }
    if(Reg->Trash > pTree->Reg.Chave){      //prucura trash maior que a chave no lado dir com recursao
        Seach(Reg, pTree->pDir);
    }else{
        *Reg = pTree->Reg;
        printf("idade %d pertence a %s.\n", Reg->Chave, Reg->Nome);  //imprime caso for igual 
    }
}
int back(Apontador q, Apontador *r){
    Apontador aux;
    if((*r)->pDir != NULL){
        back(q, &(*r)->pDir);
        return 0;
    }
    q->Reg = (*r)->Reg;
    aux = *r;
    *r = (*r)->pEsq;
    free(aux);
}
int Remove(Registro Reg, Apontador *pTree){
    Apontador aux;

    if(*pTree == NULL){
        printf("ERRO: nao tem registro na arvore\n");
        return 0;
    }
    if(Reg.Chave < (*pTree)->Reg.Chave){    
        Remove(Reg, &(*pTree)->pEsq);
        return 0; 
    }
    if(Reg.Chave > (*pTree)->Reg.Chave){
        Remove(Reg, &(*pTree)->pDir);
        return 0;
    }

    if((*pTree)->pDir == NULL){
        aux = *pTree;
        *pTree = (*pTree)->pEsq;
        free(aux);
        return 0;
    }
    if((*pTree)->pEsq != NULL){
        back(*pTree, &(*pTree)->pEsq);
        return 0;
    }
    /*if((*pTree)->pEsq == NULL){*/
    aux = *pTree;
    *pTree = (*pTree)->pDir;
    free(aux);
}

int main(){
    Registro Reg;
    Apontador pTree;
    int select = 0;
    
    pTree = NULL;

    while(select != 5){
        printf("\n1-Inserir\n2-Remover\n3-Buscar\n4-Listar\n5-Sair\n");
        scanf("%d", &select);
        switch(select){
            case 1:
                printf("Digite o nome e a idade:\n");
                scanf("%s %d", Reg.Nome, &Reg.Chave);
                Insert(Reg, &pTree);
            break;

            case 2:
                printf("Digite uma numero para remover:\n");
                scanf("%d", &Reg.Chave);
                Remove(Reg, &pTree);
            break;

            case 3:
                printf("Digite a idade para buscar:\n");
                scanf("%d", &Reg.Trash);
                Seach(&Reg, pTree);
            break;

            case 4:
                Print(pTree);                
            break;

            case 5:
                exit(1);
            break;
        }
    }
    free(pTree);
return 0;
}