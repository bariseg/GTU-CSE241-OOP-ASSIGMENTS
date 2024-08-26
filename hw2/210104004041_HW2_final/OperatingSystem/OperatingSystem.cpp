#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <map>
#include <stack>
#include <vector>
#include <iterator>
#include <sstream>
//#include <limits>

#include "OperatingSystem.h"
#include "../File/SoftLinkedFile.h"

#define STRUCTUREFILE "harddisc/fileStructure.txt"
#define STORAGEFILE "harddisc/storage.txt"


using namespace OS;
using namespace std;


void OS::Helper::notYet(){ cout << "not yet!!\n";}

string OS::Helper::getNameFromPath(string& path){
    
    path.erase(path.length() -1 );
    size_t slashPos = path.find_last_of("/");
    if (slashPos == string::npos){
        return path;
    }
    return path.substr(slashPos,path.length() -1);
}

string OS::Helper::getParameter(){
    string parameter;
    cin >> parameter;
    return parameter;
}
//reads the time from the file and uses setTimeCreated() of FileSystemEntity class
void OS::Helper::entityTimeAdjust(FileSystemEntity* entity, std::ifstream* structureFile){
    string timeofEntity = readTimeCreated(structureFile);
    entity->changeTimeCreated(timeofEntity);
}

string OS::Helper::readTimeCreated(std::ifstream* structureFile){

    string content;
    string timestr;
    *structureFile >> content; // Jan
    timestr = content;
    *structureFile >> content; // 07
    timestr += " " + content;
    *structureFile >> content; // 19:46
    timestr += " " + content;

    return timestr;
}


void OperatingSystem::fileStructureBuild(){

    ifstream structureFile(STRUCTUREFILE);
    

    if (structureFile.is_open()){
    
        vector<Directory*> SLfiles_to_be_linked_supDirs;
        vector< string> SLfiles_to_be_linked_names;
        vector< string > SLfiles_to_be_linked_times;
        vector< string > SLfiles_to_be_linked_destFilePaths;

        stack<Directory*> DirectoryStack; //helps followwing the directory hierarchy
        
        string content,baseName,basePath;

        structureFile >> content ;// *
        structureFile >> baseName;// home
        structureFile >> basePath;// home/
    
        this->baseDirectory = new Directory(baseName,basePath,nullptr) ;
        Helper::entityTimeAdjust(baseDirectory,&structureFile);
        DirectoryStack.push(baseDirectory);
        

        while (! (structureFile >> content).eof()){
            
            if(content == "*"){ // a new directory

                string dirName,dirPath;
                structureFile >> dirName;
                structureFile >> dirPath;
                Directory* newdir = DirectoryStack.top()->mkdir(dirName);
                Helper::entityTimeAdjust(newdir,&structureFile);

                DirectoryStack.push(newdir);
                
            }else if(content == "*F"){ // a new regularfile

                string fileName,filePath;
                structureFile >> fileName;
                structureFile >> filePath;
                string* data = fileDataRead(filePath);

                RegularFile* newfile = DirectoryStack.top()->addRegularFile(fileName,data);
                Helper::entityTimeAdjust(newfile,&structureFile);

                this->updateDiscStorageUsed(data->capacity());

            }else if(content == "*S"){
                // a new softlinkedfile will be created at the end of the boot.
                // just because, softlinkedfiles' destFiles are must exists before the softlinkedfile created
                string SLFileName, SLFilePath, SFLSourceFilePath;
                structureFile >> SLFileName;
                structureFile >> SLFilePath;
                structureFile >> SFLSourceFilePath;

                SLfiles_to_be_linked_names.push_back(SLFileName);
                SLfiles_to_be_linked_supDirs.push_back(DirectoryStack.top());
                SLfiles_to_be_linked_times.push_back(Helper::readTimeCreated(&structureFile));
                SLfiles_to_be_linked_destFilePaths.push_back(SFLSourceFilePath);

            }else if(content ==  "**"){ //end of a directory
                structureFile >> content; //clear the name of the director that ends
                DirectoryStack.pop();
            }
        }
        structureFile.close();
        
        for (int i = 0; i < SLfiles_to_be_linked_names.size(); i++){
            string SLFileName = SLfiles_to_be_linked_names[i];
            Directory* supDir = SLfiles_to_be_linked_supDirs[i];
            string timeCreated = SLfiles_to_be_linked_times[i];
            string destFilePath = SLfiles_to_be_linked_destFilePaths[i];

            RegularFile * destFile;
            if(destFilePath != "removed"){
                destFile = dynamic_cast<RegularFile*>(baseDirectory->findEntitybyPath(destFilePath));
            }else{
                destFile = nullptr;
            }

            SoftLinkedFile* newSLF = supDir->addSoftLinkedFile(SLFileName,destFile);
            newSLF->changeTimeCreated(timeCreated);
        }
        
    }else {throw runtime_error("fileStructure.txt cannot be opened! Boot Failed");}
}

