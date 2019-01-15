/** 
 * @file User.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include "User.hpp"
using namespace std;
using namespace server;

User::User (int idPoke,int orientation, int currentLife, int x, int y) : idPoke(idPoke),orientation(orientation),currentLife(currentLife),x(x),y(y) {
    
}
