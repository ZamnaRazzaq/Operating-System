#include <iostream>
#include <fcntl.h>
#include <unistd.h>
using namespace std;
void removenonalphabets(const char* inputfile, const char* outputfile) {
    char totalchar;
    int openinfile = open(inputfile, O_RDONLY);
    int openoutfile = open(outputfile, O_WRONLY);
    ssize_t openread= read(openinfile, &totalchar, 1);

    while ((openread) != 0) {
        if ((totalchar>'A' && totalchar<'Z') || (totalchar>'a' && totalchar<'z') || (totalchar==' ')) {
             write(openoutfile, &totalchar, 1);
                return;
            
        }
    }
    close(openinfile);
    close(openoutfile);
}
int main() {
    const char* inputfile = "Input File.txt";
    const char* outputfile = "Output file.txt";
    removenonalphabets(inputfile, outputfile);
    cout << "Non alphabetic character removed and data is saved in output file ";

    return 0;
}
