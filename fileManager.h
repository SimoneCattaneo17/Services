#include <iostream>
#include <Windows.h>
#include <winsvc.h>
#include <winnetwk.h>
#include <filesystem>
#include <string.h>
#include <string>
#include <fstream>
#include <list>

using namespace std;

int counter = 0;

//recursive - checks if new fileName already exists
void checkDuplicateFile(string &fileName, string extension) {
    string tmpFileName = fileName;
    string path = tmpFileName + '.' + extension;

    if(std::filesystem::exists(path)) {
        counter++;
        string path = tmpFileName + '_' + to_string(counter) + '.' + extension;
        if(std::filesystem::exists(path)) {
            tmpFileName = tmpFileName + '_' + to_string(counter);
            checkDuplicateFile(fileName, extension);
        }
        else {
            fileName = fileName + '_' + to_string(counter);
        }
    }
}

//renames file accordingly to checkDuplicatefile
void fileRenamer(string fileGiven) {
    string source;
    ifstream serverPath;
    serverPath.open("./serverPath.txt");
    getline(serverPath, source);
    serverPath.close();

    source = source + fileGiven;
    string delimiter = ".";
    string tmp[2];

    //split using . as a delimiter > add the date at the end of tmp[0] and then append tmp[1]
    //needs to work with xlsx, xls and xlsb when program is final
    
    //no string.split() in c++
    tmp[0] = source.substr(0, source.find(delimiter));
    source.erase(0, source.find(delimiter) + delimiter.length());
    tmp[1] = source;

    //source needs to be rebuilt
    source = tmp[0] + '.' + tmp[1];

    //today's date
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
    rename(source.c_str(), target.c_str());
}

//moves sourceFile in database folder on remote computer/server
void fileTransfer(string fileGiven) {
    fileRenamer(fileGiven);

    std::filesystem::path sourceFile = fileGiven;
    
    string targetParent;
    ifstream serverPath;
    serverPath.open("./serverPath.txt");
    getline(serverPath, targetParent);
    serverPath.close();
    
    auto target = targetParent / sourceFile.filename();

    try {
        //don't know if overwrite is good, probably not
        //anyway, before copying the file there is another function that changes its name so it should be ok
        //best thing would be to check existence and eventually case throw an error
        std::filesystem::copy_file(sourceFile, target, std::filesystem::copy_options::overwrite_existing);
    }
    catch(exception& e) {
        cout << e.what();
    }
}

//gets list of files used
list<string> inputFileName() {
    list<string> fileTargets;
    ifstream file;
    file.open("./targetFiles.txt");

    string tmp;
    while(std::getline(file, tmp)) {
        fileTargets.push_back(tmp);
    }

    return fileTargets;
}