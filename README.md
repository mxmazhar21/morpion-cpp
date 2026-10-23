# Morpion en C++ (console)

Jeu de Morpion (Tic-Tac-Toe) en mode console, écrit en C++17, avec une IA simple.
Le but du projet est de montrer la programmation orientée objet :
classes, encapsulation, héritage, classe abstraite et polymorphisme.

## Compilation

Il faut seulement `g++` et `make` (aucune bibliothèque externe).

```bash
make          # compile le jeu (morpion) et les tests (test_morpion)
make run      # lance le jeu
make test     # lance les tests automatiques
make clean    # supprime les fichiers compilés
```

Options de compilation : `-std=c++17 -Wall -Wextra -Werror -pedantic`.

## Structure du projet

```
morpion-cpp/
├── include/          fichiers .h (déclarations des classes)
├── src/              fichiers .cpp (code des classes + main.cpp)
├── tests/
│   ├── tests.cpp     tests de Plateau et JoueurIA (sans clavier)
│   └── scenarios/    fichiers d'entrées pour simuler des parties
├── Makefile
└── README.md
```

## Règles du jeu

- La grille fait 3x3, les cases sont numérotées de 1 à 9 :

```
 1 | 2 | 3
---+---+---
 4 | 5 | 6
---+---+---
 7 | 8 | 9
```

- Le joueur 1 joue avec `X` et commence, le joueur 2 joue avec `O`.
- À son tour, on tape le numéro d'une case libre.
- Le premier qui aligne 3 symboles (ligne, colonne ou diagonale) gagne.
- Si la grille est pleine sans gagnant, c'est un match nul.
- À la fin, le jeu propose de rejouer (`o` ou `n`).

Menu :
1. Humain contre Humain
2. Humain contre IA (l'humain joue `X`, l'ordinateur joue `O`)
3. Quitter

Si on tape une lettre, un nombre hors limites ou une case occupée,
un message d'erreur s'affiche et la question est reposée.

## Diagramme des classes

```
              +---------------------------+
              |      Joueur (abstraite)   |
              +---------------------------+
              | # nom : string            |
              | # symbole : char          |
              +---------------------------+
              | + getNom() : string       |
              | + getSymbole() : char     |
              | + choisirCoup(Plateau)=0  |  <- virtuelle pure
              | + ~Joueur() virtuel       |
              +---------------------------+
                   ^                 ^
                   | hérite          | hérite
     +----------------------+   +-------------------------------+
     |     JoueurHumain     |   |           JoueurIA            |
     +----------------------+   +-------------------------------+
     | + choisirCoup()      |   | + choisirCoup()               |
     |   (lit le clavier)   |   | - chercherCoupGagnant()       |
     +----------------------+   | - choisirCoupParDefaut()      |
                                | - choisirCaseAuHasard()       |
                                +-------------------------------+

     +-------------------------------+       +-------------------------+
     |              Jeu              |       |         Plateau         |
     +-------------------------------+       +-------------------------+
     | - plateau : Plateau           |------>| - cases[9] : char       |
     | - joueur1, joueur2 : Joueur*  |       +-------------------------+
     | - joueurCourant : Joueur*     |       | + afficher()            |
     +-------------------------------+       | + placer(numero, symb.) |
     | + lancer()                    |       | + estLibre(numero)      |
     | - jouerPartie()               |       | + aGagne(symbole)       |
     | - verifierFinPartie()         |       | + estPlein()            |
     | - changerJoueur()             |       | + vider()               |
     | - demanderRejouer()           |       +-------------------------+
     +-------------------------------+
```

### Où est le polymorphisme ?

La classe `Jeu` ne sait pas si le joueur est un humain ou l'ordinateur.
Elle utilise un pointeur `Joueur* joueurCourant` et appelle :

```cpp
int coup = joueurCourant->choisirCoup(plateau);
```

C'est la bonne version (`JoueurHumain` ou `JoueurIA`) qui est appelée
grâce à la méthode virtuelle. Les joueurs sont créés avec `new` et
détruits avec `delete` ; le destructeur de `Joueur` est virtuel pour que
la destruction se fasse correctement à travers un pointeur `Joueur*`.

## Fonctionnement de l'IA

L'IA applique 3 règles, dans cet ordre :

1. **Gagner** : pour chaque case libre, elle essaie son symbole sur une
   copie du plateau. Si ça donne une victoire, elle joue cette case.
2. **Bloquer** : elle fait pareil avec le symbole de l'adversaire. Si
   l'adversaire pourrait gagner sur une case, elle joue cette case.
3. **Sinon** : elle joue au centre (case 5) s'il est libre, puis dans un
   coin libre (1, 3, 7, 9), et sinon sur une case libre au hasard.

Cette IA est simple : elle ne perd pas sur les pièges faciles, mais on
peut la battre avec une "fourchette" (deux menaces en même temps).

## Tests

`make test` vérifie automatiquement (38 tests) :
- les 8 combinaisons gagnantes, pour `X` et pour `O` ;
- le match nul (plateau plein sans gagnant) ;
- le refus d'une case occupée ou hors limites (0, 10, -3) ;
- l'IA qui gagne quand elle peut, qui bloque quand il faut,
  qui préfère gagner plutôt que bloquer, puis centre / coin / hasard.

On peut aussi simuler des parties complètes avec un fichier d'entrées :

```bash
./morpion < tests/scenarios/humain_vs_humain.txt
./morpion < tests/scenarios/humain_vs_ia.txt
./morpion < tests/scenarios/fin_de_fichier.txt
```

Ces fichiers contiennent aussi des entrées invalides (lettres, `0`, `10`,
case occupée). Si le fichier se termine en pleine partie, le jeu
s'arrête proprement au lieu de boucler.

## Idées d'amélioration

- Demander le nom des joueurs au début de la partie.
- Choisir qui commence (ou alterner à chaque partie).
- Compter les scores sur plusieurs parties.
- Ajouter une IA "difficile" avec l'algorithme Minimax
  (nouvelle classe qui hérite de `Joueur`).
- Refuser les saisies comme `5abc` ou `3.7` (pour l'instant, seul le
  nombre du début est lu : `5abc` donne 5).
- Ajouter une interface graphique (SFML par exemple).
