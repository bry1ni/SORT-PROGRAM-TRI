#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NB_MAX  1000
#define NB_MIN  1
#define TRUE 1
#define FALSE 0
#define clear() printf("\033[H\033[J")


/* Functions needed */
void Gen_Tab(int T[],int N) /* Generate vector with random values */
{
    int i;
    for(i=0; i<N; i++)
    {
        T[i] = rand()%(NB_MAX-NB_MIN)+NB_MIN;
    }
}

void Aff_Tab(int T[], int N) /* Affichage du tableau */
{
    int i;
    for (i=0; i<N; i++)
    {
        printf("%d |",T[i]);
    }
    printf("\n");
}

typedef struct maillon maillon;
typedef maillon* Tptr;

typedef struct maillon
{
    int val;
    maillon* adr;
};

typedef maillon* TypePile;

void LibererP (Tptr p)
{
    free(p);
}

void Aff_val(Tptr p, int v)
{
    p->val = v;
}

void Aff_adr(Tptr p, Tptr q)
{
    p->adr = q;
}

int Valeur (Tptr p)
{
    return p->val;
}

Tptr Suivant (Tptr p)
{
    return p->adr;
}

Tptr Allouer(Tptr* p)
{
    *p = (Tptr)malloc(sizeof(maillon));
}

void CreerPile(TypePile* P)
{
    *P = NULL;
}

int PileVide(TypePile P)
{
    return (P == NULL);
}

void Empiler(TypePile* P, int val)
{
    Tptr Q;

    Allouer(&Q);
    Aff_val(Q, val);
    Aff_adr (Q, *P);
    *P = Q;
}

/* Les tris: */

/* Tri fusion - Merge Sort */
void fusion(int tableau[],int deb1,int fin1,int fin2)
 {
        
        int *table1;
        int deb2=fin1+1;
        int compt1=deb1;
        int compt2=deb2;
        int i;
        table1=malloc((fin1-deb1+1)*sizeof(int));

       
            for(i=deb1;i<=fin1;i++)
            {
            table1[i-deb1]=tableau[i];
            }
                        
            for(i=deb1;i<=fin2;i++)
            {        
                if (compt1==deb2)
                {
                break; 
                }
                else if (compt2==(fin2+1)) 
                {
                tableau[i]=table1[compt1-deb1]; 
                compt1++;
                }
                else if (table1[compt1-deb1]<tableau[compt2])
                {
                tableau[i]=table1[compt1-deb1];
                compt1++;
                }
                else
                {
                tableau[i]=tableau[compt2];
                compt2++;
                }
            }
        free(table1);
        
}
        

void tri_fusion_bis(int tableau[],int deb,int fin)
{
    if (deb!=fin)
    {
        int milieu=(fin+deb)/2;
        tri_fusion_bis(tableau,deb,milieu);
        tri_fusion_bis(tableau,milieu+1,fin);
        fusion(tableau,deb,milieu,fin);
    }
}

void tri_fusion(int tableau[],int longueur)
{
    double temps;
    clock_t start, stop;
    start = clock();
    if (longueur>0)
    {
        tri_fusion_bis(tableau,0,longueur-1);
    }
    stop = clock();
    temps=(double)(stop-start)/CLOCKS_PER_SEC;
    Aff_Tab(tableau,longueur);
    printf("Temps d'execution: %f \n", temps);
}

/* Tri a bulle */
void Tri_bulle (int T[], int N)
{
    int i,temp,x;
    int permut;
    double temps;
    clock_t start, stop;
    x=N;
    start = clock();
    do
    {
        x=x-1;
        permut=FALSE;

        for (i=0;i<x;i++)
        {
            if (T[i]>T[i+1])
            {
                temp=T[i];
                T[i]=T[i+1];
                T[i+1]=temp;
                permut=TRUE;
            }
        }
    }while (permut==TRUE);
    stop = clock();
    temps = (double)(stop-start)/CLOCKS_PER_SEC;
    Aff_Tab(T,N);
    printf("Temps d'execution: %f \n", temps);
}

