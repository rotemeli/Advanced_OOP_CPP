#include "MyFolder.h"


MyFolder::MyFolder(std::string folderName) {
    name = std::move(folderName);
    pointer = "";
}

MyFolder::MyFolder(const MyFolder &rhs) {
    name = rhs.name;
    pointer = rhs.pointer;
    folders.clear();
    files.clear();

    for(const auto & file : rhs.files) {
        auto* f = new MyFile(*file);
        files.push_back(f);
    }

    for(auto folder : rhs.folders) {
        auto* f = new MyFolder(*folder);
        folders.push_back(f);
    }
}

MyFolder &MyFolder::operator=(const MyFolder &rhs) {
    if(this == &rhs) {
        return *this;
    }
    name = rhs.name;
    pointer = rhs.pointer;

    for(const auto & file : rhs.files) {
        delete file;
    }

    for(auto & folder : folders) {
        delete folder;
    }
    for(const auto & file : rhs.files) {
        auto* f = new MyFile(*file);
        files.push_back(f);
    }

    for(auto folder : rhs.folders) {
        auto* f = new MyFolder(*folder);
        folders.push_back(f);
    }
    return *this;
}

MyFolder::~MyFolder() {
    for(auto & file : files) {
        delete file;
    }
    for(auto & folder : folders) {
        delete folder;
    }
}

void MyFolder::mkdir(const std::string &folderName, const std::string &bel) {
    std::vector<MyFolder*>::const_iterator it;
    for(it = folders.begin(); it != folders.end(); it++) {
        if((*it)->name == folderName) {
            throw FileExists("The folder already exists!\n");
        }
    }
    auto* f = new MyFolder(folderName);
    folders.push_back(f);
}

bool MyFolder::chdir(const std::string &folderName) {
    for(auto & folder : folders) {
        if(folder->name == folderName) {
            return true;
        }
    }
    std::cerr << "ERROR: no such folder" << std::endl;
    return false;

}

void MyFolder::rmdir(const std::string &folderName) {
    for(auto it1 = folders.begin(); it1 != folders.end(); ++it1) {
        if((*it1)->name == folderName) {
            folders.erase(it1);
            delete *it1;
            break;
        }
    }
}

void MyFolder::ls(const std::string& folderName) {
    std::cout << folderName << ':' <<std::endl;
    for(auto folder : folders) {
        if(folderName.find(folder->name) != std::string::npos && folderName != folder->name) {
            std::string tmp = folder->name;
            tmp.erase(tmp.begin(), tmp.begin() + (int)folderName.length()+1);
            std::cout << tmp << std::endl;
        }
    }

    for(const auto & file : files) {
        if(folderName.find(file->getFileName()) != std::string::npos && folderName != file->getFileName()) {
            std::string tmp = file->getFileName();
            tmp.erase(tmp.begin(), tmp.begin() + (int)folderName.length()+1);
            std::cout << tmp << std::endl;
        }
    }
}

void MyFolder::lproot() {
    std::cout << "V/:" << std::endl;
    for(MyFile* file : files) {
        if(file->getBelongs() == "V/") {
            std::string tmp = file->getFileName();
            tmp.erase(tmp.begin(), tmp.begin() + 2);
            std::cout << tmp << " " << file->getRefCount() << std::endl;
        }
    }
    for(MyFolder* folder : folders) {
        std::cout << folder->name << ":" << std::endl;
        for(MyFile* file : files) {
            if(file->getBelongs() == folder->name) {
                std::string tmp = file->getFileName();
                tmp.erase(tmp.begin(), tmp.begin() + (int)folder->name.length());
                std::cout << tmp << " " << file->getRefCount() << std::endl;
            }
        }
    }
}

void MyFolder::pwd() {
    std::cout << pointer << std::endl;
}

std::vector<MyFile*> &MyFolder::getFiles() {
    return files;
}

const std::string &MyFolder::getPointer() const {
    return pointer;
}

void MyFolder::setPointer(const std::string &p) {
    MyFolder::pointer = p;
}
