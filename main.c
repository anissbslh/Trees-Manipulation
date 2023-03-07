#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int bool;

typedef struct Noeud Noeud;
struct Noeud
{
    int val;
    bool color;
    Noeud* FD;
    Noeud* FG;
    Noeud* pere;
    int id;
};

void AllouerNoeud(Noeud** P)
{
    *P = (Noeud*)malloc(sizeof(Noeud));
}

void Aff_Val(Noeud* N,int val)
{
    N->val = val;
}

void Aff_Color(Noeud* N,int color)
{
    N->color = color;
}

void Aff_FG(Noeud* N,Noeud* FG)
{
    N->FG = FG;
}

void Aff_FD(Noeud* N,Noeud* FD)
{
    N->FD = FD;
}

void Aff_Id(Noeud* N,int id)
{
    N->id = id;
}

Noeud* FG(Noeud* N)
{
    return N->FG;
}

Noeud* FD(Noeud* N)
{
    return N->FD;
}

int Id(Noeud* P)
{
    return P->id;
}

int Insert(Noeud** N,int val,int color,int* id)
{
    Noeud* P = *N;
    if(*N != NULL)
    {
        Noeud* Q = NULL;
        while(P != NULL)
        {
            if(val == P->val)
                return 1;
            else
            {
                Q = P;
                if(val<P->val)
                    P = FG(P);
                else
                    P = FD(P);
            }
        }

        AllouerNoeud(&P);
        Aff_Val(P,val);
        Aff_Color(P,color);
        Aff_FD(P,NULL);
        Aff_FG(P,NULL);
        Aff_Id(P,*id);
        *id += 1;
        if(val>Q->val)
            Aff_FD(Q,P);
        else
            Aff_FG(Q,P);


        return 0;
    }
    else
    {
        AllouerNoeud(&P);
        Aff_Val(P,val);
        Aff_Color(P,color);
        Aff_FD(P,NULL);
        Aff_FG(P,NULL);
        Aff_Id(P,*id);

        *id += 1;
        *N = P;
        return 0;
    }

}

void CreerArbre(Noeud** R,int n)
{
    int val_alea;
    bool col_alea;
    bool trouv;
    Noeud* P;
    int id = 1;

    srand(time(NULL));
    if(n>0)
    {
        AllouerNoeud(R);
        Aff_FD(*R,NULL);
        Aff_FG(*R,NULL);
        Aff_Val(*R,0);
        Aff_Color(*R,0);
        Aff_Id(*R,0);

        for(int i=0;i<n;i++)
        {
            val_alea = rand()%1000;
            col_alea = rand()%2;
            if(col_alea == 0)
            {
                P = FG(*R);
                trouv = Insert(&P,val_alea,col_alea,&id);
                while(trouv == 1)
                {
                    val_alea = rand()%1000;
                    trouv = Insert(&P,val_alea,col_alea,&id);
                }
                if(FG(*R) == NULL)
                    Aff_FG(*R,P);
            }
            else
            {
                P = FD(*R);
                trouv = Insert(&P,val_alea,col_alea,&id);
                while(trouv == 1)
                {
                    val_alea = rand()%1000;
                    trouv = Insert(&P,val_alea,col_alea,&id);
                }
                if(FD(*R) == NULL)
                    Aff_FD(*R,P);
            }
        }
    }
    else
        *R = NULL;

}

void GenererGraph(Noeud* R,FILE* fptr,int* cptNil)
{
    if(R != NULL)
    {
        //printf("%10d %10d\n",R->val,R->color);
        if(FG(R) != NULL)
        {
            if(FG(R)->color == 0)
                fprintf(fptr,"\n\t%d [label=%d ,style=filled , fillcolor=black, fontcolor=white];",FG(R)->id,FG(R)->val);
            fprintf(fptr,"\n\t%d -- %d;",R->id,FG(R)->id);

            GenererGraph(FG(R),fptr,cptNil);
        }
        else
        {
            fprintf(fptr,"\n\tNIL%d [style=invis];",*cptNil);
            fprintf(fptr,"\n\t%d -- NIL%d [style=invis];",R->id,*cptNil);
            *cptNil += 1;
        }


        if(FD(R) != NULL)
        {
            if(FD(R)->color == 0)
                fprintf(fptr,"\n\t%d [label=%d ,style=filled , fillcolor=black, fontcolor=white];",FD(R)->id,FD(R)->val);
            fprintf(fptr,"\n\t%d -- %d;",R->id,FD(R)->id);

            GenererGraph(FD(R),fptr,cptNil);
        }
        else
        {
            fprintf(fptr,"\n\tNIL%d [style=invis];",*cptNil);
            fprintf(fptr,"\n\t%d -- NIL%d [style=invis];",R->id,*cptNil);
            *cptNil += 1;
        }

    }
}

void PreOrdre(Noeud* R)
{
    if(R != NULL)
    {
        printf("%10d %10d\n",R->val,R->color);
        if(FG(R) != NULL)
            PreOrdre(FG(R));

        if(FD(R) != NULL)
            PreOrdre(FD(R));
    }
}


/*Noeud* PremierInordre(Noeud* R)
{
    if(R != NULL)
    {
        if(FG(R) != NULL)
            return PremierInordre(FG(R));

        if(FD(R) != NULL)
            return PremierInordre(FD(R));
        else
            return R;
    }
    else
        return NULL;
}*/


void DessinArbre(Noeud* R,FILE* fptr)
{
    int cptNil = 0;
    if(R != NULL)
    {
        fprintf(fptr,"graph{\n\t%d [label=Inf style=filled , fillcolor=black, fontcolor=white];",R->id);
        GenererGraph(R,fptr,&cptNil);
        fprintf(fptr,"\n}");
        fclose(fptr);
        system("dot -Tpng graph.dot -o graph.png");
    }
    else
        printf("\nERREUR: L'arbre est vide!");
}

int main()
{
    Noeud* Arb;
    Noeud* Q = NULL;

    //File Initialisation-------------------------------------------
    FILE* fptr;
    fptr = fopen("graph.dot","w");
    fprintf(fptr,"");
    fclose(fptr);

    //File Configuration-------------------------------------------------------------
    fptr = fopen("graph.dot","a");

    //Tree Creation-------------------------------------------------------------------
    int n=100;
    CreerArbre(&Arb,n);
    PreOrdre(Arb);

    //Tree Drawing---------------------------------------------------------------------
    DessinArbre(Arb,fptr);


    return 0;
}
