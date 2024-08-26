#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>
#include <iterator>

#include "../FileSystemEntity/FileSystemEntity.h"
//#include "../Directory/Directory.h"



using std::string;

namespace OS{

class RegularFile: public FileSystemEntity {

public:
    RegularFile(const string& _name, const string& _path, Directory* supDir, string* _data = nullptr);
    RegularFile(const RegularFile* other,const string& _name,const string& _path, Directory* supDir);
    ~RegularFile();

    string* getData()const;
    int getSize()const;
    // dynamically allocated string pointer required
    void setData(string* data);

    void cat() const override;
    void save(ofstream* saveFile)const override;

    using iterator = string::iterator;
    using const_iterator = string::const_iterator; //to be able to use " this-> "
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;



private:
    //Directory* supDirectory;
    int size;
    string* data;
};


}



#endif /* FILE_H */

