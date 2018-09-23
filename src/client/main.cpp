#include <iostream>
#include <string.h>
// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>
#include <PixelsLoader.h>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "state.h"

using namespace std;
using namespace state;

int main(int argc,char* argv[]) 
{
    std::shared_ptr<std::vector<int>> v;
    v.reset(new vector<int>(10,10));

    for(int n : *v ){
        cout << n << endl;
        cout << &n << endl;
    }

    PixelsLoader pixelsLoader("res/map.json", "res/timemap.json","res/tilemap.png");
    if(!pixelsLoader.init()) {
        cout << "cannot parse metadata" << endl;
    }


    // check the number of arguments
    if(argc != 1) {
        // check the 1st argument
        if(strcmp(argv[1],"hello")== 0) {
            cout << "bonjour les potes" << endl;
        }
        // display a warning when a wrong number of arguments is given
        else{
            cout << "Je ne comprends pas!" << endl;
        }
    }

    sf::RenderWindow window(sf::VideoMode(526,601),"test window");



    while (window.isOpen()) {

        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();

            }
            window.clear();
            sf::Sprite sprite;
            sprite.setTexture(pixelsLoader.textureCache.get()->at(45));
            window.draw(sprite);

            window.display();
        }
    }

    return 0;
}
