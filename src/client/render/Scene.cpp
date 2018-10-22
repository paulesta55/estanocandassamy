//
// Created by paul on 22/10/18.
//

#include "Scene.h"
#include "CustomException.h"

using namespace std;
using namespace render;
using namespace sf;

Scene::Scene(state::State &state, shared_ptr<sf::RenderWindow> window, shared_ptr<ResManager> resManager) {
    this->window = window;
    this->state = state;
    this->resManager = resManager;
    if(!resManager)
    {
        CustomException exception("no resources manager");
        throw exception;
    }
    std::shared_ptr<std::vector<sf::Texture>> cachePtr = this->resManager->textureCache;

    window->clear();
    for(auto layer: *(this->state.getMap()->getLayers()))
    {
        for(int i = 0 ; i <height; i++)
        {
            for(int j = 0; j<width; j++)
            {
                uint tile = layer.getData()->at(i*width+j);

                if(tile != 0 )
                {
                    shared_ptr<sf::Texture> texture;
                    shared_ptr<sf::Sprite> sprite0;
                    sprite0.reset(new sf::Sprite());
                    sprite0->setTexture(cachePtr.get()->at(tile-1));
                    sprite0->setPosition(j*24,i*24);
                    this->window->draw(*sprite0);
                }

            }
        }
    }

}
