#include <utility>

//
// Created by paul on 25/09/18.
//

#include "Layer.h"

using namespace std;
using namespace  state;

Layer::Layer(shared_ptr<std::vector<uint>> data, uint height, uint width, int x, int y, string name): data(
        std::move(data)), height(height), width(width), x(x), y(y), name(name) {
}

int Layer::getY() {
    return this->y;
}

int Layer::getX() {
    return this->x;
}

uint Layer::getWidth() {
    return this->width;
}

uint Layer::getHeight() {
    return this->height;
}

std::shared_ptr<std::vector<uint>> Layer::getData() {
    return this->data;
}

Layer::~Layer() {
    this->data.reset();
}

