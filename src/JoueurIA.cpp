#include "JoueurIA.h"

#include <cstdlib>
#include <vector>

JoueurIA::JoueurIA(const std::string& nomJoueur, char symboleJoueur)
    : Joueur(nomJoueur, symboleJoueur)
{
}

// Applique les 3 règles de l'IA dans l'ordre
int JoueurIA::choisirCoup(const Plateau& plateau)
{
    // Règle 1 : gagner tout de suite si c'est possible
    int coup = chercherCoupGagnant(plateau, symbole);
    if (coup != 0) {
        return coup;
    }

    // Règle 2 : bloquer l'adversaire s'il peut gagner au prochain coup
    coup = chercherCoupGagnant(plateau, getSymboleAdversaire());
    if (coup != 0) {
        return coup;
    }

    // Règle 3 : centre, coin ou hasard
    return choisirCoupParDefaut(plateau);
}

char JoueurIA::getSymboleAdversaire() const
{
    if (symbole == 'X') {
        return 'O';
    }
    return 'X';
}

// Cherche une case qui fait gagner "symboleTeste" en un coup.
// On essaie chaque case libre sur une copie du plateau.
// Renvoie 0 si aucune case ne fait gagner.
int JoueurIA::chercherCoupGagnant(const Plateau& plateau, char symboleTeste) const
{
    for (int numero = 1; numero <= 9; numero++) {
        if (plateau.estLibre(numero)) {
            Plateau copie = plateau;
            copie.placer(numero, symboleTeste);
            if (copie.aGagne(symboleTeste)) {
                return numero;
            }
        }
    }
    return 0;
}

// Centre si libre, sinon un coin libre, sinon une case au hasard
int JoueurIA::choisirCoupParDefaut(const Plateau& plateau) const
{
    if (plateau.estLibre(5)) {
        return 5;
    }

    const int coins[4] = {1, 3, 7, 9};
    for (int i = 0; i < 4; i++) {
        if (plateau.estLibre(coins[i])) {
            return coins[i];
        }
    }

    return choisirCaseAuHasard(plateau);
}

// Choisit une case libre au hasard (0 si le plateau est plein)
int JoueurIA::choisirCaseAuHasard(const Plateau& plateau) const
{
    std::vector<int> casesLibres;
    for (int numero = 1; numero <= 9; numero++) {
        if (plateau.estLibre(numero)) {
            casesLibres.push_back(numero);
        }
    }

    if (casesLibres.empty()) {
        return 0;
    }
    int indice = std::rand() % static_cast<int>(casesLibres.size());
    return casesLibres[indice];
}
