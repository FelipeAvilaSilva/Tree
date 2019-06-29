// Arvore AVL
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

int back(Apontador q, Apontador *r);
int Balanceamento(Apontador *pTree);

int Insert(Registro Reg, Apontador *pTree){        
    if(*pTree == NULL){
        *pTree = (Apontador) malloc(sizeof(No));
        (*pTree)->Reg = Reg;
        (*pTree)->pEsq = NULL; (*pTree)->pDir = NULL;   //1º elemento
        return 1;
    }
    else if(Reg.Chave < (*pTree)->Reg.Chave){
        if(Insert(Reg, &(*pTree)->pEsq)){
            if(Balanceamento(pTree))
                return 0;
            else 
                return 1;
        }
    }
    else if(Reg.Chave > (*pTree)->Reg.Chave){
        if(Insert(Reg, &(*pTree)->pDir)){
            if(Balanceamento(pTree))
                return 0;
            else
                return 1;
        }else
            return 0;
    }else
        return 0; // ja tem esse valor
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

int Altura(Apontador pTree){
    int iEsq = 0, iDir = 0;

    if(pTree == NULL)
        return 0;

    iEsq = Altura(pTree->pEsq);
    iDir = Altura(pTree->pDir);

    if(iEsq > iDir)
        return iEsq + 1;
    else
        return iDir + 1;
}

int Fb(Apontador pTree){
    if(pTree == NULL) return 0;
    return Altura(pTree->pEsq) - Altura(pTree->pDir);
}

void Rotse(Apontador *pTree){
    Apontador pAux;

    pAux = (*pTree)->pDir;
    (*pTree)->pDir = pAux->pEsq;
    pAux->pEsq = (*pTree);
    (*pTree) = pAux;
}

void Rotsd(Apontador *pTree){
    Apontador pAux;

    pAux = (*pTree)->pEsq;
    (*pTree)->pEsq = pAux->pDir;
    pAux->pDir = (*pTree);
    (*pTree) = pAux;
}

int BalancaEsquerda(Apontador *pTree){
    int fbe = Fb((*pTree)->pEsq);
    if(fbe > 0){
        Rotsd(pTree);
        return 1;
    }else if(fbe < 0){  //rotação dupla direita
        Rotse(&((*pTree)->pEsq));
        Rotsd(pTree); //&(*ptree);
        return 1;
    }
return 0;
}

int BalancaDireita(Apontador *pTree){
    int fbd = Fb((*pTree)->pDir);
    if(fbd < 0){
        Rotse(pTree);
        return 1;
    }else if(fbd > 0){ //Rotação dupla esquerda
        Rotsd(&((*pTree)->pDir));
        Rotse(pTree); //&(*ptree);
        return 1;
    }
return 0;
}

int Balanceamento(Apontador *pTree){
    int fb = Fb(*pTree);
    if(fb > 1)
        return BalancaEsquerda(pTree);
    else if(fb < -1)
        return BalancaDireita(pTree);
    else 
        return 0;
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