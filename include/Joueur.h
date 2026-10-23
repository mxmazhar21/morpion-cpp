#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>

#include "Plateau.h"

// Classe abstraite : un joueur a un nom et un symbole ('X' ou 'O').
// Chaque type de joueur choisit son coup à sa façon.
class Joueur
{
protected:
    std::string nom;
    char symbole;

public:
    Joueur(const std::string& nomJoueur, char symboleJoueur);
    virtual ~Joueur(); // virtuel pour bien détruire les classes filles

    std::string getNom() const;
    char getSymbole() const;

    // Renvoie le numéro de la case choisie (1 à 9), ou 0 pour abandonner
    virtual int choisirCoup(const Plateau& plateau) = 0;
};

#endif