string* OperatingSystem::fileDataRead(const string& path){

    ifstream storage(STORAGEFILE);

    if (storage.is_open()){
        
        //no need to delete this data. At the end this memory space will be pointed by a regularfile as its data
        string* data = new string();

        const string startlabel = "*#start#*";
        const string stoplabel = "*#end#*";
        string content;

        while (! (storage >> content).eof()){
            
            if (content == startlabel){

                getline(storage,content);
                if(content == " " + path){
                    while (content != stoplabel){
                        getline(storage,content);

                        if(content != stoplabel) data->append(content + "\n");
                    }
                    data->erase(data->length() -1 );//needed to delete the last \n char which corrupts the save
                    return data; //the function ends here. the data has been found, and read.
                }else{
                    do{ //just skipping to the next file data
                        getline(storage,content);
                    } while (content != stoplabel);  
                }
            }
        }
        throw runtime_error("File data can not found in storage.txt! Boot Failed");

        storage.close();
    }else{throw runtime_error("storage.txt cannot be opened! Boot Failed");}
    

}

OperatingSystem::OperatingSystem(): DiscStorage(1048576),DiscStorageUsed(0){

    this->fileStructureBuild();

    this->currDirectory = this->baseDirectory;

    cout << "Boot Successful\n" ;
    cout << "Reading the 'readme' files is highly recommended.\n" <<
            "You may want to start with 'commands' command.\n\n";

    cout << "< < Shell Prompt > >\n" ;
}

OperatingSystem::~OperatingSystem(){
    delete baseDirectory;
    //~Directory() has everything to delete all subFileElements. each directory will call its own sub-directories destructors with deletes. 
}

void OperatingSystem::saveDisc(){

    ofstream storagetxt(STORAGEFILE,std::ios::trunc);
    if(storagetxt.is_open()){

        //storage will reset,and regularfiles will append their data while building the filestructure.
        storagetxt.close(); //the file opened clean and closed with no modifications

        //saving filestructure
        ofstream savefile(STRUCTUREFILE);

        if(savefile.is_open()){
            //filesystementity::save() is pure virtual, it works recursively to save everything 
            baseDirectory->save(&savefile);

            savefile.close();
        }else{
            cout << "Opening 'fileStructure.txt' file failed. No changes were saved\n";
        }

    }else {
        cout << "Opening 'storage.txt' file failed. No changes were saved\n";
    }



    
}

const int OperatingSystem::getDiscStorage()const { return DiscStorage;}
const int OperatingSystem::getDiscStorageUsed()const { return DiscStorageUsed;}
const string OperatingSystem::getCurrentPath()const { return currDirectory->getPath();}

void OperatingSystem::updateDiscStorageUsed(const int difference){ this->DiscStorageUsed += difference; }

bool OperatingSystem::checkStorage(const int size)const{return (this->DiscStorageUsed + size) <= this->DiscStorage ;}

string OperatingSystem::systemPrompt()const{ //this function only takes the first word of the input
    
    string input;
    
    cout << this->getCurrentPath() << "> ";
    cin >> input;
    
    for(const string& command : this->commands){
        if (command == input) return input;
    }
    throw invalid_argument("Invalid command : " + input);
}

void OperatingSystem::promptCommand(const string& command){

    if (command == "exit"){
        
        cout << "Changes are being saved\n";
        this->saveDisc();        

    }else if(command == "ls"){
        
        string parameter;
        getline(cin,parameter); // to check if -R is written

        if(parameter.empty()){ // no parameter ls
            currDirectory->ls(false);
        }else if(parameter == " -R"){
            currDirectory->ls(true);
        }else{
            throw invalid_argument("Invalid parameter :" + parameter);
        }

    }else if(command == "mkdir"){
        
        Directory* newdir = currDirectory->mkdir(Helper::getParameter());

    }else if(command == "rm"){

        int deletedSize = 0;
        string result = currDirectory->rm(Helper::getParameter(),&deletedSize);
        this->updateDiscStorageUsed(-deletedSize);

        if(result != "complete"){ 
            baseDirectory->findSLFiles_by_DestFilePath_and_update_validities(result);
        }

    }else if(command == "cp"){

        string path = Helper::getParameter();
        string name = Helper::getParameter();

        this->cp(path,name);

    }else if(command == "link"){

        string path = Helper::getParameter();
        string name = Helper::getParameter();

        this->link(path,name);

    }else if(command == "cd"){

        this->cd(Helper::getParameter());

    }else if(command == "cat"){

        currDirectory->cat();

    }else if(command == "storage"){

        this->storage();

    }else if(command == "commands"){

        this->listCommands();

    }else {
        throw invalid_argument("Invalid input reached promptCommand function, which is unexpected");
    }
}

