#include "Joueur.h"

Joueur::Joueur(const std::string& nomJoueur, char symboleJoueur)
    : nom(nomJoueur), symbole(symboleJoueur)
{
}

Joueur::~Joueur()
{
}

std::string Joueur::getNom() const
{
    return nom;
}

char Joueur::getSymbole() const
{
    return symbole;
}
