#include "Jeu.h"

#include <iostream>
#include <string>

#include "JoueurHumain.h"
#include "JoueurIA.h"

// Nombre de caractères à jeter pour vider la ligne tapée
const int TAILLE_LIGNE_MAX = 10000;

// Modes du menu
const int MODE_HUMAIN_HUMAIN = 1;
const int MODE_HUMAIN_IA = 2;
const int QUITTER = 3;

Jeu::Jeu()
    : joueur1(nullptr), joueur2(nullptr), joueurCourant(nullptr)
{
}

Jeu::~Jeu()
{
    supprimerJoueurs();
}

// Boucle principale : menu, puis parties tant qu'on veut rejouer
void Jeu::lancer()
{
    bool quitter = false;
    while (!quitter) {
        afficherMenu();
        int choix = demanderChoixMenu();
        if (choix == QUITTER) {
            quitter = true;
        } else {
            creerJoueurs(choix);
            do {
                jouerPartie();
            } while (demanderRejouer());
            supprimerJoueurs();
        }
    }
    std::cout << "Au revoir !\n";
}

void Jeu::afficherMenu() const
{
    std::cout << "\n===== MORPION =====\n";
    std::cout << "1. Humain contre Humain\n";
    std::cout << "2. Humain contre IA\n";
    std::cout << "3. Quitter\n";
}

// Demande un choix entre 1 et 3. En fin de saisie, on quitte.
int Jeu::demanderChoixMenu()
{
    while (true) {
        std::cout << "Votre choix : ";
        int choix = 0;
        std::cin >> choix;

        if (std::cin.fail() && std::cin.eof()) {
            std::cout << "\n";
            return QUITTER;
        }
        bool saisieOk = !std::cin.fail();
        std::cin.clear();
        std::cin.ignore(TAILLE_LIGNE_MAX, '\n');

        if (saisieOk && choix >= 1 && choix <= 3) {
            return choix;
        }
        std::cout << "Erreur : tapez 1, 2 ou 3.\n";
    }
}

// Crée les deux joueurs avec new (libérés dans supprimerJoueurs)
void Jeu::creerJoueurs(int mode)
{
    supprimerJoueurs();
    if (mode == MODE_HUMAIN_HUMAIN) {
        joueur1 = new JoueurHumain("Joueur 1", 'X');
        joueur2 = new JoueurHumain("Joueur 2", 'O');
    } else if (mode == MODE_HUMAIN_IA) {
        joueur1 = new JoueurHumain("Joueur", 'X');
        joueur2 = new JoueurIA("Ordinateur", 'O');
    }
}

void Jeu::supprimerJoueurs()
{
    delete joueur1;
    delete joueur2;
    joueur1 = nullptr;
    joueur2 = nullptr;
    joueurCourant = nullptr;
}

// Joue une partie complète, 'X' commence
void Jeu::jouerPartie()
{
    plateau.vider();
    joueurCourant = joueur1;
    bool finie = false;

    while (!finie) {
        plateau.afficher();
        // Polymorphisme : appelle la version humaine ou IA
        int coup = joueurCourant->choisirCoup(plateau);
        if (coup == 0) {
            std::cout << "Partie interrompue.\n";
            return;
        }
        plateau.placer(coup, joueurCourant->getSymbole());
        std::cout << joueurCourant->getNom() << " joue en case " << coup << ".\n";

        finie = verifierFinPartie();
        if (!finie) {
            changerJoueur();
        }
    }
}

// Annonce le gagnant ou le match nul, renvoie true si la partie est finie
bool Jeu::verifierFinPartie()
{
    if (plateau.aGagne(joueurCourant->getSymbole())) {
        plateau.afficher();
        std::cout << "Bravo " << joueurCourant->getNom() << " ("
                  << joueurCourant->getSymbole() << ") a gagné !\n";
        return true;
    }
    if (plateau.estPlein()) {
        plateau.afficher();
        std::cout << "Match nul !\n";
        return true;
    }
    return false;
}

void Jeu::changerJoueur()
{
    if (joueurCourant == joueur1) {
        joueurCourant = joueur2;
    } else {
        joueurCourant = joueur1;
    }
}

// Demande "o" ou "n". En fin de saisie, on répond non.
bool Jeu::demanderRejouer()
{
    while (true) {
        std::cout << "Voulez-vous rejouer ? (o/n) : ";
        std::string reponse;
        std::cin >> reponse;

        if (std::cin.fail() && std::cin.eof()) {
            std::cout << "\n";
            return false;
        }
        std::cin.ignore(TAILLE_LIGNE_MAX, '\n');

        if (reponse == "o" || reponse == "O") {
            return true;
        }
        if (reponse == "n" || reponse == "N") {
            return false;
        }
        std::cout << "Erreur : tapez o ou n.\n";
    }
}
