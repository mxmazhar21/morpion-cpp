#ifndef JOUEURHUMAIN_H
#define JOUEURHUMAIN_H

#include "Joueur.h"

// Joueur qui tape le numéro de la case au clavier
class JoueurHumain : public Joueur
{
public:
    JoueurHumain(const std::string& nomJoueur, char symboleJoueur);

    int choisirCoup(const Plateau& plateau) override;
};

#endif
