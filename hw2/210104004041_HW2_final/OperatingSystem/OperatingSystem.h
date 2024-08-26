#ifndef OPERATINGSYSTEM_H
#define OPERATINGSYSTEM_H

#include <string>
#include <vector>

#include "../Directory/Directory.h"


namespace OS{

class OperatingSystem{

public:
    OperatingSystem();
    ~OperatingSystem();

    void promptCommand(const string& command); //throws invalid_argument; sometimes itself, sometimes the functions it calls.
    string systemPrompt()const;
    
private:
    
    int DiscStorageUsed;
    const int DiscStorage;
    Directory* currDirectory;
    Directory* baseDirectory;
    vector<string> commands = {"ls","mkdir","rm","cp","link","cd","cat","exit","storage","commands"};

    const int getDiscStorage()const;
    const int getDiscStorageUsed()const;
    const string getCurrentPath()const;

    void storage()const;
    void listCommands()const;
    void cd(const string& name); //throws invalid_argument, in case of invalid name or path
    void link(const string& sourcePath, const string& newLinkedFileName);
    void cp(const string& path,const string& name);

    void updateDiscStorageUsed(const int difference);
    bool checkStorage(const int size)const;
    void fileStructureBuild();
    string* fileDataRead(const string& path);


    // saves all data to the appropriate files.
    void saveDisc();

    
}; //class OperatingSystem

//helper functions
namespace Helper{
void notYet();
string getNameFromPath(string& path);

void entityTimeAdjust(FileSystemEntity* entity, std::ifstream* structureFile);
string readTimeCreated(std::ifstream* structureFile);
string getParameter();

//very dangerous to use
//void inputStreamClear();
/*
void OS::inputStreamClear(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}*/
} //namespace Helper

} //namespace OS

#endif /* OPERATINGSYSTEM_H */