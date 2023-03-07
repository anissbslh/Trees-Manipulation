SOIENT
      X UN ARB DE (ENTIER,ENTIER,ENTIER);
      Inserer : FONCTION (ENTIER);
      Creer_Arbre,PreOrdre DES ACTION;

DEBUT
     APPEL Creer_Arbre(X,5);
     APPEL PreOrdre(X);
FIN

FONCTION Inserer(N,val,color,id): ENTIER
SOIENT
      N,P,Q DES ARB DE (ENTIER,ENTIER,ENTIER);
      val, color, id DES ENTIER;
      temp UNE STRUCTURE (ENTIER,ENTIER,ENTIER);
DEBUT
     P := N;
     AFF_STRUCT(temp,1,val);
     AFF_STRUCT(temp,2,color);
     AFF_STRUCT(temp,3,id);
     SI N <> NIL:
          Q := NIL;
          TQ P <> NIL:
             SI val = STRUCT(INFO(P),1):
                Inserer := 1;
             SINON
                  Q := P;
                  SI val < STRUCT(INFO(P),1):
                     P := FG(P);
                  SINON
                     P := FD(P);
                  FSI;
             FSI;
          FTQ;

          CREERNOEUD(P);
          AFF_INFO(P,temp);
          AFF_FD(P,NIL);
          AFF_FG(P,NIL);
          id := id+1;
          SI val > STRUCT(INFO(Q),1):
             AFF_FD(Q,P);
          SINON
             AFF_FG(Q,P);
          FSI;

          Inserer := 0;
     SINON
          CREERNOEUD(P);
          AFF_INFO(P,temp);
          AFF_FD(P,NIL);
          AFF_FG(P,NIL);
          id := id + 1;
          N := P;

          Inserer := 0;
     FSI
FIN

ACTION Creer_Arbre(R,n)
SOIENT
      R,P DES ARB DE (ENTIER,ENTIER,ENTIER);
      n,val_alea,col_alea,trouv,id,i DES ENTIER;
      temp UNE STRUCTURE (ENTIER,ENTIER,ENTIER);
DEBUT
    id := 1;

    SI n > 0:
       CREERNOEUD(R);
       AFF_FD(R,NIL);
       AFF_FG(R,NIL);
       AFF_STRUCT(temp,1,0);
       AFF_STRUCT(temp,2,0);
       AFF_STRUCT(temp,3,0);
       AFF_INFO(R,temp);

       POUR i:=0,n
            val_alea := ALEANOMBRE(1000);
            col_alea := ALEANOMBRE(2);
            SI col_alea = 0:
                P := FG(R);
                trouv := Inserer(P,val_alea,col_alea,id);
                TQ trouv = 1:
                   val_alea := ALEANOMBRE(1000);
                   trouv := Inserer(P,val_alea,col_alea,id);
                FTQ;
                Si FG(R) = NIL:
                    AFF_FG(R,P);
                FSI;
            SINON
                P := FD(R);
                trouv := Inserer(P,val_alea,col_alea,id);
                TQ trouv = 1:
                   val_alea := ALEANOMBRE(1000);
                   trouv := Inserer(P,val_alea,col_alea,id);
                FTQ;
                SI FD(R) = NIL:
                    AFF_FD(R,P);
                FSI;
            FSI
        FPOUR
    SINON
        R := NIL;
    FSI;
FIN

ACTION PreOrdre(R)
SOIENT
      R UN ARB DE (ENTIER,ENTIER,ENTIER);
DEBUT
     SI R <> NIL:
        ECRIRE(STRUCT(INFO(R),1),STRUCT(INFO(R),2));
        SI FG(R) <> NIL:
           APPEL PreOrdre(FG(R));
        FSI;
        SI FD(R) <> NIL:
           APPEL PreOrdre(FD(R));
        FSI
     FSI
FIN

