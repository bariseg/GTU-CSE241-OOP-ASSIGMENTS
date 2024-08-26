#include <iostream>
#include <string>
#include "Directory.h"


using OS::Directory;
using OS::FileSystemEntity;
using std::string;

Directory::Directory(const string& _name, const string& _path){
    this->setName(_name);
    this->setPath(_path);
    this->setTimeCreated();
}

FileSystemEntity* Directory::findEntity(const string& entityName)const{

    for (const auto& entity : subFileEntities){
        if (entity->getName() == entityName) {return entity;}

        Directory* tempEntity = dynamic_cast<Directory*>(entity);
        if (tempEntity != nullptr){

            tempEntity->findEntity(entityName);
            if (tempEntity != nullptr) {
                return tempEntity;
            }
        }
    }
    //cant find
    return nullptr;
}


