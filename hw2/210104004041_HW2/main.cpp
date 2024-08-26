#include <iostream>
#include <exception>
#include <map>
#include "OperatingSystem/OperatingSystem.h"
#include "File/File.h"
#include "Directory/Directory.h"
#include "FileSystemEntity/FileSystemEntity.h"

using namespace std;
using namespace OS;

int main(){

    OS::OperatingSystem system;

    try{
        string input;
        
        do{
            input = system.systemPrompt(); //returns a valid input taken from the user
            system.promptCommand(input); //excutes the appropriate function, based on input
        } while (input != "exit");
    }
    catch(const exception& e){
        cout << "Unexpected exception occured:\n" ;
        cerr << e.what() << '\n';
        cout << "\nAbording the Operating System\n";
    }
    
    cout << "\n\nOperating System Shut Down Successfully\n";
    return 0;
}