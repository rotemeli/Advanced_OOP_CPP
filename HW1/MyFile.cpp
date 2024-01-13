#include "MyFile.h"

#include <utility>
#include "FileNotFound.h"
#include "InvalidIndex.h"


MyFile::FileValue::FileValue() : refCount(1) {
    filename = "";
    buff = "";
}

MyFile::MyFile() {
    file = new std::fstream();
    value = new FileValue();
    isTouched = false;
    belongs = "";
}

MyFile::MyFile(const MyFile &rhs) {
    file = new std::fstream();
    file = rhs.file;
    value = rhs.value;
    isTouched = rhs.isTouched;
    belongs = rhs.belongs;
    ++value->refCount;
}

MyFile &MyFile::operator=(const MyFile &rhs) {
    if(this == &rhs) {
        return *this;
    }
    if (value == rhs.value) {
        return *this;
    }
    if (--value->refCount == 0) {
        delete value;
        value = new FileValue();
    }
    delete file;
    file = new std::fstream();
    file = rhs.file;
    value = rhs.value;
    belongs = rhs.belongs;
    isTouched = rhs.isTouched;
    ++value->refCount;
    return *this;
}

MyFile::~MyFile() {
    if (--value->refCount == 0) {
        delete value;
        delete file;
        isTouched = false;
    }
}

const char& MyFile::operator[](int index) const {
    int k = (int) value->buff.length();
    if (index < 0 || index > k - 1) {
        throw InvalidIndex("Invalid index!\n");
    }
    return value->buff[index];
}

char &MyFile::operator[](int index) {
    int k = (int) value->buff.length();
    if(index == k) {
        std::string tmp = value->buff + ' ';
        value->buff = tmp;
        k++;
    }
    if (index < 0 || index > k - 1) {
        throw InvalidIndex("Invalid index!\n");
    }
    return value->buff[index];
}

void MyFile::touch(std::string fname) {
    value->filename = std::move(fname);
    isTouched = true;
    file->open(value->filename);
    if (!(file)) {
        file->open(value->filename, std::ios::in | std::ios::out | std::ios::trunc);
    }

    if(file) {
        std::stringstream ss;
        ss << file->rdbuf();
        value->buff = ss.str();
    }

    file->flush();
    file->close();
}

void MyFile::copy(MyFile &target) {
    if (this == &target) {
        return;
    }
    target.file = file;
    target.value->refCount = value->refCount;
    target.file = file;
    target.isTouched = isTouched;
}

void MyFile::move(MyFile &target) {
    if (this == &target) {
        return;
    }
    target.belongs = belongs;
    target.file = file;
    target.value->buff = value->buff;
    target.value->filename = value->filename;
    target.isTouched = isTouched;
    --value->refCount;
    delete this;
}

void MyFile::cat() {
    std::cout << value->buff << std::endl;
}

void MyFile::wc() {
    int lines = 0, words = 0, chars = 0;
    std::fstream tmp;
    tmp.open("myTemp", std::ios::in | std::ios::out | std::ios::trunc);
    tmp << value->buff;
    if (isTouched && tmp.is_open()) {
        std::string line;
        std::string word;
        tmp.seekg(0, std::ios::beg);
        while (std::getline(tmp, line)) {
            std::stringstream ss(line);
            while (ss >> word) {
                words++;
                chars += (int) word.length() + 1;
            }
            chars--;
            lines++;
        }
    }
    std::cout << lines << " " << words << " " << chars << " " << value->filename << std::endl;
    tmp.clear();
    tmp.flush();
    tmp.close();
}

void MyFile::ln(MyFile &f) {
    if (this == &f) {
        return;
    }
    f.file = file;
    f.value->buff = value->buff;
    f.isTouched = isTouched;
    ++value->refCount;
}

int MyFile::getRefCount() const {
    return value->refCount;
}

const std::string& MyFile::getFileName() const {
    return value->filename;
}

void MyFile::setBelongs(const std::string &belong) {
    MyFile::belongs = belong;
}

const std::string &MyFile::getBelongs() const {
    return belongs;
}
