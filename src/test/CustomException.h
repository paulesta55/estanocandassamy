//
// Created by paul on 17/10/18.
//

#ifndef ESTANOCANDASSAMY_CUSTOMEXCEPTION_H
#define ESTANOCANDASSAMY_CUSTOMEXCEPTION_H

#include <iostream>
using namespace std;
class CustomException : public exception{
private:
    char * somedesc;
public:
    CustomException(char * somedesc)
    {
        this->somedesc = somedesc;
    }
    char* what()
    {
        return this->somedesc;
    }
};


#endif //ESTANOCANDASSAMY_CUSTOMEXCEPTION_H
