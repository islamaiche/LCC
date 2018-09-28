#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/************************LES STRUCTURE DEMANDER***************/

typedef struct pskis /*paires de skis*/
{
	int taille;
	struct loc *reserve;
	struct pskis  *skisuiv;
}pskis;

typedef struct loc{
	int deb;
	int fin;
	int ind;
	struct loc *ressuiv;
}loc;

typedef struct info{
	char nom[30];
	char adresse[30];
	int psk;
}info;

typedef struct TAB{
    info skieur[100];
    int  nsk;
}TAB;

TAB ski;

/*************************************************************/

/***********************LE MODELE DES "LLC" ******************/

void allouer(pskis **nouveau){*nouveau=(pskis*)malloc(sizeof(pskis));(*nouveau)->reserve=NULL;}

void allouer2(loc **nouveau){*nouveau=(loc*)malloc(sizeof(loc));}

void aff_adr (pskis *p,pskis *q){p->skisuiv=q;}

void aff_adr2(loc   *p,loc   *q){p->ressuiv=q;}

void aff_adr3(pskis *p,loc   *q){p->reserve=q;}

void aff_tai(pskis *p,int tai){p->taille=tai;}

void aff_deb(loc *p,int deb){p->deb=deb;}

void aff_fin(loc *p,int fin){p->fin=fin;}

void aff_ind(loc *p,int ind){p->ind=ind;}

pskis *suivant(pskis *p){return p->skisuiv;}

loc *suivant2(loc *p){return p->ressuiv;}

int taille(pskis *p){return p->taille;}

int debut(loc *p){return p->deb;}

int fini(loc *p){return p->fin;}

int indice(loc *p){return p->ind;}

loc *sliste(pskis *p){return p->reserve;}

void liberer(pskis**ancien){free(*ancien);*ancien=NULL;}

void liberer2(loc **ancien){free(*ancien);*ancien=NULL;}

/**************************************************************/

/***********************LES PROGRAME DE CREATION **************/

pskis *creation(){
    pskis *tete,*p,*q;int i,a,b;
    a=100;
    b=210;
    allouer(&p); aff_tai(p,alea(a,b)); tete=p;
    for(i=1;i<50;i++)
    {
        allouer(&q);
        aff_tai(q,alea(a,b));
        aff_adr(p,q);
        p=q;
    }
    aff_adr(p,NULL);
    return tete;
}

void crea_sliste(TAB *ski,pskis **p){
    int i,b,rese,deb,ind=0;
    pskis *q;
    loc *sl;
    allouer(&q);
    q=(*p);
    while(ind<ski->nsk){
        rese=0;
        b=alea_s(1,50);
        while(rese==0){
            deb=alea_s(1,alea_s(1,140));
            rese=location(&q,deb,deb+10,ind);
            if(rese==1) ski->skieur[ind].psk++;
            if (rand()%3==1)ind++;
        }
     q=suivant(q);
    }
}

int alea(int a,int b){
    int tai=(rand()%(b-a)+a);
    while(tai %5 !=0)
    {
        tai=rand()%(b-a)+a;
    }
    return tai;
}

int alea_s(int a,int b){
    return rand()%(b-a)+a;
}

void perso(TAB *ski){
    strcpy(ski->skieur[0].nom,"HAMMACHE");
    strcpy(ski->skieur[0].adresse,"TIZI OUZOU");
    strcpy(ski->skieur[1].nom,"DOUAIDI");
    strcpy(ski->skieur[1].adresse,"CONSTANTINE");
    strcpy(ski->skieur[2].nom,"TCHOULAK");
    strcpy(ski->skieur[2].adresse,"ANNABA");
    strcpy(ski->skieur[3].nom,"ATTALA");
    strcpy(ski->skieur[3].adresse,"BOUIRA");
    strcpy(ski->skieur[4].nom,"FIRAS");
    strcpy(ski->skieur[4].adresse,"ALGER");
    strcpy(ski->skieur[5].nom,"MADDI");
    strcpy(ski->skieur[5].adresse,"BLIDA");
    strcpy(ski->skieur[6].nom,"CHIBBAH");
    strcpy(ski->skieur[6].adresse,"ORAN");
    ski->nsk=7;
}