void OperatingSystem::cd(const string& name){

    if (name == "." && currDirectory->getSupDirectory() != nullptr){
        currDirectory = currDirectory->getSupDirectory();
    }else if(name == ".." && currDirectory != baseDirectory){
        currDirectory = baseDirectory;
    }else if(name.find('/') != string::npos) { // looks for if the argument 'name' has '/' in it. if so it is given a path
        //name is a directory path
        //iterating all directories in the harddisc of my operating system to find the corresponding directory,if exists.
        FileSystemEntity* searchResult = nullptr;
        searchResult = baseDirectory->findEntitybyPath(name);
        Directory* resultDir = dynamic_cast<Directory*>(searchResult);
        if(searchResult != nullptr && resultDir != nullptr){
            currDirectory = resultDir;
        }else {
            //no dir found with the path given
            throw invalid_argument("Invalid Directory : " + name);
        } 

    }else { //name is a directory name.So, it must be one of the sub-directories
        Directory* temp;
        for(FileSystemEntity* subDir : currDirectory->getSubFileEntities() ){
            temp = dynamic_cast<Directory*>(subDir);
            if(temp != nullptr && temp->getName() == name){
                currDirectory = temp;
                return; //the target found,so the function must end with no exception throwing
            }
        }
        //no dir found with the name given
        throw invalid_argument("Invalid Name : " + name);
    }        
}

void OperatingSystem::link(const string& sourcePath, const string& newLinkedFileName ){

    FileSystemEntity* searchResult = nullptr;
    searchResult = baseDirectory->findEntitybyPath(sourcePath);
    RegularFile* resultFile = dynamic_cast<RegularFile*>(searchResult);
    if (searchResult != nullptr && resultFile != nullptr){ //found sourcefile
        currDirectory->addSoftLinkedFile(newLinkedFileName,resultFile);
    }else{
        throw invalid_argument("Invalid sourcefile : " + sourcePath);
    }
}

void OperatingSystem::cp(const string& path,const string& name) {

    //first we check if there already exists a file with name "name" in the current directory
    for(const FileSystemEntity* subEntity : currDirectory->getSubFileEntities() ){
        if(subEntity->getName() == name) throw invalid_argument("There already exists an entity with name : " + name);
    }
    
    if (path[path.length() - 1 ] == '/' ){ //that means the path belongs to a filesystementity that inside the OS being developed by me
        
        FileSystemEntity* searchResult = baseDirectory->findEntitybyPath(path);
        if(searchResult != nullptr){

            if (dynamic_cast<Directory* >(searchResult)){
                //Directory* tempDirectory = dynamic_cast<Directory* >(searchResult);

                cout << "can not copy directories yet\n";
                
            }else if (dynamic_cast<RegularFile* >(searchResult)){
                RegularFile* tempRegularFile = dynamic_cast<RegularFile* >(searchResult);

                if(this->checkStorage(tempRegularFile->getSize())){
                    currDirectory->copyRegularFile(tempRegularFile, name);
                    this->updateDiscStorageUsed(tempRegularFile->getSize());
                }else {
                    throw invalid_argument("Insufficient space to complete the copy operation");
                }

            }else {
                SoftLinkedFile* tempSoftLinkedFile = dynamic_cast<SoftLinkedFile* >(searchResult);
                currDirectory->copySoftLinkedFile(tempSoftLinkedFile, name);
            }
            
        }else{
            throw invalid_argument("Source file can not be found :(belongs this OS) " + path);
        }

    }else { //means the path belongs to a file(assumed regularfile) that is from the operating system of the device(UBUNTU).

        ifstream sourceFile(path);
        if(sourceFile.is_open()){

            stringstream buffer;
            buffer << sourceFile.rdbuf();
            sourceFile.close();

            string* data = new string(std::move(buffer.str()));

            if(checkStorage(data->capacity())){
                currDirectory->addRegularFile(name,data);
                this->updateDiscStorageUsed(data->capacity());
            }else{
                throw invalid_argument("Insufficient space to complete the copy operation");
            }

        }else {
            throw invalid_argument("SourceFile is not valid, or can not open :(UBUNTU)" + path);
        }
    }
}

void OperatingSystem::storage()const{
    cout << "Used Memory    : "<< getDiscStorageUsed() << " Bytes"<< endl;
    cout << "memory Remain  : "<< getDiscStorage() - getDiscStorageUsed() << " Bytes"<< endl;
    cout << "Memory Space   : "<< getDiscStorage() << " Bytes"<< endl;
}

void OperatingSystem::listCommands()const{
    for(const string& command : commands) cout << command << "  ";
    cout << endl;
}

