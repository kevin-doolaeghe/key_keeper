#include "cihm.h"

//----------------------------------------------------------------------------------------------

//Constructeur

CIhm::CIhm()
{

}

//----------------------------------------------------------------------------------------------

//Connexion

void CIhm::connect()
{
    ifstream flux(fichierDonnees.c_str());
    string mdpFichier;

    color(0, 15); //system("color 0f");
    system("mode con cols=80 lines=25");

    getline(flux, mdpFichier);
    flux.close();

    //Connexion
    if(mdpFichier != "")
    {
        string mdp;
        unsigned short i = 3;
        unsigned short j;

        //Affichage
        color(12, 15);
        afficheCentre("Connexion", 80, 1);
        color(0, 15);
        gotoxy(32, 4);
        cout << "Doolaeghe Kevin";
        gotoxy(7, 7);
        cout << "Entrez votre mot de passe : ";

        do
        {
            gotoxy(15, 9);
            cout << "Il vous reste " << i << " tentatives";
            if(i == 1)
            {
                gotoxy(40, 9);
                cout << " ";
            }
            gotoxy(35, 7);

            //Saisie
            color(12, 15);
            mdp = cinMdp(mdp, 16);
            color(0, 15);

            mdp = crypt(mdp);
            gotoxy(35, 7);
            if(mdp != mdpFichier) for(j = 0; j < mdp.size(); j++) cout << " ";
            i--;
        } while(mdp != mdpFichier && i > 0);
        if(mdp == mdpFichier) menu(5);
    }

    //-----------------------------------------------

    //Inscription
    else
    {
        ofstream flux(fichierDonnees.c_str(), ios::app); //Ouvre le fichier (ios::app >> Editer != Ecraser)
        unsigned short i;
        short j, nbAlea;
        string mdp, verif;
        char methodeCryptage[71];
        methodeCryptage[70] = (char)0;
        short testCaracUtil[70];
        for(i = 0; i < 70; i++) testCaracUtil[i] = 0;

        do
        {
            clear();
            color(12, 15);
            afficheCentre("Inscription", 80, 1);
            color(0, 15);
            gotoxy(32, 4);
            cout << "Doolaeghe Kevin";
            gotoxy(7, 7);
            cout << "Entrez un mot de passe    : ";
            color(12, 15);
            mdp = cinMdp(mdp, 16);
            color(0, 15);
            gotoxy(7, 9);
            cout << "R" << (char)130 << "p" << (char)130 << "tez le mot de passe   : ";
            verif = cinMdp(verif, 16);
        } while(mdp != verif);

        //Création de la méthode de cryptage
        srand(time(0));
        for(i = 0; i < 70; i++)
        {
            nbAlea = rand() % 70; //Nombre aléatoire entre 0 et 69
            while(testCaracUtil[nbAlea] == 1)
            {
                nbAlea++;
                if(nbAlea == 70) nbAlea = 0;
            }
            methodeCryptage[i] = listeCarac[nbAlea];
            testCaracUtil[nbAlea] = 1;
        }

        //Cryptage
        for(i = 0; i < mdp.size(); i++)
        {
            for(j = 0; j < 70; j++)
            {
                if(mdp[i] == listeCarac[j])
                {
                    mdp[i] = methodeCryptage[j];
                    break;
                }
            }
        }

        //Edition fichier
        flux << mdp << endl << methodeCryptage << endl;
        flux.close();

        menu(5);
    }
}

//----------------------------------------------------------------------------------------------

//Menu

