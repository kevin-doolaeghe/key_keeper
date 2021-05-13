// Novembre 2017 - Doolaeghe Kevin
// Procédures d'affichage et de saisie - Variations du cin & du cout


#ifndef AFFICHETITRE_H__
#define AFFICHETITRE_H__


//*********************************--Windows--*********************************

#ifdef _WIN32

#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>

using namespace std;

//-----------------------------------------

static void afficheTitre(string titre, short x, short y)
{
    COORD coord;
    coord.X = x - 1;
    coord.Y = y - 1;
    unsigned short i;

    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << (char)201;
    for(i = 0; i < 3; i++) cout << (char)205;
    for(i = 0; i < titre.size(); i++) cout << (char)205;
    for(i = 0; i < 3; i++) cout << (char)205;
    cout << (char)187;
    coord.Y++;
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << (char)186;
    for(i = 0; i < 3; i++) cout << " ";
    cout << titre;
    for(i = 0; i < 3; i++) cout << " ";
    cout << (char)186;
    coord.Y++;
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << (char)200;
    for(i = 0; i < 3; i++) cout << (char)205;
    for(i = 0; i < titre.size(); i++) cout << (char)205;
    for(i = 0; i < 3; i++) cout << (char)205;
    cout << (char)188;
}

//-----------------------------------------

static void afficheCentre(string titre, short longueurX, short y)
{
    COORD coord;
    coord.X = ((longueurX - titre.size() - 8) / 2) - 1;
    coord.Y = y - 1;
    unsigned short i;

    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << (char)201;
    for(i = 0; i < 3; i++) cout << (char)205;
    for(i = 0; i < titre.size(); i++) cout << (char)205;
    for(i = 0; i < 3; i++) cout << (char)205;
    cout << (char)187;
    coord.Y++;
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << (char)186;
    for(i = 0; i < 3; i++) cout << " ";
    cout << titre;
    for(i = 0; i < 3; i++) cout << " ";
    cout << (char)186;
    coord.Y++;
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << (char)200;
    for(i = 0; i < 3; i++) cout << (char)205;
    for(i = 0; i < titre.size(); i++) cout << (char)205;
    for(i = 0; i < 3; i++) cout << (char)205;
    cout << (char)188;
}

//-----------------------------------------

static void afficheEncadre(short longueur, short x, short y)
{
    COORD coord;
    coord.X = x - 1;
    coord.Y = y - 1;
    unsigned short i;

    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << (char)201;
    for(i = 0; i < longueur - 2; i++) cout << (char)205;
    cout << (char)187;
    coord.Y++;
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << (char)186;
    coord.X += longueur - 1;
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << (char)186;
    coord.X = x - 1;
    coord.Y++;
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << (char)200;
    for(i = 0; i < longueur - 2; i++) cout << (char)205;
    cout << (char)188;
}

//-----------------------------------------

static void supprEncadre(short longueur, short x, short y)
{
    COORD coord;
    coord.X = x - 1;
    coord.Y = y - 1;
    unsigned short i;

    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), coord);
    for(i = 0; i < longueur; i++) cout << " ";
    coord.Y++;
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << " ";
    coord.X += longueur - 1;
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << " ";
    coord.X = x - 1;
    coord.Y++;
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), coord);
    for(i = 0; i < longueur; i++) cout << " ";
}

//-----------------------------------------

static string cinLim(string chaine, unsigned short limite)
{
    char ch;

    do
    {
        color(12, 15);
        chaine.erase();
        ch = _getch();
        while(ch != 13)
        {
            if(ch == '\b'){
                if(chaine.size() > 0) //Vérifie si la chaine peut encore être réduite
                {
                    cout << "\b \b";
                    chaine.pop_back(); //Supprime le dernier caractère
                }
            }
            else if((chaine.size() > limite)) //Limite
            {
                cout << '\a';
            }
            else
            {
                chaine.push_back(ch); //Insertion du caractère
                cout << ch;
            }
            ch = _getch();
        }
        color(0, 15);
    } while(chaine.empty());
    return chaine;
}

//-----------------------------------------

static string cinMdp(string chaine, unsigned short limite)
{
    char ch;

    do
    {
        color(12, 15);
        chaine.erase();
        ch = _getch();
        while(ch != 13)
        {
            if(ch == '\b'){
                if(chaine.size() > 0) //Vérifie si la chaine peut encore être réduite
                {
                    cout << "\b \b";
                    chaine.pop_back(); //Supprime le dernier caractère
                }
            }
            else if((chaine.size() > limite)) //Limite
            {
                cout << '\a';
            }
            else
            {
                chaine.push_back(ch); //Insertion du caractère
                cout << "*";
            }
            ch = _getch();
        }
        color(0, 15);
    } while(chaine.empty());
    return chaine;
}

#endif
#endif
