#ifndef JEU_H
#define JEU_H

#include "Joueur.h"
#include "Plateau.h"

// Gère le menu, les parties, les tours et la fin de partie
class Jeu
{
private:
    Plateau plateau;
    Joueur* joueur1;       // joue avec 'X' et commence
    Joueur* joueur2;       // joue avec 'O'
    Joueur* joueurCourant; // joueur dont c'est le tour

    void afficherMenu() const;
    int demanderChoixMenu();
    void creerJoueurs(int mode);
    void supprimerJoueurs();

    void jouerPartie();
    bool verifierFinPartie();
    void changerJoueur();
    bool demanderRejouer();

public:
    Jeu();
    ~Jeu();

    // Pas de copie : la classe possède des pointeurs
    Jeu(const Jeu&) = delete;
    Jeu& operator=(const Jeu&) = delete;

    void lancer();
};

#endif