/*
    Algorithme de la méthode menu(short nbProp)
    Auteur : Doolaeghe Kevin
    Date : Novembre 2017

    Variables :
    selection, i = Entier 16 bits
    touche1, touche2 = Caractères

    Début
    Répéter
        selection <- 1
        Appel de la procédure clear()
        Appel de la procédure afficheCentre("Menu Principal", 80, 1)
        Appel de la procédure gotoxy(32, 4)
        Afficher "Doolaeghe  Kevin"
        Appel de la procédure gotoxy(10, 6)
        Afficher "Proposition 1"
        Appel de la procédure gotoxy(10, 8)
        Afficher "Proposition 2"
        ...
        Appel de la procédure gotoxy(10, nbProp * 2 + 6)
        Afficher "Quitter"
        Répéter
            Pour i allant de 6 à nbProp * 2 + 8
                Appel de la procédure gotoxy(7, i)
                Afficher "  "
            Appel de la procédure gotoxy(7, selection * 2 + 4)
            Afficher ">>"
            Appel de la procédure gotoxy(1, 1)
            touche2 <- 0
            touche1 <- Fonction saisie d'un touche
            Si (touche1 = -32)
                Alors   touche2 <- Fonction saisie d'une touche
            Si (touche2 = 72)
                Alors   Si (selection = 1)
                            Alors   selection <- nbProp + 1
                            Sinon   selection <- selection - 1
            Si (touche2 = 80)
                Alors   Si (selection = nbProp + 1)
                            Alors   selection <- 1
                            Sinon   selection <- selection + 1
        Jusqu'à (touche1 = 13)
        Si (selection = 1)
            Alors   Appel de la méthode fonction1()
        Si (selection = 2)
            Alors   Appel de la méthode fonction2()
        ...
    Jusqu'à (selection = nbProp + 1)
    Fin
*/

void CIhm::menu(short nbProp)
{
    //Initialisation
    char touche1, touche2;
    static short selection = 1;
    short i;
    do
    {
        //Affichage du titre
        clear();
        color(12, 15);
        afficheCentre("Menu Principal", 80, 1);
        color(0, 15);
        gotoxy(32, 4);
        cout << "Doolaeghe  Kevin";
        gotoxy(1, 1);

        //Affichage des propositions
        gotoxy(10, 6);
        cout << "Nouveau mot de passe";
        gotoxy(10, 8);
        cout << "Supprimer un mot de passe";
        gotoxy(10, 10);
        cout << "Modifier un mot de passe";
        gotoxy(10, 12);
        cout << "Liste des mots de passe";
        gotoxy(10, 14);
        cout << "Param\x8atres du compte";

        //Affichage de l'option pour quitter
        gotoxy(10, nbProp * 2 + 6);
        color(15, 12);
        cout << "Quitter";
        color(0, 15);

        do //Boucle de décalage du curseur selon le choix
        {
            //Effacage du curseur
            for(i = 6; i < nbProp * 2 + 8; i++)
            {
                gotoxy(7, i);
                cout << "  ";
            }
            //Affichage du curseur
            gotoxy(7, selection * 2 + 4);
            color(12, 15);
            cout << ">>";
            color(0, 15);
            gotoxy(1, 1);

            //Détection de la touche pressée
            touche2 = 0; //Initialisation
            touche1 = getch();
            if(touche1 == -32) touche2 = getch(); //Touches directionnelles = 2 touches pressées
            if(touche2 == 72) //Flèche du haut
            {
                if(selection == 1) selection = nbProp + 1;
                else selection -= 1;
            }
            if(touche2 == 80) //Flèche du bas
            {
                if(selection == nbProp + 1) selection = 1;
                else selection += 1;
            }
        } while(touche1 != 13); //Touche entrée

        //Lancement de la fonction adéquate
        switch(selection)
        {
            case 1:
                nouvMdp();
                break;
            case 2:
                supprMdp();
                break;
            case 3:
                modifMdp();
                break;
            case 4:
                listeMdp();
                break;
            case 5:
                param();
                break;
        }
    } while(selection != nbProp + 1); //Quitter
}

//----------------------------------------------------------------------------------------------

//Nouveau mot de passe

