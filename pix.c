#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "pix.h"


void nahodnerazeni(int pexesopole[6][5])
{
    int zarazeno;
    srand(time(NULL));

    for(int i = 0; i < 15; i++)
    {
        zarazeno = 0;
        while (zarazeno != 2)
        {
            int radek = rand() % 6;
            int sloupec = rand() % 5;

            if (pexesopole[radek][sloupec] == -1)
            {
                pexesopole[radek][sloupec] = i;
                zarazeno++;
            }
        }
    }
}

void vypishernipole(char hernipole[6][5], int delkaradku, int delkasloupce)
{
    for (int radek = 0; radek < delkaradku; radek++)
    {
        if (radek == 0)
        {
            printf("   ");
            for (int i = 1; i < delkaradku; i++)printf("%d  ", i);
            printf("\n");
            //continue;
        }
        for (int sloupec = 0; sloupec < delkasloupce; sloupec++)
        {
            if (sloupec == 0)
            {
                printf("%d  ", radek+1);
            }
            printf("%c  ", hernipole[radek][sloupec]);
        }
        printf("\n");
    }
    printf("\n");
}

void vypishernipole2(int hernipole[6][5], int delkaradku, int delkasloupce)
{
    for (int radek = 0; radek < delkaradku; radek++)
    {
        if (radek == 0)
        {
            printf("   ");
            for (int i = 1; i < delkaradku; i++)printf("%d  ", i);
            printf("\n");
            //continue;
        }
        for (int sloupec = 0; sloupec < delkasloupce; sloupec++)
        {
            if (sloupec == 0)
            {
                printf("%d  ", radek+1);
            }
            printf("%d  ", hernipole[radek][sloupec]);
        }
        printf("\n");
    }
    printf("\n");
}

int kontrolasouradnic(int radek1, int radek2, int sloupec1, int sloupec2)
{
    if((radek1 == radek2) && (sloupec1 == sloupec2))
    {
        printf("\nZvolil jsi stejne souradnice\n");
        return 1;
    }
    else if ((radek1 > 5 || radek1 < 0) || (radek2 > 5 || radek2 < 0))
    {
        printf("\nRadek musi byt od 1 do 6\n");
        return 1;
    }
    else if ((sloupec1 > 4 || sloupec1 < 0) || (sloupec2 > 4 || sloupec2 < 0))
    {
        printf("\nSloupec musi byt od 1 do 5\n");
        return 1;
    }
    else return 0;
}

int kontrolaopakovani(int pexesopole[6][5], int radek1, int radek2, int sloupec1, int sloupec2)
{
    if ((pexesopole[radek1][sloupec1] == -1) || (pexesopole[radek2][sloupec2] == -1))
    {
        printf("\nPole uz bylo odhaleno a obsazeno hracem...\n\n");
        return 1;
    } else return 0;
}