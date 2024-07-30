#include"util.h"
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
