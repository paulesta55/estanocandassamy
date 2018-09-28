#include <iostream>
#include <string.h>
// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>
#include "state.h"
#include "resources.h"
void testSFML() {
    sf::Texture texture;
}

// Fin test SFML


using namespace std;
using namespace state;
using namespace resources;

int main(int argc,char* argv[])
{


//    ResManager *resManager = new ResManager("res/timemap.json");
//    PixelsLoader *pixelsLoader = new PixelsLoader("res/poketile.json");
//    if(!resManager->init()) {
//        cout << "cannot parse metadata" << endl;
//    }
//    std::shared_ptr<std::vector<sf::Texture>> cachePtr = resManager->textureCache;
    // check the number of arguments
    if(argc == 2) {
        // check the 1st argument
        if(strcmp(argv[1],"hello")== 0) {
            cout << "Bonjour le monde !" << endl;
        }
        // display a warning when a wrong number of arguments is given

    }
    else {
        cout << "I don't understand"<< endl;
        cout << "you can only say hello" << endl;
    }

//    sf::RenderWindow window(sf::VideoMode(526,601),"test window");
//
//
//
//    while (window.isOpen()) {
//
//        sf::Event event;
//        while(window.pollEvent(event))
//        {
//            if(event.type == sf::Event::Closed)
//            {
//                cachePtr.reset();
//                window.close();
//                return 0;
//            }
//            window.clear();
//            int x= 0;
//            int y = 0;
//            for (int i = 0; i < (int) resManager->getTileCount();i++)
//            {
//                auto *sprite = new sf::Sprite();
//                sprite->setTexture(cachePtr.get()->at(i));
//                sprite->setPosition(x*resManager->getTileWidth(),y*resManager->getTileHeight());
//                window.draw(*sprite);
//                x++;
//                if (x >(int) resManager->getTileSetColumns()-1)
//                {
//                    y++;
//                    x = 0;
//                }
//                delete sprite;
//
//            }
//            window.display();
//        }
//    }

    return 0;
}
