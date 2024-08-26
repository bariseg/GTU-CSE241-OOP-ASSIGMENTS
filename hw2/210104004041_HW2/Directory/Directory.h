#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>
#include <vector>

#include "../FileSystemEntity/FileSystemEntity.h"

using std::string;
using std::vector;

namespace OS{

class Directory: public FileSystemEntity{
public:
    Directory(const string& __name, const string& _path);
    FileSystemEntity* findEntity(const string& entityName)const;

private:
    vector< FileSystemEntity* > subFileEntities;
};

}



#endif /* DIRECTORY_H */
