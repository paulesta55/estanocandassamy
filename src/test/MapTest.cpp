#include <utility>

//
// Created by paul on 16/10/18.
//

#include<iostream>

#include "MapTest.h"
using namespace std;

#include "CustomException.h"

bool MapTest ::testMap(string mapPath, string tilesetPath) {
    try{
        shared_ptr<state::Map> map;
        map.reset(new Map(std::move(mapPath)));
        cout << map->getWidth() << endl;
        return true;
    }
    catch(CustomException& e)
    {
        cerr << e.what() << endl;
        return false;
    }
    catch(ios_base::failure& failure)
    {
        cerr << failure.what() << endl;
        return false;
    }
    catch(runtime_error& runtimeError)
    {
        cerr << runtimeError.what() << endl;
        return false;
    }
    catch(exception& except)
    {
        cerr << except.what() << endl;
        return false;
    }
}

