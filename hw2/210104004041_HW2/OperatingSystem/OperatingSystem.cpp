#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <map>
#include <vector>


#include "OperatingSystem.h"
#include "../Directory/Directory.h"

using namespace OS;
using namespace std;


void OS::notYet(){ cout << "not yet!!\n";}

string OS::getNameFromPath(string path){
    
    path.erase(path.length() -1 );
    size_t slashPos = path.find_last_of("/");
    if (slashPos == string::npos){
        return path;
    }
    return path.substr(slashPos,path.length() -1);
}

OperatingSystem::OperatingSystem(){

    ifstream storage;
    map< string, string> OS_options;
    
    storage.open("harddisc/OS_saves.txt");
    
    if (! storage.is_open()) throw runtime_error("File cannot be opened!");

    string key, value;
    while (!((storage >> key).eof() || (storage >> value).eof())){
        OS_options[key] = value;
    }
    storage.close();

    /* for test purposes
    map<string, string>::iterator it;
    for (it = OS_options.begin(); it != OS_options.end(); it++) {
        //cout << it->first << ":" << it->second << endl;
    }
    */
    
    this->currDirectory = new Directory(getNameFromPath(OS_options["CurrentDirectory"]),OS_options["CurrentDirectory"]);
    this->baseDirectory = new Directory("home","home/");
    this->DiscStorageUsed = stoi(OS_options["DiscStorageUsed"]);
    this->DiscStorage = stoi(OS_options["DiscStorage"]);
    



    cout << "Boot Successful\n" ;
    cout << "Shell Prompt | Current Path : " << getNameFromPath(OS_options["CurrentDirectory"])
            << "(" << currDirectory->getPath() << ") | "<< currDirectory->getTimeCreated() << endl;
}

OperatingSystem::~OperatingSystem(){
    //buraya deleteler gelecek!! gezerek uçtan köke doğru bütün entityleri silecek
}


const int OperatingSystem::getDiscStorage()const { return DiscStorage;}
const int OperatingSystem::getDiscStorageUsed()const { return DiscStorageUsed;}
const string OperatingSystem::getCurrentPath()const { return currDirectory->getPath();}

string OperatingSystem::systemPrompt()const{ //this function only takes the first word of the input
    
    string input;
    cout << getCurrentPath() <<"> ";
    cin >> input;

    return input;
}

void OperatingSystem::promptCommand(const string& command){

    if (command == "exit"){
        //intentionally left blank.
    }else if(command == "ls"){
        ls();
        notYet();
    }else if(command == "mkdir"){

        notYet();
    }else if(command == "rm"){
        notYet();
    }else if(command == "cp"){
        notYet();
    }else if(command == "link"){
        notYet();
    }else if(command == "cd"){
        notYet();
    }else if(command == "cat"){
        notYet();
    }else {
        throw invalid_argument("Invalid input reached promptCommand function");
    }
}

void OperatingSystem::ls()const{cout << "ls\n"; }
