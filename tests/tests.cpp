// Petit programme de test pour Plateau et JoueurIA.
// Aucune saisie clavier : tout est vérifié automatiquement.

#include <iostream>
#include <string>

#include "JoueurIA.h"
#include "Plateau.h"

int nbReussis = 0;
int nbEchoues = 0;

// Affiche le résultat d'un test et compte les réussites / échecs
void verifier(bool condition, const std::string& nomTest)
{
    if (condition) {
        std::cout << "[OK]    " << nomTest << "\n";
        nbReussis++;
    } else {
        std::cout << "[ECHEC] " << nomTest << "\n";
        nbEchoues++;
    }
}

// Remplit un plateau avec une chaîne de 9 caractères ('X', 'O' ou '.')
Plateau creerPlateau(const std::string& contenu)
{
    Plateau plateau;
    for (int i = 0; i < 9; i++) {
        if (contenu[i] != '.') {
            plateau.placer(i + 1, contenu[i]);
        }
    }
    return plateau;
}

// Les 8 combinaisons gagnantes, pour X puis pour O
void testerVictoires()
{
    const int combinaisons[8][3] = {
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9},
        {1, 4, 7}, {2, 5, 8}, {3, 6, 9},
        {1, 5, 9}, {3, 5, 7}
    };
    const std::string noms[8] = {
        "ligne 1", "ligne 2", "ligne 3",
        "colonne 1", "colonne 2", "colonne 3",
        "diagonale 1-5-9", "diagonale 3-5-7"
    };
    const char symboles[2] = {'X', 'O'};

    for (int s = 0; s < 2; s++) {
        char symbole = symboles[s];
        char autre = (symbole == 'X') ? 'O' : 'X';
        for (int i = 0; i < 8; i++) {
            Plateau plateau;
            for (int j = 0; j < 3; j++) {
                plateau.placer(combinaisons[i][j], symbole);
            }
            bool ok = plateau.aGagne(symbole) && !plateau.aGagne(autre);
            verifier(ok, std::string("Victoire de ") + symbole + " sur " + noms[i]);
        }
    }
}

void testerPlateau()
{
    Plateau vide;
    verifier(!vide.aGagne('X') && !vide.aGagne('O'), "Plateau vide : personne ne gagne");
    verifier(!vide.estPlein(), "Plateau vide : pas plein");

    // Deux symboles sur une ligne ne suffisent pas
    Plateau presque = creerPlateau("XX.......");
    verifier(!presque.aGagne('X'), "Deux X alignés : pas de victoire");

    // Ligne mélangée : pas de victoire
    Plateau melange = creerPlateau("XOX......");
    verifier(!melange.aGagne('X') && !melange.aGagne('O'), "Ligne X O X : pas de victoire");

    // Match nul : plateau plein sans gagnant
    Plateau nul = creerPlateau("XOXXOOOXX");
    verifier(nul.estPlein(), "Match nul : plateau plein");
    verifier(!nul.aGagne('X') && !nul.aGagne('O'), "Match nul : aucun gagnant");
}

void testerPlacement()
{
    Plateau plateau;
    verifier(plateau.placer(5, 'X'), "Placer X en case 5 (libre)");
    verifier(plateau.getCase(5) == 'X', "La case 5 contient bien X");
    verifier(!plateau.placer(5, 'O'), "Case occupée refusée");
    verifier(plateau.getCase(5) == 'X', "La case occupée n'a pas changé");
    verifier(!plateau.placer(0, 'O'), "Case 0 refusée");
    verifier(!plateau.placer(10, 'O'), "Case 10 refusée");
    verifier(!plateau.placer(-3, 'O'), "Case -3 refusée");
    verifier(!plateau.estLibre(0) && !plateau.estLibre(10), "Cases hors limites jamais libres");

    plateau.vider();
    verifier(plateau.estLibre(5), "vider() remet la case 5 à vide");
}

void testerIA()
{
    JoueurIA ia("Ordinateur", 'O');

    // L'IA (O) peut gagner en case 3
    Plateau gagne = creerPlateau("OO.XX.X..");
    verifier(ia.choisirCoup(gagne) == 3, "IA gagne quand elle peut (case 3)");

    // L'IA (O) doit bloquer X en case 9 (diagonale 1-5-9)
    Plateau bloque = creerPlateau("XO..X....");
    verifier(ia.choisirCoup(bloque) == 9, "IA bloque l'adversaire (case 9)");

    // L'IA (O) peut gagner en 6 ou bloquer en 3 : elle doit gagner
    Plateau choix = creerPlateau("XX.OO....");
    verifier(ia.choisirCoup(choix) == 6, "IA préfère gagner plutôt que bloquer (case 6)");

    // Plateau vide : l'IA joue au centre
    Plateau vide;
    verifier(ia.choisirCoup(vide) == 5, "IA joue au centre si libre");

    // Centre pris : l'IA joue dans un coin
    Plateau centrePris = creerPlateau("....X....");
    verifier(ia.choisirCoup(centrePris) == 1, "IA joue un coin si le centre est pris");

    // Centre et coins pris, sans menace : l'IA joue une case libre (2 ou 8)
    Plateau bords = creerPlateau("X.OOXXX.O");
    int coup = ia.choisirCoup(bords);
    verifier(coup == 2 || coup == 8, "IA joue une case libre au hasard");

    // L'IA avec X gagne aussi (test du symbole adverse)
    JoueurIA iaX("IA X", 'X');
    Plateau gagneX = creerPlateau("O.OXX....");
    verifier(iaX.choisirCoup(gagneX) == 6, "IA (X) gagne en case 6");
}

int main()
{
    std::cout << "=== Tests du Morpion ===\n\n";
    testerVictoires();
    testerPlateau();
    testerPlacement();
    testerIA();

    std::cout << "\nRésultat : " << nbReussis << " réussis, " << nbEchoues << " échoués\n";
    if (nbEchoues > 0) {
        return 1;
    }
    return 0;
}
