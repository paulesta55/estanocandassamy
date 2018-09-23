//
// Created by paul on 22/09/18.
//

#include <fstream>
#include "FileReader.h"

string FileReader::readFile() {
    string line;
    ifstream myfile (this->filePath);
    string lines;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {

            lines += '\n';
        }
        myfile.close();
        return lines;
    }

    else cout << "Unable to open file";
    return "error";
}

bool FileReader ::printFile() {
    string line;
    ifstream myfile (this->filePath);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            cout << line << '\n';
        }
        myfile.close();
    }

    else cout << "Unable to open file";
}

FileReader::FileReader(char *filePath): filePath(filePath) {}