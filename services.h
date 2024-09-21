#include <iostream>
#include <Windows.h>
#include <winsvc.h>
#include <filesystem>
#include <string.h>
#include <string>
#include <fstream>

using namespace std;

int counter = 0;

//local computer, all access - test purpose
SC_HANDLE connectLocalComputer(SC_HANDLE schSCManager) {

    schSCManager = OpenSCManager( 
        NULL,
        NULL,
        SC_MANAGER_ALL_ACCESS
    );

    return schSCManager;
}

void checkDuplicateFile(string &fileName, string extension) {
    string tmpFileName = fileName;
    string path = tmpFileName + '.' + extension;
/*
    cout << "counter: " << to_string(counter) << endl;
    cout << "Path: " << path << endl;
*/
    if(std::filesystem::exists(path)) {
        counter++;
        string path = tmpFileName + '_' + to_string(counter) + '.' + extension;
        if(std::filesystem::exists(path)) {
            tmpFileName = tmpFileName + '_' + to_string(counter);
            //cout << "FileName: " << tmpFileName << endl;
            checkDuplicateFile(fileName, extension);
        }
        else {
            fileName = fileName + '_' + to_string(counter);
            //cout << "File renamed to: " << fileName << endl;
        }
    }
}

void fileRenamer() {
    string source = "//HOL-PCL-996/c$/Database/Unes Scato Ord.xlsx"; //change this to test the program with other computers
    //string source = "Database/Unes Scato Ord.xlsx";        //path not final, just for test
    string delimiter = ".";
    string tmp[2];

    //split using . as a delimiter > add the date at the end of [0] and then append [1]
    //needs to work with xlsx, xls and xlsb when program is final
    
    //no string.split() in c++
    tmp[0] = source.substr(0, source.find(delimiter));
    source.erase(0, source.find(delimiter) + delimiter.length());
    tmp[1] = source;

    //source needs to be rebuilt
    source = tmp[0] + '.' + tmp[1];

    //date
    time_t t = time(nullptr);
    tm *const pTInfo = localtime(&t);

    tmp[0] = tmp[0] + to_string(pTInfo->tm_year + 1900);    //adds year
    if(pTInfo->tm_mon < 10) {
        tmp[0] = tmp[0] + '0';
    }
    tmp[0] = tmp[0] + to_string(pTInfo->tm_mon + 1);        //adds month
    if(pTInfo->tm_mday < 10) {
        tmp[0] = tmp[0] + '0';
    }
    tmp[0] = tmp[0] + to_string(pTInfo->tm_mday);           //adds day

    //recursive, checks how many files have been updated today and changes the file name accordingly
    checkDuplicateFile(tmp[0], tmp[1]);

    string target = tmp[0] + '.' + tmp[1];
    //cout << "target: " << target << endl;
    rename(source.c_str(), target.c_str());
}

//as of now moves a file from a local folder to another local folder - trying out with another computer
void fileTransfer() {
    fileRenamer();

    std::filesystem::path sourceFile = "Unes Scato Ord.xlsx";     //to be changed, not final; source will be gathered from download
    std::filesystem::path targetParent = "//HOL-PCL-996/c$/Database";            //to be changed, not final; target will be on Server
    auto target = targetParent / sourceFile.filename();
/*
    cout << sourceFile;
    cout << '\n';
    cout << target;
    cout << '\n';
*/
    try {
        //don't know if overwrite is good, probably not
        //anyway, before copying the file there is another function that changes its name so it should be ok
        //best thing would be to check existence and in case throw an error
        std::filesystem::copy_file(sourceFile, target, std::filesystem::copy_options::overwrite_existing);
    }
    catch(exception& e) {
        cout << e.what();
    }
}