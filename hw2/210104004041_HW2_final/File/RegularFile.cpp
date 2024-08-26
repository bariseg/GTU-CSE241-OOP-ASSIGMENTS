#include <iostream>
#include <stdexcept>

#include "RegularFile.h"

using OS::RegularFile;

RegularFile::RegularFile(const string& _name, const string& _path, Directory* supDir, string* _data): FileSystemEntity(_name,_path){
    this->supDirectory = supDir;
    this->data = _data;
    this->size = (_data == nullptr) ? 0 : _data->capacity();
}

RegularFile::RegularFile(const RegularFile* other,const string& _name,const string& _path, Directory* supDir): FileSystemEntity(_name,_path) {

    this->supDirectory = supDir;
    this->data = (other->getData() == nullptr) ? nullptr : new string(*(other->getData()));
    this->size = other->getSize();
}


RegularFile::~RegularFile(){
    delete data;
    data = nullptr;
}

string* RegularFile::getData()const{return this->data;}
int RegularFile::getSize()const{return this->size;}
void RegularFile::setData(string* _data){ this->data = _data;}

RegularFile::iterator RegularFile::begin() {return data->begin();}
RegularFile::iterator RegularFile::end() {return data->end();}
RegularFile::const_iterator RegularFile::begin() const {return data->begin();}
RegularFile::const_iterator RegularFile::end() const{ return data->end();}

void RegularFile::cat()const{

    if(this->data == nullptr) throw std::invalid_argument("No data : " + this->getName());
    for(const_iterator it = this->begin(); it != this->end(); it++){
        std::cout << *it;
    }
    std::cout << std::endl;
}

void RegularFile::save(ofstream* saveFile)const{

    (*saveFile) << "*F " 
                << this->getName() << " " 
                << this->getPath() << " "
                << this->getTimeCreated() << "\n";

    ofstream storage("harddisc/storage.txt",std::ios::app);

    storage << "*#start#* " << this->getPath() << "\n";
    storage << *(this->data) << "\n*#end#*\n";

    storage.close();

}

