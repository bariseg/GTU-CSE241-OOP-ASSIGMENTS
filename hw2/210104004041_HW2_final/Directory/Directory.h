#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>
#include <vector>
#include <iterator>


#include "../FileSystemEntity/FileSystemEntity.h"
#include "../File/RegularFile.h"
#include "../File/SoftLinkedFile.h"


using std::string;
using std::vector;

namespace OS{

class Directory: public FileSystemEntity{
public:
    Directory(const string& _name, const string& _path, Directory* supDir = nullptr);
    Directory(const Directory* other, const string& _path, Directory* supDir); // for cp command
    ~Directory();
 
    vector< FileSystemEntity* > getSubFileEntities()const;

    Directory* mkdir(const string& name); 
    void ls(const bool isRecursive)const;
    // throws invalid_argument, in case of invalid targetName.
    // if the deleted item is a regularfile, then it is needed to check if there is any softlinkedfile that points to the deleted file
    // we use basedir for it. you can check the usage in 
    string rm(const string& targetName,int * deletedSize); 
    //void cp(const string& path, const string& name);
    void cat()const override;
    void save(ofstream* saveFile)const override;

    using iterator = vector<FileSystemEntity*>::iterator;
    using const_iterator = vector<FileSystemEntity*>::const_iterator; //to be able to use " this-> "
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    
    RegularFile* addRegularFile(const string& name,string* data = nullptr);
    SoftLinkedFile* addSoftLinkedFile(const string& name, RegularFile* sourceFile);
   
    //note : deep copies the data of the sourceFile. so even if the sourcefile deleted, it is not affected
    RegularFile* copyRegularFile(RegularFile* sourceFile,const string& name);
    SoftLinkedFile* copySoftLinkedFile(SoftLinkedFile* sourceSoftLinkedFile,const string& name);


    FileSystemEntity* findEntitybyPath(const string& entityPath)const;
    //if the destination file is removed, then all slfiles must be found and updated.
    void findSLFiles_by_DestFilePath_and_update_validities(const string& path)const;

private:
    vector< FileSystemEntity* > subFileEntities;
    //Directory* supDirectory;


};

}



#endif /* DIRECTORY_H */
