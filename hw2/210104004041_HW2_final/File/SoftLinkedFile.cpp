#include <iostream>
#include <string>
#include <stdexcept>

#include "SoftLinkedFile.h"

using namespace OS;

SoftLinkedFile::SoftLinkedFile(const string& name,const string& _path,RegularFile* _destFile, Directory* supDir):
    FileSystemEntity(name,_path),
    destFile(_destFile),
    destFilePath((_destFile == nullptr) ?  "removed" : _destFile->getPath()){
    this->supDirectory = supDir;
    this->destValid = (_destFile == nullptr) ? false : true ;
}

SoftLinkedFile::SoftLinkedFile(const SoftLinkedFile* other,const string& _name,const string& _path, Directory* supDir):
    FileSystemEntity(_name,_path),
    destFilePath(other->destFilePath){
    this->supDirectory = supDir;
    if(other->isDestFileValid()){
        this->destFile = other->destFile;
        this->destValid = true;
    }else{
        this->destFile = nullptr;
        this->destValid = false;
    }
}

bool SoftLinkedFile::isDestFileValid()const{
    return this->destValid;
}

void SoftLinkedFile::changeDestFileValidation(const bool validation){
    this->destValid = validation;
    this->destFilePath = "removed";
}

void SoftLinkedFile::setDestFile(RegularFile* destfile){
    this->destFile = destfile;
}

RegularFile* SoftLinkedFile::getDestFile()const{
    if(this->destValid ) return destFile;
    else throw std::invalid_argument("The destination file has been deleted or corrupted");
}

string SoftLinkedFile::getDestFilePath()const{
    return destFilePath;
}

void SoftLinkedFile::cat() const {
    if(this->destValid) destFile->cat();
    else throw std::invalid_argument("The destination file has been deleted or corrupted");
}

void SoftLinkedFile::save(ofstream* saveFile)const{

    (*saveFile) << "*S "
                << this->getName() << " "
                << this->getPath() << " ";

    (*saveFile) << this->destFilePath << " ";
    (*saveFile) << this->getTimeCreated() << "\n";

}

SoftLinkedFile::iterator SoftLinkedFile::begin(){return destFile->begin();}
SoftLinkedFile::iterator SoftLinkedFile::end(){return destFile->end();}
SoftLinkedFile::const_iterator SoftLinkedFile::begin() const{return destFile->begin();}
SoftLinkedFile::const_iterator SoftLinkedFile::end() const{return destFile->end();}
