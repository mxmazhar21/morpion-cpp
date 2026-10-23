#include "JoueurHumain.h"

#include <iostream>

// Nombre de caractères à jeter pour vider la ligne tapée
const int TAILLE_LIGNE_MAX = 10000;

JoueurHumain::JoueurHumain(const std::string& nomJoueur, char symboleJoueur)
    : Joueur(nomJoueur, symboleJoueur)
{
}

// Demande une case jusqu'à obtenir une case libre entre 1 et 9.
// Renvoie 0 si la saisie est terminée (fin de fichier).
int JoueurHumain::choisirCoup(const Plateau& plateau)
{
    while (true) {
        std::cout << nom << " (" << symbole << "), choisissez une case (1-9) : ";
        int numero = 0;
        std::cin >> numero;

        if (std::cin.fail() && std::cin.eof()) {
            std::cout << "\nFin de la saisie.\n";
            return 0;
        }
        bool saisieOk = !std::cin.fail();
        std::cin.clear();                         // enlève l'erreur de cin
        std::cin.ignore(TAILLE_LIGNE_MAX, '\n');  // jette le reste de la ligne

        if (!saisieOk) {
            std::cout << "Erreur : il faut taper un nombre.\n";
        } else if (!plateau.caseValide(numero)) {
            std::cout << "Erreur : la case doit être entre 1 et 9.\n";
        } else if (!plateau.estLibre(numero)) {
            std::cout << "Erreur : la case " << numero << " est déjà occupée.\n";
        } else {
            return numero;
        }
    }
}