void afficher_tai(pskis *p){
    int i=0;
    printf("\n\t\t\t\t\tIL Y'A %d PAIRES DE SKIS\n ",nbskis(p));
    while (p!= NULL)
    {
        printf(" ''%d''  CETTE PAIRES EST LOUER :%d\t JOURS\t       |",taille(p),nbjloc(p));
        p=suivant(p);
        i++;
        if(i%2==0){printf("\n");}

    }
}

void tri_liste(pskis *p){
    int cpt=1;
    pskis *q;
    allouer(&q);
    q=p;
    while (cpt !=0)
    {
        cpt=0;
        do
        {
            if (taille(q) > taille(suivant(q)))
            {
                permute_tai(q,suivant(q));cpt++;
            }
            q=suivant(q);
        }
        while (suivant(q) != NULL );
        q=p;
    }
}

void permute_tai(pskis *p,pskis *q){
    int c;
    c=taille(q);
    aff_tai(q,taille(p));
    aff_tai(p,c);
}

loc *tri_sl(loc *q,int deb){
    loc *p,*a;
    allouer2(&p);
    allouer2(&a);
    p=q;
    a=suivant2(p);
    while(a!=NULL && fini(a)<deb)
        {
            p=suivant2(p);
            if(p!=NULL) a=suivant2(p);
            else a=NULL;
        }
    return p;
}

void crea_per(TAB *ski){
    char c,nom[30];int cpt=0,i=0;
    FILE *file = fopen("text.txt","r");
    while (c!= EOF){
        cpt=0;
        c=fgetc(file);
        if(c!= EOF && c!='\n'){
            while (c!=47){
                nom[cpt]=c;
                c=fgetc(file);
                cpt++;
            }
            nom[cpt]=NULL;
            strcpy(ski->skieur[i].nom,nom);
            cpt=0;
            c=fgetc(file);
            while (c!=47){
                nom[cpt]=c;
                c=fgetc(file);
                cpt++;
            }
            nom[cpt]=NULL;
            strcpy(ski->skieur[i].adresse,nom);
            cpt=0;
            c=fgetc(file);
            while (c!=47){
                nom[cpt]=c;
                c=fgetc(file);
                cpt++;
            }
            nom[cpt]=NULL;
            ski->skieur[i].psk=atoi(nom);
            i++;
        }
    }ski->nsk=i;
    fclose(file);
}

void sauv_per(TAB ski){
    int i;
    FILE *file = fopen("text.txt","w");
    for(i=0;i<ski.nsk;i++){
        fprintf(file,ski.skieur[i].nom);
        fprintf(file,"/");
        fprintf(file,ski.skieur[i].adresse);
        fprintf(file,"/");
        fprintf(file,"%d",ski.skieur[i].psk);
        fprintf(file,"/\n");
    }
    fclose(file);
}

void crea_pskis(pskis **tete){
    pskis *p,*q;
    loc *tsl,*sl,*ssl;
    char c,inf[10];
    int cpt,i=0,s=0;
    FILE *file = fopen("pskis.txt","r");
    fgetc(file);
    while(c!=EOF){
        c=fgetc(file);
        allouer(&p);
        cpt=0;
        while(c!='/' && c!='.'){
            inf[cpt]=c;
            c=fgetc(file);
            cpt++;
        }
        inf[cpt]=NULL;
        aff_tai(p,atoi(inf));
        if(i==0){
            (*tete)=p;
            q=p;
        }else{
            aff_adr(q,p);
            q=p;
        }
        if(c=='.'){
                allouer2(&sl);
                for(i=0;i<3;i++){
                    cpt=0;
                    c=fgetc(file);
                    while(c!='/' && c!='\n'){
                        inf[cpt]=c;
                        c=getc(file);
                        cpt++;
                    }
                    inf[cpt]=NULL;
                    if(i==0){aff_deb(sl,atoi(inf));}
                    if(i==1){aff_fin(sl,atoi(inf));}
                    if(i==2){aff_ind(sl,atoi(inf));}
                }
                if(s==0){
                        tsl=sl;
                        ssl=sl;
                        s=1;
                    }else{
                        aff_adr2(ssl,sl);
                        ssl=sl;
                    }
            aff_adr2(ssl,NULL);
            aff_adr3(q,tsl);
            s=0;
        }else c=fgetc(file);
    }
    aff_adr(q,NULL);
    fclose(file);

}