void CIhm::nouvMdp()
{
    ofstream flux(fichierDonnees.c_str(), ios::app); //Ouvre le fichier (ios::app >> Mode édition)
    string id, mdp, verif, desc;
    char touche1, touche2;
    short i, selection;
    do
    {
        do
        {
            //Initialisation
            selection = 1;
            id.erase();
            mdp.erase();
            verif.erase();
            desc.erase();
            touche1 = 0;

            //Départ
            clear();
            color(12, 15);
            afficheCentre("Nouveau mot de passe", 80, 1);
            color(0, 15);
            gotoxy(10, 5);
            cout << "Entrez votre identifiant     :";
            gotoxy(10, 7);
            cout << "Entrez votre mot de passe    :";
            gotoxy(10, 9);
            cout << "R" << (char)130 << "p" << (char)130 << "tez votre mot de passe   :";
            gotoxy(10, 11);
            cout << "Entrez une description       :";
            gotoxy(8, 15);
            cout << "Termin" << (char)130;

//----------------------------------

            do
            {
                gotoxy(45, selection * 2 + 3);
                do //Boucle de décalage du curseur selon le choix
                {
                    //Mise à jour du curseur
                    //Effacage du curseur
                    for(i = 5; i < 12; i++)
                    {
                        //Supprimer les curseurs
                        gotoxy(7, i);
                        cout << "  ";
                    }
                    //Supprimer l'encadré
                    gotoxy(4, 14);
                    for(i = 0; i < 15; i++) cout << " ";
                    gotoxy(4, 15);
                    cout << " ";
                    gotoxy(18, 15);
                    cout << " ";
                    gotoxy(4, 16);
                    for(i = 0; i < 15; i++) cout << " ";

                    //Affichage du curseur
                    if(selection == 5)
                    {
                        //Affichage encadré pour 5
                        afficheTitre("Termin\x82", 4, 14);
                        gotoxy(1, 1);
                    }
                    else
                    {
                        //Affichage du curseur pour 1; 2 et 3
                        gotoxy(7, selection * 2 + 3);
                        color(12, 15);
                        cout << ">>";
                        color(0, 15);
                        gotoxy(45, selection * 2 + 3);
                    }

                    //Détection de la touche pressée
                    touche2 = 0; //Initialisation
                    touche1 = getch();
                    if(touche1 == -32) touche2 = getch(); //Touches directionnelles = 2 touches pressées
                    if(touche2 == 72) //Flèche du haut
                    {
                        if(selection == 1) selection = 5;
                        else selection -= 1;
                    }
                    if(touche2 == 80) //Flèche du bas
                    {
                        if(selection == 5) selection = 1;
                        else selection += 1;
                    }
                    //Fin test touches
                } while(touche1 != 27 && touche1 != 13);

//----------------------------------

                //cin
                if(touche1 != 27 && selection != 5)
                {
                    //Affichage des encadrés
                    if(selection == 1) afficheEncadre(39, 41, selection * 2 + 2);
                    if(selection == 2 || selection == 3) afficheEncadre(25, 41, selection * 2 + 2);
                    if(selection == 4) afficheEncadre(29, 41, selection * 2 + 2);
                    gotoxy(45, selection * 2 + 3);

                    //Saisie
                    switch(selection)
                    {
                        case 1:
                            for(i = 0; i <= 30; i++) cout << " ";
                            gotoxy(45, selection * 2 + 3);
                            id = cinLim(id, 30);
                            break;
                        case 2:
                            for(i = 0; i <= 16; i++) cout << " ";
                            gotoxy(45, selection * 2 + 3);
                            mdp = cinMdp(mdp, 16);
                            break;
                        case 3:
                            for(i = 0; i <= 16; i++) cout << " ";
                            gotoxy(45, selection * 2 + 3);
                            verif = cinMdp(verif, 16);
                            break;
                        case 4:
                            for(i = 0; i <= 20; i++) cout << " ";
                            gotoxy(45, selection * 2 + 3);
                            desc = cinLim(desc, 20);
                            break;
                    }

                    //Suppression des encadrés
                    if(selection == 1) supprEncadre(39, 41, selection * 2 + 2);
                    if(selection == 2 || selection == 3) supprEncadre(25, 41, selection * 2 + 2);
                    if(selection == 4) supprEncadre(29, 41, selection * 2 + 2);
                }
            } while(touche1 != 27 && (selection != 5 || touche1 != 13));
        } while(touche1 != 27 && mdp != verif);
    } while(touche1 != 27 && (id.empty() || mdp.empty() || desc.empty()));

//----------------------------------

    if(touche1 != 27) //Si touche != echap
    {
        //Affichage
        clear();
        color(12, 15);
        afficheCentre("Nouveau mot de passe", 80, 1);
        color(0, 15);
        gotoxy(10, 5);
        cout << "Identifiant :";
        gotoxy(15, 6);
        cout << id;
        gotoxy(10, 8);
        cout << "Mot de passe enregistr" << (char)130 << " :";
        gotoxy(15, 9);
        cout << mdp;
        gotoxy(10, 11);
        cout << "Description :";
        gotoxy(15, 12);
        cout << desc;

//----------------------------------

        //Cryptage
        id = crypt(id);
        mdp = crypt(mdp);
        desc = crypt(desc);

        //Edition fichier
        flux << id << endl << mdp << endl << desc << endl;
        flux.close();
        gotoxy(1,1);
        getch();
    }
}

