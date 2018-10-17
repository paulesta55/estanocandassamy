//
// Created by paul on 16/10/18.
//

#ifndef ESTANOCANDASSAMY_MAPTEST_H
#define ESTANOCANDASSAMY_MAPTEST_H
#include <iostream>
#include "state.h"
#include<string>

using namespace std;
using namespace state;
class MapTest {
public:
    static bool testMap(string mapPath, string tilesetPath = "res/src/timemap.json");

};

#endif //ESTANOCANDASSAMY_MAPTEST_H
