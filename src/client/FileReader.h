//
// Created by paul on 22/09/18.
//

#ifndef ESTANOCANDASSAMY_FILEREADER_H
#define ESTANOCANDASSAMY_FILEREADER_H

#include <iostream>

using  namespace std;

class FileReader {
public:
    char* filePath;
    FileReader(char * filePath);
    bool printFile();
    string readFile();


};


#endif //ESTANOCANDASSAMY_FILEREADER_H