void sauv_pskis(pskis *p){
    FILE *file = fopen("pskis.txt","w");
    loc *sl;
    while(p!=NULL){
        fprintf(file,"\n%d",p->taille);
        sl=p->reserve;
        if (sl!=NULL) {fprintf(file,".");}
        else {fprintf(file,"/");}
        while(sl!=NULL){
            fprintf(file,"%d/%d/%d",sl->deb,sl->fin,sl->ind);
            sl=sl->ressuiv;
        }
        p=p->skisuiv;
    }
    fclose(file);
}

void afficher_per(TAB ski,pskis *p){
    int i;
    printf("\n      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,194,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,194,196,196,196,196,196,196,196,191);
    printf("      %c NOM             \t%cADRESSE        \t%cPSK    %c\n",179,179,179,179);
    for(i=0;i<ski.nsk;i++)
    {

        printf("      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,197,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,197,196,196,196,196,196,196,196,180);

        printf("      %c %s   \t\t%c%s   \t\t%c%d\t%c\n",179,ski.skieur[i].nom,179,ski.skieur[i].adresse,179,ski.skieur[i].psk,179);
    }
    printf("      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,193,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,193,196,196,196,196,196,196,196,217);

}

void info_per(pskis *p,int ind){
    pskis *prem;
    loc *a;
    allouer(&prem);
    allouer2(&a);
    prem=p;
    while (prem!=NULL){
        a=sliste(prem);
        while(a!=NULL){
            if (indice(a)==ind){
                printf("LA TAILLE %d\t   |  DEBUT DE LA LOCATION %d\t  |  FIN DE LA LOCATION %d\t\n",taille(prem),debut(a),fini(a));
            }
            a=suivant2(a);
        }
    prem=suivant(prem);
    }
}

void all_rserv(pskis *p,TAB ski){
    int ind=0;
    while(ind<ski.nsk){
        printf("%s\n",ski.skieur[ind].nom);
        info_per(p,ind);
        ind++;
    }
}

void supp(pskis **p,int ind){
    loc *q,*b;
    pskis *a;
    allouer(&a);
    allouer2(&b);
    allouer2(&q);
    a=(*p);
    int cpt=0;
    while (a!=NULL){
        q=sliste(a);
        while(q!=NULL){
            if(indice(q)==ind){
                if(suivant2(q)!=NULL){
                    aff_adr3(a,suivant2(q));
                }else {aff_adr3(a,NULL);}
            }
            if(q!=NULL) b=q;
            if(indice(b)==ind){
                if(suivant2(b)!=NULL){
                    aff_adr2(q,suivant2(b));
                }else aff_adr2(q,NULL);

            }
            if(q!=NULL) q=suivant2(q);
        }
    a=suivant(a);
    }
}

/**************************************************************/

/***********************LES MODULES DEMANDER*******************/

int nbskis(pskis *p)
{
    int cpt=0;
    while(p!=NULL){
        cpt++;
        p=suivant(p);
    }
    return cpt;
}

int nbjloc(pskis *p)
{
    loc *q;
    int cpt=0;
    q=sliste(p);
    while(q!=NULL){
        cpt=cpt+fini(q)-debut(q);
        q=suivant2(q);
    }
    return cpt;
}

pskis *skit(pskis *p,int tai)
{
    int trouv=0;
    while(p!=NULL && trouv==0)
    {
        if (taille(p)==tai){trouv=1;}
        else p=suivant(p);
    }
    return p;
}

int cherchskieur(TAB ski,char nom[30])
{
    int trouv=0,ind=0,result;
    while(trouv==0 && ind<ski.nsk)
    {
        result=strcmp(ski.skieur[ind].nom,nom);
        if(result==0){trouv=1;}
        else {ind++;}
    }
    if(ind==ski.nsk){ind=-1;}/**si le nom donner n existe pas*/
    return ind;
}

void insertete(int deb,int fin,int ind,loc *q)
{
    aff_deb(q,deb);
    aff_fin(q,fin);
    aff_ind(q,ind);
    aff_adr2(q,NULL);
}

/**********   *********  *******  ******   RANII HBEST HNA   **********  **********    */

int location(pskis **p,int deb,int fin,int ind)
{
    int reserv=1;
    loc *permloc,*q,*b;
    allouer2(&permloc);
    if(sliste(*p)==NULL)
    {
        insertete(deb,fin,ind,permloc);
        aff_adr3(*p,permloc);
    }
    else
    {
        permloc=sliste(*p);
        allouer2(&q);
        allouer2(&b);
        q=permloc;
        if (debut(q)>fin){/*************************************************/
            loc *a;
            allouer2(&a);
            insertete(deb,fin,ind,a);
            aff_adr2(a,q);
            (*p)->reserve=a;
        }
        else if(q->fin<deb){
            if(q->ressuiv==NULL){
                allouer2(&q->ressuiv);
                insertete(deb,fin,ind,q->ressuiv);
                (*p)->reserve=permloc;
            }else{
                q=tri_sl(q,deb);
                if(q->fin<deb){
                    if(q->ressuiv==NULL){
                        allouer2(&q->ressuiv);
                        insertete(deb,fin,ind,q->ressuiv);
                        (*p)->reserve=permloc;
                    }else{
                        b=q->ressuiv;
                        if(b->deb>fin){
                            loc *a;
                            allouer2(&a);
                            insertete(deb,fin,ind,a);
                            a->ressuiv=b;
                            q->ressuiv=a;
                            (*p)->reserve=permloc;
                        }else reserv=0;
                    }
                }else reserv=0;
            }
        }else reserv=0;
    }
    return reserv;
}

int reservation(TAB *ski,pskis **p,int ind,int de,int fi,int tai)
{
    int loca=0;
    pskis *prem;prem=NULL;//c est la premiere celule qui a la taille demander
    allouer(&prem);
    prem=skit(*p,tai);
    if(location(&prem,de,fi,ind)==1){ski->skieur[ind].psk++;return 1;}
    else
    {   if(prem->skisuiv->taille!=tai){return 0;}
        else
        {
            while(prem->skisuiv->taille==tai && loca==0){prem=prem->skisuiv;loca=location(&prem,de,fi,ind);}
            if(loca==1){ski->skieur[ind].psk++;}
            return loca;
        }
    }
}

void reservations(TAB *ski,pskis **p)
{
    typedef struct dft{
        int de;
        int fi;
        int t;
    }dft;

    typedef struct vec{
        dft res[100];
        int nr;
    }vec;

    vec vect;
    int ind=-1,i,n,r;
    char nom[30],adresse[30];
    while(ind==-1)
    {
        printf("\nENTRER LE NOM DE LA PERSSONNE QUI VEUT RESERVER : ");
        scanf("%s",&nom);
        ind=cherchskieur(*ski,nom);
        if(ind == -1)
        {
            printf("\nVOULEZ VOUS AJOUTER ' %s ' A LA LISTE DES RESRVATION : ",nom);
            printf("\nSI LA REPONSE EST 'OUI' ENTRER '1' //SINON '0' \nVOTRE REPONSE : ");
            scanf("%d",&r);
            if(r==1)
            {
                strcpy(ski->skieur[ski->nsk].nom,nom);
                printf("\nENTRER L' ADRESSE DE LA PERSSONNE QUI VOUS VOULEZ AJOUTEZ : ");
                scanf("%s",ski->skieur[ski->nsk].adresse);
                ind=ski->nsk;
                ski->nsk++;
            }
        }
    }
    printf("COMBIEN DE PAIRES DE SKIS DESIRE %s LOUER : ",nom);
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("\nLA %d PAIRE\n",i+1);
        vect.res[i].de=1;
        vect.res[i].fi=0;
        while(vect.res[i].de>vect.res[i].fi || vect.res[i].fi>151 || vect.res[i].de<1)
        {
            printf("ENTRER LE PREMIERE JOUR DE LA RESERVATION : ");
            scanf("%d",&vect.res[i].de);
            printf("ENTRER LE DERNIERE JOUR DE LA RESERVATION : ");
            scanf("%d",&vect.res[i].fi);
            if(vect.res[i].de>vect.res[i].fi){printf("\n *****************ERREUR *******************\nIMPOSSIBLE QUE LA DATE DU DEBUT SOIT APRES LA DATE DE LA FIN DE LA RESERVATION \n");}
            if(vect.res[i].de<1 || vect.res[i].fi>151){printf("\n *****************ERREUR *******************\nLa saison commence le 1er décembre (jour n° 1) et se termine le 30 avril (jour n° 151).  \n");}
        }
        pskis *prem;prem=NULL;//c est la premiere celule qui a la taille demander
        while(prem==NULL)
        {
            printf("ENTRER LA TAILLE A RESERVER : ");
            scanf("%d",&vect.res[i].t);
            allouer(&prem);
            prem=skit(*p,vect.res[i].t);
            if(prem==NULL){printf("\n*****************ERREUR *******************\n\nLA TAILLE DONNER N' EXISTE PAS \n\n");}
        }

    }
    vect.nr=n;
    for(i=0;i<n;i++)
    {
        if (reservation(ski,p,ind,vect.res[i].de,vect.res[i].fi,vect.res[i].t)==1){printf("\nLA %d RESERVATION A ETE BIEN EFECTUE\n",i+1);}
        else printf("\nLA %d RESERVATION N ' A PAS ETE BIEN EFECTUE\nPARCEQUE LA PAIRE DE SKI DE TAILLE %d EST DEJA LOUER",i+1,vect.res[i].t);
    }
}

void annuleres(TAB *ski,pskis **p)
{
    allouer(*p);
    char nom[30];
    int ind=-1,i;
    while(ind==-1){
        printf("\nENTRER LE NOM DE LA PERSONNE QUI VEUX ANNULER : ");
        scanf("%s",nom);
        ind=cherchskieur(*ski,nom);
        if(ind!=-1){
            supp(p,ind);
            if(ski->nsk>ind+1){
                for(i=ind;i<ski->nsk;i++){
                    strcpy(ski->skieur[i].nom,ski->skieur[i+1].nom);
                    strcpy(ski->skieur[i].adresse,ski->skieur[i+1].adresse);
                    ski->skieur[i].psk=ski->skieur[i+1].psk;
                }
            }
            ski->nsk--;
        }
    }
}

/****************************************************************/

/***************************LES MIDULE DE L'INTERFACE************/

void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void bien(){
Color(3,16);
printf("\n");
printf(" ****************************************************************************************************************************** \n");Sleep(100);
printf(" *         ");
Color(7,16);
printf("     _                                                   ");
Color(3,16);
printf("                                                          *\n");Sleep(100);
printf(" *         ");
Color(7,16);
printf("    |_|    ");
Color(3,16);
printf("                                                                                                        *\n");Sleep(100);
printf(" *   ");
Color(15,16);
printf("  ___  ___ _");
Color(3,16);
printf("                                                                                                             *\n");Sleep(100);
printf(" *  ");
Color(15,16);
printf("  / _ \\/ __| |  Ecole Nationale");
Color(3,16);
printf("                                                                                           *\n");Sleep(100);
printf(" * ");
Color(15,16);
printf("  |  __/\\__ \\ |  Superieure                        ");
Color(3,16);
printf("                                                                        *\n");Sleep(100);
printf(" *  ");
Color(15,16);
printf("  \\___||___/_|  d'Informatique                                     ");
Color(3,16);
printf("                                                       *\n");Sleep(100);
printf(" *                                     _                                                                                      *\n");Sleep(100);
printf(" *            ");
Color(15,16);
printf("                  ____ ");
Color(3,16);
printf(" |_|                                                                                     *\n");Sleep(100);
printf(" * ");
Color(15,16);
printf("                            |  _ \\  _   ___   _  __    _   _   ___   _  __   _   _   ___  ");
Color(3,16);
printf("                                 *\n");Sleep(100);
printf(" * ");
Color(15,16);
printf("                            |  __/ | | / _ \\ | |/  \\  | | | | / _ \\ | |/  \\ | |_| | / _ \\   ");
Color(3,16);
printf("                               *\n");Sleep(100);
printf(" * ");
Color(15,16);
printf("                            |  _ \\ | ||  __/ |  _  |   \\\\_// |  __/ |  _  | |     ||  __/  ");
Color(3,16);
printf("                                *\n");Sleep(100);
printf(" * ");
Color(15,16);
printf("                            |____/ |_| \\___| |_| |_|    \\_/   \\___| |_| |_| |_|\\__/ \\___|                    ");
Color(3,16);
printf("              *\n");Sleep(100);
printf(" *                                                                                                                            *\n");Sleep(100);
printf(" *                                                                    Sur La Location ski a Chrea                             *\n");Sleep(100);
printf(" *                                                                                                                            *\n");Sleep(50);
printf(" *                                                                                                                            *\n");Sleep(50);
printf(" *                                                                                                                            *\n");Sleep(50);
printf(" *                                                                                                                            *\n");Sleep(50);
printf(" *                                                                                                                            *\n");Sleep(50);
printf(" *                                                                                                                            *\n");Sleep(50);
printf(" *                                                                                                                            *\n");Sleep(50);
printf(" *                                                                                                                            *\n");Sleep(50);
printf(" *                                                                                                                            *\n");Sleep(50);
printf(" *                                                                                                                            *\n");Sleep(50);
printf(" *                                                                                                                            *\n");Sleep(50);
printf(" *                                                                                                                            *\n");Sleep(50);
printf(" *                                                                                                                            *\n");Sleep(50);
printf(" *                                                                                                                            *\n");Sleep(50);
printf(" *                                                                                                                            *\n");Sleep(50);
printf(" *                                                                                                                            *\n");Sleep(50);
printf(" *                                                                                                                            *\n");Sleep(50);
printf(" *                                                                                                                            *\n");Sleep(50);
printf(" *                                                                                                                            *\n");Sleep(50);
printf(" *                                                                                                                            *\n");Sleep(50);
printf(" *                                                                                                                            *\n");Sleep(50);
printf(" *                                                                                                                            *\n");Sleep(50);
printf(" *                                                                                                                            *\n");Sleep(50);
printf(" *                                                                                                                        TP1 *\n");Sleep(100);
printf(" *");
Color(15,16);
printf("                                          APPUYEZ SUR LA TOUCHE ENTREE POUR COMMENCER");
Color(3,16);
printf("                                       *\n");Sleep(100);
printf(" *                                                                                                                            *\n");Sleep(100);
printf(" ******************************************************************************************************************************\n");Sleep(100);
Color(15,16);
getchar() ;
}

void intro(){
Color(3,16);
printf("\n");
printf(" ****************************************************************************************************************************** \n");
printf(" *           ");
Color(7,16);
printf("   _                                                   ");
Color(3,16);
printf("                                                          *\n");
printf(" *           ");
Color(7,16);
printf("  |_|    ");
Color(3,16);
printf("                                                                                                        *\n");
printf(" *   ");
Color(15,16);
printf("  ___  ___ _");
Color(3,16);
printf("                                                                                                             *\n");
printf(" *  ");
Color(15,16);
printf("  / _ \\/ __| |  Ecole Nationale");
Color(3,16);
printf("                                                                                           *\n");
printf(" * ");
Color(15,16);
printf("  |  __/\\__ \\ |  Superieure                        ");
Color(3,16);
printf("                                                                        *\n");
printf(" *  ");
Color(15,16);
printf("  \\___||___/_|  d'Informatique                                     ");
Color(3,16);
printf("                                                       *\n");
printf(" *                                                                                                                            *\n");
printf(" *                  ");
Color(15,16);
printf("Cycle Preparatoire Integre (CPI) - ALSDD");
Color(3,16);
printf("                                                                  *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                        _________     _____              __                                                 *\n");
printf(" *                                       |___   ___|   |  __ \\            /  |                                                *\n");
printf(" *                                           | |       | |  \\ \\          /_  |                                                *\n");
printf(" *                                           | |       | |__/ /    ____    | |                                                *\n");
printf(" *                                           | |       |  ___/    |____|   | |                                                *\n");
printf(" *                                           | |       | |                _| |_                                               *\n");
printf(" *                                           |_|       |_|               |_____|                                              *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *  ");
Color(15,16);
printf("Theme : Location de skis                                           ");
Color(3,16);
printf("                                                       *\n");
printf(" *                                                                                                                            *\n");
printf(" *  ");
Color(15,16);
printf("Programme : Utilisation et Manipulation des LLC                    ");
Color(3,16);
printf("                                                       *\n");
printf(" *                                                                                                                            *\n");
printf(" *  ");
Color(15,16);
printf("Realise par : Khris Youcef (Groupe 04) - Aiche Islam (Groupe 12)                   ");
Color(3,16);
printf("                                       *\n");
printf(" *                                                                                                                            *\n");
printf(" *  ");
Color(15,16);
printf("Encadre par : Dr. Boulekradech                  ");
Color(3,16);
printf("                                                                          *\n");
printf(" *                                                                                                   ");
Color(15,16);
printf("Version N-1 - 09/04/2017");
Color(3,16);
printf(" *\n");
printf(" *                                                                                                                            *\n");
printf(" *               ");
Color(15,16);
printf("                          APPUYEZ SUR LA TOUCHE ENTREE POUR VOIR LE MENU");
Color(3,16);
printf("                                     *\n");
printf(" ******************************************************************************************************************************\n");
Color(15,16);
getchar() ;
}

void menu_aff(){
Color(3,16);
printf("\n");
printf(" ****************************************************************************************************************************** \n");
printf(" *           ");
Color(7,16);
printf("   _                                                   ");
Color(3,16);
printf("                                                          *\n");
printf(" *           ");
Color(7,16);
printf("  |_|    ");
Color(3,16);
printf("                                                                                                        *\n");
printf(" *   ");
Color(15,16);
printf("  ___  ___ _");
Color(3,16);
printf("                                                                                                             *\n");
printf(" *  ");
Color(15,16);
printf("  / _ \\/ __| |  Ecole Nationale");
Color(3,16);
printf("                                                                                           *\n");
printf(" * ");
Color(15,16);
printf("  |  __/\\__ \\ |  Superieure                        ");
Color(3,16);
printf("                                                                        *\n");
printf(" *  ");
Color(15,16);
printf("  \\___||___/_|  d'Informatique                                     ");
Color(3,16);
printf("                                                       *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                               ");
Color(15,16);
printf("_    _");
Color(3,16);
printf("                                                                       *\n");
printf(" * ");
Color(15,16);
printf("                                             | |  | |  ___   _  __   _   _        ");
Color(3,16);
printf("                                         *\n");
printf(" * ");
Color(15,16);
printf("                                             |  \\/  | / _ \\ | |/  \\ | |_| |         ");
Color(3,16);
printf("                                       *\n");
printf(" * ");
Color(15,16);
printf("                                             | |\\/| ||  __/ |  _  | |     |        ");
Color(3,16);
printf("                                        *\n");
printf(" * ");
Color(15,16);
printf("                                             |_|  |_| \\___| |_| |_| |_|\\__/                          ");
Color(3,16);
printf("                      *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                      1-");
Color(15,16);
printf(" Reserver Des Skis");
Color(3,16);
printf("                                                                                  *\n");
printf(" *                                                                                                                            *\n");
printf(" *                      2-");
Color(15,16);
printf(" Annuler Les reservations Des Skis");
Color(3,16);
printf("                                                                  *\n");
printf(" *                                                                                                                            *\n");
printf(" *                      3-");
Color(15,16);
printf(" Voir La Liste Des Reservation");
Color(3,16);
printf("                                                                      *\n");
printf(" *                                                                                                                            *\n");
printf(" *                      4-");
Color(15,16);
printf(" Voir Les Taille Disponnnible");
Color(3,16);
printf("                                                                       *\n");
printf(" *                                                                                                                            *\n");
printf(" *                      5-");
Color(15,16);
printf(" Voir Tout Les Reservaations");
Color(3,16);
printf("                                                                        *\n");
printf(" *                                                                                                                            *\n");
printf(" *                      6-");
Color(15,16);
printf(" Sortie");
Color(3,16);
printf("                                                                                             *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *                                                                                                                            *\n");
printf(" *");
Color(15,16);
printf("                                             APPUYEZ SUR LE NUMERO DE VOTRE CHOIX");
Color(3,16);
printf("                                           *\n");
printf(" *                                                                                                                            *\n");
printf(" ******************************************************************************************************************************\n");
Color(15,16);

}

void fin(){
   Color(3,16);
   printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
    printf("\t\t******************************                  **********      **        **************\n");  Sleep(100);
    printf("\t\t*******************************             ****************** ***        ***************\n"); Sleep(100);
    printf("\t\t   ***************************           *******       ***********           *******\n"); Sleep(100);
    printf("\t\t     *****                 *****         *****              *******            *****\n"); Sleep(100);
    printf("\t\t     *****                   ****        ****                 ******           *****\n"); Sleep(100);
    printf("\t\t    ******                    ***       *****                  *****          ******\n"); Sleep(100);
    printf("\t\t    ******          ***        **       ******                   ***          ******\n"); Sleep(100);
    printf("\t\t    ******          ***                  *******                  **          ******\n"); Sleep(100);
    printf("\t\t    ******         ****                  ***********                          ******\n"); Sleep(100);
    printf("\t\t    ******        *****                    ***************                    ******\n"); Sleep(100);
    printf("\t\t    *******************                      *****************                ******\n"); Sleep(100);
    printf("\t\t    *******************                         ******************            ******\n"); Sleep(100);
    printf("\t\t    ******        *****                               **************          ******\n"); Sleep(100);
    printf("\t\t    ******         ****                                     *********         ******\n"); Sleep(100);
    printf("\t\t    ******          ***                ****                    *******        ******\n"); Sleep(100);
    printf("\t\t    ******          ***         ***    ****                     ******        ******\n"); Sleep(100);
    printf("\t\t    ******                     ****     ****                     *****        ******\n"); Sleep(100);
    printf("\t\t    ******                    ****      ******                   *****        ******\n"); Sleep(100);
    printf("\t\t    *****                  ******       ******                 *****          *****\n");  Sleep(100);
    printf("\t\t    ******                *******        *********            ******          ******\n"); Sleep(100);
    printf("\t\t** *****************************         **** *********************       **************\n"); Sleep(100);
    printf("\t\t********************************         ***    ****************          ***************"); Sleep(100);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    Color(15,16);
    printf("                                           APPUYEZ SUR LA TOUCHE ENTREE POUR QUITTER");
}

/****************************************************************/

int main()
{
    int i,tai;int *p;
    pskis *mat;loc *permloc,*q;
    allouer(&mat);
    FILE *file=fopen("pskis.txt","r");
    FILE *fil=fopen("text.txt","r");
    if(file!=NULL){
        if(fil!=NULL){
            crea_per(&ski);
        }else{
            perso(&ski);
        }
        crea_pskis(&mat);
    }else{
        mat=creation();
        tri_liste(mat);
        if(fil!=NULL){
            crea_per(&ski);
        }else{
            perso(&ski);
        }
        crea_sliste(&ski,&mat);
    }
    fclose(file);
    fclose(fil);
    system(" mode con cols=128 lines=45");
    bien();
    intro();
    while(i!=6){
        menu_aff();
        scanf("%d",&i);
        system("cls");
        if(i==1){
            reservations(&ski,&mat);
            system("pause");
        }else if(i==2){
            annuleres(&ski,&mat);
            system("pause");
        }else if(i==3){
            afficher_per(ski,mat);
            system("pause");
        }else if(i==4){
            afficher_tai(mat);
            system("pause");
        }else if(i==5){
            all_rserv(mat,ski);
            system("pause");
        }
        sauv_per(ski);
        sauv_pskis(mat);
        printf("\n");
    }
    fin();
    return 0;
}
