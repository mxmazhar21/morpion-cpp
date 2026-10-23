#ifndef PLATEAU_H
#define PLATEAU_H

// Grille 3x3 du morpion.
// Les cases sont numérotées de 1 à 9 :
//   1 | 2 | 3
//   4 | 5 | 6
//   7 | 8 | 9
class Plateau
{
private:
    char cases[9]; // ' ' veut dire que la case est vide

public:
    Plateau();

    void vider();
    void afficher() const;

    bool caseValide(int numero) const;
    bool estLibre(int numero) const;
    bool placer(int numero, char symbole);
    char getCase(int numero) const;

    bool aGagne(char symbole) const;
    bool estPlein() const;
};

#endif
