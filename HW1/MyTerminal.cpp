#include "MyTerminal.h"


void MyTerminal::init() {
    auto* mainFolder = new MyFolder("V/");
    mainFolder->setPointer("V/");
    std::stringstream ss;
    std::string op, fName;
    int pos;
    while(true) {
        std::getline(std::cin, op);
        ss.clear();
        ss.str(op);
        ss >> op;
        if(op == "read") {
            ss >> fName; ss >> pos;
            MyFile* f = helper(fName, mainFolder);
            if(!f) {
                std::cout << "ERROR: no such filename" << std::endl;
                continue;
            }
            std::cout << (*f)[pos] << std::endl;
        }

        else if(op == "write") {
            char c;
            ss >> fName; ss >> pos; ss >> c;
            MyFile* f = helper(fName, mainFolder);
            if(!f) {
                std::cout << "ERROR: no such filename" << std::endl;
                continue;
            }
            (*f)[pos] = c;
        }

        else if(op == "touch") {
            ss >> fName;
            MyFile* f = helper(fName, mainFolder);
            if(!f) {
                auto* file = new MyFile();
                file->touch(fName);
                file->setBelongs(mainFolder->getPointer());
                mainFolder->getFiles().push_back(file);
            }
            else {
                f->touch(fName);
                f->setBelongs(mainFolder->getPointer());
            }
        }

        else if(op == "copy") {
            ss >> fName;
            bool flag = false;
            for(auto it = mainFolder->getFiles().begin(); it != mainFolder->getFiles().end(); ++it) {
                if((*it)->getFileName() == fName) {
                    flag = true;
                    break;
                }
            }
            if(!flag) {
                std::string tmp = mainFolder->getPointer() + fName;
                fName = tmp;
            }
            std::string target; ss >> target;
            MyFile* f = helper(fName, mainFolder);
            if(!f) {
                auto* newFile = new MyFile();
                newFile->touch(fName);
                newFile->setBelongs(mainFolder->getPointer());
                f = newFile;
                mainFolder->getFiles().push_back(f);
            }
            MyFile* f2 = helper(target, mainFolder);
            if(!f2) {
                auto* newFile = new MyFile();
                newFile->touch(target);
                newFile->setBelongs(mainFolder->getPointer());
                f2 = newFile;
                mainFolder->getFiles().push_back(f2);
            }
            f->copy(*f2);
        }

        else if(op == "remove") {
            ss >> fName;
            std::vector<MyFile*> v = mainFolder->getFiles();
            for (auto it = v.begin(); it != v.end();++it) {
                if((*it)->getFileName() == fName) {
                    v.erase(it);
                    break;
                }
            }
        }

        else if(op == "move") {
            ss >> fName;
            std::string target; ss >> target;
            MyFile* f = helper(fName, mainFolder);
            MyFile* f2 = helper(target, mainFolder);
            if(!f2) {
                auto* newFile = new MyFile();
                mainFolder->getFiles().push_back(newFile);
            }
            for(auto it = mainFolder->getFiles().begin(); it != mainFolder->getFiles().end(); ++it) {
                if((*it)->getFileName() == f->getFileName()) {
                    mainFolder->getFiles().erase(it);
                }
            }
            f->move(*f2);
        }

        else if(op == "cat") {
            ss >> fName;
            MyFile* f = helper(fName, mainFolder);
            if(!f) {
                std::cout << "ERROR: no such filename" << std::endl;
                continue;
            }
            f->cat();
        }

        else if(op == "wc") {
            ss >> fName;
            MyFile* f = helper(fName, mainFolder);
            if(!f) {
                std::cout << "ERROR: no such filename" << std::endl;
            }
            f->wc();
        }

        else if(op == "ln") {
            ss >> fName; std::string link; ss >> link;
            MyFile* f1 = helper(fName, mainFolder);
            if(!f1) {
                std::cout << "File " << fName << " not found!" << std::endl;
                continue;
            }
            MyFile* f2 = helper(link, mainFolder);
            if(!f2) {
                std::cout << "File " << link << " not found!" << std::endl;
                continue;
            }
            f1->ln(*f2);
        }

        else if(op == "mkdir") {
            std::string folderName;
            ss >> folderName;
            mainFolder->mkdir(folderName, mainFolder->getPointer());
        }

        else if(op == "chdir") {
            std::string folderName;
            ss >> folderName;
            bool flag = mainFolder->chdir(folderName);
            if(flag) {
                mainFolder->setPointer(folderName);
            }
        }

        else if(op == "rmdir") {
            std::string folderName;
            ss >> folderName;
            mainFolder->rmdir(folderName);
            if(mainFolder->getPointer() == folderName) {
                mainFolder->setPointer("V/");
            }
        }

        else if(op == "ls") {
            std::string folderName;
            ss >> folderName;
            mainFolder->ls(folderName);
        }

        else if(op == "lproot") {
            mainFolder->lproot();
        }

        else if(op == "pwd") {
            mainFolder->pwd();
        }

        else if(op == "exit") {
            exit(0);
        }

        else {
            std::cout << op << ": command not found" << std::endl;
        }
    }

}

MyFile *MyTerminal::helper(const std::string &fName, MyFolder *folder) {
    for(MyFile* f : folder->getFiles()) {
        if(fName == f->getFileName()) {
            return f;
        }
    }
    return nullptr;
}