//----------------------------------------------------------------------------------------------

//Supprimer un mot de passe

void CIhm::supprMdp()
{
    ofstream flux1(fichierTemp.c_str(), ios::app);
    ifstream flux2(fichierDonnees.c_str());
    short i;
    short selection = 1;
    short nbMdp;
    char touche1, touche2;
    bool question;
    string contenu;

    do
    {
        clear();
        color(12, 15);
        afficheCentre("Supprimer un mot de passe", 80, 1);
        color(0, 15);

        nbMdp = affichMdp();
        gotoxy(1, 1);

        //Sélection
        if(nbMdp > 0)
        {
            do
            {
                //Effacage du curseur
                for(i = 7; i < nbMdp + 7; i++)
                {
                    gotoxy(3, i);
                    cout << "  ";
                }
                //Affichage du curseur
                gotoxy(3, selection + 6);
                color(12, 15);
                cout << ">>";
                color(0, 15);
                gotoxy(1, 1);

                //Détection de la touche pressée
                touche2 = 0; //Initialisation
                touche1 = getch();
                if(touche1 == -32) touche2 = getch(); //Touches directionnelles = 2 touches pressées
                if(touche2 == 72) //Flèche du haut
                {
                    if(selection == 1) selection = nbMdp;
                    else selection -= 1;
                }
                if(touche2 == 80) //Flèche du bas
                {
                    if(selection == nbMdp) selection = 1;
                    else selection += 1;
                }
            } while(touche1 != 27 && touche1 != 13);

            if(touche1 == 13)
            {
                question = true;

                clear();
                color(12, 15);
                afficheCentre("Supprimer un mot de passe", 80, 1);
                color(0, 15);
                gotoxy(7, 5);
                cout << "Voulez-vous vraiment supprimer le mot de passe :";
                selectMdp(selection);

                gotoxy(10, 7);
                cout << mdpSelect[0];
                gotoxy(35, 7);
                cout << mdpSelect[1];
                gotoxy(55, 7);
                cout << mdpSelect[2];
                gotoxy(12, 10);
                color(12, 15);
                cout << "OUI";
                color(0, 15);
                gotoxy(25, 10);
                cout << "NON";
                gotoxy(8, 9);
                color(12, 15);
                afficheEncadre(11, 8, 9);
                color(0, 15);
                gotoxy(1, 1);

                do
                {
                    //Détection de la touche pressée
                    touche2 = 0; //Initialisation
                    touche1 = getch();
                    if(touche1 == -32) touche2 = getch(); //Touches directionnelles = 2 touches pressées
                    if(touche2 == 75) question = true; //Flèche de gauche
                    if(touche2 == 77) question = false; //Flèche de droite

                    //Effacage des propositions
                    gotoxy(8, 9);
                    for(i = 0; i < 11; i++) cout << " ";
                    gotoxy(8, 10);
                    cout << " ";
                    gotoxy(18, 10);
                    cout << " ";
                    gotoxy(8, 11);
                    for(i = 0; i < 11; i++) cout << " ";

                    gotoxy(21, 9);
                    for(i = 0; i < 11; i++) cout << " ";
                    gotoxy(21, 10);
                    cout << " ";
                    gotoxy(31, 10);
                    cout << " ";
                    gotoxy(21, 11);
                    for(i = 0; i < 11; i++) cout << " ";

                    //Affichage des propositions
                    gotoxy(12, 10);
                    cout << "OUI";
                    gotoxy(25, 10);
                    cout << "NON";
                    color(12, 15);
                    if(question == true) afficheTitre("OUI", 8, 9);
                    else afficheTitre("NON", 21, 9);
                    color(0, 15);
                    gotoxy(1, 1);
                } while(touche1 != 13);
            }
        }
        else getch();

    } while(touche1 != 27 && question == false && nbMdp != 0);

    if(touche1 != 27 && nbMdp != 0)
    {
        //Affichage
        clear();
        color(12, 15);
        afficheCentre("Supprimer un mot de passse", 80, 1);
        color(0, 15);
        gotoxy(7, 5);
        cout << "Le mot de passe suivant a correctement " << (char)130 << "t" << (char)130 << " supprim" << (char)130 << " :";
        gotoxy(10, 7);
        cout << mdpSelect[0];
        gotoxy(35, 7);
        cout << mdpSelect[1];
        gotoxy(55, 7);
        cout << mdpSelect[2];
        gotoxy(1, 1);
        getch();

        //Effaçage du mot de passe
        getline(flux2, contenu);
        flux1 << contenu << endl;
        getline(flux2, contenu);
        flux1 << contenu << endl;

        while(getline(flux2, contenu))
        {
            if(contenu != crypt(mdpSelect[0]))
            {
                flux1 << contenu << endl;
                for(i = 0; i < 2; i++)
                {
                    getline(flux2, contenu);
                    flux1 << contenu << endl;
                }
            }
            else
            {
                for(i = 0; i < 2; i++) getline(flux2, contenu);
            }
        }

        flux2.close();
        flux1.close();
        remove("data.txt");
        rename("temp.txt", "data.txt");
    }
}

