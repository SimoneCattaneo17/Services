#include <iostream>
#include <Windows.h>
#include <winsvc.h>
#include <winnetwk.h>
#include <filesystem>
#include <string.h>
#include <string>
#include <fstream>
#include <list>

#include "./serviceManager.h"
#include "./fileManager.h"

using namespace std;


int main(int argc, char *argv[]) {   
    if(argc == 2) {
        string fileGiven = argv[1];

        list<string> fileTargets = inputFileName();

        for(string fileName : fileTargets) {
            if(fileGiven.find(fileName) != string::npos) {
                fileGiven = fileName;
                break;
            }
        }

        fileTransfer(fileGiven);

        cout << "Press enter to exit..." << endl;
        cin.ignore();
        return 0;
    }
    else {
        cout << "No file given" << endl;
        cout << "Press enter to exit..." << endl;
        cin.ignore();
        return 0;
    }
}