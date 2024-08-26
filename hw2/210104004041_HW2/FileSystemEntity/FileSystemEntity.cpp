#include <iostream>
#include <exception>
#include <string>
#include <ctime>
#include "FileSystemEntity.h"

#include "../Directory/Directory.h"

using OS::FileSystemEntity;
using OS::Directory;
using namespace std;

string FileSystemEntity::getTimeCreated()const{return createdTime;}

string FileSystemEntity::getName()const{return name;}

string FileSystemEntity::getPath()const{return path;}

FileSystemEntity* FileSystemEntity::getSupDirectory()const{return supDirectory;} 


void FileSystemEntity::setTimeCreated(){

    time_t now = time(nullptr);
    tm* timeinfo = localtime(&now);
    char buffer[50];
    std::strftime(buffer, sizeof(buffer), "%b %d %H:%M", timeinfo);

    this->createdTime = buffer;
}

void FileSystemEntity::setName(const string& _name){this->name = _name;}

void FileSystemEntity::setPath(const string& _path){this->path = _path;}

void FileSystemEntity::setSupDirectory(FileSystemEntity* sup){this->supDirectory = sup;}
