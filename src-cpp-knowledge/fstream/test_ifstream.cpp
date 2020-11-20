#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

#define BUFSIZE 16;

using namespace std;

int main () {
    string filename = "test.txt";
    string filename_wrong = "test1.txt";
    ifstream fin(filename_wrong, std::ifstream::binary);
    if (!fin.good()) {
        printf("An Error happens when opening the file: %s\n", filename_wrong.c_str());
        if (fin.fail()) printf("fail\n");
        if (fin.eof()) printf("eof\n");
        if (fin.bad()) printf("bad\n");
        if (fin.rdstate()) printf("rdstate\n");
        return 0;
    }
    char chunk[BUFSIZ+1];

    while (!fin.eof()) {
        fin.read(chunk, BUFSIZ);
        std::streamsize chunksize = fin.gcount();
        chunk[chunksize] = 0;
        printf("%s", chunk);
    }

    return 0;
}