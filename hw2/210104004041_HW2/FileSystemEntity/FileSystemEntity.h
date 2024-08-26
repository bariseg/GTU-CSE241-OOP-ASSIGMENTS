#ifndef FILESYSTEMENTITY
#define FILESYSTEMENTITY

#include <string>
#include <time.h>


using std::string;


namespace OS{

class FileSystemEntity{

public:

    ~FileSystemEntity(){}

    virtual string getTimeCreated()const;
    virtual string getName()const;
    virtual string getPath()const;
    virtual FileSystemEntity* getSupDirectory()const = 0;

    void setTimeCreated();
    void setName(const string& _name);
    void setPath(const string& _path);
    void setSupDirectory(FileSystemEntity* supDir);
    

private:
    FileSystemEntity* supDirectory;
    string path;
    string name;
    string createdTime;
};
}






#endif  /* FILESYSTEMENTITY */