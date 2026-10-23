#include "Plateau.h"

#include <iostream>

// Les 8 combinaisons gagnantes (numéros des cases)
static const int COMBINAISONS[8][3] = {
    {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, // lignes
    {1, 4, 7}, {2, 5, 8}, {3, 6, 9}, // colonnes
    {1, 5, 9}, {3, 5, 7}             // diagonales
};

Plateau::Plateau()
{
    vider();
}

// Remet toutes les cases à vide
void Plateau::vider()
{
    for (int i = 0; i < 9; i++) {
        cases[i] = ' ';
    }
}

// Affiche la grille : une case vide montre son numéro
void Plateau::afficher() const
{
    std::cout << "\n";
    for (int ligne = 0; ligne < 3; ligne++) {
        std::cout << " ";
        for (int colonne = 0; colonne < 3; colonne++) {
            int numero = ligne * 3 + colonne + 1;
            if (estLibre(numero)) {
                std::cout << numero;
            } else {
                std::cout << cases[numero - 1];
            }
            if (colonne < 2) {
                std::cout << " | ";
            }
        }
        std::cout << "\n";
        if (ligne < 2) {
            std::cout << "---+---+---\n";
        }
    }
    std::cout << "\n";
}

// Vrai si le numéro est entre 1 et 9
bool Plateau::caseValide(int numero) const
{
    return numero >= 1 && numero <= 9;
}

// Vrai si la case existe et qu'elle est vide
bool Plateau::estLibre(int numero) const
{
    if (!caseValide(numero)) {
        return false;
    }
    return cases[numero - 1] == ' ';
}

// Place le symbole si la case est libre, renvoie false sinon
bool Plateau::placer(int numero, char symbole)
{
    if (!estLibre(numero)) {
        return false;
    }
    cases[numero - 1] = symbole;
    return true;
}

// Renvoie le contenu d'une case (' ' si vide ou numéro invalide)
char Plateau::getCase(int numero) const
{
    if (!caseValide(numero)) {
        return ' ';
    }
    return cases[numero - 1];
}

// Vrai si le symbole remplit une des 8 combinaisons
bool Plateau::aGagne(char symbole) const
{
    for (int i = 0; i < 8; i++) {
        bool complete = true;
        for (int j = 0; j < 3; j++) {
            if (getCase(COMBINAISONS[i][j]) != symbole) {
                complete = false;
            }
        }
        if (complete) {
            return true;
        }
    }
    return false;
}

// Vrai s'il ne reste aucune case vide
bool Plateau::estPlein() const
{
    for (int numero = 1; numero <= 9; numero++) {
        if (estLibre(numero)) {
            return false;
        }
    }
    return true;
}
