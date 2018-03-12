#include <stdio.h>
#include <stdlib.h>
int nrLinii;
int nrColoane;
int matriceStareActuala [1000][1000]; // Ne vom folosi de aceasta matrice pt a retine celulele in starea p la pasul p
char reprezentare; // Spațiul simulării poate fi reprezentat fie ca un plan ('P'), fie ca un toroid ('T')
int nrEtape;
int matriceStareNoua[1000][1000]; // In matriceStareNoua vom simula o noua etapa
float maxPopulatie; // Gradul maxim de populare înregistrat pe parcursul simulării

float procentaj () //Functie ce determina cat la suta din nr total de celule reprezinta numarul celor vii
{
    int i,j,nrCelule=0;
    float populatie=0;
    for (i = 0; i <= nrLinii-1; i++)
    {
        for (j = 0; j <= nrColoane-1; j++)
        {
            if (matriceStareActuala[i][j] == 1)
            {
                nrCelule++;
            }
        }
    }
    populatie = (float)100 * nrCelule /(nrColoane * nrLinii);
    return populatie;

}

void citireDeLaTastatura()
{
    int x,y;

    printf ("Introduceti modul de reprezentare, dimensiunile hartii si nr de etape, apoi celulele in starea initiala: \n");
    scanf("%c", &reprezentare);
    scanf("%d %d %d", &nrLinii, &nrColoane, &nrEtape);




    for ( x = 0; x < nrLinii; x++)

        for (y = 0; y < nrColoane; y++)

            scanf ("%d", &matriceStareActuala[x][y] );



}
int gasesteNumarVecini(int matriceStareActuala[1000][1000], int posLinie, int posColoana) //Functia determina nr de celule vii din jurul unei celule
{
    int startLinie = 0;
    int startColoana = 0;
    int endLinie = 0;
    int endColoana = 0;
    int nr = 0;
    int i,j;
    //Vom afla pozitiile intre care se afla vecinii unei celule in cazul reprezentarii sub forma de plan
    if (reprezentare=='P' || (nrLinii<3 || nrColoane<3))
    {
        startLinie = (posLinie > 0) ? posLinie - 1 : 0;
        startColoana = (posColoana > 0) ? posColoana - 1 : 0;
        endLinie = (posLinie < nrLinii - 1) ? posLinie + 1 : posLinie;
        endColoana = (posColoana < nrColoane - 1) ? posColoana + 1 : posColoana;

    }
    else // Aflam pozitiile intre care se afla vecinii unei celule in cazul reprezentarii toroidale
    {
        startLinie = posLinie - 1;
        startColoana = posColoana - 1;
        endLinie = (posLinie <= nrLinii- 1) ? posLinie + 1 : 0;
        endColoana = (posColoana <= nrColoane - 1) ? posColoana + 1 : 0;
    }


    for (i = startLinie; i <= endLinie; i++)          //Verificam daca pozitiile calculate mai sus nu depasesc spatiul simularii,
                                                            // acest lucru fiind posibil in cazul reprezentarii toroidale
        for (j = startColoana; j <= endColoana; j++)
        {
            int indexLinie;
            int indexColoane;
            if (i < 0)
            {
                indexLinie = nrLinii + i;
            }
            else if (i == nrLinii )
            {
                indexLinie = 0;
            }
            else
            {
                indexLinie = i;
            }
            if (j < 0)
            {
                indexColoane = nrColoane + j;
            }
            else if (j == nrColoane)
            {
                indexColoane = 0;
            }
            else
            {
                indexColoane = j;
            }
            if (matriceStareActuala[indexLinie][indexColoane] != 0) //Dupa ce am identificat indicii de linie, respectiv coloana ai unei celule vecine
                                                                       //verificam daca aceasta este celula vie
            {
                nr++;
            }
        }


    if (matriceStareActuala[posLinie][posColoana] == 1)
    {
        nr--;
    }


    return nr;
}
int main()
{

    citireDeLaTastatura();

    int i,j,k;


    if (procentaj()>maxPopulatie) //Calculam gradul de populare inregistrat in starea initiala si il comparam cu variabila max ce retine gradul maxim de populare
           maxPopulatie=procentaj();
    for (k = 1; k <= nrEtape; k++) //Incepem evolutia ce are loc pe parcursul a k etape
    {

        for ( i = 0; i <= nrLinii - 1; i++)
            for (j = 0; j <= nrColoane - 1; j++)
            {
                int nrVecini = gasesteNumarVecini(matriceStareActuala, i, j); //In functie de nr de vecini, o celula poate sa supravietuiasca, sa moara,
                if (nrVecini < 2)                                             // sau sa prinda viata
                {
                    matriceStareNoua[i][j] = 0;
                }
                else if (nrVecini > 3)
                {
                    matriceStareNoua[i][j] = 0;
                }
                else if (nrVecini ==3)
                {
                    matriceStareNoua[i][j] = 1;
                }
                else if (nrVecini==2)
                {
                    matriceStareNoua[i][j] = matriceStareActuala[i][j];
                }
            }


        for ( i = 0; i <= nrLinii - 1; i++) //Dupa ce s-a simulat o etapa, matricea stareActuala va avea valorile obtinute in urma simularii

            for (j = 0; j <= nrColoane - 1; j++)

                matriceStareActuala[i][j] = matriceStareNoua[i][j];

        if (procentaj()>maxPopulatie)
            maxPopulatie=procentaj();
    }
    printf ("Rezultatul simularii este :\n");
    for (i=0; i<=nrLinii-1; i++)
    {
        for (j=0; j<=nrColoane-1; j++)
            printf ("%d   \b", matriceStareActuala[i][j]);
        printf("\n");
    }
    printf("Gradul maxim de populare este: ");
    printf ("%.3f %c", maxPopulatie,'%') ;
    return 0;
}


