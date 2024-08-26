#include <iostream>
#include <stdexcept>
#include <string>
#include <ctime>

#include "FileSystemEntity.h"

using OS::FileSystemEntity;
using OS::Directory;
using namespace std;

string FileSystemEntity::getTimeCreated()const{return createdTime;}

string FileSystemEntity::getName()const{return name;}

string FileSystemEntity::getPath()const{return path;}

Directory* FileSystemEntity::getSupDirectory()const{ return supDirectory; }

void FileSystemEntity::setTimeCreated(){

    time_t now = time(nullptr);
    tm* timeinfo = localtime(&now);
    char buffer[50];
    std::strftime(buffer, sizeof(buffer), "%b %d %H:%M", timeinfo);

    this->createdTime = buffer;
}
void FileSystemEntity::changeTimeCreated(const string& timestr){this->createdTime = timestr;}

void FileSystemEntity::setName(const string& _name){this->name = _name;}

void FileSystemEntity::setPath(const string& _path){this->path = _path;}
