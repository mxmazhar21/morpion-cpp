#include <cstdlib>
#include <ctime>

#include "Jeu.h"

int main()
{
    // Initialise le hasard pour l'IA
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Jeu jeu;
    jeu.lancer();
    return 0;
}
