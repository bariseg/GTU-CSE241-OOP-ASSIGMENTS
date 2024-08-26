#ifndef SOFTLINKEDFILE_H
#define SOFTLINKEDFILE_H

#include <string>

#include "../FileSystemEntity/FileSystemEntity.h"
#include "RegularFile.h"

using std::string;

namespace OS{

class SoftLinkedFile: public FileSystemEntity {

public:
    SoftLinkedFile(const string& name,const string& _path,RegularFile* _destFile,Directory* supDir);
    SoftLinkedFile(const SoftLinkedFile* other,const string& _name,const string& _path, Directory* supDir);

    /*
    string getTimeCreated()const override;
    string getName()const override;
    string getPath()const override;
    string* getData()const;
    */
    RegularFile* getDestFile()const;
    string getDestFilePath()const;
    bool isDestFileValid()const;
    void changeDestFileValidation(const bool validation);
    void setDestFile(RegularFile* destfile);

    void cat() const override; //destfile cat
    void save(ofstream* saveFile)const override;

    using iterator = RegularFile::iterator;
    using const_iterator = RegularFile::const_iterator; //to be able to use " this-> "
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

private:
    RegularFile* destFile;
    bool destValid;
    string destFilePath; //even if the destfile removed, slfile will remember its path
};


}



#endif /* SOFTLINKEDFILE_H */
