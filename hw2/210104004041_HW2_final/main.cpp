#include <iostream>
#include <stdexcept>
#include <map>

#include "OperatingSystem/OperatingSystem.h"


using namespace std;
using namespace OS;

#define INVALID "invalid"


int main(){

    OS::OperatingSystem system; //if boot fails, throws exception which is never caught. Program ends.

    string input;
    do{
        do{
            try{
                input = system.systemPrompt(); //returns input taken from the user.
            } catch(const std::exception& e){
                std::cerr << e.what() << '\n';
                input = INVALID;
            }
        } while (input == INVALID);

        try{
            system.promptCommand(input); //executes the appropriate function, based on input
        } catch(const std::exception& e){
            cout << "\aError:\n" ;
            cerr << e.what() << '\n';
        }

    } while (input != "exit");

    
    cout << "\n\nOperating System Shut Down Successfully\n";
    return 0;
}