/* Tri par insertion */
void Tri_insertion (int T[], int N)
{
      int i,j,temp,stop;
        double temps;
        clock_t start, stopclock;  
        start = clock(); 
      for (i=1;i<N;i++)
      {
          j=i-1;
          stop=FALSE;
          while ((j>=0)&&(stop==FALSE))
          {
            if (T[j+1]>T[j])
            {
                stop=TRUE;
            }
            else
            {
                temp=T[j];
                T[j]=T[j+1];
                T[j+1]=temp;
                j--;
            }

          }
      }
      stopclock = clock();
      temps = (double)(stopclock - start)/CLOCKS_PER_SEC;
      Aff_Tab(T,N);
      printf("Temps d'execution: %f \n", temps);
}

/* Tri par tas */
void swap(int *a, int *b) 
  {
    int temp = *a;
    *a = *b;
    *b = temp;
  }
  
void retablir_tas(int arr[], int n, int i) 
  {
    // Find largest among root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
  
    if (left < n && arr[left] > arr[largest])
      largest = left;
  
    if (right < n && arr[right] > arr[largest])
      largest = right;
  
    // Swap and continue heapifying if root is not largest
    if (largest != i) {
      swap(&arr[i], &arr[largest]);
      retablir_tas(arr, n, largest);
    }
  }
  
  // Main function to do heap sort
void faireTas(int arr[], int n) 
  {
    double temps;
    clock_t start, stop;
    start = clock();
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
      retablir_tas(arr, n, i);
  
    // Heap sort
    for (int i = n - 1; i >= 0; i--) {
      swap(&arr[0], &arr[i]);
  
      // Heapify root element to get highest element at root again
      retablir_tas(arr, i, 0);
    }
    stop =clock();
    temps = (double)(stop-start)/CLOCKS_PER_SEC;
    Aff_Tab(arr,n);
    printf("Temps d'execution: %f \n", temps);
  }

/* Tri rapide - Quick Sort */

void Depiler (TypePile* P, int* val)
{
    Tptr Sauv;

    if (!PileVide(*P))
    {
        Sauv = *P;
        *val = Valeur(*P);
        *P = Suivant (*P);
        LibererP(Sauv);
    }
    else
        printf("\nERREUR: Pile vide !\n");
}

void AffichPile (TypePile P)
{
    Tptr Q;

    if (!PileVide(P))
    {
        Q = P;
        printf(" -----\n");
        while (Q != NULL)
        {
            printf("| %3d |\n", Valeur(Q));
            Q = Suivant(Q);
        }
        printf(" -----\n");
    }
    else
        printf("\nPile vide !\n");
}

void permut (int* p_pivot , int* Bsup)
    {
        int tmp;
        tmp=*p_pivot;
        *p_pivot=*Bsup;
        *Bsup=tmp;
    }

void Tri_rapide (int T[], int N)
{
    double temps;
    clock_t start, stop;
    int Binf,Bsup,i,pivot,p_pivot;
    TypePile P;
    start = clock();
    CreerPile (&P);
    Empiler(&P,0);
    Empiler (&P,N-1);

    while (!PileVide(P))
    {
        Depiler (&P, &Bsup);
        Depiler (&P, &Binf);
        pivot=T[Bsup];
        p_pivot=Binf;
        for (i=Binf; i<=Bsup-1; i++)
        {
            if (T[i]<=pivot)
            {
                permut(&T[i],&T[p_pivot]);
                p_pivot++;
            }
        }
        permut(&T[p_pivot], &T[Bsup]);
        if (p_pivot+1 <Bsup)
        {
            Empiler(&P,p_pivot+1);
            Empiler(&P,Bsup);
        }
        if (p_pivot-1>Binf)
        {
            Empiler(&P,Binf);
            Empiler(&P,p_pivot-1);
        }
    }
    stop = clock();
    temps=(double)(stop-start)/CLOCKS_PER_SEC;
    Aff_Tab(T,N);
    printf("Temps d'execution: %f \n", temps);
}

