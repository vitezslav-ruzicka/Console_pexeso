#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pix.h"

#define DELKA_RADKU 6
#define DELKA_SLOUPCE 5

char zasoba[15][15] = {"ElCamino", "Camaro", "ChevyVan", "Impala", "Monza",                             //Chevrolet
                       "E24 6", "E28 5", "E30 3", "E36 3", "E38 7",                                     //BMW
                       "Dodge 400", "Dodge Diplomat", "Dodge Charger", "Dodge Daytona", "Dodge Aries"}; //Dodge

struct hrac {
    char jmeno[15];
    int score;
};

int main()
{
    int postup = 0;
    struct hrac hrac1;
    struct hrac hrac2;
    char souradnice1[3];
    memset(souradnice1, '\0', 3);
    char souradnice2[3];
    memset(souradnice2, '\0', 3);

    //otevreni souboru pro zapis prubehu hry
    FILE *log = fopen("/home/vitek/Desktop/log.txt", "w");
    //jednoduche "odradkoveni"
    fprintf(log, "---------------------------------------------");

    //graficke pole
    char hernipole[DELKA_RADKU][DELKA_SLOUPCE];
    memset(hernipole, '*', sizeof(hernipole));
    //hadaci pole
    int pexesopole[DELKA_RADKU][DELKA_SLOUPCE];
    memset(pexesopole, -1, sizeof(pexesopole));
    //nahodne naplneni pexesopole
    nahodnerazeni(pexesopole);

    //predstaveni a ziskani jmeno
    printf("Pexeso pro 2 hrace!\nZadavejte 2 souradnice pro otoceni \"pexeso\" karticek\n");
    printf("prvni je radek, druhe cislo je sloupecek a druhe cislo je dalsi souradnice\nPriklad: 13 64\n\n");
    printf("Jmeno hrace c.1: ");
    scanf("%13s", &hrac1.jmeno);
    printf("\nJmeno hrace c.2: ");
    scanf("%13s", &hrac2.jmeno);
    printf("Hrac c.1 zacina\n");

    //hlavni herni loop
    for (int kolo = 0; postup != 15; kolo++)
    {
        //vypise herni pole
        vypishernipole(hernipole, DELKA_RADKU, DELKA_SLOUPCE);
        fprintf(log, "\nKolo %d",kolo);
        //kolo hrace1
        if (kolo %2 == 0)
        {
            int radek1;
            int radek2;
            int sloupec1;
            int sloupec2;
            do{
                printf("Hrac c.1: ");
                scanf("%2s", &souradnice1);
                scanf("%2s", &souradnice2);

                radek1 = souradnice1[0] - 49;
                radek2 = souradnice2[0] -49;
                sloupec1 = souradnice1[1] - 49;
                sloupec2 = souradnice2[1] - 49;
            }while (kontrolasouradnic(radek1, radek2, sloupec1, sloupec2) == 1);
            //kontrola znovu otoceni "karticek"
            if(kontrolaopakovani(pexesopole, radek1, radek2, sloupec1, sloupec2))
            {
                continue;
            }
            //nahrada cisel za string
            printf("%s\n%s\n\n", zasoba[pexesopole[radek1][sloupec1]],zasoba[pexesopole[radek2][sloupec2]]);
            //spravne uhodnuti pexeso "policek"
            if (pexesopole[radek1][sloupec1] == pexesopole[radek2][sloupec2])
            {
                printf("SHODA!!\n");
                fprintf(log, " -> Hrac1: %s SHODA! = ", hrac1.jmeno);
                fprintf(log, "%s na %d%d %d%d", zasoba[pexesopole[radek1][sloupec1]], radek1,sloupec1,radek2,sloupec2);
                pexesopole[radek1][sloupec1] = -1;
                pexesopole[radek2][sloupec2] = -1;
                hernipole[radek1][sloupec1] = 49;
                hernipole[radek2][sloupec2] = 49;
                hrac1.score++;
                postup++;
            }
        }
        //kolo hrace2
        else if (kolo %2 == 1)
        {
            int radek1;
            int radek2;
            int sloupec1;
            int sloupec2;
            do{
                printf("Hrac c.2: ");
                scanf("%2s", &souradnice1);
                scanf("%2s", &souradnice2);

                radek1 = souradnice1[0] - 49;
                radek2 = souradnice2[0] -49;
                sloupec1 = souradnice1[1] - 49;
                sloupec2 = souradnice2[1] - 49;
            }while (kontrolasouradnic(radek1, radek2, sloupec1, sloupec2) == 1);
            //kontrola znovu otoceni "karticek"
            if(kontrolaopakovani(pexesopole, radek1, radek2, sloupec1, sloupec2))
            {
                continue;
            }
            //nahrada cisel za string
            printf("%s\n%s\n\n", zasoba[pexesopole[radek1][sloupec1]],zasoba[pexesopole[radek2][sloupec2]]);
            //spravne uhodnitu pexeso "policek"
            if (pexesopole[radek1][sloupec1] == pexesopole[radek2][sloupec2])
            {
                printf("SHODA!!\n");
                fprintf(log, " -> Hrac2: %s SHODA! = ", hrac2.jmeno);
                fprintf(log, "%s na %d%d %d%d", zasoba[pexesopole[radek1][sloupec1]], radek1,sloupec1,radek2,sloupec2);
                pexesopole[radek1][sloupec1] = -1;
                pexesopole[radek2][sloupec2] = -1;
                hernipole[radek1][sloupec1] = 50;
                hernipole[radek2][sloupec2] = 50;
                hrac2.score++;
                postup++;
            }
        }
    }

    //vypsani viteze
    if (hrac1.score > hrac2.score)
    {
        printf("\n\nHrac 1: %s VYHRAL!!!!", hrac1.jmeno);
        printf("\nPrubeh hry naleznete v souboru log.txt");
        fprintf(log, "\n\nHrac 1: %s VYHRAL!!!!", hrac1.jmeno);


    } else {
        printf("\n\nHrac 2: %s VYHRAL!!!!", hrac2.jmeno);
        printf("\nPrubeh hry naleznete v souboru log.txt");
        fprintf(log, "\n\nHrac 2: %s VYHRAL!!!!", hrac2.jmeno);
    }
    fclose(log);
    //printf("Hello, World!\n");
    return 0;
}
