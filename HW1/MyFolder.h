#ifndef EX01_ADVCPP_MYFOLDER_H
#define EX01_ADVCPP_MYFOLDER_H

#include <iostream>
#include <vector>
#include <utility>
#include "MyFile.h"
#include "FileExists.h"

class MyFolder {
private:
    std::string name;
    std::vector<MyFile*> files;
    std::vector<MyFolder*> folders;
    std::string pointer;

public:
    /*
     * Constructors
     */
    MyFolder() = default;
    explicit MyFolder(std::string folderName);
    /*
     * Big three
     */
    MyFolder(const MyFolder& mf);
    MyFolder& operator=(const MyFolder& rhs);
    ~MyFolder();

    /*
     * Makes new folder
     */
    void mkdir(const std::string& folderName, const std::string &bel);

    /*
     * Changes the working folder to the given folder
     */
    bool chdir(const std::string& folderName);

    /*
     * Deletes given folder
     */
    void rmdir(const std::string& folderName);

    /*
     * Prints the files found in the given folder
     */
    void ls(const std::string& folderName);

    /*
     * Prints all the contents in the main folder
     */
    void lproot();

    /*
     * Prints the current working folder
     */
    void pwd();

    /*
     * Getters and setters
     */
    std::vector<MyFile*> &getFiles();

    const std::string &getPointer() const;

    void setPointer(const std::string &pointer);

};


#endif //EX01_ADVCPP_MYFOLDER_H
