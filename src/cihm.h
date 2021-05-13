#ifndef CIHM_H
#define CIHM_H

#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <ctime>
#include <stdlib.h>

#include "consoleJR.h"
#include "afficheTitre.h"

using namespace std;

class CIhm
{
    public:
        CIhm();
        void connect();
    private:
        void menu(short nbProp);
        void nouvMdp();
        void supprMdp();
        void modifMdp();
        void listeMdp();
        void param();
        short affichMdp();
        void selectMdp(short numMdp);
        string crypt(string chaine);
        string decrypt(string chaine);
        const string fichierDonnees = "data.txt";
        const string fichierTemp = "temp.txt";
        const string listeCarac = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-_@$%#*.";
        string mdpSelect[3];
};

#endif