//----------------------------------------------------------------------------------------------

//Modifier un mot de passe

void CIhm::modifMdp()
{
    ofstream flux1(fichierTemp.c_str(), ios::app);
    ifstream flux2(fichierDonnees.c_str());
    short i, selection;
    short selectionMdp = 1;
    short nbMdp;
    char touche1, touche2, touche1Bis;
    string id, mdp, verif, desc, contenu;
    bool testChang = false;

    do
    {
        clear();
        color(12, 15);
        afficheCentre("Modifier un mot de passe", 80, 1);
        color(0, 15);

        nbMdp = affichMdp();
        gotoxy(1, 1);

        if(nbMdp > 0)
        {
            do
            {
                //Effacage du curseur
                for(i = 7; i < nbMdp + 7; i++)
                {
                    gotoxy(3, i);
                    cout << "  ";
                }
                //Affichage du curseur
                gotoxy(3, selectionMdp + 6);
                color(12, 15);
                cout << ">>";
                color(0, 15);
                gotoxy(1, 1);

                //Détection de la touche pressée
                touche2 = 0; //Initialisation
                touche1 = getch();
                if(touche1 == -32) touche2 = getch(); //Touches directionnelles = 2 touches pressées
                if(touche2 == 72) //Flèche du haut
                {
                    if(selectionMdp == 1) selectionMdp = nbMdp;
                    else selectionMdp -= 1;
                }
                if(touche2 == 80) //Flèche du bas
                {
                    if(selectionMdp == nbMdp) selectionMdp = 1;
                    else selectionMdp += 1;
                }
                selectMdp(selectionMdp);
            } while(touche1 != 27 && touche1 != 13);

    //=============================================================================================

    //----------------------------------

            if(touche1 != 27)
            {
                do
                {
                    do
                    {
                        selection = 1;
                        id.erase();
                        mdp.erase();
                        verif.erase();
                        desc.erase();
                        touche1Bis = 0;

                        clear();
                        color(12, 15);
                        afficheCentre("Modifier un mot de passe", 80, 1);
                        color(0, 15);
                        gotoxy(20, 5);
                        cout << "Mot de passe concern\x82 :";
                        gotoxy(37, 5);
                        cout << "Id - " << mdpSelect[0];
                        gotoxy(27, 6);
                        cout << "Mot de passe - " << mdpSelect[1];
                        gotoxy(28, 7);
                        cout << "Description - " << mdpSelect[2];

                        gotoxy(10, 9);
                        cout << "Entrez votre identifiant     :";
                        gotoxy(10, 11);
                        cout << "Entrez votre mot de passe    :";
                        gotoxy(10, 13);
                        cout << "R" << (char)130 << "p" << (char)130 << "tez votre mot de passe   :";
                        gotoxy(10, 15);
                        cout << "Entrez une description       :";
                        gotoxy(8, 20);
                        cout << "Termin" << (char)130;

        //----------------------------------

                        do
                        {
                            gotoxy(45, selection * 2 + 7);
                            do //Boucle de décalage du curseur selon le choix
                            {
                                //Effacage du curseur
                                for(i = 9; i < 16; i++)
                                {
                                    //Supprimer les curseurs
                                    gotoxy(7, i);
                                    cout << "  ";
                                }
                                //Supprimer l'encadré
                                gotoxy(4, 19);
                                for(i = 0; i < 15; i++) cout << " ";
                                gotoxy(4, 20);
                                cout << " ";
                                gotoxy(18, 20);
                                cout << " ";
                                gotoxy(4, 21);
                                for(i = 0; i < 15; i++) cout << " ";

                                //Affichage du curseur
                                if(selection == 5)
                                {
                                    //Affichage encadré pour 5
                                    afficheTitre("Termin\x82", 4, 19);
                                    gotoxy(1, 1);
                                }
                                else
                                {
                                    //Affichage du curseur pour 1; 2 et 3
                                    gotoxy(7, selection * 2 + 7);
                                    color(12, 15);
                                    cout << ">>";
                                    color(0, 15);
                                    gotoxy(45, selection * 2 + 7);
                                }

                                //Détection de la touche pressée
                                touche2 = 0; //Initialisation
                                touche1Bis = getch();
                                if(touche1Bis == -32) touche2 = getch(); //Touches directionnelles = 2 touches pressées
                                if(touche2 == 72) //Flèche du haut
                                {
                                    if(selection == 1) selection = 5;
                                    else selection -= 1;
                                }
                                if(touche2 == 80) //Flèche du bas
                                {
                                    if(selection == 5) selection = 1;
                                    else selection += 1;
                                }
                                //Fin test touches
                            } while(touche1Bis != 27 && touche1Bis != 13);

    //----------------------------------

                            //cin
                            if(touche1Bis != 27 && selection != 5)
                            {
                                //Affichage des encadrés
                                if(selection == 1) afficheEncadre(39, 41, selection * 2 + 6);
                                if(selection == 2 || selection == 3) afficheEncadre(25, 41, selection * 2 + 6);
                                if(selection == 4) afficheEncadre(29, 41, selection * 2 + 6);
                                gotoxy(45, selection * 2 + 7);

                                //Saisie
                                switch(selection)
                                {
                                    case 1:
                                        for(i = 0; i <= 30; i++) cout << " ";
                                        gotoxy(45, selection * 2 + 7);
                                        id = cinLim(id, 30);
                                        break;
                                    case 2:
                                        for(i = 0; i <= 16; i++) cout << " ";
                                        gotoxy(45, selection * 2 + 7);
                                        mdp = cinMdp(mdp, 16);
                                        break;
                                    case 3:
                                        for(i = 0; i <= 16; i++) cout << " ";
                                        gotoxy(45, selection * 2 + 7);
                                        verif = cinMdp(verif, 16);
                                        break;
                                    case 4:
                                        for(i = 0; i <= 20; i++) cout << " ";
                                        gotoxy(45, selection * 2 + 7);
                                        desc = cinLim(desc, 20);
                                        break;
                                }

                                //Suppression des encadrés
                                if(selection == 1) supprEncadre(39, 41, selection * 2 + 6);
                                if(selection == 2 || selection == 3) supprEncadre(25, 41, selection * 2 + 6);
                                if(selection == 4) supprEncadre(29, 41, selection * 2 + 6);
                            }
                        } while(touche1Bis != 27 && (selection != 5 || touche1Bis != 13));
                    } while(touche1Bis != 27 && mdp != verif);
                } while(touche1Bis != 27 && (id.empty() || mdp.empty() || desc.empty()));

    //----------------------------------

                if(touche1Bis != 27)
                {
                    clear();
                    color(12, 15);
                    afficheCentre("Modifier un mot de passe", 80, 1);
                    color(0, 15);
                    gotoxy(20, 5);
                    cout << "Le mot de passe a \x82t\x82 modifi\x82 :";
                    gotoxy(37, 7);
                    cout << "Id - " << id;
                    gotoxy(27, 8);
                    cout << "Mot de passe - " << mdp;
                    gotoxy(28, 9);
                    cout << "Description - " << desc;

                    //Modification
                    for(i = 0; i < 2; i++)
                    {
                        getline(flux2, contenu);
                        flux1 << contenu << endl;
                    }
                    while(getline(flux2, contenu))
                    {
                        if(contenu != crypt(mdpSelect[0]))
                        {
                            flux1 << contenu << endl;
                            for(i = 0; i < 2; i++)
                            {
                                getline(flux2, contenu);
                                flux1 << contenu << endl;
                            }
                        }
                        else
                        {
                            flux1 << crypt(id) << endl << crypt(mdp) << endl << crypt(desc) << endl;
                            for(i = 0; i < 2; i++) getline(flux2, contenu);
                        }
                    }
                    flux1.close();
                    flux2.close();

                    remove("data.txt");
                    rename("temp.txt", "data.txt");
                    testChang = true;
                    getch();
                }
            }

    //----------------------------------

    //=============================================================================================

        }
        else getch();
    } while(touche1 != 27 && nbMdp != 0 && testChang == false);
}

