#include <iostream>
#include <string.h>
// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "state.h"

using namespace std;
using namespace state;

int main(int argc,char* argv[]) 
{
    Exemple exemple;
    exemple.setX(53);
    // check the number of arguments
    if(argc != 1) {
        // check the 1st argument
        if(strcmp(argv[1],"hello")== 0) {
            cout << "bonjour les potes" << endl;
        }
        else {
            cout << "Je ne comprends pas!" << endl;
        }
    }



    return 0;
}
