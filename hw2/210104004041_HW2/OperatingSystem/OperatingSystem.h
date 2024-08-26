#ifndef OPERATINGSYSTEM_H
#define OPERATINGSYSTEM_H

#include <string>
#include <vector>
#include <map>
#include <functional>

#include "../Directory/Directory.h"


using std::map;
using std::function;
namespace OS{

class OperatingSystem{

public:
    OperatingSystem();
    ~OperatingSystem();

    string systemPrompt()const;
    const int getDiscStorage()const;
    const int getDiscStorageUsed()const;
    const string getCurrentPath()const;
    void updateDiscStorageUsed(const int difference);
    
    void promptCommand(const string& command);

    void ls()const;


private:

    int DiscStorageUsed;
    int DiscStorage;
    Directory* currDirectory;
    const Directory* baseDirectory;

};
//helper functions
void notYet();
string getNameFromPath(string path);

}



#endif /* OPERATINGSYSTEM_H */