//----------------------------------------------------------------------------------------------

//Liste des mots de passe

void CIhm::listeMdp()
{
    clear();
    color(12, 15);
    afficheCentre("Liste des mots de passe", 80, 1);
    color(0, 15);
    affichMdp();

    gotoxy(1, 1);
    getch();
}

//----------------------------------------------------------------------------------------------

//Paramètres du compte

void CIhm::param()
{
    ofstream flux1(fichierTemp.c_str(), ios::app);
    ifstream flux2(fichierDonnees.c_str());
    short i;
    short selection = 1;
    char touche1, touche2;
    string mdpAvant, mdpApres, verif, contenu;
    bool testChang = false;
    getline(flux2, contenu);

    do
    {
        clear();
        color(12, 15);
        afficheCentre("Param\x8atres", 80, 1);
        color(0, 15);

        gotoxy(7, 7);
        cout << "Entrez l'ancien mot de passe     :";
        gotoxy(7, 9);
        cout << "Entrez le nouveau mot de passe   :";
        gotoxy(7, 11);
        cout << "R\x82p\x82tez le mot de passe          :";
        gotoxy(8, 15);
        cout << "Termin\x82";

        do
        {
            //Effacage du curseur
            for(i = 7; i < 12; i++)
            {
                //Supprimer les curseurs
                gotoxy(3, i);
                cout << "  ";
            }
            //Supprimer l'encadré
            gotoxy(4, 14);
            for(i = 0; i < 15; i++) cout << " ";
            gotoxy(4, 15);
            cout << " ";
            gotoxy(18, 15);
            cout << " ";
            gotoxy(4, 16);
            for(i = 0; i < 15; i++) cout << " ";

            //Affichage du curseur
            if(selection == 4)
            {
                //Affichage encadré pour 4
                afficheTitre("Termin\x82", 4, 14);
                gotoxy(1, 1);
            }
            else
            {
                //Affichage du curseur pour 1; 2 et 3
                gotoxy(3, selection * 2 + 5);
                color(12, 15);
                cout << ">>";
                color(0, 15);
                gotoxy(45, selection * 2 + 5);
            }

            //Détection de la touche pressée
            touche2 = 0; //Initialisation
            touche1 = getch();
            if(touche1 == -32) touche2 = getch(); //Touches directionnelles = 2 touches pressées
            if(touche2 == 72) //Flèche du haut
            {
                if(selection == 1) selection = 4;
                else selection -= 1;
            }
            if(touche2 == 80) //Flèche du bas
            {
                if(selection == 4) selection = 1;
                else selection += 1;
            }

            if(selection != 4 && touche1 == 13)
            {
                switch(selection)
                {
                    case 1:
                        for(i = 0; i < 17; i++) cout << " ";
                        afficheEncadre(23, 42, 6);
                        gotoxy(45, 7);
                        mdpAvant = cinMdp(mdpAvant, 16);
                        supprEncadre(23, 42, 6);
                        gotoxy(45, 7);
                        break;
                    case 2:
                        for(i = 0; i < 17; i++) cout << " ";
                        afficheEncadre(23, 42, 8);
                        gotoxy(45, 9);
                        mdpApres = cinMdp(mdpApres, 16);
                        supprEncadre(23, 42, 8);
                        gotoxy(45, 9);
                        break;
                    case 3:
                        for(i = 0; i < 17; i++) cout << " ";
                        afficheEncadre(23, 42, 10);
                        gotoxy(45, 11);
                        verif = cinMdp(verif, 16);
                        supprEncadre(23, 42, 10);
                        gotoxy(45, 11);
                        break;
                }
            }
        } while(touche1 != 27 && (touche1 != 13 || selection != 4));

        if(touche1 != 27 && mdpAvant.empty() == false && mdpApres.empty() == false && verif.empty() == false && contenu == crypt(mdpAvant) && mdpApres == verif)
        {
            clear();
            color(12, 15);
            afficheCentre("Changer le mot de passe", 80, 1);
            color(0, 15);
            gotoxy(29, 7);
            color(15, 12);
            cout << "Mot de passe mis \x85 jour";
            color(0, 15);
            gotoxy((80 - mdpAvant.size()) / 2 - 5, 9);
            cout << mdpAvant;
            gotoxy(39, 9);
            cout << ">>>  " << mdpApres;

            flux1 << crypt(mdpApres) << endl;
            while(getline(flux2, contenu)) flux1 << contenu << endl;

            flux1.close();
            flux2.close();
            remove("data.txt");
            rename("temp.txt", "data.txt");

            testChang = true;
            gotoxy(1, 1);
            getch();
        }
    } while(touche1 != 27 && testChang == false);
}

