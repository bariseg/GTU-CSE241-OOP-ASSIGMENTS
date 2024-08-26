#ifndef FILE_H
#define FILE_H

#include <string>

#include "../FileSystemEntity/FileSystemEntity.h"
#include "../Directory/Directory.h"

using std::string;

namespace OS{

class File: public FileSystemEntity {

public:

private:
    
    int size;
};


}



#endif /* FILE_H */
