#ifndef FILESYSTEMENTITY
#define FILESYSTEMENTITY

#include <string>
#include <time.h>
#include <fstream>

using std::string;
using std::ofstream;



namespace OS{
class Directory;//supDirectory is a common member,but it is a derived class. So, i had to declare Directory first

class FileSystemEntity{

public:

    FileSystemEntity(const string& _name, const string& _path): name(_name), path(_path) { this->setTimeCreated();}
    virtual ~FileSystemEntity(){}

    virtual string getTimeCreated()const;
    virtual string getName()const;
    virtual string getPath()const;
    virtual Directory* getSupDirectory()const;

    virtual void cat()const = 0;
    virtual void save(ofstream* saveFile)const = 0;


    void setTimeCreated();
    void changeTimeCreated(const string& timestr);
    void setName(const string& _name);
    void setPath(const string& _path);

protected:
    FileSystemEntity() = default;
    Directory* supDirectory;

private:
    string path;
    string name;
    string createdTime;
    
};
}






#endif  /* FILESYSTEMENTITY */