/* Tri par selection */

void Tri_selection (int T[],int N)
{
    double temps;
    clock_t start, stop;
    start = clock();
    int i, j,temp ;

    for (i=0; i<N-1; i++)
      {
          for (j=i+1; j<N; j++)
          {
              if (T[i]>T[j])
              {
                 temp = T[i];
                 T[i] = T[j];
                 T[j] = temp;
              }
          }
      }

    stop = clock();
    temps=(double)(stop-start)/CLOCKS_PER_SEC;
    Aff_Tab(T,N);
    printf("Temps d'execution: %f \n", temps);
}

/* Tri par comptage */
int Comp_inf (int T[],int N,int val)
{
    int i,NbInf=0;

    for (i=0;i<N;i++)
    {
        if (T[i]<val)
        {
            NbInf++;
        }
    }
    return NbInf;

}

void Const_TC (int T[], int N, int TC[])
{
    int i;

    for (i=0;i<N;i++)
    {
        TC[i]= Comp_inf(T,N,T[i]);
    }
}

void Correct_TC (int TC[],int N)
{
    int i,j;

    for (i=0;i<N-1;i++)
    {
        for (j=i+1;i<N;j++)
        {
            if (TC[i]==TC[j])
            {
                TC[j]++;
            }
        }
    }
}

void Creer_TT (int T[],int TC [],int N, int TT[])
{
    int i;

    for (i=0;i<N;i++)
    {
        TT[TC[i]]=T[i];
    }
}

void Tri_comptage (int T[],int N,int TT[])
{
    int* TC;
    int i;
    double temps;
    clock_t start, stop;
    start = clock();

    TC=malloc(N*sizeof(int));

    Const_TC(T,N,TC);
    Correct_TC(TC,N);
    Creer_TT(T,TC,N,TT);
    stop = clock();
    temps=(double)(stop-start)/CLOCKS_PER_SEC;
    Aff_Tab(TT,N);
    printf("Temps d'execution: %f \n", temps);
}

/* Entete */
void entete ()
{
    printf("*****************************************************************\n");
    printf("************************PROGRAMME DE TRI*************************\n");
    printf("**************************SORT PROGRAM***************************\n");
    printf("*****************************************************************\n");
    printf("*****************************************************************\n\n");
}

/* main */
int main()
{
    clear();
    int N;
    int tri_choisie;
    entete();
    printf("Taille du tableau: ");
    scanf("%d", &N);
    int * T= (int*)malloc(N*sizeof(int));
    /*int * Tr= (int*)malloc(N*sizeof(int));*/
    int * TT= (int*)malloc(N*sizeof(int));
    Gen_Tab(T,N);
    printf(">>Tableau généré avec %d valeurs aléatoires: \n", N);
    Aff_Tab(T,N);
    printf("\n1/ Tri de Bulles.\n");
    printf("2/ Tri par selection. \n");
    printf("3/ Tri par insertion.\n");
    printf("4/ Tri rapide.\n");
    printf("5/ Tri comptage.\n");
    printf("6/ Tri fusion.\n");
    printf("7/ Tri par tas.\n");
    printf("Choose:");
    scanf("%d",&tri_choisie);
    clear();
    entete();

    switch (tri_choisie)
    {
    case 1:
        printf("1/ Tri de Bulles.\n");
        Tri_bulle(T,N);
        break;
    case 2:
        printf("2/ Tri par selection. \n");
        Tri_selection(T,N);
        break;
    case 3:
        printf("3/ Tri par insertion.\n");
        Tri_insertion(T,N);
        break;
    case 4:
        printf("4/ Tri rapide.\n");
        Tri_rapide(T,N);
        break;
    case 5:
        printf("5/ Tri comptage.\n");
        Tri_comptage(T,N,TT);
        break;
    case 6:
        printf("6/ Tri fusion.\n");
        tri_fusion(T,N);
        break;
    case 7:
        printf("7/ Tri par tas.\n");
        faireTas(T,N);
        break;
    }
    return 0;
}