//----------------------------------------------------------------------------------------------

//Afficher les mots de passe

short CIhm::affichMdp()
{
    ifstream flux(fichierDonnees.c_str());
    short i = 0;
    short nbMdp = 0;
    string contenu;

    if(flux)
    {
        getline(flux, contenu);
        getline(flux, contenu);
        while(getline(flux, contenu))
        {
            if(contenu != "")
            {
                nbMdp++;
                gotoxy(10, 5);
                cout << "Id :";
                gotoxy(35, 5);
                cout << "Mot de passe :";
                gotoxy(55, 5);
                cout << "Description :";

                gotoxy(7, i + 7);
                cout << i;
                gotoxy(10, i + 7);
                cout << decrypt(contenu);
                gotoxy(35, i + 7);
                getline(flux, contenu);
                cout << decrypt(contenu);
                gotoxy(55, i + 7);
                getline(flux, contenu);
                cout << decrypt(contenu);
                i++;
            }
        }
        flux.close();
        if(nbMdp == 0)
        {
            gotoxy(26, 8);
            color(15, 12);
            cout << "Il n'y a aucun mot de passe";
            color(0, 15);
        }
        return nbMdp;
    }
    else
    {
        //Si ouverture impossible
        gotoxy(23, 8);
        color(15, 12);
        cout << "Erreur, le fichier est inexistant";
        color(0, 15);
    }
}

