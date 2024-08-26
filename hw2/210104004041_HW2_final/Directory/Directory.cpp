#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

#include "Directory.h"
#include "../File/SoftLinkedFile.h"

using namespace OS;
using std::string;
using std::endl;
using std::cout;
using std::find;
using std::invalid_argument;
using std::ifstream;

Directory::Directory(const string& _name, const string& _path, Directory* supDir): FileSystemEntity(_name,_path){
    this->supDirectory = supDir;
}

Directory::Directory(const Directory* other, const string& _path, Directory* supDir): FileSystemEntity(other->getName(),_path) {
    this->supDirectory = supDir;

}


Directory::~Directory(){
    for(auto entity : subFileEntities) delete entity;
}


FileSystemEntity* Directory::findEntitybyPath(const string& entityPath) const {
    for (const auto& entity : subFileEntities) {
        if (entity->getPath() == entityPath) {
            return entity;
        }

        Directory* tempEntity = dynamic_cast<Directory*>(entity);
        if (tempEntity != nullptr) {
            FileSystemEntity* foundEntity = tempEntity->findEntitybyPath(entityPath);
            if (foundEntity != nullptr) {
                return foundEntity;
            }
        }
    }
    // Can't find
    return nullptr;
}

void Directory::findSLFiles_by_DestFilePath_and_update_validities(const string& path)const{
    
    for (FileSystemEntity* subEntity : subFileEntities){
        SoftLinkedFile* tempSLFile = dynamic_cast<SoftLinkedFile* >(subEntity);
        
        if(tempSLFile != nullptr && (tempSLFile->getDestFilePath() == path) ){
            
            tempSLFile->changeDestFileValidation(false);
        }else{
            Directory* tempDir = dynamic_cast<Directory*>(subEntity);
            if(tempDir != nullptr) tempDir->findSLFiles_by_DestFilePath_and_update_validities(path);
        }
    }
}

RegularFile* Directory::addRegularFile(const string& name, string* data){
    RegularFile* newfile = new RegularFile(name, this->getPath() + name + "/" , this, data);
    subFileEntities.push_back(newfile);
    return newfile;
}

RegularFile* Directory::copyRegularFile(RegularFile* sourceFile,const string& name){
    RegularFile* newfile = new RegularFile(sourceFile,name, this->getPath() + name + "/",this);
    subFileEntities.push_back(newfile);
    return newfile;
}

SoftLinkedFile* Directory::copySoftLinkedFile(SoftLinkedFile* sourceSoftLinkedFile,const string& name){

    SoftLinkedFile * newfile = new SoftLinkedFile(sourceSoftLinkedFile,name, this->getPath() + name + "/",this);
    subFileEntities.push_back(newfile);
    return newfile;
}

SoftLinkedFile* Directory::addSoftLinkedFile(const string& name, RegularFile* sourceFile){
    SoftLinkedFile* newSLFile = new SoftLinkedFile(name, this->getPath() + name + "/", sourceFile,this);
    subFileEntities.push_back(newSLFile);
    return newSLFile;
}

Directory* Directory::mkdir(const string& name){

    for(FileSystemEntity* subEntity : this->subFileEntities){
        if (subEntity->getName() == name || name.find('/') != string::npos){
            throw invalid_argument("Invalid directory name (must be unique, and not include '/'): " + name);
        }
    }

    Directory* newDir = new Directory(name, this->getPath() + name + "/", this);
    subFileEntities.push_back(newDir);
    return newDir;
}

void Directory::ls(const bool isRecursive)const{ 
    
    if(isRecursive){
        if(! this->subFileEntities.empty())cout << this->getName() << "("<< this->getPath() << "):" << endl;
        this->ls(false);
        FileSystemEntity* entity;
        Directory* temp;
        for(auto it = this->begin(); it != this->end(); it++ ){
            entity = *it;
            temp = dynamic_cast<Directory*>(entity);
            if(temp!= nullptr){   
                temp->ls(true);   
            }
        }

    }else{ //base of the recursion, also no-parameter ls command
        FileSystemEntity* entity;
        char symbol;
        for(auto it = this->begin(); it != this->end(); it++ ){
            entity = *it;

            if (dynamic_cast<Directory*>(entity)){
                symbol = 'D';
            }else if (dynamic_cast<RegularFile*>(entity)){
                symbol = 'F';
            }else{
                symbol = 'S';
            }
            cout << symbol << ' ';
            cout << entity->getName() << "\t" << entity->getTimeCreated() << "\t";
            if(symbol == 'F') cout << dynamic_cast<RegularFile*>(entity)->getSize() << " bytes\t";
            if(symbol == 'S') cout << dynamic_cast<SoftLinkedFile*>(entity)->getDestFilePath();
            cout << endl; 
        }
    }
}

string Directory::rm(const string& targetName, int * deletedSize){

    FileSystemEntity* tempEntity;
    Directory* tempDir;

    for (iterator it= this->begin(); it != this->end(); it++){
        tempEntity = *it;
        if (tempEntity->getName() == targetName){ //we found the target
            
            tempDir = dynamic_cast<Directory* >(tempEntity);
            if (tempDir != nullptr){ //if the target is a directory, it must be check if it is empty
                if (tempDir->getSubFileEntities().empty()){
                    this->subFileEntities.erase(it);// the target is deleted from the vector subFileEntities of the currDirectory(this)
                    delete tempDir;
                    return "complete"; //the target has been deleted, so the function should end with no exception
                }
            }else{ //target is not a directory
                this->subFileEntities.erase(it);// the target is deleted from the vector subFileEntities of the currDirectory(this)

                RegularFile* tempRegFile = dynamic_cast< RegularFile* >(tempEntity);
                if(tempRegFile != nullptr){ // if the object to be deleted is a regularfile
                    *deletedSize = tempRegFile->getData()->capacity(); //to update storage usage
                    string path = tempRegFile->getPath();
                    
                    delete tempRegFile;
                    return path;
                }

                delete tempEntity; // FileSystemEntity class has virtual destructor, so it is possible to use polymorphic deletion.
                return "complete"; //the target has been deleted, so the function should end with no exception
            }
        }
    }
    throw invalid_argument("Invalid parameter : " + targetName);
}

void Directory::cat()const {

    string name;
    std::cin >> name;

    for(const FileSystemEntity* subEntity : this->subFileEntities){
        if(subEntity->getName() == name){
            subEntity->cat();
            return;
        }
    }
    throw invalid_argument("Can not found file : " + name);
}

void Directory::save(ofstream* saveFile)const{

    (*saveFile) << "* " 
                << this->getName() << " "
                << this->getPath() << " " 
                << this->getTimeCreated() <<"\n";

    for(auto subEntity: subFileEntities) subEntity->save(saveFile);

    (*saveFile) << "** " << this->getName() << "\n" ;

}

vector< FileSystemEntity* > Directory::getSubFileEntities()const{return subFileEntities;}

Directory::iterator Directory::begin(){return subFileEntities.begin(); }
Directory::iterator Directory::end(){return subFileEntities.end(); }

Directory::const_iterator Directory::begin() const { return subFileEntities.begin(); }
Directory::const_iterator Directory::end() const { return subFileEntities.end(); }

