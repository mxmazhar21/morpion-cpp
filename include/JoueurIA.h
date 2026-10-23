#ifndef JOUEURIA_H
#define JOUEURIA_H

#include "Joueur.h"

// Joueur ordinateur avec une IA simple en 3 règles :
// 1) gagner si possible, 2) bloquer l'adversaire,
// 3) sinon centre, puis coin, puis case au hasard.
class JoueurIA : public Joueur
{
public:
    JoueurIA(const std::string& nomJoueur, char symboleJoueur);

    int choisirCoup(const Plateau& plateau) override;

private:
    char getSymboleAdversaire() const;
    int chercherCoupGagnant(const Plateau& plateau, char symboleTeste) const;
    int choisirCoupParDefaut(const Plateau& plateau) const;
    int choisirCaseAuHasard(const Plateau& plateau) const;
};

#endif
