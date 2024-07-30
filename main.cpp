#include<iostream>
#include"util.h"
#include"util.cpp"
using namespace std;

int main() {
    const char* inputfile = "Input File.txt";
    const char* outputfile = "Output file.txt";
    removenonalphabets(inputfile, outputfile);
    cout << "Non alphabetic character removed and data is saved in output file ";

    return 0;
}
