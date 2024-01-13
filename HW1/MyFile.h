#ifndef EX01_ADVCPP_MYFILE_H
#define EX01_ADVCPP_MYFILE_H

#include <iostream>
#include <fstream>
#include <utility>
#include <sstream>


class MyFile {
private:
    /*
     * Manager struct for reference counting
     */
    struct FileValue {
        std::string filename;

        int refCount;
        std::string buff;

        FileValue();
    };

    std::fstream *file;
    FileValue *value;
    bool isTouched;
    std::string belongs;

public:
    /*
     * Big three
     */
    MyFile();

    MyFile(const MyFile &rhs);

    MyFile &operator=(const MyFile &rhs);

    ~MyFile();

    // Methods
    const char& operator[](int index) const;                         // Read only access

    char &operator[](int index);                                     // Write access

    /**
     * open a file
     * @param filename
     */
    void touch(std::string fname);

    /**
     * Copies a source file to a target file
     * @param target
     */
    void copy(MyFile &target);

    /**
     * Moves a source file to a target file
     * @param target
     */
    void move(MyFile &target);

    /**
     * Prints the contents of the file
     */
    void cat();

    /**
     * Prints data about the contents of the file
     */
    void wc();

    /**
     * Links an existing file to a given file
     * @param f
     */
    void ln(MyFile &f);

    /**
     * Returns the current reference counting
     * @return
     */
    int getRefCount() const;

    /*
     * Setters and getters
     */
    const std::string& getFileName() const;

    void setBelongs(const std::string &belong);

    const std::string &getBelongs() const;

};


#endif //EX01_ADVCPP_MYFILE_H