//----------------------------------------------------------------------------------------------

void CIhm::selectMdp(short numMdp)
{
    ifstream flux(fichierDonnees.c_str());
    short i;
    string id, mdp, desc;

    if(flux)
    {
        getline(flux, id);
        getline(flux, id);
        for(i = 0; i < numMdp; i++)
        {
            getline(flux, id);
            mdpSelect[0] = decrypt(id);
            getline(flux, mdp);
            mdpSelect[1] = decrypt(mdp);
            getline(flux, desc);
            mdpSelect[2] = decrypt(desc);
        }
        flux.close();
    }
    else
    {
        //Si ouverture impossible
        gotoxy(23, 8);
        color(15, 12);
        cout << "Erreur, le fichier est inexistant";
        color(0, 15);
    }
}

//----------------------------------------------------------------------------------------------

//Cryptage

string CIhm::crypt(string chaine)
{
    ifstream flux(fichierDonnees.c_str());
    string methodeCryptage;
    unsigned short i, j;

    if(flux)
    {
        getline(flux, methodeCryptage);
        getline(flux, methodeCryptage);
        flux.close();
    }
    else
    {
        //Si ouverture impossible;
        gotoxy(15, 13);
        color(15, 12);
        cout << "Erreur, impossible d'ouvrir le fichier";
        color(0, 15);
    }

    for(i = 0; i < chaine.size(); i++)
    {
        for(j = 0; j < 70; j++)
        {
            if(chaine[i] == listeCarac[j])
            {
                chaine[i] = methodeCryptage[j];
                break;
            }
        }
    }
    return chaine;
}

//----------------------------------------------------------------------------------------------

//Décryptage

string CIhm::decrypt(string chaine)
{
    ifstream flux(fichierDonnees.c_str());
    string methodeCryptage;
    unsigned short i;
    short j;

    if(flux)
    {
        getline(flux, methodeCryptage);
        getline(flux, methodeCryptage);
        flux.close();
    }
    else
    {
        //Si ouverture impossible;
        gotoxy(15, 13);
        color(15, 12);
        cout << "Erreur, impossible d'ouvrir le fichier";
        color(0, 15);
    }

    for(i = 0; i < chaine.size(); i++)
    {
        for(j = 0; j < 70; j++)
        {
            if(chaine[i] == methodeCryptage[j])
            {
                chaine[i] = listeCarac[j];
                break;
            }
        }
    }
    return chaine;
}
